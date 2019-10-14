#pragma once
//Contains all draw functions, handles minimum logic, only cares about actual rendering (decsisions about what should be rendered is mainly handled by the game manager).
class DrawManager
{
public:
	void UI() const;
	void MainMenuScreen() const;
	void HighScoreScreen() const;
	void GameScreen() const;
	void SplashScreen() const;
	void HowToPlayScreen() const;
	void Aliens() const;
	void AlienColliders() const;
	void ShieldColliders() const;
};
extern DrawManager Draw;