#include "MysteryShip.h"
#include "ScreenData.h"
#include "UGFW.h"
#include "UG_Defines.h"


MysteryShip::MysteryShip()
{
	fCenterX = g_iScreenWidth + 100.0f;
	fWaitTimer = 0;
	bState = true;
	fLeftX = fCenterX - SpriteWidth / 2;
	fRightX = fCenterX + SpriteWidth / 2;
}

//Whether it is alive or not
bool MysteryShip::GetState() const 
{ 
	return bState;
}
void MysteryShip::SetState(bool a_bState) 
{ 
	bState = a_bState; 
}

//Collision Box
float MysteryShip::GetLeftX()const 
{ 
	return fLeftX;
}											
float MysteryShip::GetRightX()const 
{ 
	return fRightX; 
}
float MysteryShip::GetBottomY()const 
{ 
	return fBottomY; 
}
void MysteryShip::SetLeftX(float a_fLeftX)
{
	fLeftX = a_fLeftX;
}
void MysteryShip::SetRightX(float a_fRightx) 
{ 
	fRightX = a_fRightx; 
}

//Sprite Positioning
float MysteryShip::GetCenterX()const
{ 
	return fCenterX;
}													
float MysteryShip::GetCenterY()const
{ 
	return fCenterY;
}
void MysteryShip::SetCenterX(float a_fX)
{ 
	fCenterX = a_fX; 
}

//Time until it will move onto the screen again
float MysteryShip::GetTimer()const 
{ 
	return fWaitTimer; 
}
void MysteryShip::SetTime(float a_fTime) 
{ 
	fWaitTimer = a_fTime; 
}

//Direction travelling in
void MysteryShip::SetDirection(std::string a_sNewDirection) 
{
	m_sDirection = a_sNewDirection; 
}
std::string MysteryShip::GetDirection()const
{
	return m_sDirection;
}
float MysteryShip::GetSpeed()const
{ 
	return MoveSpeed;
}

//Sprite Data
int MysteryShip::GetSprite()const 
{ 
	return iSprite; 
}
void MysteryShip::SetSprite(std::string a_sSprite, float a_fX, float a_fY) 
{
	iSprite = UG::CreateSprite(a_sSprite.c_str(), a_fX, a_fY, true); 
}

void MysteryShip::Update(float a_g_fDeltaSum) 
{
	if (bState) 
	{
		if (m_sDirection == "LEFT") 
		{
			fCenterX -= MoveSpeed;
			fRightX -= MoveSpeed;
			fLeftX -= MoveSpeed;
			UG::SetSpritePosition(iSprite, fCenterX, fCenterY);
			//changes direction when it hits the edge.
			if (fCenterX <= -SpriteWidth) //Add sprite width to ensure entire sprite is off screen.
			{
				m_sDirection = "RIGHT";
			}
		}
		else if (m_sDirection == "RIGHT") 
		{
			if (fWaitTimer == 0.0f) {
				fCenterX += MoveSpeed;
				fRightX += MoveSpeed;
				fLeftX += MoveSpeed;
				UG::SetSpritePosition(iSprite, fCenterX, fCenterY);
			}
			//if it is on the right side of the screen, it will wait 25s before coming backk again. (if it goes over the left side, it will come back instantly as this is how the strafe run worked in the original)
			if (fCenterX >= g_iScreenWidth + SpriteWidth) //Add sprite width to ensure entire sprite is off screen.
			{
				fWaitTimer += a_g_fDeltaSum;
				if (fWaitTimer >= 25.0f) {//Appears every 25s
					m_sDirection = "LEFT";
					fWaitTimer = 0.0f;
				}

			}
		}
	}
	else if (!bState) 
	{
		//If it dies, it is respawned at the right side of the screen and must wait 25s
		bState = true;
		UG::SetSpritePosition(iSprite, 900.0f, 810.0f);
		m_sDirection = "RIGHT";
		fCenterX = g_iScreenWidth + SpriteWidth;
		fWaitTimer = 0.0f;
		fLeftX = fCenterX - (SpriteWidth / 2.0f);
		fRightX = fCenterX + (SpriteWidth / 2.0f);
	}
}