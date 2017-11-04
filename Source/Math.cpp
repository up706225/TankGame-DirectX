#include "gameclass.h" 
#include <DirectXMath.h>
//Function converts 'float a' from degrees to radian
float radianMath(float a)
{
	float newRadian;
	newRadian = a * 3.14159265359f / 180;
	return  newRadian;
}
//Function converts 'float a' from radian to degrees
float angleMath(float a)
{
	float newAngle;
	newAngle = a * 180 / 3.14159265359f;
	return  newAngle;
}

//Function works out the distance between two points
float distanceMath(float a, float b, float x, float y)
{

	return  sqrt((a - x)*(a - x) + (b - y)*(b - y));
}

bool isCollision(float px, float py, float bx, float by, float bWidth, float bHeight, float bAngle)
{
	// convert angle to radians...
	//bAngle *= DEGTORAD;

	// "de-rotate" point...
	float newX = bx + (px - bx) * cos(-bAngle) - (py - by) * sin(-bAngle);
	float newY = by + (px - bx) * sin(-bAngle) + (py - by) * cos(-bAngle);

	// check if it would be inside a "straight" version of the bounding box...
	if ((newX >= (bx - (bWidth))) && (newX <= (bx + (bWidth))) && (newY >= (by - (bHeight))) && (newY <= (by + (bHeight))))
	{
		return true;
	}
	else
	{
		return false;
	}

}