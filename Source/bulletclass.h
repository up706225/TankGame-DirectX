#ifndef BULLET_H_
#define BULLET_H_

class bulletInfo //creates the bullet class 
{
public:
	bulletInfo();

	float startTime; //time bullet was created
	float bulletLife;

	float xPos; //bullets x position
	float yPos; //bullets y position

	float bulletWidth;
	float bulletHeight;

	float xSpeed; //speed bullet is traveling at
	float ySpeed;

	float bulletRotation; //rotation bullet is traveling on
};

#endif /* BULLET_H_ */