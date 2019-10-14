#include "GameManager.h"
#include "Player.h"
#include "Bullet.h"
#include "GameData.h"
#include "UGFW.h"
#include "UG_Defines.h"
#include "ScreenData.h"
#include <random>
#include <string>
#include "HighScoreManager.h"
#include "GameData.h"
#include <iostream>
#include "MainMenuSelector.h"
#include "MysteryShip.h"
#include "DrawManager.h"
#include "Shield.h"
#include "EnemyAlien.h"

void GameManager::TakeUserInput()const
{
	switch (g_iGameState)
	{
	case PLAY:
	{
		if (UG::IsKeyDown(UG::KEY_A)) 
		{
			player.MoveLeft();
		}
		if (UG::IsKeyDown(UG::KEY_D)) 
		{
			player.MoveRight();
		}
		if (UG::IsKeyDown(UG::KEY_SPACE)) 
		{
			player.Shoot();
		}
		if (UG::IsKeyDown(UG::KEY_ESCAPE))
		{
			g_iGameState = PAUSE;
		}
		break;
	}
	case MAIN_MENU:
	{
		if (UG::WasKeyPressed(UG::KEY_W) || UG::WasKeyPressed(UG::KEY_UP)) 
		{
			mainmenuselector.MoveUp();
		}
		if (UG::WasKeyPressed(UG::KEY_S) || UG::WasKeyPressed(UG::KEY_DOWN)) 
		{
			mainmenuselector.MoveDown();
		}
		else if (UG::WasKeyPressed(UG::KEY_ENTER)) 
		{
			mainmenuselector.Select();
		}
		break;
	}
	case PAUSE:
	{
		if (UG::WasKeyPressed(UG::KEY_Q)) 
		{
			UG::Close();
		}
		else if (UG::WasKeyPressed(UG::KEY_M)) 
		{
			//clears data, as when you start a new game, the data will be recreated. This speeds up the game.
			HighScore.UpdateScores();
			gamemanager.DeleteWave();
			gamemanager.DeleteShields();
			UG::DestroySprite(player.GetSprite());
			UG::DestroySprite(mysteryship.GetSprite());
			UG::DestroySprite(playerbullet.GetSprite());
			UG::DestroySprite(enemybullet.GetSprite());
			g_iGameState = MAIN_MENU;
		}
		else if (UG::WasKeyPressed(UG::KEY_ESCAPE)) 
		{
			g_iGameState = PLAY;
		}
		break;
	}
	case HIGH_SCORES:
	{
		if (UG::WasKeyPressed(UG::KEY_ESCAPE))
		{
			g_iGameState = MAIN_MENU;
		}
	}
	case HOW_TO_PLAY:
	{
		if (UG::WasKeyPressed(UG::KEY_SPACE)) 
		{
			if (HowToPlayPage >= 3) {
				g_iGameState = MAIN_MENU;
			}
			else {
				HowToPlayPage += 1;
			}
		}
	}
	default:
	{
		break;
	}
	};
}
void GameManager::CreateGame()const 
{
	//moves player to the middle of the screen
	player.SetX(g_iScreenWidth / 2.0f);
	player.SetLeftX(player.GetX() - (player.GetSpriteWidth() / 2));
	player.SetRightX(player.GetX() + (player.GetSpriteWidth() / 2));

	player.SetLives(3);
	player.SetScore(0);
	player.SetShotsFired(0);

	player.SetSprite("./images/Player.PNG");
	UG::SetSpritePosition(player.GetSprite(), player.GetX(), player.GetY());

	//Creates enemy aliens
	CreateWave();
	CreateShields();

	playerbullet.SetSprite("./images/Bullet.PNG", 5.0f, 15.0f);
	enemybullet.SetSprite("./images/Bullet.PNG", 5.0f, 15.0f);

	mysteryship.SetSprite("./images/MysteryShip.PNG", 80.0f, 35.0f);
	UG::SetSpritePosition(mysteryship.GetSprite(), 900.0f, 810.0f);
	mysteryship.SetDirection("RIGHT");
	mysteryship.SetTime(0.0f);
}
void GameManager::CreateShields()const
{
	for (int row = 0; row < 16; row++) 
	{
		for (int column = 0; column < 24; column++) 
		{
			//Checks with a template array to see which pixels should be active for the shield at start.
			if (g_abShieldTemplate[row][column]) 
			{
				g_apShieldOnePixels[row][column] = new ShieldPiece(column * 5.0f + (200.0f), row * 5.0f + (2.0f * gc_fHeightIncrement) + 30.0f);
				UG::SetSpritePosition(g_apShieldOnePixels[row][column]->GetSprite(), g_apShieldOnePixels[row][column]->GetX(), g_apShieldOnePixels[row][column]->GetY());
				g_apShieldOnePixels[row][column]->SetState(true);

				g_apShieldTwoPixels[row][column] = new ShieldPiece(column * 5.0f + (500.0f), row * 5.0f + (2.0f * gc_fHeightIncrement) + 30.0f);
				UG::SetSpritePosition(g_apShieldTwoPixels[row][column]->GetSprite(), g_apShieldTwoPixels[row][column]->GetX(), g_apShieldTwoPixels[row][column]->GetY());
				g_apShieldTwoPixels[row][column]->SetState(true);

				g_apShieldThreePixels[row][column] = new ShieldPiece(column * 5.0f + (800.0f), row * 5.0f + (2.0f * gc_fHeightIncrement) + 30.0f);
				UG::SetSpritePosition(g_apShieldThreePixels[row][column]->GetSprite(), g_apShieldThreePixels[row][column]->GetX(), g_apShieldThreePixels[row][column]->GetY());
				g_apShieldThreePixels[row][column]->SetState(true);
			}
			else 
			{
				g_apShieldOnePixels[row][column] = new ShieldPiece(column * 5.0f + (200.0f), row * 5.0f + (2.0f * gc_fHeightIncrement) + 30.0f);
				g_apShieldOnePixels[row][column]->SetSprite("");
				g_apShieldOnePixels[row][column]->SetState(false);

				g_apShieldTwoPixels[row][column] = new ShieldPiece(column * 5.0f + (500.0f), row * 5.0f + (2.0f * gc_fHeightIncrement) + 30.0f);
				g_apShieldTwoPixels[row][column]->SetSprite("");
				g_apShieldTwoPixels[row][column]->SetState(false);

				g_apShieldThreePixels[row][column] = new ShieldPiece(column * 5.0f + (800.0f), row * 5.0f + (2.0f * gc_fHeightIncrement) + 30.0f);
				g_apShieldThreePixels[row][column]->SetSprite("");
				g_apShieldThreePixels[row][column]->SetState(false);
			}
		}
	}
}
void GameManager::CreateWave()const 
{
		int points;
		float width;
		std::string sprite;

		for (int row = 0; row < gc_iWaveDepth; row++)
		{
			if (row == 4) 
			{				//Decides what the alien is based on its row, this then decides what it is worth and what sprite it will display.
				points = 30;
				sprite = "./images/EnemyAlien_3_1.PNG";
				width = 40.0f;
			}
			else if (row == 2 || row == 3)
			{
				points = 20;
				sprite = "./images/EnemyAlien_2_1.PNG";
				width = 60.0f;
			}
			else if (row == 0 || row == 1)
			{
				points = 10;
				sprite = "./images/EnemyAlien_1_1.PNG";
				width = 55.0f;
			}
			else {
				points = 0;
				width = 0.0f;
			}

			for (int column = 0; column < gc_iWaveWidth; column++)
			{
				g_apEnemyAlienArray[row][column] = new EnemyAlien(points, (column * gc_fHeightIncrement) + (gc_fHeightIncrement * 2), (row * gc_fHeightIncrement) + (gc_fHeightIncrement * 6), sprite, width);
			}
		}
		g_iEnemyAliensAlive = gc_iWaveDepth * gc_iWaveWidth;
}
void GameManager::DrawCurrentScreen()const
{
	UG::ClearScreen();
	switch (g_iGameState)
	{
	case PLAY:
	{
		Draw.GameScreen();
		break;
	}
	case PAUSE:
	{
		Draw.GameScreen();
		UG::DrawString("PAUSED", 350, 850, 2, UG::SColour(255, 0, 0, 255));
		break;
	}
	case MAIN_MENU:
	{
		Draw.MainMenuScreen();
		break;
	}
	case GAME_OVER:
	{
		Draw.GameScreen();
		UG::DrawString("Game Over!", 350, 500, 2, UG::SColour(50, 205, 50, 255));
	}
	case SPLASH_SCREEN:
	{
		Draw.SplashScreen();
		break;
	}
	case HIGH_SCORES:
	{
		Draw.HighScoreScreen();
		break;
	}
	case HOW_TO_PLAY:
	{
		Draw.HowToPlayScreen();
		break;
	}
	case LOSE_LIFE:
	{
		Draw.GameScreen();
		break;
	}
	default:
	{
		break;
	}
	};
}
void GameManager::DeleteWave()const
{
	for (int row = 0; row < gc_iWaveDepth; row++) 
	{
		for (int column = 0; column < gc_iWaveWidth; column++)
		{
			UG::DestroySprite(g_apEnemyAlienArray[row][column]->GetSprite());
			delete g_apEnemyAlienArray[row][column];
		}
	}
}
void GameManager::DeleteShields()const
{
	for (int row = 0; row < 16; row++)
	{
		for (int column = 0; column < 24; column++)
		{
			UG::DestroySprite(g_apShieldOnePixels[row][column]->GetSprite());
			UG::DestroySprite(g_apShieldTwoPixels[row][column]->GetSprite());
			UG::DestroySprite(g_apShieldThreePixels[row][column]->GetSprite());
			delete g_apShieldOnePixels[row][column];
			delete g_apShieldTwoPixels[row][column];
			delete g_apShieldThreePixels[row][column];
		}
	}
}
void GameManager::CheckAllAliensDead()const 
{
	if (g_iEnemyAliensAlive <= 0) 
	{
		CreateWave();
	}
}
void GameManager::ShouldEnemyShoot()const
{
	//always shoots if a bullet isnt active. 
	if (!enemybullet.GetState()) 
	{
		EnemyAlien::ChooseShooter();
	}
}
void GameManager::UpdateAliens(float a_g_fDeltaSum)const 
{
	g_fDeltaSum += a_g_fDeltaSum;
	float ActualSpeed = g_fGameSpeed;
	if (g_iEnemyAliensAlive == 1) {//speeds up the game 5x while there is only 1 alien left. Making it very hard to hit.
		ActualSpeed = (g_fGameSpeed / 5);
	}

	if (g_fDeltaSum > ActualSpeed)
	{
		MoveAliensX();
		ShouldEnemyShoot(); //Enemy's currently shoot aslong as there is not another enemy bullet active.
		for (int row = 0; row < gc_iWaveDepth; row++)
		{
			for (int column = 0; column < gc_iWaveWidth; column++)
			{
				if (g_apEnemyAlienArray[row][column]->GetIsDying()) 
				{															//By having an isdying variable.
					g_apEnemyAlienArray[row][column]->Die();				//The death sprite is able to be kept for an extra ingame clock tick, 
				}															//without killing off the enemy.


				//The following section is for animating the sprites. Each alien can have either 1 or 2 states.
				//An animationstate variable is used to state which sprite it should print. If the alien has state 1, it becomes 2 in the next update. and vice versa.
				//Then based on how many points the alien is worth I can determin which type of alien it is (1 of 3) without need for another variable.
				//Then for that alien, the aproppriate sprite is selected (EnemyAlien_x_y.png where x is the alien type, and y is the animation state).
				if (g_apEnemyAlienArray[row][column]->GetAnimationState() == 1)
				{
					g_apEnemyAlienArray[row][column]->SetAnimationState(2);
					if (g_apEnemyAlienArray[row][column]->GetPointsWorth() == 30) 
					{//3
						g_apEnemyAlienArray[row][column]->SetSprite("./images/EnemyAlien_3_1.png", 40.0f, 40.0f);
						UG::SetSpritePosition(g_apEnemyAlienArray[row][column]->GetSprite(), g_apEnemyAlienArray[row][column]->GetX(), g_apEnemyAlienArray[row][column]->GetY());
					}
					else if (g_apEnemyAlienArray[row][column]->GetPointsWorth() == 20) 
					{// 2
						g_apEnemyAlienArray[row][column]->SetSprite("./images/EnemyAlien_2_1.png", 60.0f, 40.0f);
						UG::SetSpritePosition(g_apEnemyAlienArray[row][column]->GetSprite(), g_apEnemyAlienArray[row][column]->GetX(), g_apEnemyAlienArray[row][column]->GetY());
					}
					else if (g_apEnemyAlienArray[row][column]->GetPointsWorth() == 10) 
					{ // 1
						g_apEnemyAlienArray[row][column]->SetSprite("./images/EnemyAlien_1_1.png", 55.0f, 40.0f);
						UG::SetSpritePosition(g_apEnemyAlienArray[row][column]->GetSprite(), g_apEnemyAlienArray[row][column]->GetX(), g_apEnemyAlienArray[row][column]->GetY());
					}
				}
				else if (g_apEnemyAlienArray[row][column]->GetAnimationState() == 2) 
				{
					g_apEnemyAlienArray[row][column]->SetAnimationState(1);
					if (g_apEnemyAlienArray[row][column]->GetPointsWorth() == 30) {//3
						g_apEnemyAlienArray[row][column]->SetSprite("./images/EnemyAlien_3_2.png", 40.0f, 40.0f);
						UG::SetSpritePosition(g_apEnemyAlienArray[row][column]->GetSprite(), g_apEnemyAlienArray[row][column]->GetX(), g_apEnemyAlienArray[row][column]->GetY());
					}
					else if (g_apEnemyAlienArray[row][column]->GetPointsWorth() == 20) {// 2
						g_apEnemyAlienArray[row][column]->SetSprite("./images/EnemyAlien_2_2.png", 60.0f, 40.0f);
						UG::SetSpritePosition(g_apEnemyAlienArray[row][column]->GetSprite(), g_apEnemyAlienArray[row][column]->GetX(), g_apEnemyAlienArray[row][column]->GetY());
					}
					else if (g_apEnemyAlienArray[row][column]->GetPointsWorth() == 10) { // 1
						g_apEnemyAlienArray[row][column]->SetSprite("./images/EnemyAlien_1_2.png", 55.0f, 40.0f);
						UG::SetSpritePosition(g_apEnemyAlienArray[row][column]->GetSprite(), g_apEnemyAlienArray[row][column]->GetX(), g_apEnemyAlienArray[row][column]->GetY());
					}

				}
			}
		}
		g_fDeltaSum = 0.0f;
	}
}
void GameManager::MoveAliensX()const 
{
	std::string CurrentDirection = EnemyAlien::GetDirection();
	for (int row = 0; row < gc_iWaveDepth; row++) 
	{
		for (int column = 0; column < gc_iWaveWidth; column++)
		{
			if (!g_apEnemyAlienArray[row][column]->GetState()) 
			{
				if (!CurrentDirection.compare("LEFT")) 
				{
					g_apEnemyAlienArray[row][column]->MoveLeft();
				}
				else if (!CurrentDirection.compare("RIGHT"))
				{
					g_apEnemyAlienArray[row][column]->MoveRight();
				}
			}
		}
	}
}
void GameManager::MoveAliensY()const {
	for (int row = 0; row < gc_iWaveDepth; row++) 
	{
		for (int column = 0; column < gc_iWaveWidth; column++) 
		{
			g_apEnemyAlienArray[row][column]->MoveDown();
		}
	}
}
void GameManager::CheckAliensAtYBoundary()const	//makes the aliens change direction when they hit the edge of the game screen aswell as making htem descend
{
	for (int row = 0; row < gc_iWaveDepth; row++) 
	{
		for (int column = 0; column < gc_iWaveWidth; column++)
		{
			float CurrentXPos = g_apEnemyAlienArray[row][column]->GetX();
			if (CurrentXPos >= gc_fRightYBound) 
			{
				EnemyAlien::SetDirection("LEFT");
				gamemanager.MoveAliensX();
				gamemanager.MoveAliensY();
			}
			else if (CurrentXPos <= gc_fLeftYBound) 
			{
				EnemyAlien::SetDirection("RIGHT");
				gamemanager.MoveAliensX();
				gamemanager.MoveAliensY();
			}
		}
	}
}
void GameManager::CheckAliensAtFloor()const
{
	for (int row = 0; row < gc_iWaveDepth; row++) 
	{
		for (int column = 0; column < gc_iWaveWidth; column++) 
		{
			if (g_apEnemyAlienArray[row][column]->IsAtFloor())
			{
				g_iGameState = GAME_OVER;
			}
		}
	}
}
void GameManager::ImageShield()const
{
	std::cout << " " << std::endl;
	std::cout << "_________________________" << std::endl;
	std::cout << "Debug : Image Of Shield" << std::endl;
	for (int row = 15; row >= 0; row--)
	{
		for (int column = 0; column < 24; column++)
		{
			if (g_apShieldOnePixels[row][column]->GetState())
			{
				std::cout << "1";
			}
			else 
			{
				std::cout << " ";
			}
		}
		std::cout << std::endl;
	}
	std::cout << "_________________________" << std::endl;
}
void GameManager::HitShield(std::string a_sShooter, int a_iShield, int a_iY, int a_iX)const //handles destroying pixels in the shield when it is hit, by using a pretdermined explosion pattern.
{
	auto g_apShield = g_apShieldOnePixels; //creates default value.
	if (a_iShield == 1) 
	{
		g_apShield = g_apShieldOnePixels;
	}
	else if (a_iShield == 2) 
	{
		g_apShield = g_apShieldTwoPixels;
	}
	else if (a_iShield == 3) 
	{
		g_apShield = g_apShieldThreePixels;
	}

	g_apShield[a_iY][a_iX]->SetState(false);	//deletes hit pixel

	if (a_sShooter == "PLAYER") 
	{						//Then goes on to delete pixels around area of hit pixel to imitate explosion. explosion acts from direction of shooter(from above or below)
		if (a_iX > 0) 
		{
			g_apShield[a_iY][a_iX - 1]->SetState(false);
		}
		if (a_iX < 23) 
		{
			g_apShield[a_iY][a_iX + 1]->SetState(false);
		}
		if (a_iY < 15)
		{
			g_apShield[a_iY + 1][a_iX]->SetState(false);
		}
		if (a_iX < 23 && a_iY < 14) 
		{
			g_apShield[a_iY + 2][a_iX + 1]->SetState(false);
		}
		if (a_iX > 0 && a_iY < 13) 
		{
			g_apShield[a_iY + 3][a_iX - 1]->SetState(false);
		}
	}
	else if (a_sShooter == "ENEMY") 
	{
		if (a_iX > 0) 
		{
			g_apShield[a_iY][a_iX - 1]->SetState(false);
		}
		if (a_iX < 24) 
		{
			g_apShield[a_iY][a_iX + 1]->SetState(false);
		}
		if (a_iY > 1) 
		{
			g_apShield[a_iY - 1][a_iX]->SetState(false);
		}
		if (a_iX < 24 && a_iY > 2)
		{
			g_apShield[a_iY - 2][a_iX + 1]->SetState(false);
		}
		if (a_iX > 0 && a_iY > 3) 
		{
			g_apShield[a_iY - 3][a_iX - 1]->SetState(false);
		}
	}
	if (Settings.ShieldImagingOn()) {
		gamemanager.ImageShield();
	}
}
void GameManager::EnemyBodyCollisionWithShieldsDetection()const
{
	//Destroys the parts of the shields touched by the enemy aliens, if they have managed to descend far enough.
	for (int row = 0; row < gc_iWaveDepth; row++)
	{
		for (int column = 0; column < gc_iWaveWidth; column++)
		{
			if (!g_apEnemyAlienArray[row][column]->GetState()) 
			{
				if (g_apEnemyAlienArray[row][column]->GetBottomY() <= ShieldOne.GetTopY()) 
				{
					for (int row2 = 0; row2 < 16; row2++)
					{
						for (int column2 = 0; column2 < 24; column2++) 
						{
							if ((g_apEnemyAlienArray[row][column]->GetBottomY() <= g_apShieldOnePixels[row2][column2]->GetTopY() && g_apEnemyAlienArray[row][column]->GetRightX() >= g_apShieldOnePixels[row2][column2]->GetLeftX())
								&& g_apEnemyAlienArray[row][column]->GetLeftX() <= g_apShieldOnePixels[row2][column2]->GetRightX())
							{
								g_apShieldOnePixels[row2][column2]->SetState(false);
							}
							if ((g_apEnemyAlienArray[row][column]->GetBottomY() <= g_apShieldTwoPixels[row2][column2]->GetTopY() && g_apEnemyAlienArray[row][column]->GetRightX() >= g_apShieldTwoPixels[row2][column2]->GetLeftX())
								&& g_apEnemyAlienArray[row][column]->GetLeftX() <= g_apShieldTwoPixels[row2][column2]->GetRightX())
							{
								g_apShieldTwoPixels[row2][column2]->SetState(false);
							}
							if ((g_apEnemyAlienArray[row][column]->GetBottomY() <= g_apShieldThreePixels[row2][column2]->GetTopY() && g_apEnemyAlienArray[row][column]->GetRightX() >= g_apShieldThreePixels[row2][column2]->GetLeftX())
								&& g_apEnemyAlienArray[row][column]->GetLeftX() <= g_apShieldThreePixels[row2][column2]->GetRightX())
							{
								g_apShieldThreePixels[row2][column2]->SetState(false);
							}
						}
					}
				}
			}
		}
	}
}
void GameManager::EnemyBulletCollisionDetection()const
{
	//lose life if player is hit
	if (enemybullet.GetX() <= player.GetRightX() && enemybullet.GetX() >= player.GetLeftX() &&
		enemybullet.GetY() <= player.GetTopY())
	{
		g_iGameState = LOSE_LIFE;
	}

	//First Checks if the alien bullet is within the collider box of the entire shield 
	//(This means the code isnt constantly iterating each shield piece when the bullet isnt near the pixels, Speeding up the code).
	if (enemybullet.GetX() <= ShieldOne.GetRightX() && enemybullet.GetX() >= ShieldOne.GetLeftX() &&
		enemybullet.GetY() >= ShieldOne.GetBottomY() && enemybullet.GetY() <= ShieldOne.GetTopY()) 
	{
		//Then iterates each piece of the shield. If the piece is still alive, then checks if the center of the enemy bullet is within the collider box of the shield piece
		//If it is, destroys the enemy bullet and runs code to hit the shield from the position of the piece hit and direction of the enemy (From Above).
		for (int row = 0; row < 16; row++) 
		{
			for (int column = 0; column < 24; column++) 
			{
				if (g_apShieldOnePixels[row][column]->GetState()) 
				{
					if ((enemybullet.GetX() <= g_apShieldOnePixels[row][column]->GetRightX() && enemybullet.GetX() >= g_apShieldOnePixels[row][column]->GetLeftX() &&
						enemybullet.GetY() >= g_apShieldOnePixels[row][column]->GetBottomY() && enemybullet.GetY() <= g_apShieldOnePixels[row][column]->GetTopY()))
					{
						gamemanager.HitShield("ENEMY", 1, row, column);
						enemybullet.SetState(false);
					}
				}
			}
		}
	}
	//Repeats code for each the other 2 shields. 
	//(Tried to create an array of the shields to iterate through and condense code, but arrayrs of arrays of pointers got a bit confusing for me)
	if (enemybullet.GetX() <= ShieldTwo.GetRightX() && enemybullet.GetX() >= ShieldTwo.GetLeftX() &&
		enemybullet.GetY() >= ShieldTwo.GetBottomY() && enemybullet.GetY() <= ShieldTwo.GetTopY())
	{
		for (int row = 0; row < 16; row++) 
		{
			for (int column = 0; column < 24; column++)
			{
				if (g_apShieldTwoPixels[row][column]->GetState()) 
				{
					if ((enemybullet.GetX() <= g_apShieldTwoPixels[row][column]->GetRightX() && enemybullet.GetX() >= g_apShieldTwoPixels[row][column]->GetLeftX() &&
						enemybullet.GetY() >= g_apShieldTwoPixels[row][column]->GetBottomY() && enemybullet.GetY() <= g_apShieldTwoPixels[row][column]->GetTopY())) 
					{
						gamemanager.HitShield("ENEMY", 2, row, column);
						enemybullet.SetState(false);
					}
				}
			}
		}
	}
	if (enemybullet.GetX() <= ShieldThree.GetRightX() && enemybullet.GetX() >= ShieldThree.GetLeftX() &&
		enemybullet.GetY() >= ShieldThree.GetBottomY() && enemybullet.GetY() <= ShieldThree.GetTopY()) 
	{
		for (int row = 0; row < 16; row++) 
		{
			for (int column = 0; column < 24; column++)
			{
				if (g_apShieldThreePixels[row][column]->GetState()) 
				{
					if ((enemybullet.GetX() <= g_apShieldThreePixels[row][column]->GetRightX() && enemybullet.GetX() >= g_apShieldThreePixels[row][column]->GetLeftX() &&
						enemybullet.GetY() >= g_apShieldThreePixels[row][column]->GetBottomY() && enemybullet.GetY() <= g_apShieldThreePixels[row][column]->GetTopY()))
					{
						gamemanager.HitShield("ENEMY", 3, row, column);
						enemybullet.SetState(false);
					}
				}
			}
		}
	}
}
void GameManager::PlayerBulletCollisionDetection()const 
{
	gamemanager.CheckAliensAtYBoundary(); // Fixes bug where if enemy is shot while moving down a row, it would get stuck on the boundary, causing it to move down all the rows, and losing the game.
	for (int row = 0; row < gc_iWaveDepth; row++) 
	{
		for (int column = 0; column < gc_iWaveWidth; column++) 
		{
			if (!g_apEnemyAlienArray[row][column]->GetState() && !g_apEnemyAlienArray[row][column]->GetIsDying())
			{
				if (playerbullet.GetX() <= g_apEnemyAlienArray[row][column]->GetRightX() && playerbullet.GetX() >= g_apEnemyAlienArray[row][column]->GetLeftX() &&
					playerbullet.GetY() <= g_apEnemyAlienArray[row][column]->GetTopY() && playerbullet.GetY() >= g_apEnemyAlienArray[row][column]->GetBottomY())
				{
					playerbullet.SetState(false);

					g_apEnemyAlienArray[row][column]->SetIsDying(true);
					g_apEnemyAlienArray[row][column]->SetSprite("./images/EnemyExplosion.PNG", 60.0f, 40.0f);
					UG::SetSpritePosition(g_apEnemyAlienArray[row][column]->GetSprite(), g_apEnemyAlienArray[row][column]->GetX(), g_apEnemyAlienArray[row][column]->GetY());
					g_iEnemyAliensAlive -= 1;
					gamemanager.CheckAllAliensDead();

					//gain points for every alien killed
					int currentscore = player.GetScore();
					int EnemyAlienPointsWorth = g_apEnemyAlienArray[row][column]->GetPointsWorth();
					currentscore += EnemyAlienPointsWorth;
					player.SetScore(currentscore);

					//game speeds up for every alien killed.
					g_fGameSpeed -= 0.005f;
				}
			}
		}
	}
	if (playerbullet.GetX() <= mysteryship.GetRightX() && playerbullet.GetX() >= mysteryship.GetLeftX() && playerbullet.GetY() >= mysteryship.GetBottomY()) 
	{
		mysteryship.SetState(false);
		playerbullet.SetState(false);

		//Work Out What the mystery ship is worth
		if (player.GetShotsFired() == 23 || (player.GetShotsFired() != 15 && player.GetShotsFired() % 15 == 0))
		{	//worth 300
			player.SetScore(player.GetScore() + 300);
		}
		else 
		{
			//random number algorithm sourced from stack overflow
			std::random_device rd;		//initialise seed
			std::mt19937 rng(rd());		//random number engine
			std::uniform_int_distribution<int> uni(0, 2); //values are inclusive

			int aiPossibleOutcomes[3]{ 50, 100, 150 };

			auto PointsWorthIndex = uni(rng);

			player.SetScore(player.GetScore() + aiPossibleOutcomes[PointsWorthIndex]);
		}
	}

	if (playerbullet.GetX() <= ShieldOne.GetRightX() && playerbullet.GetX() >= ShieldOne.GetLeftX() &&
		playerbullet.GetY() >= ShieldOne.GetBottomY() && playerbullet.GetY() <= ShieldOne.GetTopY())
	{
		for (int row = 0; row < 16; row++)
		{
			for (int column = 0; column < 24; column++)
			{
				if (g_apShieldOnePixels[row][column]->GetState()) {
					if ((playerbullet.GetX() <= g_apShieldOnePixels[row][column]->GetRightX() && playerbullet.GetX() >= g_apShieldOnePixels[row][column]->GetLeftX() &&
						playerbullet.GetY() >= g_apShieldOnePixels[row][column]->GetBottomY() && playerbullet.GetY() <= g_apShieldOnePixels[row][column]->GetTopY())) 
					{
						gamemanager.HitShield("PLAYER", 1, row, column);
						playerbullet.SetState(false);
					}
				}
			}
		}
	}
	if (playerbullet.GetX() <= ShieldTwo.GetRightX() && playerbullet.GetX() >= ShieldTwo.GetLeftX() &&
		playerbullet.GetY() >= ShieldTwo.GetBottomY() && playerbullet.GetY() <= ShieldTwo.GetTopY())
	{
		for (int row = 0; row < 16; row++)
		{
			for (int column = 0; column < 24; column++)
			{
				if (g_apShieldTwoPixels[row][column]->GetState()) 
				{
					if ((playerbullet.GetX() <= g_apShieldTwoPixels[row][column]->GetRightX() && playerbullet.GetX() >= g_apShieldTwoPixels[row][column]->GetLeftX() &&
						playerbullet.GetY() >= g_apShieldTwoPixels[row][column]->GetBottomY() && playerbullet.GetY() <= g_apShieldTwoPixels[row][column]->GetTopY())) 
					{
						gamemanager.HitShield("PLAYER", 2, row, column);
						playerbullet.SetState(false);
					}
				}
			}
		}
	}
	if (playerbullet.GetX() <= ShieldThree.GetRightX() && playerbullet.GetX() >= ShieldThree.GetLeftX() &&
		playerbullet.GetY() >= ShieldThree.GetBottomY() && playerbullet.GetY() <= ShieldThree.GetTopY())
	{
		for (int row = 0; row < 16; row++)
		{
			for (int column = 0; column < 24; column++) 
			{
				if (g_apShieldThreePixels[row][column]->GetState()) 
				{
					if ((playerbullet.GetX() <= g_apShieldThreePixels[row][column]->GetRightX() && playerbullet.GetX() >= g_apShieldThreePixels[row][column]->GetLeftX() &&
						playerbullet.GetY() >= g_apShieldThreePixels[row][column]->GetBottomY() && playerbullet.GetY() <= g_apShieldThreePixels[row][column]->GetTopY())) 
					{
						gamemanager.HitShield("PLAYER", 3, row, column);
						playerbullet.SetState(false);
					}
				}
			}
		}
	}
}
void GameManager::Update(float a_g_fDeltaSum)const
{
	switch (g_iGameState) 
	{
	case PLAY:
	{
		gamemanager.UpdateAliens(a_g_fDeltaSum);
		enemybullet.Update();
		playerbullet.Update();
		mysteryship.Update(a_g_fDeltaSum);
		gamemanager.CheckAliensAtYBoundary();
		gamemanager.CheckAliensAtFloor();
		gamemanager.EnemyBodyCollisionWithShieldsDetection();
		break;
	}
	case GAME_OVER:
		g_fDeltaSum += a_g_fDeltaSum;
		if (g_fDeltaSum > gc_fGameOverMsgShowTime)
		{
			//clears memory, checks the score earned with the highscores. And takes you back to the main menu
			HighScore.UpdateScores();
			gamemanager.DeleteWave();
			gamemanager.DeleteShields();
			UG::DestroySprite(player.GetSprite());
			UG::DestroySprite(mysteryship.GetSprite());
			UG::DestroySprite(playerbullet.GetSprite());
			UG::DestroySprite(enemybullet.GetSprite());
			g_iGameState = MAIN_MENU;
			g_fDeltaSum = 0.0f;
		}
		break;
	case LOSE_LIFE:
		//Game pauses for a period of time to let the player soak in the death sprite. Then moves the player back to the center of the screen.
		enemybullet.SetState(false);
		player.SetSprite("./images/PlayerExplosion.PNG");
		UG::SetSpritePosition(player.GetSprite(), player.GetX(), player.GetY());

		if (player.GetLives() <= 0) 
		{
			g_iGameState = GAME_OVER;
		}
		g_fDeltaSum += a_g_fDeltaSum;
		if (g_fDeltaSum > 1.5f) {
			player.SetLives(player.GetLives() - 1);
			player.SetX(g_iScreenWidth / 2.0f);
			player.SetLeftX(player.GetX() - (player.GetSpriteWidth() / 2));
			player.SetRightX(player.GetX() + (player.GetSpriteWidth() / 2));
			player.SetSprite("./images/Player.PNG");
			UG::SetSpritePosition(player.GetSprite(), player.GetX(), player.GetY());
			g_iGameState = PLAY;
			g_fDeltaSum = 0.0f;
		}
		break;
	case SPLASH_SCREEN:
	{
		g_fDeltaSum += a_g_fDeltaSum;
		if (g_fDeltaSum > gc_fSplashScreenShowTime)
		{
			HighScore.UpdateScores();
			g_iGameState = MAIN_MENU;
			g_fDeltaSum = 0.0f;
		}
		break;
	}
	};
}