#include <string>
#include "GameData.h"
#pragma once
//Class to repersent each enemy alien on the game screen.
class EnemyAlien 
{
public:
	EnemyAlien(int iPointsWorth, float StartingX, float StartingY, std::string SpriteFilePath, float SpriteWidth);
	void Die();
	bool GetState() const;

	void SetIsDying(bool isDying);
	bool GetIsDying() const;

	static void SetDirection(std::string sNewDirection);
	static std::string GetDirection();

	float GetLeftX() const;
	float GetRightX()const;
	float GetTopY() const;
	float GetBottomY() const;
	void SetLeftX(float LeftX);
	void SetRightX(float Rightx);
	void SetTopY(float TopY);
	void SetBottomY(float BottomY);

	float GetX() const;
	float GetY() const;
	void SetX(float x);
	void SetY(float y);

	int GetSprite() const;
	void SetSprite(std::string sprite, float x, float y);

	int GetAnimationState() const;
	void SetAnimationState(int NewAnimationState);

	bool IsAtFloor() const;

	static void ChooseShooter();

	void MoveLeft();
	void MoveRight();
	void MoveDown();

	int GetPointsWorth() const;
private:
	void Shoot() const;
	const float iSpriteHeight = 40.0f;
	int m_iPointsWorth;	//points scored for the player when the alien is destroyed
	bool bIsDead;
	bool iIsDying;
	static std::string s_sWaveDirection;	//Direction for entire wave of aliens
	int iSprite;

	float fLeftX;					//X and Y coordinates for the collider box
	float fRightX;
	float fTopY;
	float fBottomY;

	float fCenterX;					//X and Y coordinates for the center of the alien used for positioning calculations.
	float fCenterY;

	int AnimationState;				//1 or 2 (which sprite to display)
};
extern EnemyAlien* g_apEnemyAlienArray[gc_iWaveDepth][gc_iWaveWidth];
