#include <string>
#pragma once
//Class repersenting each indiviual piece/pixel of a shield so that destruction of the shield can be on a pixel level.
class ShieldPiece {
public:
	ShieldPiece(float a_fStartingX, float a_fStartingY);

	//Sprite Positioning
	float GetX()const;
	void SetX(float a_fCenterX);
	float GetY()const;
	void SetY(float a_fCenterY);

	//Collision Box
	float GetLeftX()const;
	float GetRightX()const;
	float GetTopY()const;
	float GetBottomY()const;
	void SetLeftX(float a_fLeftX);
	void SetRightX(float a_fRightx);
	void SetTopY(float a_fTopY);
	void SetBottomY(float a_fBottomY);

	bool GetState()const;
	void SetState(bool a_bState);

	int GetSprite()const;
	void SetSprite(std::string a_sSprite);
private:
	int iSprite;
	bool bState;
	float fTopY;
	float fBottomY;
	float fLeftX;
	float fRightX;

	float fCenterX;
	float fCenterY;

	const float c_fSpriteWidth = 5.0f;
	const float c_fSpriteHeight = 5.0f;
};

//Used to create a collider box around the entire shield, so that collision detectors only iterate through every shield pixel when it is inside the actual shield.
//Speeding up the game when bullets arent in the shield
class Shield {
public:
	Shield(float a_fLeftX, float a_fRightX, float a_fTopY, float a_fBottomY);
	float GetLeftX()const;												
	float GetRightX()const;
	float GetTopY()const;
	float GetBottomY()const;

private:
	float fLeftX;
	float fRightX;
	float fTopY;
	float fBottomY;
};

//Array of shield pieces for each of the 3 shields. 
extern ShieldPiece* g_apShieldOnePixels[16][24];
extern ShieldPiece* g_apShieldTwoPixels[16][24];
extern ShieldPiece* g_apShieldThreePixels[16][24];

//This template states which parts of the shield should have shield pieces at start. (because of the way loops iterrate, this template is actually upside down)
const bool g_abShieldTemplate[16][24] =
{
	{ true, true, true, true, true,	false, false, false, false, false, false, false, false, false, false, false, false, false, false, true, true, true, true, true },
	{ true, true, true, true, true,	false, false, false, false, false, false, false, false, false, false, false, false, false, false, true, true, true, true, true },
	{ true, true, true, true, true,	true, false, false, false, false, false, false, false, false, false, false, false, false, true, true, true, true, true, true },
	{ true, true, true, true, true,	true, true, false, false, false, false, false, false, false, false, false, false, true, true, true, true, true, true, true },
	{ true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true },
	{ true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true },
	{ true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true },
	{ true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true },
	{ true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true },
	{ true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true },
	{ true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true },
	{ true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true },
	{ false, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, false },
	{ false, false, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, false, false },
	{ false, false, false, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, false, false, false },
	{ false, false, false ,false, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, false ,false ,false ,false }
};

extern Shield ShieldOne;
extern Shield ShieldTwo;
extern Shield ShieldThree;