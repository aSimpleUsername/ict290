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

	// set the world co-ordinates (used to set quadrants for bounding boxes)
	cam.SetWorldCoordinates(36000.0, 43200.0);
	// turn collision detection on
	cam.SetCollisionDetectionOn(true);
	// set number of bounding boxes required
	cam.SetNoBoundingBoxes(5);


	// set starting position of user
	cam.Position(10000, 10550.0, 11000.0, 180.0);

	// creates bounding boxes and places in array
	CreateBoundingBoxes();
	// copies bounding boxes from array to linked lists (one fopr each quadrant)
	cam.InitiateBoundingBoxes();

	// load texture images and create display lists
	CreateTextureList();
	CreateTextures();

	initEnemies();
	//Creating enemy object in the array at a given position
	//enemyObjects.addObjectToBuffer(Enemy(10020, 10455, 10000));
}

//--------------------------------------------------------------------------------------
//  Initialize Enemies
//--------------------------------------------------------------------------------------
void DisplayWrathWorld::initEnemies()
{
	enemyObjects.addObjectToBuffer(&enemy0);	//room 1
	enemyObjects.addObjectToBuffer(&enemy1);	//room 1
	enemyObjects.addObjectToBuffer(&enemy2);	//room 1
	enemyObjects.addObjectToBuffer(&enemy3);	//room 1


	for(int i=0; i<enemyObjects.size(); ++i)
		enemyObjects.getObjectFromBuffer(i)->setEnemyPosition(player.getPlayerLocationPointer()); 
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
	stepsReturn.setLocation(cam.getX(), cam.getY(), cam.getZ());
	stepsReturn.portalDimensions(-500, -500, -500);
	return(stepsReturn.createPortal(10500, 10600.0, 15000.0));
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

	image = tp.LoadTexture("data/hexagon.png");
	tp.CreatePNGTexture(CIRCUIT, image, 650, 1155);

	image = tp.LoadTexture("data/heart.png");
	tp.CreatePNGTexture(HEALTH, image, 417, 390);

	image = tp.LoadTexture("data/shield.png");
	tp.CreatePNGTexture(SHIELD, image, 417, 390);

	image = tp.LoadTexture("data/ammo.png");
	tp.CreatePNGTexture(AMMO, image, 417, 390);

	image = tp.LoadTexture("data/heartyz.png");
	tp.CreatePNGTexture(HEALTH_YZ, image, 390, 417);

	image = tp.LoadTexture("data/shieldyz.png");
	tp.CreatePNGTexture(SHIELD_YZ, image, 390, 417);

	image = tp.LoadTexture("data/ammoyz.png");
	tp.CreatePNGTexture(AMMO_YZ, image, 390, 417);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void DisplayWrathWorld::DrawBackdrop()
{
	displayEnemies();
	displaySkyBox();
	displayGroundPlane();
	displayPortal();
	displayRoom1Walls();
	displayServerWalls();
	healthChecksDisplay();
	shieldChecksDisplay();
	ammoChecksDisplay(); 
}

void DisplayWrathWorld::displayEnemies()
{
	player.updateLocation(cam.getX(), cam.getY(), cam.getZ());

	for (int i = 0; i<enemyObjects.size(); ++i)
	{
		enemyObjects.getObjectFromBuffer(i)->stateMachine();
		enemyObjects.getObjectFromBuffer(i)->drawEnemy(); 
	}

	if (enemyObjects.detectCollisionWithSphere(cam.GetLX(), cam.GetLY(), cam.GetLZ(), cam.getX(), cam.getY(), cam.getZ())) {
		std::cout << "hit" << std::endl;
	}
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
	tp.CreateDisplayList(XY, 8, 10240, 10240, -10000.0, -10000.0, -30000.0, 10, 10);	// Left
	tp.CreateDisplayList(XY, 9, 10240, 10240, -10000.0, -10000.0, 72400, 10, 10);		// Right	
}

void DisplayWrathWorld::displayGroundPlane()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(GROUND_PLANE));
	glCallList(3);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(CIRCUIT));
	glCallList(87);
}

