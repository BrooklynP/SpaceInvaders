#include <string>
#include "Player.h"
#include "HighScoreManager.h"
#include "DrawManager.h"
#include "GameData.h"
#include "GameManager.h"
#include "ScreenData.h"
#include "MainMenuSelector.h"
#include "EnemyAlien.h"
#include "Shield.h"
#include "Bullet.h"
#include "MysteryShip.h"
#include "UGFW.h"
#include "UG_Defines.h"

int MainMenuSprite;
int HowToPlayPage;

int HowToPage1;
int HowToPage2;
int HowToPage3;

void DrawManager::UI() const
{
	//Prints the players current score in the top left of the screen. It first retrieves the current score from the player and stores it in a variable. Appends that to the word "score:"
	// and then converts it to the correct form to be drawn by the UG framework.
	std::string sCurrentScoreText = "Score: ";
	const std::string sCurrentPoints = (std::to_string(player.GetScore()));
	sCurrentScoreText += sCurrentPoints;
	const char* cScoreText = sCurrentScoreText.c_str();
	UG::DrawString(cScoreText, 30, 850, 1, UG::SColour(255, 255, 255, 255));

	//Prints how many lives have the player currently has in the bottom left of the screen.
	std::string sCurrentLives = (std::to_string(player.GetLives()));
	const char* cCurrentLives = sCurrentLives.c_str();
	UG::DrawString(cCurrentLives, 50, 40, 1, UG::SColour(255, 255, 255, 255));

	//Prints the high score in the top right of the screen.
	HighScore.DrawHighestScore();

	//Draws a line across the screen to repersent the earth's floor that the aliens are trying to reach.
	UG::DrawLine(0, gc_fFloorHeight, (float)g_iScreenWidth, gc_fFloorHeight, 1.0f, 1, UG::SColour(50, 205, 50, 255));

	UG::DrawString("CREDIT 00", 700, 40, 1, UG::SColour(255, 255, 255, 255));

	//Draws the highest point player bullets can travel, and also the Y level the mystery ship travels along.
	if (Settings.ShouldDrawYBoundary()) 
	{
		UG::DrawLine(0.0f, 800.0f, (float)g_iScreenWidth, 800.0f, 1, 1, UG::SColour(255, 255, 255, 255));
	}
}
void DrawManager::MainMenuScreen() const 
{
	//Draws a logo in at the top of the screen.
	UG::SetSpritePosition(MainMenuSprite, g_iScreenWidth / 2.0f, g_iScreenHeight - 200.0f);
	UG::DrawSprite(MainMenuSprite);

	UG::DrawSprite(mainmenuselector.GetSprite());

	UG::DrawString("Play", (g_iScreenWidth / 2) - 55, 500, 1, UG::SColour(255, 255, 255, 255));
	UG::DrawString("HighScores", (g_iScreenWidth / 2) - 140, 450, 1, UG::SColour(255, 255, 255, 255));
	UG::DrawString("How To Play", (g_iScreenWidth / 2) - 165, 400, 1, UG::SColour(255, 255, 255, 255));
	UG::DrawString("Exit", (g_iScreenWidth / 2) - 57, 350, 1, UG::SColour(255, 255, 255, 255));
}
void DrawManager::SplashScreen() const 
{
	//Draws a logo in at the top of the screen.
	UG::SetSpritePosition(MainMenuSprite, g_iScreenWidth / 2.0f, g_iScreenHeight / 2.0f);
	UG::DrawSprite(MainMenuSprite);

	UG::DrawString("By Brooklyn Pedley", (g_iScreenWidth / 2) - 280, 250, 1, UG::SColour(255, 255, 255, 255));
}
void DrawManager::HighScoreScreen() const
{
	//Prints Logo on screen
	UG::SetSpritePosition(MainMenuSprite, g_iScreenWidth / 2.0f, g_iScreenHeight - 200.0f);
	UG::DrawSprite(MainMenuSprite);

	//Printed some numbering to show which is the 1st highscore or 10th etc.
	for (int i = 0; i < 10; i++)
	{
		std::string sScoreIndex = std::to_string(10 - i);
		const char* cScoreIndex = sScoreIndex.c_str();
		UG::DrawString(cScoreIndex, g_iScreenWidth / 2 - 150, i * 50 + 50, 1, UG::SColour(255, 255, 255, 255));
	}

	//prints the highscores onto the screen.
	HighScore.Draw();
}
void DrawManager::Aliens() const 
{
	//Draws every enemy alien that is alive
	for (int row = 0; row < gc_iWaveDepth; row++) 
	{
		for (int column = 0; column < gc_iWaveWidth; column++)
		{
			if (!g_apEnemyAlienArray[row][column]->GetState()) 
			{
				UG::DrawSprite(g_apEnemyAlienArray[row][column]->GetSprite());
			}
		}
	}

	if (mysteryship.GetState()) 
	{
		UG::DrawSprite(mysteryship.GetSprite());
	}
}
void DrawManager::GameScreen() const 
{
	UG::DrawSprite(player.GetSprite());
	Draw.Aliens();
	Draw.UI();

	//Draws collision boxes around the game objects.
	if (Settings.ShouldDrawHitBoxes()) 
	{
		AlienColliders();
		ShieldColliders();
	}

	if (playerbullet.GetState()) 
	{
		UG::DrawSprite(playerbullet.GetSprite());
	}
	if (enemybullet.GetState()) 
	{
		UG::DrawSprite(enemybullet.GetSprite());
	}

	//Draws the pixels that are active for the 3 shields.
	for (int row = 0; row < 16; row++) 
	{
		for (int column = 0; column < 24; column++) 
		{
			if (g_apShieldOnePixels[row][column]->GetState()) 
			{
				UG::DrawSprite(g_apShieldOnePixels[row][column]->GetSprite());
			}
			if (g_apShieldTwoPixels[row][column]->GetState()) 
			{
				UG::DrawSprite(g_apShieldTwoPixels[row][column]->GetSprite());
			}
			if (g_apShieldThreePixels[row][column]->GetState()) 
			{
				UG::DrawSprite(g_apShieldThreePixels[row][column]->GetSprite());
			}
		}
	}
}
void DrawManager::HowToPlayScreen() const {
	switch (HowToPlayPage) {
	case 1:
	{
		UG::DrawSprite(HowToPage1);
		break;
	}
	case 2:
	{
		UG::DrawSprite(HowToPage2);
		break;
	}
	case 3:
	{
		UG::DrawSprite(HowToPage3);
		break;
	}
	default:
	{
		break;
	}
	};
}

