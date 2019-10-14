#pragma once
const int gc_iWaveWidth = 11; //Number of enemies wide each row will be
const int gc_iWaveDepth = 5; //How many rows will be in each wave
const int gc_iMaxEnemyBullets = 3;
const float gc_fSplashScreenShowTime = 3.0f;
const float gc_fGameOverMsgShowTime = 3.0f;
const float gc_fLeftYBound = 50;
const float gc_fRightYBound = 974;
const float gc_fFloorHeight = 100.0f;
const float gc_fHeightIncrement = 75.0f; //How tall the rows are for sprite positioning. Means that all aliens and the player will stay on a grid.

extern int HowToPage1;
extern int HowToPage2;
extern int HowToPage3;

extern int g_iGameState;	//Uses enum from gamemanager.h
extern int g_iEnemyAliensAlive;
extern int HowToPlayPage; //what page the player is on on the how to play screen
extern float g_fGameSpeed;
extern float g_fDeltaSum;