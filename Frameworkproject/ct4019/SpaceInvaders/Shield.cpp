#include "Shield.h"
#include "UGFW.h"
#include "UG_Defines.h"
#include <iostream>

Shield::Shield(float a_fLeftX, float a_fRightX, float a_fTopY, float a_fBottomY)
{
	fLeftX = a_fLeftX;
	fRightX = a_fRightX;
	fTopY = a_fTopY;
	fBottomY = a_fBottomY;
}

//collision box
float Shield::GetLeftX()const 
{ 
	return fLeftX; 
}													
float Shield::GetRightX()const 
{ 
	return fRightX;
}
float Shield::GetTopY()const 
{ 
	return fTopY; 
}
float Shield::GetBottomY()const
{ 
	return fBottomY; 
}

ShieldPiece::ShieldPiece(float a_fStartingX, float a_fStartingY) 
{
fCenterX = a_fStartingX;
fCenterY = a_fStartingY;

fLeftX = fCenterX - 2.5f;
fRightX = fCenterX + 2.5f;
fTopY = fCenterY + 2.5f;
fBottomY = fCenterY - 2.5f;
iSprite = UG::CreateSprite("./images/ShieldPiece.PNG", 5.0f, 5.0f, true);
}

//sprite data
float ShieldPiece::GetX()const 
{
	return fCenterX;
}				//Position Handling
void ShieldPiece::SetX(float a_fCenterX)
{
	fCenterX = a_fCenterX; 
}
float ShieldPiece::GetY()const 
{
	return fCenterY; 
}
void ShieldPiece::SetY(float a_fCenterY)
{
	fCenterY = a_fCenterY; 
}
int ShieldPiece::GetSprite()const 
{ 
	return iSprite;
}
void ShieldPiece::SetSprite(std::string a_sSprite)
{ 
	iSprite = UG::CreateSprite(a_sSprite.c_str(), c_fSpriteWidth, c_fSpriteHeight, true);
}

//collision box
float ShieldPiece::GetLeftX()const 
{ 
	return fLeftX; 
}				//Collision Box
float ShieldPiece::GetRightX()const 
{ 
	return fRightX;
}
float ShieldPiece::GetTopY()const 
{
	return fTopY;
}
float ShieldPiece::GetBottomY()const
{ 
	return fBottomY;
}
void ShieldPiece::SetLeftX(float a_fLeftX)
{
	fLeftX = a_fLeftX;
}
void ShieldPiece::SetRightX(float a_fRightx) 
{
	fRightX = a_fRightx; 
}
void ShieldPiece::SetTopY(float a_fTopY) 
{ 
	fTopY = a_fTopY;
}
void ShieldPiece::SetBottomY(float a_fBottomY)
{ 
	fBottomY = a_fBottomY; 
}

bool ShieldPiece::GetState()const 
{
	return bState;
}
void ShieldPiece::SetState(bool a_bState) 
{ 
	bState = a_bState; 
}
