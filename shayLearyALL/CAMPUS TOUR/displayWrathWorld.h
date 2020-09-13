
#ifndef DISPLAYWRATHWORLD_H
#define DISPLAYWRATHWORLD_H

#include "camera.h"
#include "texturedPolygons.h"
#include "Portal.h"

// TEXTURE IMAGE AXISES
#define XY		0
#define XZ		1
#define YZ		2
#define YZ_FLIP 3
#define XY_FLIP 4

// Wall Brick Textures
#define WELCOME_SCREEN				1
#define EXIT_SCREEN					2
#define GROUND_PLANE				3
#define SPACE_1						4
#define PORTAL_1					5

class DisplayWrathWorld
{
public:
	// objects
	Camera cam;
	TexturedPolygons tp;
	unsigned char* image = NULL;

	//booleans
	// display campus map
	bool DisplayMap = false;
	// display welcome screen
	bool DisplayWelcome = false;
	// display exit screen
	bool DisplayExit = false;
	// display light fittings
	
	void myinit();
	// calls display functions below to draw the backdrops
	void DrawBackdrop();

	// deletes image and clears memory
	void DeleteImageFromMemory(unsigned char* tempImage);

	bool stairsReturnPortal();

private:
	// varibles used for tarnslating graphics etc
	GLdouble step, step2, stepLength;
	// Glut Cylinder
	GLUquadricObj* glu_cylinder;

	// Stores raw image file
	std::vector<unsigned char>* pngImage;

	void displaySkyBox();
	void displayGroundPlane();
	void displayPortal();

	// calls functions to create display lists (below)
	void CreateTextureList();
	// creates display lists
	void drawSkyBox();
	void drawGroundPlane();
	void drawPortal();

	// loads images and creates texture
	void CreateTextures();
	// creates bounding boxes for collsion detection
	void CreateBoundingBoxes();
};

#endif DISPLAYWRATHWORLD_H