void DisplayWrathWorld::drawGroundPlane()
{
	tp.CreateDisplayList(XZ, 3, 431, 431, 0.0, 10000.0, -30000.0, 50, 100);	// groundPlane
	tp.CreateDisplayList(XZ, 87, 650, 1155, 0.0, 11500.0, -30000.0, 50, 50);	// ceiling
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

void DisplayWrathWorld::displayServerWalls()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SPACESHIP_WALL_1_YZ));
	for (int i = 42; i <= 43; ++i) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SPACESHIP_WALL_1));
	for (int i = 44; i <= 46; ++i) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SPACESHIP_WALL_1_YZ));
	glCallList(47);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SPACESHIP_WALL_1));
	for (int i = 48; i <= 52; ++i) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SPACESHIP_WALL_1_YZ));
	glCallList(53);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SPACESHIP_WALL_1));
	for (int i = 54; i <= 62; ++i) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SPACESHIP_WALL_1_YZ));
	for (int i = 63; i <= 69; ++i) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SPACESHIP_WALL_1));
	for (int i = 70; i <= 71; ++i) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SPACESHIP_WALL_1_YZ));
	for (int i = 72; i <= 74; ++i) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SPACESHIP_WALL_1));
	for (int i = 75; i <= 76; ++i) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SPACESHIP_WALL_1_YZ));
	for (int i = 77; i <= 78; ++i) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SPACESHIP_WALL_1));
	for (int i = 79; i <= 80; ++i) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SPACESHIP_WALL_1_YZ));
	for (int i = 81; i <= 84; ++i) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SPACESHIP_WALL_1));
	for (int i = 85; i <= 86; ++i) glCallList(i);
}

void DisplayWrathWorld::drawServerWalls()
{
	//server room
	tp.CreateDisplayList(YZ, 42, 500, 1000, 7000, 10000, -9500, 3.0, 6.0);
	tp.CreateDisplayList(YZ, 43, 500, 1000, 19000, 10000, -9500, 3.0, 6.0);

	tp.CreateDisplayList(XY, 44, 1000, 500, 7000, 11000, -9500, 12.0, 1.0);
	tp.CreateDisplayList(XY, 45, 1000, 500, 7000, 10000, -9500, 1.0, 2.0);
	tp.CreateDisplayList(XY, 46, 1000, 500, 9000, 10000, -9500, 10.0, 2.0);

	//side hall
	tp.CreateDisplayList(YZ, 47, 500, 1000, 6000, 10000, -13500, 3.0, 10.0);
	tp.CreateDisplayList(XY, 48, 1000, 500, 6000, 10000, -3500, 1.0, 3.0);

	//hallway 1
	tp.CreateDisplayList(XY, 49, 1000, 500, 6000, 11000, -11250, 13.0, 1.0);
	tp.CreateDisplayList(XY, 50, 1000, 500, 6000, 10000, -11250, 2.0, 2.0);
	tp.CreateDisplayList(XY, 51, 1000, 500, 16000, 10000, -11250, 1.0, 2.0);
	tp.CreateDisplayList(XY, 52, 1000, 500, 6000, 10000, -11250, 11.0, 1.0);

	//hallway 2
	tp.CreateDisplayList(YZ, 53, 500, 1000, 19000, 10000, -13500, 3.0, 4.0);
	tp.CreateDisplayList(XY, 54, 1000, 500, 6000, 11000, -13500, 13.0, 1.0);
	tp.CreateDisplayList(XY, 55, 1000, 500, 6000, 10000, -13500, 1.0, 2.0);
	tp.CreateDisplayList(XY, 56, 1000, 500, 8000, 10000, -13500, 11.0, 2.0);

	//hallway mid window
	tp.CreateDisplayList(XY, 57, 1000, 500, 6000, 11000, -11750, 13.0, 1.0);
	tp.CreateDisplayList(XY, 58, 1000, 500, 6000, 10000, -11750, 2.0, 2.0);
	tp.CreateDisplayList(XY, 59, 1000, 500, 16000, 10000, -11750, 1.0, 2.0);
	tp.CreateDisplayList(XY, 60, 1000, 500, 6000, 10000, -11750, 11.0, 1.0);

	tp.CreateDisplayList(XZ, 61, 1000, 500, 6000, 10500, -11750, 11.0, 1.0);
	tp.CreateDisplayList(XZ, 62, 1000, 500, 6000, 11000, -11750, 13.0, 1.0);

	tp.CreateDisplayList(YZ, 63, 500, 1000, 16000, 10000, -11750, 3.0, 0.5);
	tp.CreateDisplayList(YZ, 64, 500, 1000, 17000, 10000, -11750, 3.0, 0.5);
	tp.CreateDisplayList(YZ, 65, 500, 1000, 8000, 10000, -11750, 3.0, 0.5);

	//last room
	tp.CreateDisplayList(YZ, 66, 500, 1000, 7000, 10000, -18500, 3.0, 5.0);
	tp.CreateDisplayList(YZ, 67, 500, 1000, 8000, 10000, -18500, 3.0, 2.0);
	tp.CreateDisplayList(YZ, 68, 500, 1000, 8000, 10000, -15500, 3.0, 2.0);
	tp.CreateDisplayList(YZ, 69, 500, 1000, 8000, 11000, -16500, 1.0, 1.0);
	tp.CreateDisplayList(XY, 70, 1000, 500, 7000, 11000, -18500, 1.0, 1.0);

	//supply room
	tp.CreateDisplayList(XY, 71, 1000, 500, 8000, 10000, -18500, 11.0, 3.0);
	tp.CreateDisplayList(YZ, 72, 500, 1000, 19000, 10000, -18500, 3.0, 5.0);

	//supply seperators
	tp.CreateDisplayList(YZ, 73, 500, 1000, 10000, 10000, -16500, 3.0, 1.0);
	tp.CreateDisplayList(YZ, 74, 500, 1000, 11000, 10000, -16500, 3.0, 1.0);
	tp.CreateDisplayList(XY, 75, 1000, 500, 10000, 10000, -16500, 1.0, 3.0);
	tp.CreateDisplayList(XY, 76, 1000, 500, 10000, 10000, -15500, 1.0, 3.0);

	tp.CreateDisplayList(YZ, 77, 500, 1000, 16000, 10000, -16500, 3.0, 1.0);
	tp.CreateDisplayList(YZ, 78, 500, 1000, 17000, 10000, -16500, 3.0, 1.0);
	tp.CreateDisplayList(XY, 79, 1000, 500, 16000, 10000, -16500, 1.0, 3.0);
	tp.CreateDisplayList(XY, 80, 1000, 500, 16000, 10000, -15500, 1.0, 3.0);

	//supply mid divider
	tp.CreateDisplayList(YZ, 81, 500, 1000, 13000, 10000, -18500, 3.0, 2.0);
	tp.CreateDisplayList(YZ, 82, 500, 1000, 14000, 10000, -18500, 3.0, 2.0);
	tp.CreateDisplayList(YZ, 83, 500, 1000, 13000, 10000, -15500, 3.0, 2.0);
	tp.CreateDisplayList(YZ, 84, 500, 1000, 14000, 10000, -15500, 3.0, 2.0);

	tp.CreateDisplayList(XY, 85, 1000, 500, 13000, 10000, -16500, 1.0, 3.0);
	tp.CreateDisplayList(XY, 86, 1000, 500, 13000, 10000, -15500, 1.0, 3.0);
}

