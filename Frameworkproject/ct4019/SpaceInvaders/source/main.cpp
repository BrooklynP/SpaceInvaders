//\===========================================================================================================================================
//\ Filename: main.cpp
//\ Author  : Brooklyn Pedley
//\ Date    : 4/12/17
//\ Brief   : Space Invaders
//\===========================================================================================================================================
#pragma region Includes
#include <string>
#include <iostream>
#include <vector>
#include <random>
#include <cstdlib>
#include <fstream>
#include <Windows.h>
#pragma comment(lib, "winmm.lib")

#include "UGFW.h"
#include "UG_Defines.h"
#include "HighScoreManager.h"
#include "Player.h"
#include "Shield.h"
#include "EnemyAlien.h"
#include "DrawManager.h"
#include "Bullet.h"
#include "MainMenuSelector.h"
#include "ScreenData.h"
#include "GameData.h"
#include "GameManager.h"
#include "MysteryShip.h"
#pragma endregion

#pragma region Global Variables
int g_iScreenHeight = 900;
int g_iScreenWidth = 1024;

float g_fDeltaSum = 0.0f;
float g_fGameSpeed = 0.80f;

int g_iEnemyAliensAlive = 0;
int g_iGameState;
std::string EnemyAlien::s_sWaveDirection = "RIGHT";
#pragma endregion

#pragma region Classes Used
MainMenuSelector mainmenuselector;
MysteryShip mysteryship;
PlayerBullet playerbullet;
EnemyBullet enemybullet;
DrawManager Draw;
Player player;
HighScoreManager HighScore;
GameManager gamemanager;
GameSettings Settings;
Shield ShieldOne(200, 320, 260, 180);
Shield ShieldTwo(500, 620, 260, 180);
Shield ShieldThree(800, 920, 260, 180);
#pragma endregion

#pragma region Arrays
EnemyAlien* g_apEnemyAlienArray[gc_iWaveDepth][gc_iWaveWidth];
Bullet g_aEnemyBullets[gc_iMaxEnemyBullets];
ShieldPiece* g_apShieldOnePixels[16][24];
ShieldPiece* g_apShieldTwoPixels[16][24];
ShieldPiece* g_apShieldThreePixels[16][24];
#pragma endregion

int main(int argv, char* argc[])
{
	//Initialise Window
	if (!UG::Create(g_iScreenWidth, g_iScreenHeight, false, "Space Invaders", 100, 100)) 
	{
		return 1;
	}

	HowToPage1 = UG::CreateSprite("./images/MainMenu.PNG", (float)g_iScreenWidth, (float)g_iScreenHeight, true);
	HowToPage2 = UG::CreateSprite("./images/HighScores.PNG", (float)g_iScreenWidth, (float)g_iScreenHeight, true);
	HowToPage3 = UG::CreateSprite("./images/InGame.PNG", (float)g_iScreenWidth, (float)g_iScreenHeight, true);
	UG::SetSpritePosition(HowToPage1, (float)g_iScreenWidth / 2, (float)g_iScreenHeight / 2);
	UG::SetSpritePosition(HowToPage2, (float)g_iScreenWidth / 2, (float)g_iScreenHeight / 2);
	UG::SetSpritePosition(HowToPage3, (float)g_iScreenWidth / 2, (float)g_iScreenHeight / 2);

	mainmenuselector.SetSprite("./images/EnemyAlien_1_1.PNG");
	UG::SetSpritePosition(mainmenuselector.GetSprite(), mainmenuselector.GetX(), mainmenuselector.GetY());
	MainMenuSprite = UG::CreateSprite("./images/SpaceInvadersLogo.PNG", 600.0f, 200.0f, true);//Logo for splash screen and main menu

	//initialise Graphics
	const int iFont = UG::AddFont("./fonts/REDENSEK.ttf", 72);						//Stores a pixelated style font for use
	UG::SetFont(iFont);																//Current font being used by the draw function.
	UG::SetBackgroundColor(UG::SColour(0x00, 0x00, 0x00, 0x00));					//Set Background to black

	//Downloads highscores into the games memory from a .txt file.
	HighScore.DownloadScores();
	//Game Starts on the splash screen.
	g_iGameState = SPLASH_SCREEN;

	do
	{
		float fDeltaTime = UG::GetDeltaTime();
		gamemanager.TakeUserInput();
		gamemanager.Update(fDeltaTime);
		gamemanager.DrawCurrentScreen();
	} while (UG::Process());
	UG::Dispose();
	
	//Before closing, Checks once more if any high scores have been beaten, and then rewrites the highscore .txt file.
	HighScore.UpdateScores();
	HighScore.UploadScores();

	return 0;
}