#include <string>
#pragma once
//Class to repersent both player and enemy bullets
class Bullet 
{
public:
	bool GetState() const;
	void SetState(bool a_Bstate);

	float GetX() const;
	float GetY() const;
	void SetX(float a_fX);
	void SetY(float a_fY);

	int GetSprite() const;
	void SetSprite(std::string a_Ssprite, float a_fX, float a_fY);
protected:
	float m_X;
	float m_Y;
	bool m_bState;
	int m_iSprite;
};

//Each bullet required a seperate update function as they travel in different directions and handle collisions differently, and so inheritance was used.
class PlayerBullet : public Bullet 
{
public:
	void Update();
};
class EnemyBullet : public Bullet 
{
public:
	void Update();
};

extern PlayerBullet playerbullet;
extern EnemyBullet enemybullet;