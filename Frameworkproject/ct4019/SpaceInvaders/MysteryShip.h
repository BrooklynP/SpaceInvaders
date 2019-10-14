#include <string>

#pragma once
//Class to repersent the mystery ship that flies across the top of the screen every 25s
class MysteryShip
{
public:
	MysteryShip();

	//Whether it is alive or not
	bool GetState() const;
	void SetState(bool a_bState);

	//Collision Box
	float GetLeftX() const;
	float GetRightX() const;
	float GetBottomY() const;
	void SetLeftX(float a_fLeftX);
	void SetRightX(float a_fRightx);

	//Sprite Positioning
	float GetCenterX() const;
	float GetCenterY() const;
	void SetCenterX(float a_fX);

	//Time until it will move onto the screen again
	float GetTimer() const;
	void SetTime(float a_fTime);

	//Direction travelling in
	void SetDirection(std::string a_sNewDirection);
	std::string GetDirection() const;

	//Movement speed
	float GetSpeed() const;

	//Sprite Data
	int GetSprite() const;
	void SetSprite(std::string a_sSprite, float a_fX, float a_fY);

	//Handles the logic for the ships movement and state.
	void Update(float a_g_fDeltaSum);
private:
	float fCenterX;
	const float fCenterY = 810.0f;

	float fRightX;
	float fLeftX;
	const float fBottomY = 792.5f;

	float fWaitTimer;
	bool bState;

	std::string m_sDirection;
	const float MoveSpeed = 2.0f;

	int iSprite;
	const float SpriteWidth = 80.0f;
	const float SpriteHeight = 35.0f;
};
extern MysteryShip mysteryship; 