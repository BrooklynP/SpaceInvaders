#include "EnemyAlien.h"
#include "UGFW.h"
#include "UG_Defines.h"
#include "Bullet.h"
#include "GameManager.h"
#include <random>

EnemyAlien::EnemyAlien(int iPointsWorth, float StartingX, float StartingY, std::string SpriteFilePath, float SpriteWidth)
{ //Constructor
m_iPointsWorth = iPointsWorth;

fCenterX = StartingX;
fCenterY = StartingY;

fLeftX = StartingX - (SpriteWidth / 2);			//Works out the edges of the sprite
fRightX = StartingX + (SpriteWidth / 2);
fTopY = StartingY + (iSpriteHeight / 2);
fBottomY = StartingY - (iSpriteHeight / 2);

iSprite = UG::CreateSprite(SpriteFilePath.c_str(), SpriteWidth, iSpriteHeight, true);
UG::SetSpritePosition(iSprite, fCenterX, fCenterY);

//States a starting sprite to display for the alien
AnimationState = 1;

bIsDead = false;
iIsDying = false;
}
void EnemyAlien::Die() 
{ 
	bIsDead = true;
}													
bool EnemyAlien::GetState()const 
{ 
	return bIsDead;
}
void EnemyAlien::SetIsDying(bool isDying) 
{ 
	iIsDying = isDying; 
}
bool EnemyAlien::GetIsDying()const 
{ 
	return iIsDying;
}

//Direction all aliens travel in "LEFT" or "RIGHT"
void EnemyAlien::SetDirection(std::string sNewDirection) 
{ 
	s_sWaveDirection = sNewDirection; 
}			
std::string EnemyAlien::GetDirection() 
{
	return s_sWaveDirection; 
}

//Collision Box
float EnemyAlien::GetLeftX()const
{ 
	return fLeftX; 
}
float EnemyAlien::GetRightX()const 
{ 
	return fRightX;
}
float EnemyAlien::GetTopY()const 
{ 
	return fTopY; 
}
float EnemyAlien::GetBottomY()const 
{ 
	return fBottomY; 
}
void EnemyAlien::SetLeftX(float LeftX) 
{ 
	fLeftX = LeftX; 
}
void EnemyAlien::SetRightX(float Rightx) 
{ 
	fRightX = Rightx; 
}
void EnemyAlien::SetTopY(float TopY) 
{ 
	fTopY = TopY;
}
void EnemyAlien::SetBottomY(float BottomY)
{ 
	fBottomY = BottomY; 
}

//Sprite Data
float EnemyAlien::GetX()const 
{ 
	return fCenterX; 
}
float EnemyAlien::GetY()const 
{ 
	return fCenterY;
}
void EnemyAlien::SetX(float x) 
{ 
	fCenterX = x; 
}
void EnemyAlien::SetY(float y) 
{ 
	fCenterY = y; 
}
int EnemyAlien::GetSprite()const
{ 
	return iSprite; 
}
void EnemyAlien::SetSprite(std::string sprite, float x, float y) 
{ 
	iSprite = UG::CreateSprite(sprite.c_str(), x, y, true); 
}
int EnemyAlien::GetAnimationState()const 
{ 
	return AnimationState;
}
void EnemyAlien::SetAnimationState(int NewAnimationState)
{
	AnimationState = NewAnimationState; 
}

int EnemyAlien::GetPointsWorth() const
{ 
	return m_iPointsWorth;
}	
bool EnemyAlien::IsAtFloor() const
{
	if (fCenterY <= 150 && !bIsDead) 
	{
		return true;
	}
	else 
	{
		return false;
	}
}
void EnemyAlien::MoveLeft() 
{
	fCenterX -= 10.0f;
	fLeftX -= 10.0f;
	fRightX -= 10.0f;
	UG::SetSpritePosition(iSprite, fCenterX, fCenterY);
}
void EnemyAlien::MoveRight() 
{
	fCenterX += 10.0f;
	fLeftX += 10.0f;
	fRightX += 10.0f;
	UG::SetSpritePosition(iSprite, fCenterX, fCenterY);
}
void EnemyAlien::MoveDown() 
{
	if (iIsDying) 
	{
		EnemyAlien::Die();				//Stops the death sprite being able to move in the Y. Makes the game look cleaner.
	}
	fCenterY -= 50;
	fTopY -= 50;
	fBottomY -= 50;
}

void EnemyAlien::ChooseShooter()
{
	std::random_device rd;		//initialise seed
	std::mt19937 rng(rd());		//random number engine
	std::uniform_int_distribution<int> uni(0, gc_iWaveWidth - 1); //values are inclusive

	auto shooter_column = uni(rng);
	//Starts on the bottom row
	int shooter_row = 0;
	bool shooter_found = false;

	//Checks if randomly chosen shotoer is alive, if it is not, checks above aliens until it reaches top. 
	//If no aliens in column, it will check the next column(Also Checks to make sure all aliens aren't dead if none are found in column as this can cause null ptr.
	while (!shooter_found) 
	{
		if (!g_apEnemyAlienArray[shooter_row][shooter_column]->GetState()) 
		{
			shooter_found = true;
		}
		else if (shooter_row == gc_iWaveDepth - 1) 
		{
			shooter_column = uni(rng);
			shooter_row = 0;
			gamemanager.CheckAllAliensDead();
		}
		else 
		{
			shooter_row += 1;
		}
	}

	//Spawns bullet at shooters position
	g_apEnemyAlienArray[shooter_row][shooter_column]->Shoot();
}
void EnemyAlien::Shoot() const 
{
	//Spawns a bullet at the aliens position
	enemybullet.SetX(fCenterX);
	enemybullet.SetY(fCenterY);
	enemybullet.SetState(true);
}