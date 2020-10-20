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
	cam.SetNoBoundingBoxes(55);


	// set starting position of user
	cam.Position(10000, 10550.0, 12150.0, 180.0);

	//Boss room
	//cam.Position(13500, 10550.0, -46820.0, 180.0);

	//electricity room
	//cam.Position(6780, 10550.0, -20950.0, 180.0);

	// creates bounding boxes and places in array
	CreateBoundingBoxes();
	// copies bounding boxes from array to linked lists (one fopr each quadrant)
	cam.InitiateBoundingBoxes();

	// load texture images and create display lists
	CreateTextureList();
	CreateTextures();

	initEnemies();
}

//--------------------------------------------------------------------------------------
//  Initialize Enemies
//--------------------------------------------------------------------------------------
void DisplayWrathWorld::initEnemies()
{
	for (int i = 0; i < NUM_ENEMIES; ++i)
	{
		enemyObjects.addObjectToBuffer(&enemies[i]);
		enemyObjects.getObjectFromBuffer(i)->setEnemyPosition(player.getPlayerLocationPointer());
	}
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
	cam.SetAABBMaxX(0, 7050.0);
	cam.SetAABBMinX(0, 6900.0);
	cam.SetAABBMaxZ(0, 12500.0);
	cam.SetAABBMinZ(0, 8500.0);

	cam.SetAABBMaxX(1, 13100.0);
	cam.SetAABBMinX(1, 12950.0);
	cam.SetAABBMaxZ(1, 12500.0);
	cam.SetAABBMinZ(1, 8500.0);

	cam.SetAABBMaxX(2, 9050.0);
	cam.SetAABBMinX(2, 7000.0);
	cam.SetAABBMaxZ(2, 8550.0);
	cam.SetAABBMinZ(2, 2450.0);

	cam.SetAABBMaxX(3, 19000.0);
	cam.SetAABBMinX(3, 10950.0);
	cam.SetAABBMaxZ(3, 8550.0);
	cam.SetAABBMinZ(3, 2450.0);

	cam.SetAABBMaxX(4, 9550.0);
	cam.SetAABBMinX(4, 8450.0);
	cam.SetAABBMaxZ(4, 11050.0);
	cam.SetAABBMinZ(4, 9950.0);

	cam.SetAABBMaxX(5, 11550.0);
	cam.SetAABBMinX(5, 10450.0);
	cam.SetAABBMaxZ(5, 11050.0);
	cam.SetAABBMinZ(5, 9950.0);

	cam.SetAABBMaxX(6, 11550.0);
	cam.SetAABBMinX(6, 8450.0);
	cam.SetAABBMaxZ(6, 10150.0);
	cam.SetAABBMinZ(6, 9950.0);

	cam.SetAABBMaxX(7, 19150.0);
	cam.SetAABBMinX(7, 18950.0);
	cam.SetAABBMaxZ(7, 2500.0);
	cam.SetAABBMinZ(7, -28500.0);

	cam.SetAABBMaxX(8, 7050.0);
	cam.SetAABBMinX(8, 5950.0);
	cam.SetAABBMaxZ(8, 2500.0);
	cam.SetAABBMinZ(8, -3550.0);

	cam.SetAABBMaxX(9, 6050.0);
	cam.SetAABBMinX(9, 3950.0);
	cam.SetAABBMaxZ(9, -3550.0);
	cam.SetAABBMinZ(9, -23550.0);

	cam.SetAABBMaxX(10, 7050.0);
	cam.SetAABBMinX(10, 5950.0);
	cam.SetAABBMaxZ(10, -13450.0);
	cam.SetAABBMinZ(10, -18550.0);

	cam.SetAABBMaxX(11, 4050.0);
	cam.SetAABBMinX(11, 3950.0);
	cam.SetAABBMaxZ(11, -23550.0);
	cam.SetAABBMinZ(11, -26450.0);

	cam.SetAABBMaxX(12, 6050.0);
	cam.SetAABBMinX(12, 3950.0);
	cam.SetAABBMaxZ(12, -26450.0);
	cam.SetAABBMinZ(12, -28550.0);

	cam.SetAABBMaxX(13, 11050.0);
	cam.SetAABBMinX(13, 1050.0);
	cam.SetAABBMaxZ(13, -28450.0);
	cam.SetAABBMinZ(13, -34050.0);

	cam.SetAABBMaxX(14, 1050.0);
	cam.SetAABBMinX(14, 850.0);
	cam.SetAABBMaxZ(14, -34050.0);
	cam.SetAABBMinZ(14, -45050.0);

	cam.SetAABBMaxX(15, 4800.0);
	cam.SetAABBMinX(15, 1050.0);
	cam.SetAABBMaxZ(15, -44950.0);
	cam.SetAABBMinZ(15, -49500.0);

	cam.SetAABBMaxX(16, 8550.0);
	cam.SetAABBMinX(16, 4700.0);
	cam.SetAABBMaxZ(16, -49450.0);
	cam.SetAABBMinZ(16, -53950.0);

	cam.SetAABBMaxX(17, 16550.0);
	cam.SetAABBMinX(17, 8450.0);
	cam.SetAABBMaxZ(17, -53950.0);
	cam.SetAABBMinZ(17, -54150.0);

	cam.SetAABBMaxX(18, 20400.0);
	cam.SetAABBMinX(18, 16450.0);
	cam.SetAABBMaxZ(18, -49450.0);
	cam.SetAABBMinZ(18, -54150.0);

	cam.SetAABBMaxX(19, 23950.0);
	cam.SetAABBMinX(19, 20200.0);
	cam.SetAABBMaxZ(19, -44950.0);
	cam.SetAABBMinZ(19, -49550.0);

	cam.SetAABBMaxX(20, 24150.0);
	cam.SetAABBMinX(20, 23950.0);
	cam.SetAABBMaxZ(20, -33950.0);
	cam.SetAABBMinZ(20, -45050.0);

	cam.SetAABBMaxX(21, 24050.0);
	cam.SetAABBMinX(21, 13950.0);
	cam.SetAABBMaxZ(21, -28450.0);
	cam.SetAABBMinZ(21, -34050.0);

	cam.SetAABBMaxX(22, 12950.0);
	cam.SetAABBMinX(22, 7050.0);
	cam.SetAABBMaxZ(22, 12650.0);
	cam.SetAABBMinZ(22, 12450.0);

	//interior
	cam.SetAABBMaxX(23, 17000.0);
	cam.SetAABBMinX(23, 7000.0);
	cam.SetAABBMaxZ(23, -3450.0);
	cam.SetAABBMinZ(23, -3550.0);

	cam.SetAABBMaxX(24, 19000.0);
	cam.SetAABBMinX(24, 18000.0);
	cam.SetAABBMaxZ(24, -3450.0);
	cam.SetAABBMinZ(24, -3550.0);

	cam.SetAABBMaxX(25, 12050.0);
	cam.SetAABBMinX(25, 8950.0);
	cam.SetAABBMaxZ(25, -4650.0);
	cam.SetAABBMinZ(25, -5950.0);

	cam.SetAABBMaxX(26, 12050.0);
	cam.SetAABBMinX(26, 8950.0);
	cam.SetAABBMaxZ(26, -7050.0);
	cam.SetAABBMinZ(26, -8350.0);

	cam.SetAABBMaxX(27, 17050.0);
	cam.SetAABBMinX(27, 13950.0);
	cam.SetAABBMaxZ(27, -4650.0);
	cam.SetAABBMinZ(27, -5950.0);

	cam.SetAABBMaxX(28, 17050.0);
	cam.SetAABBMinX(28, 13950.0);
	cam.SetAABBMaxZ(28, -7050.0);
	cam.SetAABBMinZ(28, -8350.0);

	cam.SetAABBMaxX(29, 7050.0);
	cam.SetAABBMinX(29, 6950.0);
	cam.SetAABBMaxZ(29, -3500.0);
	cam.SetAABBMinZ(29, -9500.0);

	cam.SetAABBMaxX(30, 8000.0);
	cam.SetAABBMinX(30, 6950.0);
	cam.SetAABBMaxZ(30, -9450.0);
	cam.SetAABBMinZ(30, -9550.0);

	cam.SetAABBMaxX(31, 19000.0);
	cam.SetAABBMinX(31, 9000.0);
	cam.SetAABBMaxZ(31, -9450.0);
	cam.SetAABBMinZ(31, -9550.0);

	cam.SetAABBMaxX(32, 17050.0);
	cam.SetAABBMinX(32, 6000.0);
	cam.SetAABBMaxZ(32, -11200.0);
	cam.SetAABBMinZ(32, -11800.0);

	cam.SetAABBMaxX(33, 19000.0);
	cam.SetAABBMinX(33, 8000.0);
	cam.SetAABBMaxZ(33, -13450.0);
	cam.SetAABBMinZ(33, -13550.0);

	cam.SetAABBMaxX(34, 8050.0);
	cam.SetAABBMinX(34, 7950.0);
	cam.SetAABBMaxZ(34, -13500.0);
	cam.SetAABBMinZ(34, -15500.0);

	cam.SetAABBMaxX(35, 8050.0);
	cam.SetAABBMinX(35, 7950.0);
	cam.SetAABBMaxZ(35, -16500.0);
	cam.SetAABBMinZ(35, -18500.0);

	cam.SetAABBMaxX(36, 14050.0);
	cam.SetAABBMinX(36, 12950.0);
	cam.SetAABBMaxZ(36, -13500.0);
	cam.SetAABBMinZ(36, -15550.0);

	cam.SetAABBMaxX(37, 14050.0);
	cam.SetAABBMinX(37, 12950.0);
	cam.SetAABBMaxZ(37, -16450.0);
	cam.SetAABBMinZ(37, -18500.0);

	cam.SetAABBMaxX(38, 11050.0);
	cam.SetAABBMinX(38, 9950.0);
	cam.SetAABBMaxZ(38, -15450.0);
	cam.SetAABBMinZ(38, -16550.0);

	cam.SetAABBMaxX(39, 17050.0);
	cam.SetAABBMinX(39, 15950.0);
	cam.SetAABBMaxZ(39, -15450.0);
	cam.SetAABBMinZ(39, -16550.0);

	cam.SetAABBMaxX(40, 19000.0);
	cam.SetAABBMinX(40, 8000.0);
	cam.SetAABBMaxZ(40, -18450.0);
	cam.SetAABBMinZ(40, -18550.0);

	cam.SetAABBMaxX(41, 19000.0);
	cam.SetAABBMinX(41, 6000.0);
	cam.SetAABBMaxZ(41, -23450.0);
	cam.SetAABBMinZ(41, -23550.0);

	cam.SetAABBMaxX(42, 6050.0);
	cam.SetAABBMinX(42, 5950.0);
	cam.SetAABBMaxZ(42, -23500.0);
	cam.SetAABBMinZ(42, -24500.0);

	cam.SetAABBMaxX(43, 6050.0);
	cam.SetAABBMinX(43, 5950.0);
	cam.SetAABBMaxZ(43, -25500.0);
	cam.SetAABBMinZ(43, -26500.0);

	cam.SetAABBMaxX(44, 11550.0);
	cam.SetAABBMinX(44, 10950.0);
	cam.SetAABBMaxZ(44, -25450.0);
	cam.SetAABBMinZ(44, -28550.0);

	cam.SetAABBMaxX(45, 14050.0);
	cam.SetAABBMinX(45, 13450.0);
	cam.SetAABBMaxZ(45, -25450.0);
	cam.SetAABBMinZ(45, -28550.0);

	cam.SetAABBMaxX(46, 6050.0);
	cam.SetAABBMinX(46, 3450.0);
	cam.SetAABBMaxZ(46, -36450.0);
	cam.SetAABBMinZ(46, -39050.0);

	cam.SetAABBMaxX(47, 21550.0);
	cam.SetAABBMinX(47, 18950.0);
	cam.SetAABBMaxZ(47, -36450.0);
	cam.SetAABBMinZ(47, -39050.0);

	cam.SetAABBMaxX(48, 9550.0);
	cam.SetAABBMinX(48, 8450.0);
	cam.SetAABBMaxZ(48, -41450.0);
	cam.SetAABBMinZ(48, -42550.0);

	cam.SetAABBMaxX(49, 16550.0);
	cam.SetAABBMinX(49, 15450.0);
	cam.SetAABBMaxZ(49, -41450.0);
	cam.SetAABBMinZ(49, -42550.0);

	cam.SetAABBMaxX(50, 14550.0);
	cam.SetAABBMinX(50, 10450.0);
	cam.SetAABBMaxZ(50, -49450.0);
	cam.SetAABBMinZ(50, -50550.0);

	// current AABB array size = 55
	// change array size with cam.SetNoBoundingBoxes() found in myinit()
}

