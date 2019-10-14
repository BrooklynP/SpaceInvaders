#include <string>
#pragma once

//Handles most logic in the game.
class GameManager
{
public:
	//Game loop functions
	void TakeUserInput() const;
	void Update(float a_g_fDeltaSum) const;
	void DrawCurrentScreen() const;

	//initialisers
	void CreateGame() const;
	void CreateShields() const;
	void CreateWave() const;

	//cleanup
	void DeleteShields() const;
	void DeleteWave() const;

	//Descision Functions
	void ShouldEnemyShoot() const;
	void CheckAllAliensDead() const;
	void CheckAliensAtYBoundary() const;
	void EnemyBulletCollisionDetection() const;
	void EnemyBodyCollisionWithShieldsDetection() const;
	void PlayerBulletCollisionDetection() const;
	void CheckAliensAtFloor() const;

	//Updates the entire wave of aliens
	void UpdateAliens(float a_g_fDeltaSum) const;
	void MoveAliensX() const;
	void MoveAliensY() const;

	//Manages the shields
	void ImageShield() const;
	void HitShield(std::string a_sShooter, int a_iShield, int a_iY, int a_iX) const;
};
extern GameManager gamemanager;

struct GameSettings {
public:
	//DebugSettings
	bool ShouldDrawHitBoxes() const { return DrawHitBoxes; }		//Hitboxes for every game object
	bool ShouldDrawXBoundaries() const { return DrawXBoundaries; }	//Boundaries that the game objects must stay within.
	bool ShouldDrawYBoundary() const { return DrawYBoundary; }
	bool ShieldImagingOn() const { return ShieldImaging; }		//Displays an image of which shield pieces are active in the console.
private:
	bool DrawXBoundaries = false;
	bool DrawYBoundary = false;
	bool DrawHitBoxes = false;
	bool ShieldImaging = false;
	bool SoundOn = false;
};
extern GameSettings Settings;

enum GAME_STATE {
	SPLASH_SCREEN,
	MAIN_MENU,
	HIGH_SCORES,
	PLAY,
	LOSE_LIFE,
	PAUSE,
	GAME_OVER,
	HOW_TO_PLAY,
	GAME_STATE_COUNT
};
