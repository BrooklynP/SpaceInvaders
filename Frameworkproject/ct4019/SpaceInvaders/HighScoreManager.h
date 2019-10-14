#include<vector>

#pragma once
//Handles all highscore logic and communicates with the highscore.txt file in the project folder.
class HighScoreManager
{
public:
	void DownloadScores();
	void UploadScores()const;
	void UpdateScores();
	
	void Draw()const; //Draw function for the high score screen
	void DrawHighestScore()const; //Draw function for the UI
private:
	std::vector<int> g_vHighScores; //Used a vector so that the push back function could be used when downloading scores from txt file (This could not be done in a standard array)
	void ShiftHighScores(int a_iShiftIndex); //Function that moves highscores lower than the index down the vector so that a new high score can be placed in the middle of the vector.
};
extern HighScoreManager HighScore;