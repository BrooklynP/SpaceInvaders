#include<string>

#ifndef __PLAYER_CLASS__
#define __PLAYER_CLASS__

//Class to represent the ship the user controls while playing.
class Player
{
public:
	//Sprite Positioning
	float GetX()const;					
	void SetX(float a_fCenterX);
	float GetY()const;

	//Collision Box
	float GetLeftX()const;
	float GetRightX()const;
	float GetTopY()const;
	void SetLeftX(float a_fLeftX);
	void SetRightX(float a_fRightx);

	int GetLives()const;
	void SetLives(int a_iLives);
	void LoseLife();

	//Used to decide what the mystery ship is worth (In the original game, 23 and multiples of 15 shots fired would mean the mystery ship was worth 300)
	int GetShotsFired()const;
	void SetShotsFired(int a_iShotsFired);

	int GetScore()const;
	void SetScore(int  a_iscore);

	//Movement Speed
	float GetSpeed()const;

	void MoveLeft();
	void MoveRight();

	void Shoot();

	//Sprite Data
	float GetSpriteWidth()const;
	float GetSpriteHeight()const;
	int GetSprite()const;
	void SetSprite(std::string a_sSprite);
private:
	const float fTopY = 165;
	float fLeftX;
	float fRightX;

	float fCenterX;
	const float fCenterY = 150.0f;

	int iShotsFired;
	int iScore;
	int iLives;
	const float fMoveSpeed = 7.0f;

	int iSprite;
	const float c_fSpriteWidth = 65.0f;
	const float c_fSpriteHeight = 40.0f;
};
extern Player player;
#endif