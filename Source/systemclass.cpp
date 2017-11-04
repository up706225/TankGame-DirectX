////////////////////////////////////////////////////////////////////////////////
// Filename: systemclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "systemclass.h"


SystemClass::SystemClass()
{
	m_Input = 0;
	m_Graphics = 0;

}


SystemClass::SystemClass(const SystemClass& other)
{
}


SystemClass::~SystemClass()
{
}


bool SystemClass::Initialize()
{
	int screenWidth, screenHeight;
	bool result;


	
	
	// Initialize the width and height of the screen to zero before sending the variables into the function.
	screenWidth = 0;
	screenHeight = 0;

	// Initialize the windows api.
	InitializeWindows(screenWidth, screenHeight);

	// Create the input object.  This object will be used to handle reading the keyboard input from the user.
	m_Input = new InputClass;
	if(!m_Input)
	{
		return false;
	}

	// Initialize the input object.
	m_Input->Initialize();

	// Create the graphics object.  This object will handle rendering all the graphics for this application.
	m_Graphics = new GraphicsClass;
	if(!m_Graphics)
	{
		return false;
	}

	// Initialize the graphics object.
	result = m_Graphics->Initialize(screenWidth, screenHeight, m_hwnd, m_Graphics->m_Game);
	if(!result)
	{
		return false;
	}
	
	return true;
}


void SystemClass::Shutdown()
{
	// Release the graphics object.
	if(m_Graphics)
	{
		m_Graphics->Shutdown();
		delete m_Graphics;
		m_Graphics = 0;
	}

	// Release the input object.
	if(m_Input)
	{
		delete m_Input;
		m_Input = 0;
	}

	// Shutdown the window.
	ShutdownWindows();
	
	return;
}


void SystemClass::Run()
{
	MSG msg;
	bool done, result;
	deltaAdjustment = (float)m_Graphics->m_Game->delta / IDEAL_DELTA;

	// Initialize the message structure.
	ZeroMemory(&msg, sizeof(MSG));
	
	// Loop until there is a quit message from the window or the user.
	done = false;
	while(!done)
	{
		
		// Handle the windows messages.
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// If windows signals to end the application then exit out.
		if(msg.message == WM_QUIT)
		{
			done = true;
		}
		else
		{
			// Otherwise do the frame processing.
			result = Frame();
			if(!result)
			{
				done = true;
			}
		}

	}

	return;
}

