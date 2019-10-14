#include <string>
#pragma once
//Sprite that will be used to store the game logo on the main menu and splash screen.
extern int MainMenuSprite;

//Class to reperesent the selections in the main menu screen. Comes equipped with an indicating icon to show which option the player is currently on.
class MainMenuSelector
{
	public:
	MainMenuSelector();

	float GetX() const;
	float GetY() const;
	void SetY(float a_fCenterY);

	int GetSprite() const;
	void SetSprite(std::string a_sSprite);

	void MoveUp();
	void MoveDown();
	void Select() const;

	private:
	const float fCenterX = 800.0f;
	float fCenterY;
	int iSprite;
};

//Y co-ordinates the main menu selector can be
enum MENUOPTIONS_Y_COORDS 
{
	OPTION_PLAY = 520,
	OPTION_HIGHSCORES = 470,
	OPTION_HOWTOPLAY = 420,
	OPTION_EXIT = 370,
	MENUOPTIONS_Y_COORDS_COUNT
};

extern MainMenuSelector mainmenuselector;