bool DisplayWrathWorld::stairsReturnPortal()
{
	stepsReturn.setLocation(cam.getX(), cam.getY(), cam.getZ());
	stepsReturn.portalDimensions(-900, -500, -500);
	return(stepsReturn.createPortal(10450, 10600.0, 10600.0));
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

	image = tp.LoadTexture("data/electric.png");
	tp.CreatePNGTexture(ELECTRICITY, image, 512, 384);

	image = tp.LoadTexture("data/vent.png");
	tp.CreatePNGTexture(VENT, image, 352, 626);

	image = tp.LoadTexture("data/server.png");
	tp.CreatePNGTexture(SERVER, image, 800, 508);

	image = tp.LoadTexture("data/serveryz.png");
	tp.CreatePNGTexture(SERVER_YZ, image, 508, 800);

	image = tp.LoadTexture("data/enemy_front.png");
	tp.CreatePNGTexture(ENEMY_FRONT, image, 500, 500);

	image = tp.LoadTexture("data/enemy_back.png");
	tp.CreatePNGTexture(ENEMY_BACK, image, 500, 500);

	image = tp.LoadTexture("data/enemy_side.png");
	tp.CreatePNGTexture(ENEMY_SIDE, image, 500, 500);

	image = tp.LoadTexture("data/portalv2.png");
	tp.CreatePNGTexture(PORTAL_2, image, 2000, 2000);

	image = tp.LoadTexture("data/boss_front.png");
	tp.CreatePNGTexture(BOSS_FRONT, image, 500, 500);

	image = tp.LoadTexture("data/boss_back.png");
	tp.CreatePNGTexture(BOSS_BACK, image, 500, 500);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void DisplayWrathWorld::DrawBackdrop()
{
	displayEnemies();
	displaySkyBox();
	displayGroundPlane();
	displayPortal();
	displayInnerPortals();
	displayRoom1Walls();
	displayServerWalls();
	displayPowerWalls();
	displayBossRoom();

	healthChecksDisplay();
	shieldChecksDisplay();
	ammoChecksDisplay(); 

	ui.playerHealth(player.getHealth());
	ui.info(player.GetX(), player.GetY(), player.GetZ());

	if (player.getHealth() <= 0)
	{
		//cam.dead = true;
		//DisplayExit = true;
	}
}

void DisplayWrathWorld::displayEnemies()
{
	Point3D ray(cam.GetLX(), cam.GetLY(), cam.GetLZ());
	Point3D camPos(cam.getX(), cam.getY(), cam.getZ());
	player.updateLocation(cam.getX(), cam.getY(), cam.getZ());

	for (int i = 0; i < NUM_ENEMIES; ++i)
	{
		enemyObjects.getObjectFromBuffer(i)->stateMachine();

		//bottom
		glNewList(286, GL_COMPILE);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(enemies[i].getPoints()[4].x, enemies[i].getPoints()[4].y, enemies[i].getPoints()[4].z);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(enemies[i].getPoints()[5].x, enemies[i].getPoints()[5].y, enemies[i].getPoints()[5].z);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(enemies[i].getPoints()[6].x, enemies[i].getPoints()[6].y, enemies[i].getPoints()[6].z);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(enemies[i].getPoints()[7].x, enemies[i].getPoints()[7].y, enemies[i].getPoints()[7].z);
		glEnd();
		glEndList();

		//top
		glNewList(287, GL_COMPILE);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(enemies[i].getPoints()[0].x, enemies[i].getPoints()[0].y, enemies[i].getPoints()[0].z);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(enemies[i].getPoints()[1].x, enemies[i].getPoints()[1].y, enemies[i].getPoints()[1].z);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(enemies[i].getPoints()[2].x, enemies[i].getPoints()[2].y, enemies[i].getPoints()[2].z);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(enemies[i].getPoints()[3].x, enemies[i].getPoints()[3].y, enemies[i].getPoints()[3].z);
		glEnd();
		glEndList();

		//front
		glNewList(288, GL_COMPILE);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(enemies[i].getPoints()[4].x, enemies[i].getPoints()[4].y, enemies[i].getPoints()[4].z);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(enemies[i].getPoints()[0].x, enemies[i].getPoints()[0].y, enemies[i].getPoints()[0].z);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(enemies[i].getPoints()[3].x, enemies[i].getPoints()[3].y, enemies[i].getPoints()[3].z);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(enemies[i].getPoints()[7].x, enemies[i].getPoints()[7].y, enemies[i].getPoints()[7].z);
		glEnd();
		glEndList();

		//back
		glNewList(289, GL_COMPILE);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(enemies[i].getPoints()[6].x, enemies[i].getPoints()[6].y, enemies[i].getPoints()[6].z);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(enemies[i].getPoints()[2].x, enemies[i].getPoints()[2].y, enemies[i].getPoints()[2].z);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(enemies[i].getPoints()[1].x, enemies[i].getPoints()[1].y, enemies[i].getPoints()[1].z);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(enemies[i].getPoints()[5].x, enemies[i].getPoints()[5].y, enemies[i].getPoints()[5].z);
		glEnd();
		glEndList();

		//Left
		glNewList(290, GL_COMPILE);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(enemies[i].getPoints()[5].x, enemies[i].getPoints()[5].y, enemies[i].getPoints()[5].z);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(enemies[i].getPoints()[1].x, enemies[i].getPoints()[1].y, enemies[i].getPoints()[1].z);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(enemies[i].getPoints()[0].x, enemies[i].getPoints()[0].y, enemies[i].getPoints()[0].z);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(enemies[i].getPoints()[4].x, enemies[i].getPoints()[4].y, enemies[i].getPoints()[4].z);
		glEnd();
		glEndList();

		//Right
		glNewList(291, GL_COMPILE);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(enemies[i].getPoints()[7].x, enemies[i].getPoints()[7].y, enemies[i].getPoints()[7].z);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(enemies[i].getPoints()[3].x, enemies[i].getPoints()[3].y, enemies[i].getPoints()[3].z);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(enemies[i].getPoints()[2].x, enemies[i].getPoints()[2].y, enemies[i].getPoints()[2].z);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(enemies[i].getPoints()[6].x, enemies[i].getPoints()[6].y, enemies[i].getPoints()[6].z);
		glEnd();
		glEndList();

		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ENEMY_SIDE));
		glCallList(286);		// bottom
		glCallList(287);		// top
		glCallList(290);		// left
		glCallList(291);		// right

		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ENEMY_FRONT));
		glCallList(288);		// front

		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ENEMY_BACK));
		glCallList(289);		// back

		if (enemyObjects.detectCollisionWithBox(ray, camPos, enemyObjects.getObjectFromBuffer(i)->getAABB(), enemyObjects.getObjectFromBuffer(i)->getLocation()))
			ui.hitmarker();

		enemies[i].checkHit(&player);
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
	tp.CreateDisplayList(XZ, 4, 10240, 10240, -10000.0, -10000.0, -60000.0, 10, 13);	// Bottom
	tp.CreateDisplayList(XZ, 5, 10240, 10240, -10000.0, 92400.0, -60000.0, 10, 13);		// Top
	tp.CreateDisplayList(YZ, 6, 10240, 10240, -10000.0, -10000.0, -60000.0, 10, 13);	// FRONT
	tp.CreateDisplayList(YZ, 7, 10240, 10240, 30000.0, -10000.0, -60000.0, 10, 13);		// Back 
	tp.CreateDisplayList(XY, 8, 10240, 10240, -10000.0, -10000.0, -60000.0, 10, 10);	// Left
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
	tp.CreateDisplayList(XZ, 3, 431, 431, 0.0, 10000.0, -54000.0, 60, 160);	// groundPlane
	tp.CreateDisplayList(XZ, 87, 650, 1155, 0.0, 11500.0, -34000.0, 50, 50);	// ceiling
}