// PICKUPS
//////////////////////////////////////////////////////////////////////////////////////////////////

void DisplayWrathWorld::displayHealthPickups()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(HEALTH));
	for (int i = 88; i <= 89; ++i) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(HEALTH_YZ));
	for (int i = 90; i <= 92; ++i) glCallList(i);
}

void DisplayWrathWorld::displayHealthPickups1()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(HEALTH));
	for (int i = 103; i <= 104; ++i) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(HEALTH_YZ));
	for (int i = 105; i <= 107; ++i) glCallList(i);
}

void DisplayWrathWorld::displayHealthPickups2()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(HEALTH));
	for (int i = 108; i <=109; ++i) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(HEALTH_YZ));
	for (int i = 110; i <= 112; ++i) glCallList(i);
}

void DisplayWrathWorld::displayHealthPickups3()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(HEALTH));
	for (int i = 113; i <= 114; ++i) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(HEALTH_YZ));
	for (int i = 115; i <= 117; ++i) glCallList(i);
}

void DisplayWrathWorld::displayHealthPickups4()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(HEALTH));
	for (int i = 118; i <= 119; ++i) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(HEALTH_YZ));
	for (int i = 120; i <= 122; ++i) glCallList(i);
}

void DisplayWrathWorld::displayHealthPickups5()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(HEALTH));
	for (int i = 163; i <= 164; ++i) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(HEALTH_YZ));
	for (int i = 165; i <= 167; ++i) glCallList(i);
}

void DisplayWrathWorld::displayHealthPickups6()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(HEALTH));
	for (int i = 168; i <= 169; ++i) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(HEALTH_YZ));
	for (int i = 170; i <= 172; ++i) glCallList(i);
}

void DisplayWrathWorld::drawHealthPickups()
{
	int x = 16000;
	int y = 10100;
	int z = -1500;
	int size = 250;

	tp.CreateDisplayList(XY, 88, size, size, x, y, z, 1.0, 1.0);
	tp.CreateDisplayList(XY, 89, size, size, x, y, z - size, 1.0, 1.0);
	tp.CreateDisplayList(YZ, 90, size, size, x, y, z - size, 1.0, 1.0);
	tp.CreateDisplayList(YZ, 91, size, size, x + size, y, z - size, 1.0, 1.0);
	tp.CreateDisplayList(XZ, 92, size, size, x, y + size, z - size, 1.0, 1.0);
}