bool SystemClass::Frame()
{
	m_Graphics->m_Game->frameStart = GetTickCount();
	bool result;


	// Check if the user pressed escape and wants to exit the application.
	if (m_Input->IsKeyDown(VK_ESCAPE))
	{
		return false;
	}

	//key checks, if the key is pressed/released, it will flip a corresponding bool
	//PLAYER 1
	if (!m_Input->IsKeyDown(0x51)) //Turn Turret Left (player 1 = Q))
	{
		m_Graphics->m_Game->playerArray[0]->turretLeft = false;
	}
	if (m_Input->IsKeyDown(0x51)) //Turn Turret Left (player 1 = Q))
	{
		m_Graphics->m_Game->playerArray[0]->turretLeft = true;
	}
	if (!m_Input->IsKeyDown(0x45)) //Turn Turret Right (player 1 = E))
	{
		m_Graphics->m_Game->playerArray[0]->turretRight = false;
	}
	if (m_Input->IsKeyDown(0x45)) //Turn Turret Right (player 1 = E))
	{
		m_Graphics->m_Game->playerArray[0]->turretRight = true;
	}
	if (!m_Input->IsKeyDown(0x57)) //Forward (player 1 = W)
	{
		m_Graphics->m_Game->playerArray[0]->upPressed = false;
	}
	if (m_Input->IsKeyDown(0x57)) //Forward (player 1 = W)
	{
		m_Graphics->m_Game->playerArray[0]->upPressed = true;
	}
	if (!m_Input->IsKeyDown(0x41)) //Turn left (player 1 = A)
	{
		m_Graphics->m_Game->playerArray[0]->leftPressed = false;
	}
	if (m_Input->IsKeyDown(0x41)) //Turn left (player 1 = A)
	{
		m_Graphics->m_Game->playerArray[0]->leftPressed = true;
	}
	if (!m_Input->IsKeyDown(0x53)) //backwards (player 1 = S)
	{
		m_Graphics->m_Game->playerArray[0]->downPressed = false;
	}
	if (m_Input->IsKeyDown(0x53)) //backwards (player 1 = S)
	{
		m_Graphics->m_Game->playerArray[0]->downPressed = true;
	}
	if (!m_Input->IsKeyDown(0x44)) //Turn Right (player 1 = D)
	{
		m_Graphics->m_Game->playerArray[0]->rightPressed = false;
	}
	if (m_Input->IsKeyDown(0x44)) //Turn Right (player 1 = D)
	{
		m_Graphics->m_Game->playerArray[0]->rightPressed = true;
	}
	if (!m_Input->IsKeyDown(VK_SPACE)) //Shoot (player 1 = SPACE)
	{
		m_Graphics->m_Game->playerArray[0]->fireNormal = false;
	}
	if (m_Input->IsKeyDown(VK_SPACE)) //Shoot (player 1 = SPACE)
	{
		m_Graphics->m_Game->playerArray[0]->fireNormal = true;
	}
	if (!m_Input->IsKeyDown(0x31)) //Shoot special(player 1 = 1 key)
	{
		m_Graphics->m_Game->playerArray[0]->fireSpecial = false;
	}
	if (m_Input->IsKeyDown(0x31) && m_Graphics->m_Game->playerArray[0]->hasSpecial) //Shoot special(player 1 = 1 key)
	{
		m_Graphics->m_Game->playerArray[0]->fireSpecial = true;
		m_Graphics->m_Game->playerArray[0]->hasSpecial = false;
	}
	if (!m_Input->IsKeyDown(0x32)) //Shoot Grenade (player 1 = 2 key)
	{
		m_Graphics->m_Game->playerArray[0]->fireGrenade = false;
	}
	if (m_Input->IsKeyDown(0x32) && m_Graphics->m_Game->playerArray[0]->hasGrenade) //Shoot Grenade(player 1 = 2 key)
	{
		m_Graphics->m_Game->playerArray[0]->fireGrenade = true;
		m_Graphics->m_Game->playerArray[0]->hasGrenade = false;
	}
	if (!m_Input->IsKeyDown(0x52)) //Reload (player 1 = R)
	{

	}
	if ((m_Input->IsKeyDown(0x52)) && (!m_Input->IsKeyDown(VK_SPACE))) //Reload (player 1 = R)
	{
		m_Graphics->m_Game->playerArray[0]->canFire = true;
	}
	//PLAYER 2
	if (!m_Input->IsKeyDown(VK_NUMPAD7)) //Turn Turret Left (player 2 = NUM7))
	{
		m_Graphics->m_Game->playerArray[1]->turretLeft = false;
	}
	if (m_Input->IsKeyDown(VK_NUMPAD7)) //Turn Turret Left (player 2 = NUM7))
	{
		m_Graphics->m_Game->playerArray[1]->turretLeft = true;
	}
	if (!m_Input->IsKeyDown(VK_NUMPAD9)) //Turn Turret Right (player 2 = NUM9))
	{
		m_Graphics->m_Game->playerArray[1]->turretRight = false;
	}
	if (m_Input->IsKeyDown(VK_NUMPAD9)) //Turn Turret Right (player 2 = NUM9))
	{
		m_Graphics->m_Game->playerArray[1]->turretRight = true;
	}
	if (!m_Input->IsKeyDown(VK_NUMPAD8)) //Forward (player 2 = NUM8)
	{
		m_Graphics->m_Game->playerArray[1]->upPressed = false;
	}
	if (m_Input->IsKeyDown(VK_NUMPAD8)) //Forward (player 2 = NUM8)
	{
		m_Graphics->m_Game->playerArray[1]->upPressed = true;
	}
	if (!m_Input->IsKeyDown(VK_NUMPAD4)) //Turn left (player 2 = NUM4)
	{
		m_Graphics->m_Game->playerArray[1]->leftPressed = false;
	}
	if (m_Input->IsKeyDown(VK_NUMPAD4)) //Turn left (player 2 = NUM4)
	{
		m_Graphics->m_Game->playerArray[1]->leftPressed = true;
	}
	if (!m_Input->IsKeyDown(VK_NUMPAD5)) //backwards (player 2 = NUM5)
	{
		m_Graphics->m_Game->playerArray[1]->downPressed = false;
	}
	if (m_Input->IsKeyDown(VK_NUMPAD5)) //backwards (player 2 = NUM5)
	{
		m_Graphics->m_Game->playerArray[1]->downPressed = true;
	}
	if (!m_Input->IsKeyDown(VK_NUMPAD6)) //Turn Right (player 2 = NUM6)
	{
		m_Graphics->m_Game->playerArray[1]->rightPressed = false;
	}
	if (m_Input->IsKeyDown(VK_NUMPAD6)) //Turn Right (player 2 = NUM6)
	{
		m_Graphics->m_Game->playerArray[1]->rightPressed = true;
	}
	if (!m_Input->IsKeyDown(VK_NUMPAD0)) //Shoot (player 2 = NUM0)
	{
		m_Graphics->m_Game->playerArray[1]->fireNormal = false;
	}
	if (m_Input->IsKeyDown(VK_NUMPAD0)) //Shoot (player 2 = NUM0)
	{
		m_Graphics->m_Game->playerArray[1]->fireNormal = true;
	}

	if (!m_Input->IsKeyDown(VK_NUMPAD2)) //Shoot special(player 2 = NUM2)
	{
		m_Graphics->m_Game->playerArray[1]->fireSpecial = false;
	}
	if (m_Input->IsKeyDown(VK_NUMPAD2) && m_Graphics->m_Game->playerArray[1]->hasSpecial) //Shoot special(player 2 = NUM2)
	{
		m_Graphics->m_Game->playerArray[1]->fireSpecial = true;
		m_Graphics->m_Game->playerArray[1]->hasSpecial = false;
	}
	if (!m_Input->IsKeyDown(VK_NUMPAD3)) //Shoot Grenade (player 2 = NUM3)
	{
		m_Graphics->m_Game->playerArray[1]->fireGrenade = false;
	}
	if (m_Input->IsKeyDown(VK_NUMPAD3) && m_Graphics->m_Game->playerArray[1]->hasGrenade) //Shoot Grenade(player 2 = NUM3)
	{
		m_Graphics->m_Game->playerArray[1]->fireGrenade = true;
		m_Graphics->m_Game->playerArray[1]->hasGrenade = false;
	}
	if (!m_Input->IsKeyDown(VK_NUMPAD1)) //Reload (player 2 = NUM1)
	{

	}
	if ((m_Input->IsKeyDown(VK_NUMPAD1)) && (!m_Input->IsKeyDown(VK_NUMPAD0))) //Reload (player 2 = NUM1)
	{
		m_Graphics->m_Game->playerArray[1]->canFire = true;
	}
	//controls the tanks movement 
	for (int i = 0; i < NUMBER_OF_PLAYERS; i++)
	{
		//checks if tanks is in the game
		if (m_Graphics->m_Game->playerArray[i]->xPos > SCREEN_WIDTH || m_Graphics->m_Game->playerArray[i]->xPos < -SCREEN_WIDTH)
		{
			m_Graphics->m_Game->playerArray[i]->xPos = (-m_Graphics->m_Game->playerArray[i]->xPos);

		}
		if (m_Graphics->m_Game->playerArray[i]->yPos > SCREEN_HEIGHT || m_Graphics->m_Game->playerArray[i]->yPos < -SCREEN_HEIGHT)
		{
			m_Graphics->m_Game->playerArray[i]->yPos = (-m_Graphics->m_Game->playerArray[i]->yPos);

		}
		//if left is pressed
		if (m_Graphics->m_Game->playerArray[i]->leftPressed)
		{
			if (m_Graphics->m_Game->playerArray[i]->leftSpeed <= MAX_ROTATION_SPEED * deltaAdjustment)//checks that left is pressed and that the rotation speed doesnt exceed the max rotation speed
			{
				m_Graphics->m_Game->playerArray[i]->leftSpeed += (ROTATION_SPEED * deltaAdjustment);
			}
		}
		//if right is pressed
		if (m_Graphics->m_Game->playerArray[i]->rightPressed)
		{
			if (m_Graphics->m_Game->playerArray[i]->rightSpeed <= MAX_ROTATION_SPEED * deltaAdjustment)//checks that left is pressed and that the rotation speed doesnt exceed the max rotation speed
			{
				m_Graphics->m_Game->playerArray[i]->rightSpeed += (ROTATION_SPEED * deltaAdjustment);
			}
		}
		//if turret left is pressed
		if (m_Graphics->m_Game->playerArray[i]->turretLeft)
		{
			m_Graphics->m_Game->playerArray[i]->turretRotation += (TURRET_SPEED * deltaAdjustment); //adds left rotation to the turret

		}
		//if turret right is pressed
		if (m_Graphics->m_Game->playerArray[i]->turretRight)
		{
			m_Graphics->m_Game->playerArray[i]->turretRotation -= (TURRET_SPEED * deltaAdjustment); //adds left rotation to the turret

		}
		//rotation config
		if (m_Graphics->m_Game->playerArray[i]->rotation > 360.0f) //Make sure that rotation stays under 360 degrees (so when it gets to +360 degrees, it takes away by 360)
		{
			m_Graphics->m_Game->playerArray[i]->rotation -= 360.0f; //sets rotation to 0
		}
		if (m_Graphics->m_Game->playerArray[i]->turretRotation > 360.0f) //If statement to make sure that rotation stays under 360 degrees (so when it gets to +360 degrees, it takes away by 360)
		{
			m_Graphics->m_Game->playerArray[i]->turretRotation -= 360.0f; //sets turret rotation to 0
		}
		//if forward is pressed
		if (m_Graphics->m_Game->playerArray[i]->upPressed)
		{

		
			m_Graphics->m_Game->playerArray[i]->xSpeed += (MOVE_SPEED * deltaAdjustment); //adds forward movement to xSpeed
			m_Graphics->m_Game->playerArray[i]->ySpeed += (MOVE_SPEED * deltaAdjustment); //adds forward movement to ySpeed

		}
		//if backwards is pressed
		if (m_Graphics->m_Game->playerArray[i]->downPressed)
		{

			
			m_Graphics->m_Game->playerArray[i]->xSpeed -= (MOVE_SPEED * deltaAdjustment); //adds forward movement to xSpeed
			m_Graphics->m_Game->playerArray[i]->ySpeed -= (MOVE_SPEED * deltaAdjustment); //adds forward movement to ySpeed

		}
		//applies the speed if the speed is under/equal to the max speed
		if (m_Graphics->m_Game->playerArray[i]->xSpeed <= MAX_SPEED * deltaAdjustment) //checks the xSpeed is under the max speed
		{
			m_Graphics->m_Game->playerArray[i]->xSpeed += (MOVE_SPEED * deltaAdjustment); //adds forward movement to xSpeed
		}
		if (m_Graphics->m_Game->playerArray[i]->ySpeed <= MAX_SPEED * deltaAdjustment)  //checks the ySpeed is under the max speed
		{
			m_Graphics->m_Game->playerArray[i]->ySpeed += (MOVE_SPEED * deltaAdjustment); //adds forward movement to ySpeed
		}
		if (m_Graphics->m_Game->playerArray[i]->xSpeed >= MAX_REVERSE * deltaAdjustment) //checks the xSpeed is under the max reverse speed
		{
			m_Graphics->m_Game->playerArray[i]->xSpeed -= (MOVE_SPEED * deltaAdjustment); //adds forward movement to xSpeed
		}
		if (m_Graphics->m_Game->playerArray[i]->ySpeed >= MAX_REVERSE * deltaAdjustment) //checks the ySpeed is under the max reverse speed
		{
			m_Graphics->m_Game->playerArray[i]->ySpeed -= (MOVE_SPEED * deltaAdjustment); //adds forward movement to ySpeed
		}
		float radian = radianMath(m_Graphics->m_Game->playerArray[i]->rotation); // sends rotation to radianMath function to work out the radian
		float turretRadian = radianMath(m_Graphics->m_Game->playerArray[i]->turretRotation);
		int t = 0;
		if (i == 0)
		{
			t = 1;
		}
		if (isCollision(m_Graphics->m_Game->playerArray[i]->xPos, m_Graphics->m_Game->playerArray[i]->yPos, m_Graphics->m_Game->playerArray[t]->xPos, m_Graphics->m_Game->playerArray[t]->yPos, m_Graphics->m_Game->playerArray[i]->tankWidth, m_Graphics->m_Game->playerArray[i]->tankHeight,radian)) //checks if tanks are coliding
		{
			m_Graphics->m_Game->playerArray[i]->leftSpeed = -m_Graphics->m_Game->playerArray[i]->leftSpeed; //if they are colliding, make leftSpeed negative leftSpeed (so player moves in oposite direction)
			m_Graphics->m_Game->playerArray[i]->rightSpeed = -m_Graphics->m_Game->playerArray[i]->rightSpeed; //if they are colliding, make rightSpeed negative rightSpeed (so player moves in oposite direction)
		}
		else
		{
			//applies the left/right speed to the rotation
			m_Graphics->m_Game->playerArray[i]->leftSpeed -= m_Graphics->m_Game->playerArray[i]->leftSpeed * (FRICTION * deltaAdjustment); //friction for left rotation (used in acceleration/deceleration)
			m_Graphics->m_Game->playerArray[i]->rightSpeed -= m_Graphics->m_Game->playerArray[i]->rightSpeed * (FRICTION * deltaAdjustment); //friction for right rotation (used in acceleration/deceleration)
		}
		m_Graphics->m_Game->playerArray[i]->rotation += m_Graphics->m_Game->playerArray[i]->leftSpeed; //rotates the tank left
		m_Graphics->m_Game->playerArray[i]->rotation -= m_Graphics->m_Game->playerArray[i]->rightSpeed; //rotates the tank right
		if (isCollision(m_Graphics->m_Game->playerArray[t]->xPos, m_Graphics->m_Game->playerArray[t]->yPos, m_Graphics->m_Game->playerArray[i]->xPos, m_Graphics->m_Game->playerArray[i]->yPos, m_Graphics->m_Game->playerArray[i]->tankWidth, m_Graphics->m_Game->playerArray[i]->tankHeight, radian)) //checks if tanks are coliding
		{
			m_Graphics->m_Game->playerArray[i]->xSpeed = -m_Graphics->m_Game->playerArray[i]->xSpeed; //if they are colliding, make xSpeed negative xSpeed (so player moves in oposite direction)
			m_Graphics->m_Game->playerArray[i]->ySpeed = -m_Graphics->m_Game->playerArray[i]->ySpeed; //if they are colliding, make ySpeed negative ySpeed (so player moves in oposite direction)
		}
		else
		{
			//applies the forwards/backwrads movement to the tank
			m_Graphics->m_Game->playerArray[i]->xSpeed -= m_Graphics->m_Game->playerArray[i]->xSpeed * (FRICTION * deltaAdjustment); //applies friction to xSpeed (used in acceleration/deceleration)
			m_Graphics->m_Game->playerArray[i]->ySpeed -= m_Graphics->m_Game->playerArray[i]->ySpeed * (FRICTION * deltaAdjustment); //applies friction to ySpeed (used in acceleration/deceleration).
		}
		//math used for turning radians into degrees, currently not used.

		//applies the rotation to the tank
		m_Graphics->m_Game->playerArray[i]->xPos += ((m_Graphics->m_Game->playerArray[i]->xSpeed) * (float)cos(m_Graphics->m_Game->playerArray[i]->rotation)); //movement on x - forward and reverse
		m_Graphics->m_Game->playerArray[i]->yPos += ((m_Graphics->m_Game->playerArray[i]->ySpeed) * (float)sin(m_Graphics->m_Game->playerArray[i]->rotation)); //movement on y - forward and reverse

		if (m_Graphics->m_Game->playerArray[i]->canFire && (m_Graphics->m_Game->playerArray[i]->fireNormal || m_Graphics->m_Game->playerArray[i]->fireSpecial || m_Graphics->m_Game->playerArray[i]->fireGrenade))
		{
			int totalBullets;
			float bulletLife;
			float shootDistance;
			float grenadeAngle = 0.0f; //values set here are used for working out normal bullets (special bullets edit these values, this saves having the bullets section written 3 times)
			float specialAngle = 0.0f;
			if (m_Graphics->m_Game->playerArray[i]->fireNormal)
			{
				totalBullets = 1;
				bulletLife = NORMAL_FIRE_LIFE;
				shootDistance = 45.0f;
			}
			if (m_Graphics->m_Game->playerArray[i]->fireSpecial) //values here are for special bullets
			{
				shootDistance = 120.0f;
				totalBullets = 5;
				bulletLife = SPECIAL_FIRE_LIFE;
			}
			if (m_Graphics->m_Game->playerArray[i]->fireGrenade)//values here are for grenades 
			{
				shootDistance = 700.0f;
				grenadeAngle = 30.0;
				totalBullets = 18;
				bulletLife = SPECIAL_FIRE_LIFE;
			}
			for (int s = 0; s < totalBullets; s++) //runs through the total bullets required for the shot
			{
				if (m_Graphics->m_Game->playerArray[i]->fireSpecial) //if special, it gives the angle a specific value depending on what the value of s is in the loop
				{
					if (s == 1)
					{
						specialAngle = radianMath(10.0f);
					}
					if (s == 2)
					{
						specialAngle = radianMath(-10.0f);
					}
					if (s == 3)
					{
						specialAngle = radianMath(20.0f);
					}
					if (s == 4)
					{
						specialAngle = radianMath(-20.0f);
					}
				}
				if (m_Graphics->m_Game->playerArray[i]->fireGrenade) //if grenade, it takes the angle set above and adds the value below each time the loop runs
				{
					grenadeAngle = grenadeAngle + radianMath(30.0f);
				}
			

				m_Graphics->m_Game->playerArray[i]->canFire = false; //sets it so that player cannot fire
				bulletInfo tempBullet; // creates temp bullet info for transfering info about the bullet (using tanks info)
				tempBullet.xPos = m_Graphics->m_Game->playerArray[i]->xPos + (shootDistance * (float)cos(m_Graphics->m_Game->playerArray[i]->rotation + m_Graphics->m_Game->playerArray[i]->turretRotation)); //sets xpos for temp bullet
				tempBullet.yPos = m_Graphics->m_Game->playerArray[i]->yPos + (shootDistance * (float)sin(m_Graphics->m_Game->playerArray[i]->rotation + m_Graphics->m_Game->playerArray[i]->turretRotation)); //sets ypos for temp bullet
				tempBullet.xSpeed = (BULLET_SPEED * deltaAdjustment); //sets temp bullets speed using the speed defined in BULLET_SPEED#
				tempBullet.ySpeed = (BULLET_SPEED * deltaAdjustment); //sets temp bullets speed using the speed defined in BULLET_SPEED
				tempBullet.bulletRotation = (m_Graphics->m_Game->playerArray[i]->turretRotation + m_Graphics->m_Game->playerArray[i]->rotation + grenadeAngle + specialAngle);
				m_Graphics->m_Game->previousTime = GetTickCount();
				tempBullet.startTime = GetTickCount();
				tempBullet.bulletLife = bulletLife;
				m_Graphics->m_Game->playerArray[i]->bulletArray.push_back(tempBullet); //adds the temp bullet info to the bulletArray
			}
		}

		for (unsigned j = 0; j < m_Graphics->m_Game->playerArray[i]->bulletArray.size(); j++) // for loop so the following translations/rotations apply to all bullets
		{
			float bulletRadian = radianMath(m_Graphics->m_Game->playerArray[i]->bulletArray[j].bulletRotation);
			int t = 0;
			if (i == 0)
			{
				t = 1;
			}
			if (isCollision(m_Graphics->m_Game->playerArray[i]->bulletArray[j].xPos, m_Graphics->m_Game->playerArray[i]->bulletArray[j].yPos, m_Graphics->m_Game->playerArray[i]->xPos, m_Graphics->m_Game->playerArray[i]->yPos, m_Graphics->m_Game->playerArray[i]->tankWidth / 3, m_Graphics->m_Game->playerArray[i]->tankHeight / 3, m_Graphics->m_Game->playerArray[i]->bulletArray[j].bulletRotation) || isCollision(m_Graphics->m_Game->playerArray[i]->bulletArray[j].xPos, m_Graphics->m_Game->playerArray[i]->bulletArray[j].yPos, m_Graphics->m_Game->playerArray[t]->xPos, m_Graphics->m_Game->playerArray[t]->yPos, m_Graphics->m_Game->playerArray[i]->tankWidth / 2, m_Graphics->m_Game->playerArray[i]->tankHeight / 2, m_Graphics->m_Game->playerArray[i]->bulletArray[j].bulletRotation))
			{
				m_Graphics->m_Game->playerArray[i]->bulletArray.erase(m_Graphics->m_Game->playerArray[i]->bulletArray.begin() + j); //deletes bullets after collision
				j--;
				if (m_Graphics->m_Game->playerArray[t]->sheild)
				{
					m_Graphics->m_Game->playerArray[t]->sheild = false;
				}
				else
				{
					m_Graphics->m_Game->playerArray[0]->xPos = PLAYER1XPOS; //moves player 1 left
					m_Graphics->m_Game->playerArray[0]->yPos = PLAYER1YPOS; //moves player 1 up
					m_Graphics->m_Game->playerArray[1]->xPos = PLAYER2XPOS; //moves player 2 right
					m_Graphics->m_Game->playerArray[1]->yPos = PLAYER2YPOS; //moves player 2 down
					m_Graphics->m_Game->playerArray[0]->rotation = radianMath(PLAYER1ROTATION);
					m_Graphics->m_Game->playerArray[1]->rotation = radianMath(PLAYER2ROTATION);
					m_Graphics->m_Game->playerArray[0]->turretRotation = PLAYERTURRETROTATION;
					m_Graphics->m_Game->playerArray[1]->turretRotation = PLAYERTURRETROTATION;
					m_Graphics->m_Game->playerArray[0]->canFire = true;
					m_Graphics->m_Game->playerArray[1]->canFire = true;
					m_Graphics->m_Game->playerArray[0]->sheild = true;
					m_Graphics->m_Game->playerArray[1]->sheild = true;
					m_Graphics->m_Game->playerArray[0]->hasSpecial = SPECIAL_MODE;
					m_Graphics->m_Game->playerArray[1]->hasSpecial = SPECIAL_MODE;
					m_Graphics->m_Game->playerArray[0]->hasGrenade = SPECIAL_MODE;
					m_Graphics->m_Game->playerArray[1]->hasGrenade = SPECIAL_MODE;
					m_Graphics->m_Game->playerArray[0]->bulletArray.clear();
					m_Graphics->m_Game->playerArray[1]->bulletArray.clear();
				}
			}
			else
			{
				{
					if (m_Graphics->m_Game->playerArray[i]->bulletArray[j].xSpeed > BULLET_SPEED * deltaAdjustment)
					{
						m_Graphics->m_Game->playerArray[i]->bulletArray[j].xSpeed = BULLET_SPEED * deltaAdjustment;
					}
					if (m_Graphics->m_Game->playerArray[i]->bulletArray[j].ySpeed > BULLET_SPEED * deltaAdjustment)
					{
						m_Graphics->m_Game->playerArray[i]->bulletArray[j].ySpeed = BULLET_SPEED * deltaAdjustment;
					}

					if (m_Graphics->m_Game->playerArray[i]->bulletArray[j].xPos > SCREEN_WIDTH || m_Graphics->m_Game->playerArray[i]->bulletArray[j].xPos < -SCREEN_WIDTH)
					{
						m_Graphics->m_Game->playerArray[i]->bulletArray[j].xPos = (-m_Graphics->m_Game->playerArray[i]->bulletArray[j].xPos);

					}
					if (m_Graphics->m_Game->playerArray[i]->bulletArray[j].yPos > SCREEN_HEIGHT || m_Graphics->m_Game->playerArray[i]->bulletArray[j].yPos < -SCREEN_HEIGHT)
					{
						m_Graphics->m_Game->playerArray[i]->bulletArray[j].yPos = (-m_Graphics->m_Game->playerArray[i]->bulletArray[j].yPos);
					}
					if (m_Graphics->m_Game->playerArray[i]->bulletArray[j].xSpeed == 0.0f && m_Graphics->m_Game->playerArray[i]->bulletArray[j].ySpeed == 0.0f)
					{
						m_Graphics->m_Game->playerArray[i]->bulletArray[j].ySpeed = BULLET_SPEED * deltaAdjustment;
						m_Graphics->m_Game->playerArray[i]->bulletArray[j].xSpeed = BULLET_SPEED * deltaAdjustment;
					}
					if ((GetTickCount() - m_Graphics->m_Game->playerArray[i]->bulletArray[j].startTime) > m_Graphics->m_Game->playerArray[i]->bulletArray[j].bulletLife)
					{
						m_Graphics->m_Game->playerArray[i]->bulletArray.erase(m_Graphics->m_Game->playerArray[i]->bulletArray.begin() + j);
						break;
					}

					m_Graphics->m_Game->playerArray[i]->bulletArray[j].xPos += (((m_Graphics->m_Game->playerArray[i]->bulletArray[j].xSpeed) * deltaAdjustment) * (float)cos(m_Graphics->m_Game->playerArray[i]->bulletArray[j].bulletRotation)); //uses the xPos set above to fire the bullet along the correct axis
					m_Graphics->m_Game->playerArray[i]->bulletArray[j].yPos += (((m_Graphics->m_Game->playerArray[i]->bulletArray[j].ySpeed) * deltaAdjustment) * (float)sin(m_Graphics->m_Game->playerArray[i]->bulletArray[j].bulletRotation)); //uses the yPos set above to fire the bullet along the correct axis

				}
			}
		}
}



	// Do the frame processing for the graphics object.
	result = m_Graphics->Frame();
	if(!result)
	{
		return false;
	}
	m_Graphics->m_Game->frameEnd = GetTickCount();
	m_Graphics->m_Game->delta = (m_Graphics->m_Game->frameEnd - m_Graphics->m_Game->frameStart);
	return true;
}


