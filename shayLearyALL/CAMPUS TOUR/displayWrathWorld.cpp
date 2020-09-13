#include "displayWrathWorld.h"






//--------------------------------------------------------------------------------------
//  Initialize Settings
//--------------------------------------------------------------------------------------
void DisplayWrathWorld::myinit()
{
	// set background (sky colour)
	glClearColor(97.0 / 255.0, 140.0 / 255.0, 185.0 / 255.0, 1.0);

	// set perpsective
	gluLookAt(0.0, 1.75, 0.0,
		0.0, 1.75, -1,
		0.0f, 1.0f, 0.0f);

	// settings for glut cylinders
	//glu_cylinder = gluNewQuadric();
	//gluQuadricTexture(glu_cylinder, GL_TRUE);

	// set the world co-ordinates (used to set quadrants for bounding boxes)
	cam.SetWorldCoordinates(36000.0, 43200.0);
	// turn collision detection on
	cam.SetCollisionDetectionOn(true);
	// set number of bounding boxes required
	cam.SetNoBoundingBoxes(5);


	// set starting position of user
	cam.Position(10000, 10450.0, 10000.0, 180.0);

	//ORIGINAL POSITION
	/*
	cam.Position(32720.0, 9536.0,
		4800.0, 180.0);
		*/

	//CreatePlains();

	// creates bounding boxes and places in array
	CreateBoundingBoxes();
	// copies bounding boxes from array to linked lists (one fopr each quadrant)
	cam.InitiateBoundingBoxes();

	// load texture images and create display lists
	CreateTextureList();
	CreateTextures();
}


//--------------------------------------------------------------------------------------
//  Delete raw image and clear memory
//--------------------------------------------------------------------------------------
void DisplayWrathWorld::DeleteImageFromMemory(unsigned char* tempImage)
{
	tempImage = NULL;
	if (tempImage == NULL)
	{
		delete[] tempImage;
	}
}

//--------------------------------------------------------------------------------------
// Set up bounding boxes for collsion detection
//--------------------------------------------------------------------------------------
void DisplayWrathWorld::CreateBoundingBoxes()
{
	// chanc block
	//cam.SetAABBMaxX(0, 35879.0);
	//cam.SetAABBMinX(0, 33808.0);
	//cam.SetAABBMaxZ(0, 22096.0);
	//cam.SetAABBMinZ(0, 4688.0);
	// current AABB array size = 5
	// change array size with cam.SetNoBoundingBoxes() found in myinit()
}

void DisplayWrathWorld::CreateTextures()
{
	glEnable(GL_DEPTH_TEST);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// set texture count
	tp.SetTextureCount(256);

	image = tp.LoadTexture("data/map.raw", 256, 256);
	tp.CreateTexture(217, image, 256, 256);
	image = tp.LoadTexture("data/welcome.png");

	tp.CreatePNGTexture(WELCOME_SCREEN, image, 512, 512);

	image = tp.LoadTexture("data/thanks.png");
	tp.CreatePNGTexture(EXIT_SCREEN, image, 512, 512);

	image = tp.LoadTexture("data/groundPlane.png");
	tp.CreatePNGTexture(GROUND_PLANE, image, 431, 431);

	image = tp.LoadTexture("data/space1.png");
	tp.CreatePNGTexture(SPACE_1, image, 1024, 1024);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void DisplayWrathWorld::DrawBackdrop()
{
	displaySkyBox();
	displayGroundPlane();
}

void DisplayWrathWorld::displaySkyBox()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SPACE_1));
	for(int i=4; i<10; i++)
		glCallList(i);
}

void DisplayWrathWorld::displayGroundPlane()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(GROUND_PLANE));
	glCallList(3);
}

void DisplayWrathWorld::drawSkyBox()
{
	tp.CreateDisplayList(XZ, 4, 1024, 1024, -10000.0, -10000.0, -30000.0, 100, 100);	// Top
	tp.CreateDisplayList(XZ, 5, 1024, 1024, -10000.0, 92400.0, -30000.0, 100, 100);		// Bottom
	tp.CreateDisplayList(YZ, 6, 1024, 1024, -10000.0, -10000.0, -30000.0, 100, 100);	// FRONT
	tp.CreateDisplayList(YZ, 7, 1024, 1024, 30000.0, -10000.0, -30000.0, 100, 100);		// Back
	tp.CreateDisplayList(XY, 8, 1024, 1024, -10000.0, -10000.0, -10000.0, 100, 100);	// Left
	tp.CreateDisplayList(XY, 9, 1024, 1024, -10000.0, -10000.0, 72400, 100, 100);		// Right	
}

void DisplayWrathWorld::drawGroundPlane()
{
	tp.CreateDisplayList(XZ, 3, 431, 431, 0.0, 10000.0, 0.0, 50, 50);	// groundPlane
}

//--------------------------------------------------------------------------------------
//  Create display lists
//	Numbers indicate list numbers
//--------------------------------------------------------------------------------------
void DisplayWrathWorld::CreateTextureList()
{
	drawSkyBox();				// 4-9
	drawGroundPlane();			// 3
	//last number used: 601
}