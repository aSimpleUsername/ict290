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
	cam.Position(10000, 10450.0, 11000.0, 180.0);

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

bool DisplayWrathWorld::stairsReturnPortal()
{
	stepsReturn.setLocation(cam.GetLR(), cam.GetUD(), cam.GetFB());
	stepsReturn.portalDimensions(-500, -500, -500);
	return(stepsReturn.createPortal(10500, 10500.0, 15000.0));
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

	image = tp.LoadTexture("data/space_1.png");
	tp.CreatePNGTexture(SPACE_1, image, 1024, 1024);

	image = tp.LoadTexture("data/spaceportal.png");
	tp.CreatePNGTexture(PORTAL_1, image, 512, 385);

	image = tp.LoadTexture("data/spaceship_wall_1.png");
	tp.CreatePNGTexture(SPACESHIP_WALL_1, image, 600, 600);

	image = tp.LoadTexture("data/spaceship_wall_1_YZ.png");
	tp.CreatePNGTexture(SPACESHIP_WALL_1_YZ, image, 600, 600);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void DisplayWrathWorld::DrawBackdrop()
{
	displaySkyBox();
	displayGroundPlane();
	displayPortal();
	displayRoom1Walls();
}

void DisplayWrathWorld::displaySkyBox()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SPACE_1));
	for(int i=4; i<10; i++)
		glCallList(i);
}

void DisplayWrathWorld::drawSkyBox()
{
	tp.CreateDisplayList(XZ, 4, 10240, 10240, -10000.0, -10000.0, -30000.0, 10, 10);	// Bottom
	tp.CreateDisplayList(XZ, 5, 10240, 10240, -10000.0, 92400.0, -30000.0, 10, 10);		// Top
	tp.CreateDisplayList(YZ, 6, 10240, 10240, -10000.0, -10000.0, -30000.0, 10, 10);	// FRONT
	tp.CreateDisplayList(YZ, 7, 10240, 10240, 30000.0, -10000.0, -30000.0, 10, 10);		// Back 
	tp.CreateDisplayList(XY, 8, 10240, 10240, -10000.0, -10000.0, -10000.0, 10, 10);	// Left
	tp.CreateDisplayList(XY, 9, 10240, 10240, -10000.0, -10000.0, 72400, 10, 10);		// Right	
}

void DisplayWrathWorld::displayGroundPlane()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(GROUND_PLANE));
	glCallList(3);
}

void DisplayWrathWorld::drawGroundPlane()
{
	tp.CreateDisplayList(XZ, 3, 431, 431, 0.0, 10000.0, 0.0, 50, 50);	// groundPlane

}

void DisplayWrathWorld::displayPortal()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(PORTAL_1));
	glCallList(10);
}

void DisplayWrathWorld::drawPortal()
{
	tp.CreateDisplayList(XY, 10, 512, 385, 10000, 10000, 15000, 1.0, 2);
}

void DisplayWrathWorld::displayRoom1Walls()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SPACESHIP_WALL_1));
	for (int i = 11; i <= 19; ++i)		//teleporter room
		glCallList(i);
	for (int i = 34; i <= 38; ++i)		//first room
		glCallList(i);
	glCallList(31);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SPACESHIP_WALL_1_YZ));
	for (int i = 20; i <= 33; ++i)		//teleporter room
		glCallList(i);
	for (int i = 38; i <= 41; ++i)		//first room
		glCallList(i);
}