// PORTALS
/////////////////////////////////////////////////////////////////////////////////////////
void DisplayWrathWorld::displayPortal()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(PORTAL_1));
	glCallList(10);
}

void DisplayWrathWorld::drawPortal()
{
	tp.CreateDisplayList(XY, 10, 900, 1000, 9550, 10000, 10150, 1.0, 1);
}

void DisplayWrathWorld::displayInnerPortals()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(PORTAL_2));
	for (int i = 292; i <= 297; i++) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SPACESHIP_WALL_1));
	for (int i = 298; i <= 309; i++) glCallList(i);
}

void DisplayWrathWorld::drawInnerPortals()
{
	//electricity
	tp.CreateDisplayList(YZ, 292, 1000, 1000, 18900, 10000, -21500, 1.0, 1);
	tp.CreateDisplayList(YZ, 293, 1000, 1000, 18900, 10000, -26500, 1.0, 1);

	//server
	tp.CreateDisplayList(XY, 294, 1000, 1000, 7500, 10000, -3600, 1.0, 1);
	tp.CreateDisplayList(XY, 295, 1000, 1000, 17500, 10000, -9400, 1.0, 1);

	//boss
	tp.CreateDisplayList(YZ, 296, 1000, 1000, 1100, 10000, -44250, 1.0, 1);
	tp.CreateDisplayList(YZ, 297, 1000, 1000, 23900, 10000, -44250, 1.0, 1);

	//side supports
	//electricity
	tp.CreateDisplayList(XY, 298, 100, 250, 18900, 10000, -21500, 1.0, 4);
	tp.CreateDisplayList(XY, 299, 100, 250, 18900, 10000, -20500, 1.0, 4);

	tp.CreateDisplayList(XY, 300, 100, 250, 18900, 10000, -26500, 1.0, 4);
	tp.CreateDisplayList(XY, 301, 100, 250, 18900, 10000, -25500, 1.0, 4);

	//server
	tp.CreateDisplayList(YZ, 302, 250, 100, 7500, 10000, -3600, 4, 1);
	tp.CreateDisplayList(YZ, 303, 250, 100, 8500, 10000, -3600, 4, 1);

	tp.CreateDisplayList(YZ, 304, 250, 100, 17500, 10000, -9500, 4, 1);
	tp.CreateDisplayList(YZ, 305, 250, 100, 18500, 10000, -9500, 4, 1);

	//boss
	tp.CreateDisplayList(XY, 306, 100, 250, 1000, 10000, -44250, 1.0, 4);
	tp.CreateDisplayList(XY, 307, 100, 250, 1000, 10000, -43250, 1.0, 4);

	tp.CreateDisplayList(XY, 308, 100, 250, 23900, 10000, -44250, 1.0, 4);
	tp.CreateDisplayList(XY, 309, 100, 250, 23900, 10000, -43250, 1.0, 4);
}