LRESULT CALLBACK SystemClass::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	switch(umsg)
	{
		// Check if a key has been pressed on the keyboard.
		case WM_KEYDOWN:
		{
			// If a key is pressed send it to the input object so it can record that state.
			m_Input->KeyDown((unsigned int)wparam);
			return 0;
		}

		// Check if a key has been released on the keyboard.
		case WM_KEYUP:
		{
			// If a key is released then send it to the input object so it can unset the state for that key.
			m_Input->KeyUp((unsigned int)wparam);
			return 0;
		}

		// Any other messages send to the default message handler as our application won't make use of them.
		default:
		{
			return DefWindowProc(hwnd, umsg, wparam, lparam);
		}
	}
}


void SystemClass::InitializeWindows(int& screenWidth, int& screenHeight)
{
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	int posX, posY;


	// Get an external pointer to this object.	
	ApplicationHandle = this;

	// Get the instance of this application.
	m_hinstance = GetModuleHandle(NULL);

	// Give the application a name.
	m_applicationName = L"Engine";

	// Setup the windows class with default settings.
	wc.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc   = WndProc;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = m_hinstance;
	wc.hIcon		 = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm       = wc.hIcon;
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName  = NULL;
	wc.lpszClassName = m_applicationName;
	wc.cbSize        = sizeof(WNDCLASSEX);
	
	// Register the window class.
	RegisterClassEx(&wc);

	// Determine the resolution of the clients desktop screen.
	screenWidth  = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);

	// Setup the screen settings depending on whether it is running in full screen or in windowed mode.
	if(FULL_SCREEN)
	{
		// If full screen set the screen to maximum size of the users desktop and 32bit.
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize       = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth  = (unsigned long)screenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;			
		dmScreenSettings.dmFields     = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Change the display settings to full screen.
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		// Set the position of the window to the top left corner.
		posX = posY = 0;
	}
	else
	{
		// If windowed then set it to 800x600 resolution.
		screenWidth  = SCREEN_WIDTH_REAL;
		screenHeight = SCREEN_HEIGHT_REAL;

		// Place the window in the middle of the screen.
		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth)  / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
	}

	// Create the window with the screen settings and get the handle to it.
	m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName, m_applicationName, 
						    WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
						    posX, posY, screenWidth, screenHeight, NULL, NULL, m_hinstance, NULL);

	// Bring the window up on the screen and set it as main focus.
	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);

	// Hide the mouse cursor.
	ShowCursor(false);

	return;
}


void SystemClass::ShutdownWindows()
{
	// Show the mouse cursor.
	ShowCursor(true);

	// Fix the display settings if leaving full screen mode.
	if(FULL_SCREEN)
	{
		ChangeDisplaySettings(NULL, 0);
	}

	// Remove the window.
	DestroyWindow(m_hwnd);
	m_hwnd = NULL;

	// Remove the application instance.
	UnregisterClass(m_applicationName, m_hinstance);
	m_hinstance = NULL;

	// Release the pointer to this class.
	ApplicationHandle = NULL;

	return;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch(umessage)
	{
		// Check if the window is being destroyed.
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}

		// Check if the window is being closed.
		case WM_CLOSE:
		{
			PostQuitMessage(0);		
			return 0;
		}

		// All other messages pass to the message handler in the system class.
		default:
		{
			return ApplicationHandle->MessageHandler(hwnd, umessage, wparam, lparam);
		}
	}
}