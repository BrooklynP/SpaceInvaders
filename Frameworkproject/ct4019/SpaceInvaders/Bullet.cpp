#include "Bullet.h"
#include "GameData.h"
#include "GameManager.h"
#include "Shield.h"
#include "UGFW.h"
#include "UG_Defines.h"

bool Bullet::GetState() const 
{ 
	return m_bState; 
}
void Bullet::SetState(bool a_Bstate) 
{ 
	m_bState = a_Bstate; 
}
float Bullet::GetX() const
{ 
	return m_X;
}
float Bullet::GetY() const
{ 
	return m_Y; 
}
void Bullet::SetX(float a_fX) 
{ 
	m_X = a_fX; 
}
void Bullet::SetY(float a_fY)
{
	m_Y = a_fY; 
}
int Bullet::GetSprite() const
{ 
	return m_iSprite;
}
void Bullet::SetSprite(std::string a_Ssprite, float a_fX, float a_fY) 
{ 
	m_iSprite = UG::CreateSprite(a_Ssprite.c_str(), a_fX, a_fY, true); 
}

void EnemyBullet::Update() 
{
	//As long as the enemey bullet is active, it will move down 4.0 pixels every tick, It will also check if it has collided with anything.
	//If it gets to ground level without hitting anything, it is destroyed.
	if (GetState()) 
	{
		m_Y -= 4.0f;
		UG::SetSpritePosition(m_iSprite, m_X, m_Y);
		gamemanager.EnemyBulletCollisionDetection();
		//.GetY() returns the center of bullet, so by adding 7.5f, this detects if the bottom of the bullet has hit the ground level (Bit nicer visually).
		if (m_Y <= gc_fFloorHeight + 7.5f) 
		{
			SetState(false);
		}
	}
}

void PlayerBullet::Update() 
{
	if (GetState()) 
	{
		gamemanager.PlayerBulletCollisionDetection();
		//If bullet reaches top and thus has no chance of hitting eneemies, set its state to false so that it is deleted, and the player can shoot again.
		if (m_Y >= 800) 
		{
			SetState(false);
		}
		else 
		{
			//Every tick the bullet moves 5.0 pixels. This is intended to be slightly quicker than the enemy bullets.
			m_Y += 5.0f;
			UG::SetSpritePosition(m_iSprite, m_X, m_Y);
		}
	}
}