void DisplayWrathWorld::drawHealthPickups1()
{
	int x = 11000;
	int y = 10100;
	int z = -6500;
	int size = 250;

	tp.CreateDisplayList(XY, 103, size, size, x, y, z, 1.0, 1.0);
	tp.CreateDisplayList(XY, 104, size, size, x, y, z - size, 1.0, 1.0);
	tp.CreateDisplayList(YZ, 105, size, size, x, y, z - size, 1.0, 1.0);
	tp.CreateDisplayList(YZ, 106, size, size, x + size, y, z - size, 1.0, 1.0);
	tp.CreateDisplayList(XZ, 107, size, size, x, y + size, z - size, 1.0, 1.0);
}

void DisplayWrathWorld::drawHealthPickups2()
{
	int x = 11000;
	int y = 10100;
	int z = -7000;
	int size = 250;

	tp.CreateDisplayList(XY, 108, size, size, x, y, z, 1.0, 1.0);
	tp.CreateDisplayList(XY, 109, size, size, x, y, z - size, 1.0, 1.0);
	tp.CreateDisplayList(YZ, 110, size, size, x, y, z - size, 1.0, 1.0);
	tp.CreateDisplayList(YZ, 111, size, size, x + size, y, z - size, 1.0, 1.0);
	tp.CreateDisplayList(XZ, 112, size, size, x, y + size, z - size, 1.0, 1.0);
}

void DisplayWrathWorld::drawHealthPickups3()
{
	int x = 18000;
	int y = 10100;
	int z = -10400;
	int size = 250;

	tp.CreateDisplayList(XY, 113, size, size, x, y, z, 1.0, 1.0);
	tp.CreateDisplayList(XY, 114, size, size, x, y, z - size, 1.0, 1.0);
	tp.CreateDisplayList(YZ, 115, size, size, x, y, z - size, 1.0, 1.0);
	tp.CreateDisplayList(YZ, 116, size, size, x + size, y, z - size, 1.0, 1.0);
	tp.CreateDisplayList(XZ, 117, size, size, x, y + size, z - size, 1.0, 1.0);
}

void DisplayWrathWorld::drawHealthPickups4()
{
	int x = 18000;
	int y = 10100;
	int z = -12400;
	int size = 250;

	tp.CreateDisplayList(XY, 118, size, size, x, y, z, 1.0, 1.0);
	tp.CreateDisplayList(XY, 119, size, size, x, y, z - size, 1.0, 1.0);
	tp.CreateDisplayList(YZ, 120, size, size, x, y, z - size, 1.0, 1.0);
	tp.CreateDisplayList(YZ, 121, size, size, x + size, y, z - size, 1.0, 1.0);
	tp.CreateDisplayList(XZ, 122, size, size, x, y + size, z - size, 1.0, 1.0);
}

void DisplayWrathWorld::drawHealthPickups5()
{
	int x = 10375;
	int y = 10100;
	int z = -14250;
	int size = 250;

	tp.CreateDisplayList(XY, 163, size, size, x, y, z, 1.0, 1.0);
	tp.CreateDisplayList(XY, 164, size, size, x, y, z - size, 1.0, 1.0);
	tp.CreateDisplayList(YZ, 165, size, size, x, y, z - size, 1.0, 1.0);
	tp.CreateDisplayList(YZ, 166, size, size, x + size, y, z - size, 1.0, 1.0);
	tp.CreateDisplayList(XZ, 167, size, size, x, y + size, z - size, 1.0, 1.0);
}

void DisplayWrathWorld::drawHealthPickups6()
{
	int x = 16375;
	int y = 10100;
	int z = -17250;
	int size = 250;

	tp.CreateDisplayList(XY, 168, size, size, x, y, z, 1.0, 1.0);
	tp.CreateDisplayList(XY, 169, size, size, x, y, z - size, 1.0, 1.0);
	tp.CreateDisplayList(YZ, 170, size, size, x, y, z - size, 1.0, 1.0);
	tp.CreateDisplayList(YZ, 171, size, size, x + size, y, z - size, 1.0, 1.0);
	tp.CreateDisplayList(XZ, 172, size, size, x, y + size, z - size, 1.0, 1.0);
}

// END OF HEALTH 
////////////////////////////////////////////////////////////////////////////////

void DisplayWrathWorld::displayShieldPickups()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SHIELD));
	for (int i = 93; i <= 94; ++i) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SHIELD_YZ));
	for (int i = 95; i <= 97; ++i) glCallList(i);
}

void DisplayWrathWorld::displayShieldPickups1()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SHIELD));
	for (int i = 123; i <= 124; ++i) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SHIELD_YZ));
	for (int i = 125; i <= 127; ++i) glCallList(i);
}

void DisplayWrathWorld::displayShieldPickups2()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SHIELD));
	for (int i = 128; i <= 129; ++i) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SHIELD_YZ));
	for (int i = 130; i <= 132; ++i) glCallList(i);
}

