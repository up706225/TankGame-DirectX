////////////////////////////////////////////////////////////////////////////////
// Filename: gameClass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "gameclass.h"


GameClass::GameClass()
{

	frameStart = 0;
	frameEnd = 0;
	delta = 0;

	// Set the number of instances in the array.
	m_instanceCount = NUMBER_OF_PLAYERS;

	// Create the instance array.
	instances = new InstanceType[m_instanceCount];
}

GameClass::GameClass(const GameClass& other)
{
}
GameClass::~GameClass()
{
	for (int i = 0; i < NUMBER_OF_PLAYERS; i++)
	{
		delete playerArray[i];
		playerArray[i] = NULL;
	}

	// then delete the array itself and set its pointer to NULL
	delete[] playerArray;
	playerArray = NULL;

}
void GameClass::Initialize()
{
	playerArray = new playerClass*[NUMBER_OF_PLAYERS];

	// for each player in the array, allocate memory for that player
	for (int i = 0; i < NUMBER_OF_PLAYERS; i++)
	{
		playerArray[i] = new playerClass;
	}
	playerArray[0]->sheild = true;
	playerArray[1]->sheild = true;
	playerArray[0]->xPos = PLAYER1XPOS; //moves player 1 left
	playerArray[0]->yPos = PLAYER1YPOS; //moves player 1 up
	playerArray[1]->xPos = PLAYER2XPOS; //moves player 2 right
	playerArray[1]->yPos = PLAYER2YPOS; //moves player 2 down
	playerArray[0]->rotation = radianMath(PLAYER1ROTATION);
	playerArray[1]->rotation = radianMath(PLAYER2ROTATION);
	playerArray[0]->turretRotation = PLAYERTURRETROTATION;
	playerArray[1]->turretRotation = PLAYERTURRETROTATION;
	playerArray[0]->hasSpecial = SPECIAL_MODE;
	playerArray[1]->hasSpecial = SPECIAL_MODE;
	playerArray[0]->hasGrenade = SPECIAL_MODE;
	playerArray[1]->hasGrenade = SPECIAL_MODE;
	delta = IDEAL_DELTA;
}
