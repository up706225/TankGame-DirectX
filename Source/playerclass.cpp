////////////////////////////////////////////////////////////////////////////////
// Filename: Player.cpp
////////////////////////////////////////////////////////////////////////////////
#include "playerclass.h"

playerClass::playerClass()
{

	xPos = 0.0f;
	yPos = 0.0f;
	xSpeed = 0.0f;
	ySpeed = 0.0f;

	tankHeight = 0.0f;
	tankWidth = 0.0f;

	rotation = 0.0f;
	leftSpeed = 0.0f;
	rightSpeed = 0.0f;

	turretRotation = 0.0f;
	canFire = true;
	reload = false;

	upPressed = false;
	downPressed = false;
	leftPressed = false;
	rightPressed = false;
	
	turretLeft = false;
	turretRight = false;
	fireNormal = false;
	fireSpecial = false;
	fireGrenade = false;
	hasSpecial = false;
	hasGrenade = false;
}