void DisplayWrathWorld::displayShieldPickups3()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SHIELD));
	for (int i = 133; i <= 134; ++i) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SHIELD_YZ));
	for (int i = 135; i <= 137; ++i) glCallList(i);
}

void DisplayWrathWorld::displayShieldPickups4()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SHIELD));
	for (int i = 138; i <= 139; ++i) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SHIELD_YZ));
	for (int i = 140; i <= 142; ++i) glCallList(i);
}

void DisplayWrathWorld::displayShieldPickups5()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SHIELD));
	for (int i = 173; i <= 174; ++i) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SHIELD_YZ));
	for (int i = 175; i <= 177; ++i) glCallList(i);
}

void DisplayWrathWorld::displayShieldPickups6()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SHIELD));
	for (int i = 178; i <= 179; ++i) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SHIELD_YZ));
	for (int i = 180; i <= 182; ++i) glCallList(i);
}

void DisplayWrathWorld::drawShieldPickups()
{
	int x = 16000;
	int y = 10100;
	int z = -500;
	int size = 250;

	tp.CreateDisplayList(XY, 93, size, size, x, y, z, 1.0, 1.0);
	tp.CreateDisplayList(XY, 94, size, size, x, y, z - size, 1.0, 1.0);
	tp.CreateDisplayList(YZ, 95, size, size, x, y, z - size, 1.0, 1.0);
	tp.CreateDisplayList(YZ, 96, size, size, x + size, y, z - size, 1.0, 1.0);
	tp.CreateDisplayList(XZ, 97, size, size, x, y + size, z - size, 1.0, 1.0);
}

void DisplayWrathWorld::drawShieldPickups1()
{
	int x = 12000;
	int y = 10100;
	int z = -6500;
	int size = 250;

	tp.CreateDisplayList(XY, 123, size, size, x, y, z, 1.0, 1.0);
	tp.CreateDisplayList(XY, 124, size, size, x, y, z - size, 1.0, 1.0);
	tp.CreateDisplayList(YZ, 125, size, size, x, y, z - size, 1.0, 1.0);
	tp.CreateDisplayList(YZ, 126, size, size, x + size, y, z - size, 1.0, 1.0);
	tp.CreateDisplayList(XZ, 127, size, size, x, y + size, z - size, 1.0, 1.0);
}

void DisplayWrathWorld::drawShieldPickups2()
{
	int x = 12000;
	int y = 10100;
	int z = -7000;
	int size = 250;

	tp.CreateDisplayList(XY, 128, size, size, x, y, z, 1.0, 1.0);
	tp.CreateDisplayList(XY, 129, size, size, x, y, z - size, 1.0, 1.0);
	tp.CreateDisplayList(YZ, 130, size, size, x, y, z - size, 1.0, 1.0);
	tp.CreateDisplayList(YZ, 131, size, size, x + size, y, z - size, 1.0, 1.0);
	tp.CreateDisplayList(XZ, 132, size, size, x, y + size, z - size, 1.0, 1.0);
}

void DisplayWrathWorld::drawShieldPickups3()
{
	int x = 6400;
	int y = 10100;
	int z = -6500;
	int size = 250;

	tp.CreateDisplayList(XY, 133, size, size, x, y, z, 1.0, 1.0);
	tp.CreateDisplayList(XY, 134, size, size, x, y, z - size, 1.0, 1.0);
	tp.CreateDisplayList(YZ, 135, size, size, x, y, z - size, 1.0, 1.0);
	tp.CreateDisplayList(YZ, 136, size, size, x + size, y, z - size, 1.0, 1.0);
	tp.CreateDisplayList(XZ, 137, size, size, x, y + size, z - size, 1.0, 1.0);
}

void DisplayWrathWorld::drawShieldPickups4()
{
	int x = 6400;
	int y = 10100;
	int z = -7500;
	int size = 250;

	tp.CreateDisplayList(XY, 138, size, size, x, y, z, 1.0, 1.0);
	tp.CreateDisplayList(XY, 139, size, size, x, y, z - size, 1.0, 1.0);
	tp.CreateDisplayList(YZ, 140, size, size, x, y, z - size, 1.0, 1.0);
	tp.CreateDisplayList(YZ, 141, size, size, x + size, y, z - size, 1.0, 1.0);
	tp.CreateDisplayList(XZ, 142, size, size, x, y + size, z - size, 1.0, 1.0);
}

void DisplayWrathWorld::drawShieldPickups5()
{
	int x = 10375;
	int y = 10100;
	int z = -17250;
	int size = 250;

	tp.CreateDisplayList(XY, 173, size, size, x, y, z, 1.0, 1.0);
	tp.CreateDisplayList(XY, 174, size, size, x, y, z - size, 1.0, 1.0);
	tp.CreateDisplayList(YZ, 175, size, size, x, y, z - size, 1.0, 1.0);
	tp.CreateDisplayList(YZ, 176, size, size, x + size, y, z - size, 1.0, 1.0);
	tp.CreateDisplayList(XZ, 177, size, size, x, y + size, z - size, 1.0, 1.0);
}