void DisplayWrathWorld::servPortalL()
{
	serverPortal1.setLocation(cam.getX(), cam.getY(), cam.getZ());
	serverPortal1.portalDimensions(-1000, -500, -500);
	if (serverPortal1.createPortal(8500, 10600.0, -3500.0))
	{
		cam.Position(18000, 10550, -8500, 180);
	}
}

void DisplayWrathWorld::servPortalR()
{
	serverPortal2.setLocation(cam.getX(), cam.getY(), cam.getZ());
	serverPortal2.portalDimensions(-1000, -500, -500);
	if (serverPortal2.createPortal(18500, 10600.0, -9000.0))
	{
		cam.Position(8000, 10550, -4500, 180);
	}
}

void DisplayWrathWorld::elecPortal()
{
	electricityPortal.setLocation(cam.getX(), cam.getY(), cam.getZ());
	electricityPortal.portalDimensions(-500, -500, -1000);
	if (electricityPortal.createPortal(19000, 10600.0, -20500.0))
	{
		cam.Position(18000, 10550, -26000, 180);
	}
}

void DisplayWrathWorld::postElecPortal()
{
	postElectricityPortal.setLocation(cam.getX(), cam.getY(), cam.getZ());
	postElectricityPortal.portalDimensions(-500, -500, -1000);
	if (postElectricityPortal.createPortal(19000, 10600.0, -25500.0))
	{
		cam.Position(18000, 10550, -21000, 180);
	}
}

