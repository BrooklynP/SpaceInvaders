#include "MainMenuSelector.h"
#include "UGFW.h"
#include "UG_Defines.h"
#include "GameData.h"
#include "GameManager.h"

MainMenuSelector::MainMenuSelector() 
{
	//Starts the selector on play, so that the player can get into the game ASAP
	fCenterY = OPTION_PLAY;
}
float MainMenuSelector::GetX() const 
{ 
	return fCenterX;
}
float MainMenuSelector::GetY() const 
{ 
	return fCenterY;
}
void MainMenuSelector::SetY(float a_fCenterY)
{ 
	fCenterY = a_fCenterY; 
}
int MainMenuSelector::GetSprite() const 
{ 
	return iSprite;
}
void MainMenuSelector::SetSprite(std::string a_sSprite) 
{ 
	iSprite = UG::CreateSprite(a_sSprite.c_str(), 55.0f, 40.0f, true); 
}
void MainMenuSelector::MoveUp() 
{
	//If at the top, wraps around to the bottom.
	if (fCenterY >= OPTION_PLAY)
	{
		fCenterY = OPTION_EXIT;
	}
	else 
	{
		fCenterY += 50.0f;
	}
	UG::SetSpritePosition(iSprite, fCenterX, fCenterY);
}
void MainMenuSelector::MoveDown()
{
	//if at the bottom, wraps around to the top.
	if (fCenterY <= OPTION_EXIT)
	{
		fCenterY = OPTION_PLAY;
	}
	else 
	{
		fCenterY -= 50.0f;
	}
	UG::SetSpritePosition(iSprite, fCenterX, fCenterY);
}
void MainMenuSelector::Select() const
{
	if (mainmenuselector.GetY() == OPTION_PLAY)
	{
		g_iGameState = PLAY;
		gamemanager.CreateGame();
	}
	else if (mainmenuselector.GetY() == OPTION_HIGHSCORES)
	{
		g_iGameState = HIGH_SCORES;
	}
	else if (mainmenuselector.GetY() == OPTION_HOWTOPLAY)
	{
		HowToPlayPage = 1;
		g_iGameState = HOW_TO_PLAY;
	}
	else if (mainmenuselector.GetY() == OPTION_EXIT)
	{
		UG::Close();
	}

}