////////////////////////////////////////////////////////////////////////////////
// Filename: gameClass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GAMECLASS_H_
#define _GAMECLASS_H_

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "playerclass.h"
#include "windows.h"
using namespace std;
#define IDEAL_FPS 30
#define IDEAL_DELTA (1000 / IDEAL_FPS)
#define SCREEN_WIDTH_REAL 1280
#define SCREEN_HEIGHT_REAL 720

// some player constants
#define ROTATION_SPEED	0.01f //tank rotation speed
#define MAX_ROTATION_SPEED	0.03f //max rotation speed
#define TURRET_SPEED	0.04f //turret rotation speed
#define MOVE_SPEED 1.0f //tank move speed
#define MAX_SPEED 6.0f //tank max speed
#define MAX_REVERSE -MAX_SPEED //tank max reverse speed
#define FRICTION 0.2f //friction in the world
#define BULLET_SPEED 8.0f //bullets move speed
#define NUMBER_OF_PLAYERS 2	//max number of players
#define NUMBER_OF_PICKUPS 4 //number of total pickups
#define MAX_NUMBER_OF_PICKUPS 1 //max number to load at once
#define SPEEDBOOST 0.02f //speedboost value
#define SPEEDBOOST_TIME 2500.0f //speedboost time
#define SHEILDBOOST_TIME 2500.0f //sheild time
#define SCREEN_WIDTH (SCREEN_WIDTH_REAL/2)
#define SCREEN_HEIGHT (SCREEN_HEIGHT_REAL/2)
#define NORMAL_FIRE_LIFE 6000.0f //normal shot life
#define SPECIAL_FIRE_LIFE 3000.0f //special shot life
#define GRENADE_FIRE_LIFE 1000.0f //grenade life
#define RELOAD_TIME 250.0f //time to reload new bullet
// player position 
#define PLAYER1XPOS (-SCREEN_WIDTH + 100)//-500.0f //default x for player1
#define PLAYER1YPOS (SCREEN_HEIGHT - 75) //default y for player1
#define PLAYER2XPOS (SCREEN_WIDTH - 100) //default x for player 2
#define PLAYER2YPOS (-SCREEN_HEIGHT + 75) //default y for player 2
#define PLAYER1ROTATION 0 //default rotation for player 1
#define PLAYER2ROTATION 180  //default rotation for player 2
#define PLAYERTURRETROTATION 0.0f //default rotation of turret for both players
#define SPECIAL_MODE true //if you want to turn powerups on/off, set this to true/false
float radianMath(float a); //forward declaration for radianMath function
////////////////////////////////////////////////////////////////////////////////
// Class name: GameClass
////////////////////////////////////////////////////////////////////////////////

class GameClass
{
public:

	GameClass();
	GameClass(const GameClass&);
	~GameClass();
	struct InstanceType
	{
		XMFLOAT3 position;
		XMFLOAT4 color;
	};
	InstanceType* instances;
	void Initialize();

	//may not use
	DWORD frameStart;
	DWORD frameEnd;
	DWORD delta;
	DWORD previousTime;
	int m_vertexCount, m_instanceCount;
	playerClass **playerArray;
};

#endif