void DisplayWrathWorld::drawShieldPickups6()
{
	int x = 16375;
	int y = 10100;
	int z = -14250;
	int size = 250;

	tp.CreateDisplayList(XY, 178, size, size, x, y, z, 1.0, 1.0);
	tp.CreateDisplayList(XY, 179, size, size, x, y, z - size, 1.0, 1.0);
	tp.CreateDisplayList(YZ, 180, size, size, x, y, z - size, 1.0, 1.0);
	tp.CreateDisplayList(YZ, 181, size, size, x + size, y, z - size, 1.0, 1.0);
	tp.CreateDisplayList(XZ, 182, size, size, x, y + size, z - size, 1.0, 1.0);
}

// END OF SHIELD
//////////////////////////////////////////////////////////////////////////////////////////

void DisplayWrathWorld::displayAmmoPickups()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(AMMO));
	for (int i = 98; i <= 99; ++i) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(AMMO_YZ));
	for (int i = 100; i <= 102; ++i) glCallList(i);
}

void DisplayWrathWorld::displayAmmoPickups1()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(AMMO));
	for (int i = 143; i <= 144; ++i) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(AMMO_YZ));
	for (int i = 145; i <= 147; ++i) glCallList(i);
}

void DisplayWrathWorld::displayAmmoPickups2()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(AMMO));
	for (int i = 148; i <= 149; ++i) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(AMMO_YZ));
	for (int i = 150; i <= 152; ++i) glCallList(i);
}

void DisplayWrathWorld::displayAmmoPickups3()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(AMMO));
	for (int i = 153; i <= 154; ++i) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(AMMO_YZ));
	for (int i = 155; i <= 157; ++i) glCallList(i);
}

void DisplayWrathWorld::displayAmmoPickups4()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(AMMO));
	for (int i = 158; i <= 159; ++i) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(AMMO_YZ));
	for (int i = 160; i <= 162; ++i) glCallList(i);
}

void DisplayWrathWorld::displayAmmoPickups5()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(AMMO));
	for (int i = 183; i <= 184; ++i) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(AMMO_YZ));
	for (int i = 185; i <= 187; ++i) glCallList(i);
}

void DisplayWrathWorld::displayAmmoPickups6()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(AMMO));
	for (int i = 188; i <= 189; ++i) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(AMMO_YZ));
	for (int i = 190; i <= 192; ++i) glCallList(i);
}

void DisplayWrathWorld::drawAmmoPickups()
{
	int x = 16000;
	int y = 10100;
	int z = 500;
	int size = 250;
	
	tp.CreateDisplayList(XY, 98, size, size, x, y, z, 1.0, 1.0);
	tp.CreateDisplayList(XY, 99, size, size, x, y, z - size, 1.0, 1.0);
	tp.CreateDisplayList(YZ, 100, size, size, x, y, z - size, 1.0, 1.0);
	tp.CreateDisplayList(YZ, 101, size, size, x + size, y, z - size, 1.0, 1.0);
	tp.CreateDisplayList(XZ, 102, size, size, x, y + size, z - size, 1.0, 1.0);
}

void DisplayWrathWorld::drawAmmoPickups1()
{
	int x = 13000;
	int y = 10100;
	int z = -6500;
	int size = 250;

	tp.CreateDisplayList(XY, 143, size, size, x, y, z, 1.0, 1.0);
	tp.CreateDisplayList(XY, 144, size, size, x, y, z - size, 1.0, 1.0);
	tp.CreateDisplayList(YZ, 145, size, size, x, y, z - size, 1.0, 1.0);
	tp.CreateDisplayList(YZ, 146, size, size, x + size, y, z - size, 1.0, 1.0);
	tp.CreateDisplayList(XZ, 147, size, size, x, y + size, z - size, 1.0, 1.0);
}

void DisplayWrathWorld::drawAmmoPickups2()
{
	int x = 13000;
	int y = 10100;
	int z = -7000;
	int size = 250;

	tp.CreateDisplayList(XY, 148, size, size, x, y, z, 1.0, 1.0);
	tp.CreateDisplayList(XY, 149, size, size, x, y, z - size, 1.0, 1.0);
	tp.CreateDisplayList(YZ, 150, size, size, x, y, z - size, 1.0, 1.0);
	tp.CreateDisplayList(YZ, 151, size, size, x + size, y, z - size, 1.0, 1.0);
	tp.CreateDisplayList(XZ, 152, size, size, x, y + size, z - size, 1.0, 1.0);
}

