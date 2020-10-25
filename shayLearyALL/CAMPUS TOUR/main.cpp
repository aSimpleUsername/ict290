// ICT290 Assignment 1 
// main.cpp - runs our game world from Shay's world
// Group Noname 2
// 13/09/2020


#include <math.h>
#include <GL/glut.h>
#include <time.h>

#include <iostream>
#include <irrKlang.h>
#pragma comment(lib, "irrKlang.lib")

//#include <windows.h> // only used if mouse is required (not portable)
#include "camera.h"
#include "texturedPolygons.h"
#include "Portal.h"
#include "DisplayShaysWorld.h"
#include "displayWrathWorld.h"
#include "weapon.h"
#include "point3D.h"
#include "camera.h"
//--------------------------------------------------------------------------------------

#define PI 3.1415962654

// USE THESE STTEINGS TO CHANGE SPEED (on different spec computers)
// Set speed (steps)

DisplayShaysWorld shaysWorld;
DisplayWrathWorld wrathWorld;
GLdouble movementSpeed = 15.0;
GLdouble xrotationSpeed = 0.0015;
GLdouble yrotationSpeed = 0.0012;	// (speed based on trial and error)
Weapon playerWeapon;
GLdouble stepIncrement;
GLdouble angleIncrement;
int frameCount = 0;
clock_t lastClock = 0;
bool canShoot = true;
// ratio of screen
float ratio;
// screen width and height
int width, height;

// keyboard and mouse functions
bool* keyStates = new bool[256];
void initKeyStates();
void keyPressed(unsigned char, int x, int y);
void releaseKey(unsigned char key, int x, int y);
void processKeys();
void Mouse(int button, int state, int x, int y);
void mouseMove(int x, int y);

bool isShaysWorld = true;
void Display();
void reshape(int w, int h);
void IncrementFrameCount();
void timerCallback(int value);
void setGameMode();
irrklang::ISoundEngine* engine = irrklang::createIrrKlangDevice();
irrklang::ISoundSource* music = engine->addSoundSourceFromFile("sounds/metal.mp3");
//--------------------------------------------------------------------------------------
//  Main function
//--------------------------------------------------------------------------------------
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	setGameMode();
	initKeyStates();	//clear keystate array
	shaysWorld.myinit();
	glutTimerFunc(1000 / 60, timerCallback, 1);
	if (!engine)
		return 0; // error starting up the engine
	glutIgnoreKeyRepeat(1);
	glutKeyboardUpFunc(releaseKey);
	glutKeyboardFunc(keyPressed);
	

	glutDisplayFunc(Display);
	glutMouseFunc(Mouse);
	// ONLY USE IF REQUIRE MOUSE MOVEMENT
	glutPassiveMotionFunc(mouseMove);
	glutMotionFunc(mouseMove);
	glutSetCursor(GLUT_CURSOR_CROSSHAIR);
	
	wrathWorld.engine = engine;
	shaysWorld.engine = engine;
	music->setDefaultVolume(0.35);
	glutReshapeFunc(reshape);
	glutMainLoop();
 	return(0);
}

//--------------------------------------------------------------------------------------
//  Sets the correct game mode for monitor
//--------------------------------------------------------------------------------------
void setGameMode()
{
	int i = 0;
	do
	{
		switch (i)
		{
		case 0:
			glutGameModeString("1920x1080:32@240");
			break;
		case 1:
			glutGameModeString("1920x1080:32@165");
			break;
		case 2:
			glutGameModeString("1920x1080:32@144");
			break;
		case 3:
			glutGameModeString("1920x1080:32@120");
			break;
		case 4:
			glutGameModeString("1920x1080:32@60");
			break;
		default:
			std::cout << "Cannot run on this system";
			exit(1);
		}

		++i;
	} while (!glutGameModeGet(GLUT_GAME_MODE_POSSIBLE));
	glutEnterGameMode();
}

