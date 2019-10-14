#include "HighScoreManager.h"
#include "Player.h"
#include "ScreenData.h"
#include "UGFW.h"
#include "UG_Defines.h"
#include <string>
#include <fstream>

void HighScoreManager::ShiftHighScores(int a_iShiftIndex) 
{
	//shifts the list of highscores down from the point passed through. This makes room for new highscores to be in the middle of the list.
	for (int i = 0; i < a_iShiftIndex; i++) 
	{
		g_vHighScores[i] = g_vHighScores[i + 1];
	}
}
void HighScoreManager::UpdateScores() 
{
	//algorithm to see if the player score is higher than any of the scores in the list, and if so, figures out which part of the list the players score should be entered.
	bool x = false;
	int i = 1;
	while (x == false) 
	{
		if (i >= 10) 
		{
			ShiftHighScores(9);
			g_vHighScores[9] = player.GetScore();
			x = true;
		}
		else if (player.GetScore() > g_vHighScores[i])
		{
			i++;
		}
		else if (player.GetScore() > g_vHighScores[i - 1]) 
		{
			if (i - 1 == 0)
			{
				g_vHighScores[0] = player.GetScore();
			}
			else
			{
				ShiftHighScores(i - 1);
				g_vHighScores[i - 1] = player.GetScore();
				x = true;
			}
		}
		else 
		{
			x = true;
		}
	}
}
void HighScoreManager::DownloadScores() 
{
	std::string line;
	std::fstream fsHighScoresFile;
	fsHighScoresFile.open("./HighScores.txt");

	while (std::getline(fsHighScoresFile, line))
	{
		g_vHighScores.push_back(atoi(line.c_str()));	//used push back and vectors so each line in the highscore txt file is added to the end.
	}
	fsHighScoresFile.close();
}
void HighScoreManager::UploadScores()const
{
	std::fstream fsHighScoresFile;
	fsHighScoresFile.open("./HighScores.txt");
	for (int i = 0; i < 10; i++) 
	{	//adds each item in the highscore array to its own line in the highscorefile. Note everytime this happens, the old highscore file is wiped.
		fsHighScoresFile << g_vHighScores[i] << std::endl;
	}
	fsHighScoresFile.close();
}
void HighScoreManager::Draw()const
{
	std::string sHighScore1 = std::to_string(g_vHighScores[9]);					//Tried to fit the conversion on one line. Did not work. (conversion for int to const char*)
	const char* cHighScore1 = sHighScore1.c_str();
	std::string sHighScore2 = std::to_string(g_vHighScores[8]);
	const char* cHighScore2 = sHighScore2.c_str();
	std::string sHighScore3 = std::to_string(g_vHighScores[7]);
	const char* cHighScore3 = sHighScore3.c_str();
	std::string sHighScore4 = std::to_string(g_vHighScores[6]);
	const char* cHighScore4 = sHighScore4.c_str();
	std::string sHighScore5 = std::to_string(g_vHighScores[5]);
	const char* cHighScore5 = sHighScore5.c_str();
	std::string sHighScore6 = std::to_string(g_vHighScores[4]);
	const char* cHighScore6 = sHighScore6.c_str();
	std::string sHighScore7 = std::to_string(g_vHighScores[3]);
	const char* cHighScore7 = sHighScore7.c_str();
	std::string sHighScore8 = std::to_string(g_vHighScores[2]);
	const char* cHighScore8 = sHighScore8.c_str();
	std::string sHighScore9 = std::to_string(g_vHighScores[1]);;
	const char* cHighScore9 = sHighScore9.c_str();
	std::string sHighScore10 = std::to_string(g_vHighScores[0]);
	const char* cHighScore10 = sHighScore10.c_str();

	//Draws the top 10 highest scores to the highscore screen
	UG::DrawString("Highscores", g_iScreenWidth / 2 - 200, 550, 1, UG::SColour(255, 255, 255, 255));
	UG::DrawString(cHighScore1, g_iScreenWidth / 2 - 15, 500, 1, UG::SColour(255, 255, 255, 255));
	UG::DrawString(cHighScore2, g_iScreenWidth / 2 - 15, 450, 1, UG::SColour(255, 255, 255, 255));
	UG::DrawString(cHighScore3, g_iScreenWidth / 2 - 15, 400, 1, UG::SColour(255, 255, 255, 255));
	UG::DrawString(cHighScore4, g_iScreenWidth / 2 - 15, 350, 1, UG::SColour(255, 255, 255, 255));
	UG::DrawString(cHighScore5, g_iScreenWidth / 2 - 15, 300, 1, UG::SColour(255, 255, 255, 255));
	UG::DrawString(cHighScore6, g_iScreenWidth / 2 - 15, 250, 1, UG::SColour(255, 255, 255, 255));
	UG::DrawString(cHighScore7, g_iScreenWidth / 2 - 15, 200, 1, UG::SColour(255, 255, 255, 255));
	UG::DrawString(cHighScore8, g_iScreenWidth / 2 - 15, 150, 1, UG::SColour(255, 255, 255, 255));
	UG::DrawString(cHighScore9, g_iScreenWidth / 2 - 15, 100, 1, UG::SColour(255, 255, 255, 255));
	UG::DrawString(cHighScore10, g_iScreenWidth / 2 - 15, 50, 1, UG::SColour(255, 255, 255, 255));
}
void HighScoreManager::DrawHighestScore()const 
{
	//Draws the number 1 highest score on the UI for when in game.
	std::string sCurrentHighScoreText = "High Score: ";
	std::string sCurrentHighScore = (std::to_string(g_vHighScores[9]));
	sCurrentHighScoreText += sCurrentHighScore;
	const char* cHighScoreText = sCurrentHighScoreText.c_str();
	UG::DrawString(cHighScoreText, 550, 850, 1, UG::SColour(255, 255, 255, 255));
}