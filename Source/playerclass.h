////////////////////////////////////////////////////////////////////////////////
// Filename: playerClass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _PLAYERCLASS_H_
#define _PLAYERCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <directxmath.h>
#include <vector> 
#include "bulletclass.h"	


using namespace DirectX;
using namespace std;

class playerClass
{
public:
	playerClass();		// the constructor

	float xPos;			// x position
	float yPos;			// y position
	float rotation;
	float turretRotation;
	float xSpeed;		// x speed
	float ySpeed;		// y speed

	float tankHeight;
	float tankWidth;

	float leftSpeed;// left rotation speed
	float rightSpeed; // rigght rotation speed

	bool upPressed;		// forward (up key pushed)
	bool downPressed;	// reverse (down key pushed)
	bool leftPressed;	// turn left (left key pushed)
	bool rightPressed;  // turn right (rigght key pushed)
	bool hasSpecial;
	bool hasGrenade;
	bool turretLeft;	//turret left rotation (turret left key)
	bool turretRight;	//turret right rotation (turret right key)

	bool fireNormal;	//fire normal bullets (space bar pushed)
	bool fireSpecial;	//fire special bullets
	bool fireGrenade;
	bool canFire;		//can tank fire (disables firing so tank can be reloaded, etc.)
	bool reload;		//tank reload (enables canFire)
	bool sheild;
	std::vector<bulletInfo> bulletArray;

};

#endif