//--------------------------------------------------------------------------------------
//  Main Display Function
//--------------------------------------------------------------------------------------*/
void Display()
{
	processKeys();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// DISPLAY TEXTURES
	//enable texture mapping
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glPushMatrix();
	// displays the welcome screen
	

	if (isShaysWorld)
	{
		shaysWorld.cam.CheckCamera();
		// set the movement and rotation speed accordiwng to frame count
		IncrementFrameCount();
		shaysWorld.cam.SetMoveSpeed(stepIncrement);
		if (shaysWorld.stairsPortal())
		{
			isShaysWorld = false;
			wrathWorld.myinit();
			wrathWorld.cam.SetAngleUD(shaysWorld.cam.GetAngleUD());
			wrathWorld.cam.SetXRotateSpeed(xrotationSpeed);
			wrathWorld.cam.SetYRotateSpeed(yrotationSpeed);
			wrathWorld.cam.SetMoveSpeed(movementSpeed);
		}
		shaysWorld.specialPortal();

		// displays the map
		if (shaysWorld.DisplayMap) shaysWorld.cam.DisplayMap(width, height, shaysWorld.tp.GetTexture(MAP));
		// display no exit sign (position check should really be in an object, but didn't have time)
		if ((shaysWorld.cam.getX() > 35500.0) && (shaysWorld.cam.getZ() < 25344.0) ||
			(shaysWorld.cam.getX() > 34100.0) && (shaysWorld.cam.getZ() > 41127.0))
		{
			shaysWorld.cam.DisplayNoExit(width, height, shaysWorld.tp.GetTexture(NO_EXIT));
		}

		// display images
		shaysWorld.DrawBackdrop();

		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
	}
	if(!isShaysWorld)
	{
		wrathWorld.cam.CheckCamera();
		// set the movement and rotation speed according to frame count
		IncrementFrameCount();
		wrathWorld.cam.SetMoveSpeed(stepIncrement);

		if (wrathWorld.stairsReturnPortal())
		{
			isShaysWorld = true;
			shaysWorld.myinit();
			shaysWorld.cam.Position(1400, 11234, 39740, 90);
		}

		// display images
		wrathWorld.DrawBackdrop();

		wrathWorld.collectionCheck();

		wrathWorld.elecPortal();
		wrathWorld.postElecPortal();
		wrathWorld.servPortalL();
		wrathWorld.servPortalR();
		wrathWorld.bossPortalL();
		wrathWorld.bossPortalR();
		wrathWorld.electricFloorCheck();

		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
	}

	/// <summary>
	/// for transparency to work clear objects need to be drawn last.
	/// </summary>

	if (shaysWorld.DisplayWelcome && isShaysWorld) shaysWorld.cam.DisplayWelcomeScreen(width, height, 1, shaysWorld.tp.GetTexture(WELCOME));
	if (wrathWorld.DisplayWelcome && !isShaysWorld) wrathWorld.cam.DisplayWelcomeScreen(width, height, 1, wrathWorld.tp.GetTexture(WELCOME_SCREEN));
	// displays the exit screen
	if (shaysWorld.DisplayExit) shaysWorld.cam.DisplayWelcomeScreen(width, height, 0, shaysWorld.tp.GetTexture(EXIT));
	if (wrathWorld.DisplayExit) wrathWorld.cam.DisplayWelcomeScreen(width, height, 0, wrathWorld.tp.GetTexture(EXIT_SCREEN));
	// clear buffers
	glFlush();
	glutSwapBuffers();
	if (!engine->isCurrentlyPlaying(music) && !isShaysWorld) {
		engine->play2D(music);
	}
}


//--------------------------------------------------------------------------------------
void reshape(int w, int h)
{
	width = w;
	height = h;
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0) h = 1;
	ratio = 1.0f * w / h;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(45,ratio,1,250000);
	glMatrixMode(GL_MODELVIEW);
}

//--------------------------------------------------------------------------------------
void initKeyStates()
{
	for (int i = 0; i < 256; i++)
		keyStates[i] = false;
}

void keyPressed(unsigned char key, int x, int y)
{
	keyStates[key] = true;	//set keystate to pressed

	// display welcome page (space key)
	if (key == ' ' && isShaysWorld)
	{
		if (shaysWorld.DisplayWelcome)		//if info screen is up don't allow player to look around
		{
			shaysWorld.cam.SetXRotateSpeed(xrotationSpeed);
			shaysWorld.cam.SetYRotateSpeed(yrotationSpeed);
			shaysWorld.cam.SetMoveSpeed(movementSpeed);
			shaysWorld.DisplayWelcome = false;
		}
		else
		{
			shaysWorld.cam.SetXRotateSpeed(0.0f);
			shaysWorld.cam.SetYRotateSpeed(0.0f);
			shaysWorld.cam.SetMoveSpeed(0.0f);
			shaysWorld.DisplayWelcome = true;
		}
	}
	else if (key == ' ' && !isShaysWorld)
	{
		if (wrathWorld.DisplayWelcome)		//if info screen is up don't allow player to look around
		{
			wrathWorld.cam.SetXRotateSpeed(xrotationSpeed);
			wrathWorld.cam.SetYRotateSpeed(yrotationSpeed);
			wrathWorld.cam.SetMoveSpeed(movementSpeed);
			wrathWorld.DisplayWelcome = false;
		}
		else
		{
			wrathWorld.cam.SetXRotateSpeed(0.0f);
			wrathWorld.cam.SetYRotateSpeed(0.0f);
			wrathWorld.cam.SetMoveSpeed(0.0f);
			wrathWorld.DisplayWelcome = true;
		}
	}
}

