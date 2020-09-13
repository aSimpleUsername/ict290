
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
#define WALL_BRICK_YZ				15
#define WALL_BRICK_XY				16
#define WALL_BRICK_XY_87WIDTH		17
#define WALL_BRICK_GAP_YZ			18
#define WALL_BRICK_GAP2_YZ			19
#define	WALL_BRICK_USD_YZ			20
#define WALL_BRICK_XY_END			21
#define WALL_BRICK_YZ_END			22
#define	WALL_GAP_1					23
#define WALL_BRICK_3_4				24
#define SHADOW_BRICK				25
#define WALL_BRICK_SEC_SIGN			216

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
	bool DisplayWelcome = true;
	// display exit screen
	bool DisplayExit = false;
	// display light fittings
	
	void myinit();
	// calls display functions below to draw the backdrops
	void DrawBackdrop();

	// deletes image and clears memory
	void DeleteImageFromMemory(unsigned char* tempImage);

private:
	// varibles used for tarnslating graphics etc
	GLdouble step, step2, stepLength;
	// Glut Cylinder
	GLUquadricObj* glu_cylinder;

	// Stores raw image file
	std::vector<unsigned char>* pngImage;

	void DisplayBricks();

	// calls functions to create display lists (below)
	void CreateTextureList();
	// creates display lists
	void DrawBricks();

	// loads images and creates texture
	void CreateTextures();
	// creates bounding boxes for collsion detection
	void CreateBoundingBoxes();
};

#endif DISPLAYWRATHWORLD_H