void DisplayWrathWorld::drawAmmoPickups3()
{
	int x = 6400;
	int y = 10100;
	int z = -7000;
	int size = 250;

	tp.CreateDisplayList(XY, 153, size, size, x, y, z, 1.0, 1.0);
	tp.CreateDisplayList(XY, 154, size, size, x, y, z - size, 1.0, 1.0);
	tp.CreateDisplayList(YZ, 155, size, size, x, y, z - size, 1.0, 1.0);
	tp.CreateDisplayList(YZ, 156, size, size, x + size, y, z - size, 1.0, 1.0);
	tp.CreateDisplayList(XZ, 157, size, size, x, y + size, z - size, 1.0, 1.0);
}

void DisplayWrathWorld::drawAmmoPickups4()
{
	int x = 6400;
	int y = 10100;
	int z = -8000;
	int size = 250;

	tp.CreateDisplayList(XY, 158, size, size, x, y, z, 1.0, 1.0);
	tp.CreateDisplayList(XY, 159, size, size, x, y, z - size, 1.0, 1.0);
	tp.CreateDisplayList(YZ, 160, size, size, x, y, z - size, 1.0, 1.0);
	tp.CreateDisplayList(YZ, 161, size, size, x + size, y, z - size, 1.0, 1.0);
	tp.CreateDisplayList(XZ, 162, size, size, x, y + size, z - size, 1.0, 1.0);
}

void DisplayWrathWorld::drawAmmoPickups5()
{
	int x = 12000;
	int y = 10100;
	int z = -15875;
	int size = 250;

	tp.CreateDisplayList(XY, 183, size, size, x, y, z, 1.0, 1.0);
	tp.CreateDisplayList(XY, 184, size, size, x, y, z - size, 1.0, 1.0);
	tp.CreateDisplayList(YZ, 185, size, size, x, y, z - size, 1.0, 1.0);
	tp.CreateDisplayList(YZ, 186, size, size, x + size, y, z - size, 1.0, 1.0);
	tp.CreateDisplayList(XZ, 187, size, size, x, y + size, z - size, 1.0, 1.0);
}

void DisplayWrathWorld::drawAmmoPickups6()
{
	int x = 18000;
	int y = 10100;
	int z = -15875;
	int size = 250;

	tp.CreateDisplayList(XY, 188, size, size, x, y, z, 1.0, 1.0);
	tp.CreateDisplayList(XY, 189, size, size, x, y, z - size, 1.0, 1.0);
	tp.CreateDisplayList(YZ, 190, size, size, x, y, z - size, 1.0, 1.0);
	tp.CreateDisplayList(YZ, 191, size, size, x + size, y, z - size, 1.0, 1.0);
	tp.CreateDisplayList(XZ, 192, size, size, x, y + size, z - size, 1.0, 1.0);
}

// END OF AMMO
///////////////////////////////////////////////////////////////////////////////////////////

void DisplayWrathWorld::setHealth()
{
	pick.setHealthBox(0, 16000, 16250, -1500, -1250);
	pick.setHealthBox(1, 11000, 11250, -6500, -6250);
	pick.setHealthBox(2, 11000, 11250, -7000, -6750);
	pick.setHealthBox(3, 18000, 18250, -10400, -10150);
	pick.setHealthBox(4, 18000, 18250, -12400, -12150);
	pick.setHealthBox(5, 10375, 10625, -14250, -14000);
	pick.setHealthBox(6, 16375, 16625, -17250, -17000);
}

void DisplayWrathWorld::setShields()
{
	pick.setShieldBox(0, 16000, 16250, -500, -250);
	pick.setShieldBox(1, 12000, 12250, -6500, -6250);
	pick.setShieldBox(2, 12000, 12250, -7000, -6750);
	pick.setShieldBox(3, 6400, 6650, -6500, -6250);
	pick.setShieldBox(4, 6400, 6650, -7500, -7250);
	pick.setShieldBox(5, 10375, 10625, -17250, -17000);
	pick.setShieldBox(6, 16375, 16625, -14250, -14000);
}

void DisplayWrathWorld::setAmmo()
{
	pick.setAmmoBox(0, 16000, 16250, 250, 500);
	pick.setAmmoBox(1, 13000, 13250, -6500, -6250);
	pick.setAmmoBox(2, 13000, 13250, -7000, -6750);
	pick.setAmmoBox(3, 6400, 6650, -7000, -6750);
	pick.setAmmoBox(4, 6400, 6650, -8000, -7750);
	pick.setAmmoBox(5, 12000, 12250, -15875, -15625);
	pick.setAmmoBox(6, 18000, 18250, -15875, -15625);
}

