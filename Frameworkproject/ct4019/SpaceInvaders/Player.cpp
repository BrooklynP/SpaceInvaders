#include "Player.h"
#include "Bullet.h"
#include "UGFW.h"
#include "UG_Defines.h"
#include "GameData.h"

//Sprite Positioning
float Player::GetX()const 
{
	return fCenterX;
}
void Player::SetX(float a_fCenterX)
{
	fCenterX = a_fCenterX; 
}
float Player::GetY()const 
{ 
	return fCenterY;
}

//Collision Box
float Player::GetLeftX()const
{
	return fLeftX; 
}												
float Player::GetRightX()const
{ 
	return fRightX; 
}
float Player::GetTopY()const 
{ 
	return fTopY;
}
void Player::SetLeftX(float a_fLeftX) 
{ 
	fLeftX = a_fLeftX; 
}
void Player::SetRightX(float a_fRightx)
{ 
	fRightX = a_fRightx; 
}

int Player::GetLives()const 
{ 
	return iLives;
}
void Player::SetLives(int a_iLives) 
{
	iLives = a_iLives; 
}
void Player::LoseLife() 
{ 
	iLives -= 1; 
}

int Player::GetShotsFired()const 
{ 
	return iShotsFired; 
}
void Player::SetShotsFired(int a_iShotsFired) 
{ 
	iShotsFired = a_iShotsFired;
}

int Player::GetScore()const
{ 
	return iScore;
}
void Player::SetScore(int  a_iscore) 
{ 
	iScore = a_iscore;
}

float Player::GetSpeed()const 
{ 
	return fMoveSpeed;
}

void Player::Shoot() 
{
	if (!playerbullet.GetState())
	{
		playerbullet.SetX(fCenterX);
		playerbullet.SetY(fCenterY);
		playerbullet.SetState(true);
		iShotsFired += 1; //when shotsfired = 23 and then a mutlitple of 15, the mystery ships shot score 300
	}
}

//Sprite Data
float Player::GetSpriteWidth() const { return c_fSpriteWidth; }
float Player::GetSpriteHeight() const{ return c_fSpriteHeight; }
int Player::GetSprite()const { return iSprite; }
void Player::SetSprite(std::string a_sSprite) { iSprite = UG::CreateSprite(a_sSprite.c_str(), c_fSpriteWidth, c_fSpriteHeight, true); }

void Player::MoveLeft() 
{
	if (fCenterX >= gc_fLeftYBound) 
	{
		fCenterX -= fMoveSpeed;
		fLeftX -= fMoveSpeed;
		fRightX -= fMoveSpeed;
		UG::SetSpritePosition(iSprite, fCenterX, fCenterY);
	}
}
void Player::MoveRight() 
{
	if (fCenterX <= gc_fRightYBound) 
	{
		fCenterX += fMoveSpeed;
		fLeftX += fMoveSpeed;
		fRightX += fMoveSpeed;
		UG::SetSpritePosition(iSprite, fCenterX, fCenterY);
	}
}