void releaseKey(unsigned char key, int x, int y)
{
	keyStates[key] = false;		//set keystate to released
}

// Will cut this code in half once I overload the camera assignment operator
void processKeys()
{
	int speed = 3;
	if (!wrathWorld.cam.dead && !shaysWorld.cam.dead) {
		if ((keyStates['a'] || keyStates['A']) && isShaysWorld)		//step left
			shaysWorld.cam.DirectionLR(-speed);
		if ((keyStates['a'] || keyStates['A']) && !isShaysWorld)		//step left
			wrathWorld.cam.DirectionLR(-speed);

		if ((keyStates['d'] || keyStates['D']) && isShaysWorld)		//step right
			shaysWorld.cam.DirectionLR(speed);
		if ((keyStates['d'] || keyStates['D']) && !isShaysWorld)		//step right
			wrathWorld.cam.DirectionLR(speed);

		if ((keyStates['w'] || keyStates['W']) && isShaysWorld) 	//step forward
			shaysWorld.cam.DirectionFB(speed);
		if ((keyStates['w'] || keyStates['W']) && !isShaysWorld) 	//step forward
			wrathWorld.cam.DirectionFB(speed);

		if ((keyStates['s'] || keyStates['S']) && isShaysWorld)	// step backward
			shaysWorld.cam.DirectionFB(-speed);
		if ((keyStates['s'] || keyStates['S']) && !isShaysWorld)	// step backward
			wrathWorld.cam.DirectionFB(-speed);

		if ((!keyStates['a'] && !keyStates['A'] && !keyStates['d'] && !keyStates['D']) && isShaysWorld)	//stops player LR
			shaysWorld.cam.DirectionLR(0);
		if ((!keyStates['a'] && !keyStates['A'] && !keyStates['d'] && !keyStates['D']) && !isShaysWorld)	//stops player LR
			wrathWorld.cam.DirectionLR(0);

		if ((!keyStates['w'] && !keyStates['W'] && !keyStates['s'] && !keyStates['S']) && isShaysWorld)	//stops player FB
			shaysWorld.cam.DirectionFB(0);
		if ((!keyStates['w'] && !keyStates['W'] && !keyStates['s'] && !keyStates['S']) && !isShaysWorld)	//stops player FB
			wrathWorld.cam.DirectionFB(0);
	}
	else {
		wrathWorld.cam.SetMoveSpeed(0);
		shaysWorld.cam.SetMoveSpeed(0);
	}

	if ((keyStates['m'] || keyStates['M']) && isShaysWorld)	// display campus map
	{
		if (shaysWorld.DisplayMap)
		{
			shaysWorld.DisplayMap = false;
		}
		else
		{
			shaysWorld.DisplayMap = true;
		}
	}

	if ((keyStates['p'] || keyStates['P']) && isShaysWorld)	// change world - temp
	{
		wrathWorld.myinit();
		isShaysWorld = false;
	}

	if ((keyStates[27]) && isShaysWorld)	// exit tour (escape key)
	{
		shaysWorld.cam.SetXRotateSpeed(0.0f);
		shaysWorld.cam.SetYRotateSpeed(0.0f);
		shaysWorld.cam.SetMoveSpeed(0.0f);
		shaysWorld.DisplayExit = true;
	}
	if ((keyStates[27]) && !isShaysWorld)	// exit tour (escape key)
	{
		wrathWorld.cam.SetXRotateSpeed(0.0f);
		wrathWorld.cam.SetYRotateSpeed(0.0f);
		wrathWorld.cam.SetMoveSpeed(0.0f);
		wrathWorld.DisplayExit = true;
	}

	// display light fittings
	if ((keyStates['l'] || keyStates['L']) && isShaysWorld)
	{
		if (shaysWorld.lightsOn)
		{
			shaysWorld.lightsOn = false;
		}
		else
		{
			shaysWorld.lightsOn = true;
		}
	}

	// Respawn player
	if ((keyStates['r'] || keyStates['R']) && isShaysWorld)
	{
		shaysWorld.respawn();
		shaysWorld.cam.SetXRotateSpeed(xrotationSpeed);
		shaysWorld.cam.SetYRotateSpeed(yrotationSpeed);
	}
	if ((keyStates['r'] || keyStates['R']) && !isShaysWorld)
	{
		wrathWorld.reload();
		//wrathWorld.respawn();
		//wrathWorld.cam.SetXRotateSpeed(xrotationSpeed);
		//wrathWorld.cam.SetYRotateSpeed(yrotationSpeed);
	}

}


