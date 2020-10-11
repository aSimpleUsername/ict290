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
	cam.Position(10000, 10550.0, 11000.0, 180.0);

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

	//Creating enemy object in the array at a given position
	enemyObjects.addObjectToBuffer(Enemy(10020, 10455, 10000));


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

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void DisplayWrathWorld::DrawBackdrop()
{
	displaySkyBox();
	displayGroundPlane();
	displayPortal();
	displayRoom1Walls();
	displayServerWalls();

	//enemy is drawn 
	enemyObjects.getObjectFromBuffer(0).drawEnemy();
	//hit detection is called from current look position(LX,LY,lZ) if collision is detected it outputs hit to console
	if (enemyObjects.detectCollisionWithSphere(cam.GetLX(), cam.GetLY(), cam.GetLZ(), cam.getX(), cam.getY(), cam.getZ())){
		std::cout << "hit" << std::endl;
	}

	
	healthChecksDisplay();
	shieldChecksDisplay();
	ammoChecksDisplay();

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

void DisplayWrathWorld::displayHealthPickups()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(HEALTH));
	for (int i = 88; i <= 92; ++i) glCallList(i);
}

void DisplayWrathWorld::drawHealthPickups()
{
	tp.CreateDisplayList(XY, 88, 250, 250, 9600, 10100, 5000, 1.0, 1.0);
	tp.CreateDisplayList(XY, 89, 250, 250, 9600, 10100, 4750, 1.0, 1.0);
	tp.CreateDisplayList(YZ, 90, 250, 250, 9600, 10100, 4750, 1.0, 1.0);
	tp.CreateDisplayList(YZ, 91, 250, 250, 9850, 10100, 4750, 1.0, 1.0);
	tp.CreateDisplayList(XZ, 92, 250, 250, 9600, 10350, 4750, 1.0, 1.0);
}

void DisplayWrathWorld::displayShieldPickups()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SHIELD));
	for (int i = 93; i <= 97; ++i) glCallList(i);
}

void DisplayWrathWorld::drawShieldPickups()
{
	tp.CreateDisplayList(XY, 93, 250, 250, 10100, 10100, 5000, 1.0, 1.0);
	tp.CreateDisplayList(XY, 94, 250, 250, 10100, 10100, 4750, 1.0, 1.0);
	tp.CreateDisplayList(YZ, 95, 250, 250, 10100, 10100, 4750, 1.0, 1.0);
	tp.CreateDisplayList(YZ, 96, 250, 250, 10350, 10100, 4750, 1.0, 1.0);
	tp.CreateDisplayList(XZ, 97, 250, 250, 10100, 10350, 4750, 1.0, 1.0);
}

void DisplayWrathWorld::displayAmmoPickups()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(AMMO));
	for (int i = 98; i <= 102; ++i) glCallList(i);
}

void DisplayWrathWorld::drawAmmoPickups()
{
	tp.CreateDisplayList(XY, 98, 250, 250, 10100, 10100, 4500, 1.0, 1.0);
	tp.CreateDisplayList(XY, 99, 250, 250, 10100, 10100, 4250, 1.0, 1.0);
	tp.CreateDisplayList(YZ, 100, 250, 250, 10100, 10100, 4250, 1.0, 1.0);
	tp.CreateDisplayList(YZ, 101, 250, 250, 10350, 10100, 4250, 1.0, 1.0);
	tp.CreateDisplayList(XZ, 102, 250, 250, 10100, 10350, 4250, 1.0, 1.0);
}

void DisplayWrathWorld::setHealth()
{
	pick.setHealthBox(0, 9600, 9850, 4750, 5000);
}

void DisplayWrathWorld::setShields()
{
	pick.setShieldBox(0, 10100, 10350, 4750, 5000);
}

void DisplayWrathWorld::setAmmo()
{
	pick.setAmmoBox(0, 10100, 10350, 4250, 4500);
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
}

void DisplayWrathWorld::shieldChecksDraw()
{
	if (pick.getGatheredShield(0) == false) {
		drawShieldPickups();
	}
}

void DisplayWrathWorld::ammoChecksDraw()
{
	if (pick.getGatheredAmmo(0) == false) {
		drawAmmoPickups();
	}
}

void DisplayWrathWorld::healthChecksDisplay()
{
	if (pick.getGatheredHealth(0) == false) {
		displayHealthPickups();
	}
}

void DisplayWrathWorld::shieldChecksDisplay()
{
	if (pick.getGatheredShield(0) == false) {
		displayShieldPickups();
	}
}

void DisplayWrathWorld::ammoChecksDisplay()
{
	if (pick.getGatheredAmmo(0) == false) {
		displayAmmoPickups();
	}
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
	drawServerWalls();
	
	healthChecksDraw();
	shieldChecksDraw();
	ammoChecksDraw();
	//last number used: 11
}