void DisplayWrathWorld::bossPortalL()
{
	bossPortal1.setLocation(cam.getX(), cam.getY(), cam.getZ());
	bossPortal1.portalDimensions(-500, -500, -1000);
	if (bossPortal1.createPortal(1500, 10600.0, -43250.0))
	{
		cam.Position(23000, 10550, -43750, 180);
	}
}

void DisplayWrathWorld::bossPortalR()
{
	bossPortal2.setLocation(cam.getX(), cam.getY(), cam.getZ());
	bossPortal2.portalDimensions(-500, -500, -1000);
	if (bossPortal2.createPortal(24000, 10600.0, -43250.0))
	{
		cam.Position(2000, 10550, -43750, 180);
	}
}

// END OF PORTALS
/////////////////////////////////////////////////////////////////////////////////////////

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

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SERVER));
	for (int i = 253; i <= 260; i++) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SERVER_YZ));
	for (int i = 261; i <= 268; ++i) glCallList(i);
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

	//servers xy walls
	tp.CreateDisplayList(XY, 253, 1000, 500, 9000, 10000, -4700, 3.0, 3.0);
	tp.CreateDisplayList(XY, 254, 1000, 500, 14000, 10000, -4700, 3.0, 3.0);
	tp.CreateDisplayList(XY, 255, 1000, 500, 9000, 10000, -5900, 3.0, 3.0);
	tp.CreateDisplayList(XY, 256, 1000, 500, 14000, 10000, -5900, 3.0, 3.0);

	tp.CreateDisplayList(XY, 257, 1000, 500, 9000, 10000, -7100, 3.0, 3.0);
	tp.CreateDisplayList(XY, 258, 1000, 500, 14000, 10000, -7100, 3.0, 3.0);
	tp.CreateDisplayList(XY, 259, 1000, 500, 9000, 10000, -8300, 3.0, 3.0);
	tp.CreateDisplayList(XY, 260, 1000, 500, 14000, 10000, -8300, 3.0, 3.0);

	//servers yz walls
	tp.CreateDisplayList(YZ, 261, 500, 1200, 9000, 10000, -8300, 3.0, 1.0);
	tp.CreateDisplayList(YZ, 262, 500, 1200, 9000, 10000, -5900, 3.0, 1.0);
	tp.CreateDisplayList(YZ, 263, 500, 1200, 12000, 10000, -8300, 3.0, 1.0);
	tp.CreateDisplayList(YZ, 264, 500, 1200, 12000, 10000, -5900, 3.0, 1.0);

	tp.CreateDisplayList(YZ, 265, 500, 1200, 14000, 10000, -8300, 3.0, 1.0);
	tp.CreateDisplayList(YZ, 266, 500, 1200, 14000, 10000, -5900, 3.0, 1.0);
	tp.CreateDisplayList(YZ, 267, 500, 1200, 17000, 10000, -8300, 3.0, 1.0);
	tp.CreateDisplayList(YZ, 268, 500, 1200, 17000, 10000, -5900, 3.0, 1.0);
}