//Draws collision boxes around game objects
void DrawManager::AlienColliders() const
{
	for (int row = 0; row < gc_iWaveDepth; row++)
	{
		for (int column = 0; column < gc_iWaveWidth; column++)
		{
			if (!g_apEnemyAlienArray[row][column]->GetState()) 
			{
				UG::DrawLine(g_apEnemyAlienArray[row][column]->GetLeftX(), g_apEnemyAlienArray[row][column]->GetTopY(), g_apEnemyAlienArray[row][column]->GetRightX(), g_apEnemyAlienArray[row][column]->GetTopY());
				UG::DrawLine(g_apEnemyAlienArray[row][column]->GetLeftX(), g_apEnemyAlienArray[row][column]->GetBottomY(), g_apEnemyAlienArray[row][column]->GetRightX(), g_apEnemyAlienArray[row][column]->GetBottomY());
				UG::DrawLine(g_apEnemyAlienArray[row][column]->GetLeftX(), g_apEnemyAlienArray[row][column]->GetBottomY(), g_apEnemyAlienArray[row][column]->GetLeftX(), g_apEnemyAlienArray[row][column]->GetTopY());
				UG::DrawLine(g_apEnemyAlienArray[row][column]->GetRightX(), g_apEnemyAlienArray[row][column]->GetBottomY(), g_apEnemyAlienArray[row][column]->GetRightX(), g_apEnemyAlienArray[row][column]->GetTopY());
			}
		}
	}
}
void DrawManager::ShieldColliders() const 
{
	UG::DrawLine(ShieldOne.GetLeftX(), ShieldOne.GetTopY(), ShieldOne.GetRightX(), ShieldOne.GetTopY());
	UG::DrawLine(ShieldOne.GetLeftX(), ShieldOne.GetBottomY(), ShieldOne.GetRightX(), ShieldOne.GetBottomY());
	UG::DrawLine(ShieldOne.GetLeftX(), ShieldOne.GetBottomY(), ShieldOne.GetLeftX(), ShieldOne.GetTopY());
	UG::DrawLine(ShieldOne.GetRightX(), ShieldOne.GetBottomY(), ShieldOne.GetRightX(), ShieldOne.GetTopY());

	UG::DrawLine(ShieldTwo.GetLeftX(), ShieldTwo.GetTopY(), ShieldTwo.GetRightX(), ShieldTwo.GetTopY());
	UG::DrawLine(ShieldTwo.GetLeftX(), ShieldTwo.GetBottomY(), ShieldTwo.GetRightX(), ShieldTwo.GetBottomY());
	UG::DrawLine(ShieldTwo.GetLeftX(), ShieldTwo.GetBottomY(), ShieldTwo.GetLeftX(), ShieldTwo.GetTopY());
	UG::DrawLine(ShieldTwo.GetRightX(), ShieldTwo.GetBottomY(), ShieldTwo.GetRightX(), ShieldTwo.GetTopY());

	UG::DrawLine(ShieldThree.GetLeftX(), ShieldThree.GetTopY(), ShieldThree.GetRightX(), ShieldThree.GetTopY());
	UG::DrawLine(ShieldThree.GetLeftX(), ShieldThree.GetBottomY(), ShieldThree.GetRightX(), ShieldThree.GetBottomY());
	UG::DrawLine(ShieldThree.GetLeftX(), ShieldThree.GetBottomY(), ShieldThree.GetLeftX(), ShieldThree.GetTopY());
	UG::DrawLine(ShieldThree.GetRightX(), ShieldThree.GetBottomY(), ShieldThree.GetRightX(), ShieldThree.GetTopY());
}