void DisplayWrathWorld::drawRoom1Walls()
{
	//teleporter room
	tp.CreateDisplayList(XY, 11, 1000, 500, 8500, 10000, 10000, 3.0, 3.0);
	tp.CreateDisplayList(XY, 12, 1000, 500, 8500, 10000, 11000, 1.0, 3.0);
	tp.CreateDisplayList(XY, 13, 1000, 500, 10500, 10000, 11000, 1.0, 3.0);

	tp.CreateDisplayList(XY, 14, 1000, 500, 7000, 10000, 12500, 2.0, 3.0);		//back window
	tp.CreateDisplayList(XY, 15, 1000, 500, 9000, 10000, 12500, 2.0, 1.0);		//back window
	tp.CreateDisplayList(XY, 16, 1000, 500, 9000, 11000, 12500, 2.0, 1.0);		//back window
	tp.CreateDisplayList(XY, 17, 1000, 500, 11000, 10000, 12500, 2.0, 3.0);		//back window

	tp.CreateDisplayList(XY, 18, 1000, 500, 7000, 10000, 8500, 2.0, 3.0);
	tp.CreateDisplayList(XY, 19, 1000, 500, 11000, 10000, 8500, 2.0, 3.0);

	tp.CreateDisplayList(YZ, 20, 500, 1000, 9500, 10000, 10000, 3.0, 1.0);
	tp.CreateDisplayList(YZ, 21, 500, 1000, 10500, 10000, 10000, 3.0, 1.0);
	tp.CreateDisplayList(YZ, 22, 500, 1000, 8500, 10000, 10000, 3.0, 1.0);
	tp.CreateDisplayList(YZ, 23, 500, 1000, 11500, 10000, 10000, 3.0, 1.0);
	tp.CreateDisplayList(YZ, 24, 500, 1000, 7000, 10000, 8500, 3.0, 4.0);
	tp.CreateDisplayList(YZ, 25, 500, 1000, 13000, 10000, 8500, 3.0, 4.0);

	tp.CreateDisplayList(YZ, 26, 500, 1000, 11000, 10000, 7500, 3.0, 1.0);		//hallway
	tp.CreateDisplayList(YZ, 27, 500, 1000, 11000, 10000, 3500, 1.0, 4.0);		//hallway
	tp.CreateDisplayList(YZ, 28, 500, 1000, 11000, 11000, 3500, 1.0, 4.0);		//hallway
	tp.CreateDisplayList(YZ, 29, 500, 1000, 11000, 10000, 2500, 3.0, 1.0);		//hallway

	tp.CreateDisplayList(YZ, 30, 500, 1000, 9000, 10000, 7500, 3.0, 1.0);		//hallway
	tp.CreateDisplayList(YZ, 31, 500, 1000, 9000, 10000, 3500, 1.0, 4.0);		//hallway
	tp.CreateDisplayList(YZ, 32, 500, 1000, 9000, 11000, 3500, 1.0, 4.0);		//hallway
	tp.CreateDisplayList(YZ, 33, 500, 1000, 9000, 10000, 2500, 3.0, 1.0);		//hallway

	//first room
	tp.CreateDisplayList(XY, 34, 1000, 500, 7000, 10000, 2500, 2.0, 2.0);
	tp.CreateDisplayList(XY, 35, 1000, 500, 7000, 11000, 2500, 12.0, 1.0);
	tp.CreateDisplayList(XY, 36, 1000, 500, 11000, 10000, 2500, 8.0, 2.0);
	tp.CreateDisplayList(XY, 37, 1000, 500, 7000, 11000, -3500, 12.0, 1.0);
	tp.CreateDisplayList(XY, 38, 1000, 500, 7000, 10000, -3500, 10.0, 2.0);
	tp.CreateDisplayList(XY, 39, 1000, 500, 18000, 10000, -3500, 1.0, 2.0);

	tp.CreateDisplayList(YZ, 40, 500, 1000, 7000, 10000, -3500, 3.0, 6.0);
	tp.CreateDisplayList(YZ, 41, 500, 1000, 19000, 10000, -3500, 3.0, 6.0);
}

//--------------------------------------------------------------------------------------
//  Create display lists
//	Numbers indicate list numbers
//--------------------------------------------------------------------------------------
void DisplayWrathWorld::CreateTextureList()
{
	drawSkyBox();				// 4-9
	drawGroundPlane();			// 3
	drawPortal();				//10
	drawRoom1Walls();		//11-41

								//last number used: 11
}