void DisplayWrathWorld::collisionCheck()
{
	pick.checkHealthUp(cam.getX(), cam.getY(), cam.getZ());
	pick.checkShieldUp(cam.getX(), cam.getY(), cam.getZ());
	pick.checkAmmoUp(cam.getX(), cam.getY(), cam.getZ());
}

void DisplayWrathWorld::healthChecksDraw()
{
	if (pick.getGatheredHealth(0) == false) {
		drawHealthPickups();
	}
	if (pick.getGatheredHealth(1) == false) {
		drawHealthPickups1();
	}
	if (pick.getGatheredHealth(2) == false) {
		drawHealthPickups2();
	}
	if (pick.getGatheredHealth(3) == false) {
		drawHealthPickups3();
	}
	if (pick.getGatheredHealth(4) == false) {
		drawHealthPickups4();
	}
	if (pick.getGatheredHealth(5) == false) {
		drawHealthPickups5();
	}
	if (pick.getGatheredHealth(6) == false) {
		drawHealthPickups6();
	}
}

void DisplayWrathWorld::shieldChecksDraw()
{
	if (pick.getGatheredShield(0) == false) {
		drawShieldPickups();
	}
	if (pick.getGatheredShield(1) == false) {
		drawShieldPickups1();
	}
	if (pick.getGatheredShield(2) == false) {
		drawShieldPickups2();
	}
	if (pick.getGatheredShield(3) == false) {
		drawShieldPickups3();
	}
	if (pick.getGatheredShield(4) == false) {
		drawShieldPickups4();
	}
	if (pick.getGatheredShield(5) == false) {
		drawShieldPickups5();
	}
	if (pick.getGatheredShield(6) == false) {
		drawShieldPickups6();
	}
}

void DisplayWrathWorld::ammoChecksDraw()
{
	if (pick.getGatheredAmmo(0) == false) {
		drawAmmoPickups();
	}
	if (pick.getGatheredAmmo(1) == false) {
		drawAmmoPickups1();
	}
	if (pick.getGatheredAmmo(2) == false) {
		drawAmmoPickups2();
	}
	if (pick.getGatheredAmmo(3) == false) {
		drawAmmoPickups3();
	}
	if (pick.getGatheredAmmo(4) == false) {
		drawAmmoPickups4();
	}
	if (pick.getGatheredAmmo(5) == false) {
		drawAmmoPickups5();
	}
	if (pick.getGatheredAmmo(6) == false) {
		drawAmmoPickups6();
	}
}

void DisplayWrathWorld::healthChecksDisplay()
{
	if (pick.getGatheredHealth(0) == false) {
		displayHealthPickups();
	}
	if (pick.getGatheredHealth(1) == false) {
		displayHealthPickups1();
	}
	if (pick.getGatheredHealth(2) == false) {
		displayHealthPickups2();
	}
	if (pick.getGatheredHealth(3) == false) {
		displayHealthPickups3();
	}
	if (pick.getGatheredHealth(4) == false) {
		displayHealthPickups4();
	}
	if (pick.getGatheredHealth(5) == false) {
		displayHealthPickups5();
	}
	if (pick.getGatheredHealth(6) == false) {
		displayHealthPickups6();
	}
}

void DisplayWrathWorld::shieldChecksDisplay()
{
	if (pick.getGatheredShield(0) == false) {
		displayShieldPickups();
	}
	if (pick.getGatheredShield(1) == false) {
		displayShieldPickups1();
	}
	if (pick.getGatheredShield(2) == false) {
		displayShieldPickups2();
	}
	if (pick.getGatheredShield(3) == false) {
		displayShieldPickups3();
	}
	if (pick.getGatheredShield(4) == false) {
		displayShieldPickups4();
	}
	if (pick.getGatheredShield(5) == false) {
		displayShieldPickups5();
	}
	if (pick.getGatheredShield(6) == false) {
		displayShieldPickups6();
	}
}

void DisplayWrathWorld::ammoChecksDisplay()
{
	if (pick.getGatheredAmmo(0) == false) {
		displayAmmoPickups();
	}
	if (pick.getGatheredAmmo(1) == false) {
		displayAmmoPickups1();
	}
	if (pick.getGatheredAmmo(2) == false) {
		displayAmmoPickups2();
	}
	if (pick.getGatheredAmmo(3) == false) {
		displayAmmoPickups3();
	}
	if (pick.getGatheredAmmo(4) == false) {
		displayAmmoPickups4();
	}
	if (pick.getGatheredAmmo(5) == false) {
		displayAmmoPickups5();
	}
	if (pick.getGatheredAmmo(6) == false) {
		displayAmmoPickups6();
	}
}

// END OF PICKUPS
//////////////////////////////////////////////////////////////////////////////////////////////////

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
	drawServerWalls();
	
	healthChecksDraw();
	shieldChecksDraw();
	ammoChecksDraw();

	//last number used: 102
}