void DisplayWrathWorld::displayPowerWalls()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SPACESHIP_WALL_1));
	glCallList(193);
	glCallList(196);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SPACESHIP_WALL_1_YZ));
	for (int i = 194; i <= 195; ++i) glCallList(i);
	glCallList(197);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SPACESHIP_WALL_1));
	for (int i = 198; i <= 203; ++i) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SPACESHIP_WALL_1_YZ));
	for (int i = 204; i <= 211; ++i) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SPACESHIP_WALL_1));
	for (int i = 212; i <= 213; ++i) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(VENT));
	glCallList(214);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SPACESHIP_WALL_1_YZ));
	for (int i = 215; i <= 218; ++i) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SPACESHIP_WALL_1));
	glCallList(219);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ELECTRICITY));
	for (int i = 246; i <= 252; ++i) glCallList(i);
}

void DisplayWrathWorld::drawPowerWalls()
{
	//electricity area
	tp.CreateDisplayList(XY, 193, 1000, 500, 6000, 10000, -23500, 13.0, 3.0);
	tp.CreateDisplayList(YZ, 194, 500, 1000, 6000, 10000, -23500, 3.0, 5.0);
	tp.CreateDisplayList(YZ, 195, 500, 1000, 19000, 10000, -23500, 3.0, 5.0);

	//after electricity
	tp.CreateDisplayList(XY, 196, 1000, 500, 6000, 10000, -18500, 1.0, 3.0);
	tp.CreateDisplayList(YZ, 197, 500, 1000, 19000, 10000, -28500, 3.0, 5.0);
	tp.CreateDisplayList(XY, 198, 1000, 500, 6000, 10000, -28500, 5.5, 3.0);
	tp.CreateDisplayList(XY, 199, 1000, 500, 6000, 11000, -28500, 7.5, 1.0);
	tp.CreateDisplayList(XY, 200, 1000, 500, 13500, 10000, -28500, 5.5, 3.0);

	//Entrance hallway
	tp.CreateDisplayList(XY, 201, 500, 500, 11500, 11000, -25500, 4.0, 1.0);
	tp.CreateDisplayList(XY, 202, 500, 500, 11000, 10000, -25500, 1.0, 3.0);
	tp.CreateDisplayList(XY, 203, 500, 500, 13500, 10000, -25500, 1.0, 3.0);

	tp.CreateDisplayList(YZ, 204, 500, 1000, 11000, 10000, -28500, 3, 3.0);
	tp.CreateDisplayList(YZ, 205, 500, 1000, 11500, 10000, -28500, 3, 3.0);
	tp.CreateDisplayList(YZ, 206, 500, 1000, 13500, 10000, -28500, 3, 3.0);
	tp.CreateDisplayList(YZ, 207, 500, 1000, 14000, 10000, -28500, 3, 3.0);

	//Hidden room
	tp.CreateDisplayList(YZ, 208, 500, 1000, 6000, 10000, -28500, 3, 3);
	tp.CreateDisplayList(YZ, 209, 500, 1000, 6000, 11000, -25500, 1, 1);
	tp.CreateDisplayList(YZ, 210, 500, 1000, 6000, 10000, -24500, 3, 1);

	tp.CreateDisplayList(YZ, 211, 500, 1000, 4000, 10000, -26500, 3, 3);
	tp.CreateDisplayList(XY, 212, 1000, 500, 4000, 10000, -26500, 2, 3);
	tp.CreateDisplayList(XY, 213, 1000, 500, 4000, 10000, -23500, 2, 3);
	
	//Vent
	tp.CreateDisplayList(YZ, 214, 1000, 1000, 6000, 10000, -25500, 1, 1);

	//Final Hallway
	tp.CreateDisplayList(YZ, 215, 500, 1000, 11000, 10000, -34000, 1, 5.5);
	tp.CreateDisplayList(YZ, 216, 500, 1000, 11000, 11000, -34000, 1, 5.5);
	tp.CreateDisplayList(YZ, 217, 500, 1000, 14000, 10000, -34000, 1, 5.5);
	tp.CreateDisplayList(YZ, 218, 500, 1000, 14000, 11000, -34000, 1, 5.5);
	tp.CreateDisplayList(XY, 219, 1000, 500, 11000, 11000, -34000, 3, 4);

	//electricity
	tp.CreateDisplayList(XZ, 246, 500, 500, 9000, 10010.0, -23500.0, 2, 4);
	tp.CreateDisplayList(XZ, 247, 500, 500, 13000, 10010.0, -23500.0, 6, 4);

	tp.CreateDisplayList(XZ, 248, 500, 500, 9000, 10010.0, -19500.0, 14, 2);
	tp.CreateDisplayList(XZ, 249, 500, 500, 9000, 10010.0, -20500.0, 6, 2);

	tp.CreateDisplayList(XZ, 250, 500, 500, 11000, 10010.0, -22500.0, 2, 4);
	tp.CreateDisplayList(XZ, 251, 500, 500, 13000, 10010.0, -21500.0, 2, 2);
	tp.CreateDisplayList(XZ, 252, 500, 500, 15000, 10010.0, -20500.0, 2, 2);
}