//--------------------------------------------------------------------------------------
//  Mouse Buttons
//--------------------------------------------------------------------------------------
void Mouse(int button, int state, int x, int y)
{
	// exit tour if clicked on exit splash screen

	if (((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)) && isShaysWorld)
	{
		
		if ((shaysWorld.DisplayExit) && (x <= width / 2.0 + 256.0) && (x >= width / 2.0 - 256.0)
			&& (y <= height / 2.0 + 256.0) && (y >= height / 2.0 - 256.0))
		{
			shaysWorld.DeleteImageFromMemory(shaysWorld.image);
			exit(1);
		}

		if (canShoot) {
			//mciSendString("play sounds/shot.wav", NULL, 0, NULL);
			//PlaySound(TEXT("sounds/shot.wav"), NULL, SND_FILENAME | SND_ASYNC);// - the correct code
			//stepSound->Play();
			engine->play2D("sounds/gunshot.wav", false);
			
			Point3D ray(shaysWorld.cam.GetLX(), shaysWorld.cam.GetLY(), shaysWorld.cam.GetLZ());
			Point3D camPos(shaysWorld.cam.getX(), shaysWorld.cam.getY(), shaysWorld.cam.getZ());
			if(playerWeapon.shoot(ray, camPos, shaysWorld.enemyObjects, shaysWorld.maxWallPoints, shaysWorld.minWallPoints))
				shaysWorld.ui.m_hit = true;
			shaysWorld.cam.RotateCamera(1920 / 2, 530, 1920, 1080);
			//general shoot logic (regardless of hit or miss)
			canShoot = false;
		}
	}
	if (((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)) && !isShaysWorld)
	{

		if ((wrathWorld.DisplayExit) && (x <= width / 2.0 + 256.0) && (x >= width / 2.0 - 256.0)
			&& (y <= height / 2.0 + 256.0) && (y >= height / 2.0 - 256.0))
		{
			wrathWorld.DeleteImageFromMemory(wrathWorld.image);
			exit(1);
		}

		if (canShoot) {
			engine->play2D("sounds/gunshot.wav", false);
			Point3D ray(wrathWorld.cam.GetLX(), wrathWorld.cam.GetLY(), wrathWorld.cam.GetLZ());
			Point3D camPos(wrathWorld.cam.getX(), wrathWorld.cam.getY(), wrathWorld.cam.getZ());
			if(playerWeapon.shoot(ray, camPos, wrathWorld.enemyObjects, wrathWorld.maxWallPoints, wrathWorld.minWallPoints) || playerWeapon.shoot(ray, camPos, wrathWorld.enemyBossObject, wrathWorld.maxWallPoints,wrathWorld.minWallPoints))
				wrathWorld.ui.m_hit = true;		
			wrathWorld.cam.RotateCamera(1920 / 2, 530, 1920, 1080);
			wrathWorld.reduceAmmo();
			wrathWorld.ammoCheck();
			// general shoot logic (regardless of hit or miss)
			canShoot = false;
		}
	}

	if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_UP)) {
		canShoot = true;
	}
	
	
}

//--------------------------------------------------------------------------------------
//	used to rotate around screen using mouse
//--------------------------------------------------------------------------------------
void mouseMove(int x, int y)
{
	if (isShaysWorld)
	{
		shaysWorld.cam.RotateCamera(x, y, width, height);
		glutWarpPointer(width / 2, height / 2);
	}
	if(!isShaysWorld)
	{
		wrathWorld.cam.RotateCamera(x, y, width, height);
		glutWarpPointer(width / 2, height / 2);
	}
}

//--------------------------------------------------------------------------------------
//  Increments frame count used for setting movement speed
//--------------------------------------------------------------------------------------
void IncrementFrameCount()
{
	double t = ((GLdouble)(clock()-lastClock))/(GLdouble)CLOCKS_PER_SEC;
	frameCount ++;

	// reset after t
	if (t > 0.1)
	{
		stepIncrement = t/frameCount * 1400;
		angleIncrement = t/frameCount;
		frameCount = 0;
		lastClock = clock();
	}
}

//--------------------------------------------------------------------------------------
//runs the program at 120fps on all systems
//--------------------------------------------------------------------------------------
void timerCallback(int value)
{
	glutPostRedisplay();
	glutTimerFunc(1000 / 120, timerCallback, 1);
}