void DisplayWrathWorld::displayBossRoom()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SPACESHIP_WALL_1));
	for (int i = 220; i <= 227; ++i) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SPACESHIP_WALL_1_YZ));
	for (int i = 228; i <= 231; ++i) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SPACESHIP_WALL_1));
	for (int i = 232; i <= 233; ++i) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SPACESHIP_WALL_1_YZ));
	for (int i = 234; i <= 235; ++i) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SPACESHIP_WALL_1));
	for (int i = 236; i <= 237; ++i) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SPACESHIP_WALL_1_YZ));
	for (int i = 238; i <= 239; ++i) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SPACESHIP_WALL_1));
	for (int i = 240; i <= 241; ++i) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SPACESHIP_WALL_1_YZ));
	for (int i = 242; i <= 243; ++i) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SPACESHIP_WALL_1));
	for (int i = 244; i <= 245; ++i) glCallList(i);

	//controls xy
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SERVER));
	glCallList(269);
	glCallList(271);
	glCallList(275);
	glCallList(277);
	for (int i = 281; i <= 282; ++i) glCallList(i);

	//controls yz
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SERVER_YZ));
	glCallList(270);
	glCallList(272);
	glCallList(276);
	glCallList(278);
	for (int i = 284; i <= 285; ++i) glCallList(i);

	//control tops
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SERVER));
	glCallList(273);
	glCallList(274);
	glCallList(279);
	glCallList(280);
	glCallList(283);

}

void DisplayWrathWorld::drawBossRoom()
{
	tp.CreateDisplayList(XY, 220, 1000, 500, 1000, 10000, -34000, 10, 6);
	tp.CreateDisplayList(XY, 221, 1000, 500, 14000, 10000, -34000, 10, 6);

	//Front Window Supports
	tp.CreateDisplayList(XY, 222, 1000, 500, 8500, 10000, -54000, 8, 1);

	glNewList(223, GL_COMPILE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(1000, 10000, -45000);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(1000, 10500, -45000);
	glTexCoord2f(20.0, 1.0);
	glVertex3f(8500, 10500, -54000);
	glTexCoord2f(20.0, 0.0);
	glVertex3f(8500, 10000, -54000);
	glEnd();
	glEndList();

	glNewList(224, GL_COMPILE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(16500, 10000, -54000);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(16500, 10500, -54000);
	glTexCoord2f(20.0, 1.0);
	glVertex3f(24000, 10500, -45000);
	glTexCoord2f(20.0, 0.0);
	glVertex3f(24000, 10000, -45000);
	glEnd();
	glEndList();

	tp.CreateDisplayList(XY, 225, 1000, 500, 8500, 12500, -54000, 8, 1);

	glNewList(226, GL_COMPILE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(1000, 12500, -45000);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(1000, 13000, -45000);
	glTexCoord2f(20.0, 1.0);
	glVertex3f(8500, 13000, -54000);
	glTexCoord2f(20.0, 0.0);
	glVertex3f(8500, 12500, -54000);
	glEnd();
	glEndList();

	glNewList(227, GL_COMPILE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(16500, 12500, -54000);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(16500, 13000, -54000);
	glTexCoord2f(20.0, 1.0);
	glVertex3f(24000, 13000, -45000);
	glTexCoord2f(20.0, 0.0);
	glVertex3f(24000, 12500, -45000);
	glEnd();
	glEndList();

	//Side walls
	tp.CreateDisplayList(YZ, 228, 500, 1000, 1000, 10000, -45000, 6, 11);
	tp.CreateDisplayList(YZ, 229, 500, 1000, 24000, 10000, -45000, 6, 11);

	//Pillars
	tp.CreateDisplayList(YZ, 230, 500, 1000, 3500, 10000, -39000, 6, 2.5);
	tp.CreateDisplayList(YZ, 231, 500, 1000, 6000, 10000, -39000, 6, 2.5);
	tp.CreateDisplayList(XY, 232, 1000, 500, 3500, 10000, -39000, 2.5, 6);
	tp.CreateDisplayList(XY, 233, 1000, 500, 3500, 10000, -36500, 2.5, 6);

	tp.CreateDisplayList(YZ, 234, 500, 1000, 19000, 10000, -39000, 6, 2.5);
	tp.CreateDisplayList(YZ, 235, 500, 1000, 21500, 10000, -39000, 6, 2.5);
	tp.CreateDisplayList(XY, 236, 1000, 500, 19000, 10000, -39000, 2.5, 6);
	tp.CreateDisplayList(XY, 237, 1000, 500, 19000, 10000, -36500, 2.5, 6);

	tp.CreateDisplayList(YZ, 238, 500, 1000, 15500, 10000, -42500, 6, 1);
	tp.CreateDisplayList(YZ, 239, 500, 1000, 16500, 10000, -42500, 6, 1);
	tp.CreateDisplayList(XY, 240, 1000, 500, 15500, 10000, -42500, 1, 6);
	tp.CreateDisplayList(XY, 241, 1000, 500, 15500, 10000, -41500, 1, 6);

	tp.CreateDisplayList(YZ, 242, 500, 1000, 8500, 10000, -42500, 6, 1);
	tp.CreateDisplayList(YZ, 243, 500, 1000, 9500, 10000, -42500, 6, 1);
	tp.CreateDisplayList(XY, 244, 1000, 500, 8500, 10000, -42500, 1, 6);
	tp.CreateDisplayList(XY, 245, 1000, 500, 8500, 10000, -41500, 1, 6);

	//Control panels left 
	tp.CreateDisplayList(XY, 269, 1000, 500, 1000, 10000, -45000, 3.75, 1);
	tp.CreateDisplayList(YZ, 270, 500, 1000, 4750, 10000, -49500, 1, 4.5);

	tp.CreateDisplayList(XY, 271, 1000, 500, 4750, 10000, -49500, 3.75, 1);
	tp.CreateDisplayList(YZ, 272, 500, 1000, 8500, 10000, -54000, 1, 4.5);

	glNewList(273, GL_COMPILE);
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(1000, 10500, -45000);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(4750, 10500, -45000);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(4750, 10500, -49500);
	glEnd();
	glEndList();

	glNewList(274, GL_COMPILE);
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(4750, 10500, -49500);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(8500, 10500, -49500);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(8500, 10500, -54000);
	glEnd();
	glEndList();

	//Control Panels right
	tp.CreateDisplayList(XY, 275, 1000, 500, 20250, 10000, -45000, 3.75, 1);
	tp.CreateDisplayList(YZ, 276, 500, 1000, 20250, 10000, -49500, 1, 4.5);

	tp.CreateDisplayList(XY, 277, 1000, 500, 16500, 10000, -49500, 3.75, 1);
	tp.CreateDisplayList(YZ, 278, 500, 1000, 16500, 10000, -54000, 1, 4.5);

	glNewList(279, GL_COMPILE);
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(24000, 10500, -45000);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(20250, 10500, -45000);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(20250, 10500, -49500);
	glEnd();
	glEndList();

	glNewList(280, GL_COMPILE);
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(20250, 10500, -49500);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(16500, 10500, -49500);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(16500, 10500, -54000);
	glEnd();
	glEndList();

	//Centre controls
	tp.CreateDisplayList(XY, 281, 1000, 500, 10500, 10000, -49500, 4, 1);
	tp.CreateDisplayList(XY, 282, 1000, 500, 10500, 10000, -50500, 4, 1);
	tp.CreateDisplayList(XZ, 283, 1000, 1000, 10500, 10500, -50500, 4, 1);
	tp.CreateDisplayList(YZ, 284, 500, 1000, 10500, 10000, -50500, 1, 1);
	tp.CreateDisplayList(YZ, 285, 500, 1000, 14500, 10000, -50500, 1, 1);

	/*
	//Ceiling
	tp.CreateDisplayList(XZ, 230, 1000, 1000, 1000, 13000, -45000, 23, 11);
	
	//NEEDS FIXING
	glNewList(231, GL_COMPILE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(1000, 13000, -45000);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(24000, 13000, -45000);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(16500, 13000, -54000);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(8500, 13000, -54000);
	glEnd();
	glEndList();

	*/
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
	pick.setHealthBox(0, 16000, 16250, -1750, -1500);
	pick.setHealthBox(1, 11000, 11250, -6750, -6500);
	pick.setHealthBox(2, 11000, 11250, -7250, -7000);
	pick.setHealthBox(3, 18000, 18250, -10650, -10400);
	pick.setHealthBox(4, 18000, 18250, -12650, -12400);
	pick.setHealthBox(5, 10375, 10625, -14500, -14250);
	pick.setHealthBox(6, 16375, 16625, -17500, -17250);
}

void DisplayWrathWorld::setShields()
{
	pick.setShieldBox(0, 16000, 16250, -750, -500);
	pick.setShieldBox(1, 12000, 12250, -6750, -6500);
	pick.setShieldBox(2, 12000, 12250, -7250, -7000);
	pick.setShieldBox(3, 6400, 6650, -6750, -6500);
	pick.setShieldBox(4, 6400, 6650, -7750, -7500);
	pick.setShieldBox(5, 10375, 10625, -17500, -17250);
	pick.setShieldBox(6, 16375, 16625, -14500, -14250);
}

void DisplayWrathWorld::setAmmo()
{
	pick.setAmmoBox(0, 16000, 16250, 250, 500);
	pick.setAmmoBox(1, 13000, 13250, -6750, -6500);
	pick.setAmmoBox(2, 13000, 13250, -7250, -7000);
	pick.setAmmoBox(3, 6400, 6650, -7250, -7000);
	pick.setAmmoBox(4, 6400, 6650, -8250, -8000);
	pick.setAmmoBox(5, 12000, 12250, -16025, -15875);
	pick.setAmmoBox(6, 18000, 18250, -16025, -15875);
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
	drawInnerPortals();
	drawRoom1Walls();		//11-41
	drawServerWalls();
	drawPowerWalls();
	drawBossRoom();
	
	healthChecksDraw();
	shieldChecksDraw();
	ammoChecksDraw();

							//286-291 used in drawEnemies()

	//last number used: 309 (20/10/2020)
}