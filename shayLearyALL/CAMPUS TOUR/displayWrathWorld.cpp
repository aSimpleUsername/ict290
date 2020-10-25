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

	// creates bounding boxes and places in array
	CreateBoundingBoxes();
	// copies bounding boxes from array to linked lists (one fopr each quadrant)
	cam.InitiateBoundingBoxes();

	// load texture images and create display lists
	CreateTextureList();
	CreateTextures();

	initEnemies();
	//NEW
	setUpPowerups();
	// set starting position of user 
	cam.Position(10000, 10550.0, 12150.0, 180.0);

	//Boss room
	//cam.Position(13500, 10550.0, -46820.0, 180.0);

	//electricity room
	//cam.Position(6780, 10550.0, -20950.0, 180.0);

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

		for (int j = 0; j < enemies[i].MAX_PROJECTILES; ++j)
			enemies[i].getProjectiles(j)->setCollision(&cam.m_colDetect);
	}

	enemyBossObject.addObjectToBuffer(&boss);
	enemyBossObject.getObjectFromBuffer(0)->setEnemyPosition(player.getPlayerLocationPointer());

	for (int i = 0; i < boss.MAX_PROJECTILES; ++i)
		boss.getProjectiles(i)->setCollision(&cam.m_colDetect);
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
	cam.SetAABBMinZ(17, -54550.0);

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

	SetWallPoints();

	// current AABB array size = 55
	// change array size with cam.SetNoBoundingBoxes() found in myinit()
}

int DisplayWrathWorld::grabAmmo()
{
	return player.getAmmo();
}

void DisplayWrathWorld::reduceAmmo()
{
	player.decreaseAmmo();
}

void DisplayWrathWorld::ammoCheck()
{
	if (player.getAmmo() == 0) {
		player.reload();
	}
}

void DisplayWrathWorld::reload()
{
	player.reload();
}

void DisplayWrathWorld::SetWallPoints() {
	
	for (int i = 0; i < cam.m_colDetect.GetNoBoundingBoxes(); i++) {
		maxWallPoints.push_back(Point3D(cam.GetAABBMaxX(i), cam.GetAABBMaxY(i), cam.GetAABBMaxZ(i)));
		minWallPoints.push_back(Point3D(cam.GetAABBMinX(i), cam.GetAABBMinY(i), cam.GetAABBMinZ(i)));
	}
}

void DisplayWrathWorld::respawn()
{
	cam.Position(10000, 10550.0, 12150.0, 180.0);
	player.resetHealth();
	for (int i = 0; i < NUM_ENEMIES; ++i)
		enemies[i].reset();
	boss.reset();
	cam.dead = false;
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

	tp.LoadPNGTexture(WELCOME_SCREEN, "data/welcome.png");

	tp.LoadPNGTexture(EXIT_SCREEN, "data/thanks.png");

	tp.LoadPNGTexture(GROUND_PLANE, "data/groundPlane.png");

	tp.LoadPNGTexture(SPACE_1, "data/space_1.png");
	
	tp.LoadPNGTexture(PORTAL_1, "data/spaceportal.png");

	tp.LoadPNGTexture(SPACESHIP_WALL_1, "data/spaceship_wall_1.png");

	tp.LoadPNGTexture(SPACESHIP_WALL_1_YZ, "data/spaceship_wall_1_YZ.png");

	tp.LoadPNGTexture(CIRCUIT, "data/hexagon.png");
	
	tp.LoadPNGTexture(HEALTH, "data/heart.png");

	tp.LoadPNGTexture(SHIELD, "data/shield.png");

	tp.LoadPNGTexture(AMMO, "data/ammo.png");
	
	tp.LoadPNGTexture(HEALTH_YZ, "data/heartyz.png");
	
	tp.LoadPNGTexture(SHIELD_YZ, "data/shieldyz.png");
	
	tp.LoadPNGTexture(AMMO_YZ, "data/ammoyz.png");

	tp.LoadPNGTexture(ELECTRICITY, "data/electric.png");

	tp.LoadPNGTexture(VENT, "data/vent.png");

	tp.LoadPNGTexture(SERVER, "data/server.png");

	tp.LoadPNGTexture(SERVER_YZ, "data/serveryz.png");

	tp.LoadPNGTexture(ENEMY_FRONT,"data/enemy_front.png");

	tp.LoadPNGTexture(ENEMY_BACK, "data/enemy_back.png");

	tp.LoadPNGTexture(ENEMY_SIDE, "data/enemy_side.png");

	tp.LoadPNGTexture(PORTAL_2, "data/portalv2.png");

	tp.LoadPNGTexture(BOSS_FRONT, "data/boss_front.png");
	
	tp.LoadPNGTexture(BOSS_BACK, "data/boss_back.png");

	tp.LoadPNGTexture(GUN, "data/gun.png");

	tp.LoadPNGTexture(BOSS_NAME, "data/boss_name.png");

	tp.LoadPNGTexture(BOSS_HEALTH, "data/boss_health.png");

	tp.LoadPNGTexture(PLAYER_HEALTH, "data/player_health.png");

	tp.LoadPNGTexture(PLAYER_SHIELD, "data/player_shield.png");

	tp.LoadPNGTexture(PLAYER_HIT, "data/player_hit.png");

	tp.LoadPNGTexture(TRANSPARENT_1, "data/transparent.png");

	tp.LoadPNGTexture(HITMARKER, "data/hitmarker.png");

	tp.LoadPNGTexture(NUM_0, "data/num_0.png");

	tp.LoadPNGTexture(NUM_1, "data/num_1.png");

	tp.LoadPNGTexture(NUM_2, "data/num_2.png");

	tp.LoadPNGTexture(NUM_3, "data/num_3.png");

	tp.LoadPNGTexture(NUM_4, "data/num_4.png");

	tp.LoadPNGTexture(NUM_5, "data/num_5.png");

	tp.LoadPNGTexture(NUM_6, "data/num_6.png");

	tp.LoadPNGTexture(NUM_7, "data/num_7.png");

	tp.LoadPNGTexture(NUM_8, "data/num_8.png");

	tp.LoadPNGTexture(NUM_9, "data/num_9.png");
	tp.LoadPNGTexture(WIN, "data/win.png");
	tp.LoadPNGTexture(LOSE, "data/lose.png");
	
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);.
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void DisplayWrathWorld::DrawBackdrop()
{
	displayEnemies();
	displayBoss();
	displaySkyBox();
	displayGroundPlane();
	displayPortal();
	displayInnerPortals();
	displayRoom1Walls();
	displayServerWalls();
	displayPowerWalls();
	displayBossRoom();
	displayHealth();
	displayShields();
	displayAmmo();

	drawUI();
	if (player.getHealth() <= 0)
	{
		LoseState();
	}
	else
	{
		ui.playerHealth(player.getAmmo());
		ui.playerShield(player.getReserveAmmo());
		ui.info(cam.getX(), cam.getY(), cam.getZ());

		ui.hitmarker(1920, 1080, tp.GetTexture(HITMARKER));
		ui.healthBar(1920, 1080, tp.GetTexture(PLAYER_HEALTH));
		ui.shieldBar(1920, 1080, tp.GetTexture(PLAYER_SHIELD));
		ammoLogic();
		if (player.GetZ() < -30000)												// if player in boss room
		{
			ui.bossHealthBar(1920, 1080, tp.GetTexture(BOSS_HEALTH));
			ui.bossName(1920, 1080, tp.GetTexture(BOSS_NAME));
		}
		ui.transparent(1920, 1080, tp.GetTexture(TRANSPARENT_1));
		ui.weapon(1920, 1080, tp.GetTexture(GUN));
		ui.playerHit(1920, 1080, tp.GetTexture(PLAYER_HIT));
	}
}

void DisplayWrathWorld::ammoLogic()
{
	int arr[] = { NUM_0, NUM_1, NUM_2, NUM_3, NUM_4, NUM_5, NUM_6, NUM_7, NUM_8, NUM_9};
	
	if(player.getReserveAmmo() >= 0)
	{
		int remainder = player.getAmmo() % 10;

		ui.ammoCount1(1920, 1080, tp.GetTexture(arr[(player.getAmmo() - remainder) / 10]));
		ui.ammoCount2(1920, 1080, tp.GetTexture(arr[remainder]));

		int rRemainder = player.getReserveAmmo() % 10;

		ui.rAmmoCount1(1920, 1080, tp.GetTexture(arr[(player.getReserveAmmo() - rRemainder) / 10]));
		ui.rAmmoCount2(1920, 1080, tp.GetTexture(arr[rRemainder]));
	}
	else
	{
		ui.ammoCount1(1920, 1080, tp.GetTexture(arr[0]));
		ui.ammoCount2(1920, 1080, tp.GetTexture(arr[0]));

		ui.rAmmoCount1(1920, 1080, tp.GetTexture(arr[0]));
		ui.rAmmoCount2(1920, 1080, tp.GetTexture(arr[0]));
	}
	
}

void DisplayWrathWorld::displayEnemies()
{
	Point3D ray(cam.GetLX(), cam.GetLY(), cam.GetLZ());
	Point3D camPos(cam.getX(), cam.getY(), cam.getZ());
	player.updateLocation(cam.getX(), cam.getY(), cam.getZ());

	for (int i = 0; i < NUM_ENEMIES; ++i)
	{
		if (enemies[i].getHealth() > 0)
		{
			enemyObjects.getObjectFromBuffer(i)->stateMachine(engine);

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

			if (enemies[i].checkHit(&player))
				ui.m_playerHit = true;

			if (player.GetZ() < -30000)
				enemies[i].setState(ATTACK);
		}
	}

}

void DisplayWrathWorld::displayBoss()
{
	Point3D ray(cam.GetLX(), cam.GetLY(), cam.GetLZ());
	Point3D camPos(cam.getX(), cam.getY(), cam.getZ());
	player.updateLocation(cam.getX(), cam.getY(), cam.getZ());

	if (boss.getHealth() > 0)
	{
		enemyBossObject.getObjectFromBuffer(0)->stateMachine(engine);

		//bottom
		glNewList(286, GL_COMPILE);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(boss.getPoints()[4].x, boss.getPoints()[4].y, boss.getPoints()[4].z);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(boss.getPoints()[5].x, boss.getPoints()[5].y, boss.getPoints()[5].z);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(boss.getPoints()[6].x, boss.getPoints()[6].y, boss.getPoints()[6].z);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(boss.getPoints()[7].x, boss.getPoints()[7].y, boss.getPoints()[7].z);
		glEnd();
		glEndList();

		//top
		glNewList(287, GL_COMPILE);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(boss.getPoints()[0].x, boss.getPoints()[0].y, boss.getPoints()[0].z);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(boss.getPoints()[1].x, boss.getPoints()[1].y, boss.getPoints()[1].z);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(boss.getPoints()[2].x, boss.getPoints()[2].y, boss.getPoints()[2].z);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(boss.getPoints()[3].x, boss.getPoints()[3].y, boss.getPoints()[3].z);
		glEnd();
		glEndList();

		//front
		glNewList(288, GL_COMPILE);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(boss.getPoints()[4].x, boss.getPoints()[4].y, boss.getPoints()[4].z);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(boss.getPoints()[0].x, boss.getPoints()[0].y, boss.getPoints()[0].z);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(boss.getPoints()[3].x, boss.getPoints()[3].y, boss.getPoints()[3].z);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(boss.getPoints()[7].x, boss.getPoints()[7].y, boss.getPoints()[7].z);
		glEnd();
		glEndList();

		//back
		glNewList(289, GL_COMPILE);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(boss.getPoints()[6].x, boss.getPoints()[6].y, boss.getPoints()[6].z);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(boss.getPoints()[2].x, boss.getPoints()[2].y, boss.getPoints()[2].z);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(boss.getPoints()[1].x, boss.getPoints()[1].y, boss.getPoints()[1].z);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(boss.getPoints()[5].x, boss.getPoints()[5].y, boss.getPoints()[5].z);
		glEnd();
		glEndList();

		//Left
		glNewList(290, GL_COMPILE);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(boss.getPoints()[5].x, boss.getPoints()[5].y, boss.getPoints()[5].z);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(boss.getPoints()[1].x, boss.getPoints()[1].y, boss.getPoints()[1].z);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(boss.getPoints()[0].x, boss.getPoints()[0].y, boss.getPoints()[0].z);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(boss.getPoints()[4].x, boss.getPoints()[4].y, boss.getPoints()[4].z);
		glEnd();
		glEndList();

		//Right
		glNewList(291, GL_COMPILE);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(boss.getPoints()[7].x, boss.getPoints()[7].y, boss.getPoints()[7].z);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(boss.getPoints()[3].x, boss.getPoints()[3].y, boss.getPoints()[3].z);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(boss.getPoints()[2].x, boss.getPoints()[2].y, boss.getPoints()[2].z);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(boss.getPoints()[6].x, boss.getPoints()[6].y, boss.getPoints()[6].z);
		glEnd();
		glEndList();

		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ENEMY_SIDE));
		glCallList(286);		// bottom
		glCallList(287);		// top
		glCallList(290);		// left
		glCallList(291);		// right

		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(BOSS_FRONT));
		glCallList(288);		// front

		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(BOSS_BACK));
		glCallList(289);		// back

		boss.checkHit(&player);

		if (player.GetZ() < -30000)
			boss.setState(ATTACK);
	}
}

void DisplayWrathWorld::WinState() {
	
}
void DisplayWrathWorld::LoseState() {
		cam.dead = true;
		cam.DisplayWelcomeScreen(1920, 1080, 0, tp.GetTexture(LOSE));
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
	tp.CreateDisplayList(XZ, 3, 1000, 1000, 1000.0, 10000.0, -54000.0, 24, 68);	// groundPlane
	tp.CreateDisplayList(XZ, 87, 1000, 2000, 1000.0, 11500.0, -34000.0, 24, 24);	// ceiling
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
		cam.Position(8000, 10550, -4500, 0);
	}
}

void DisplayWrathWorld::elecPortal()
{
	electricityPortal.setLocation(cam.getX(), cam.getY(), cam.getZ());
	electricityPortal.portalDimensions(-500, -500, -1000);
	if (electricityPortal.createPortal(19000, 10600.0, -20500.0))
	{
		cam.Position(18000, 10550, -26000, 270);
	}
}

void DisplayWrathWorld::postElecPortal()
{
	postElectricityPortal.setLocation(cam.getX(), cam.getY(), cam.getZ());
	postElectricityPortal.portalDimensions(-500, -500, -1000);
	if (postElectricityPortal.createPortal(19000, 10600.0, -25500.0))
	{
		cam.Position(18000, 10550, -21000, 270);
	}
}

void DisplayWrathWorld::bossPortalL()
{
	bossPortal1.setLocation(cam.getX(), cam.getY(), cam.getZ());
	bossPortal1.portalDimensions(-500, -500, -1000);
	if (bossPortal1.createPortal(1500, 10600.0, -43250.0))
	{
		cam.Position(23000, 10550, -43750, 270);
	}
}

void DisplayWrathWorld::bossPortalR()
{
	bossPortal2.setLocation(cam.getX(), cam.getY(), cam.getZ());
	bossPortal2.portalDimensions(-500, -500, -1000);
	if (bossPortal2.createPortal(24000, 10600.0, -43250.0))
	{
		cam.Position(2000, 10550, -43750, 90);
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

// ELECTRICITY CHECK
/////////////////////////////////////////////////////////////////////////////////////////////
void DisplayWrathWorld::electricFloor(float maxX, float minX, float maxZ, float minZ)
{
	float x = cam.getX();
	float z = cam.getZ();

	if (x < maxX && x > minX)
	{
		if (z < maxZ && z > minZ)
		{
			player.decreaseHealth();
		}
	}
}

void DisplayWrathWorld::electricFloorCheck()
{
	electricFloor(10000, 9000, -21500, -23500);
	electricFloor(16000, 13000, -21500, -23500);
	electricFloor(16000, 9000, -18500, -19500);
	electricFloor(12000, 9000, -19500, -20500);
	electricFloor(12000, 11000, -20500, -22500);
	electricFloor(14000, 13000, -20500, -21500); 
	electricFloor(16000, 15000, -19500, -20500);
}
/////////////////////////////////////////////////////////////////////////////////////////////

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

	//ceiling
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(CIRCUIT));
	for (int i = 310; i <= 311; ++i) glCallList(i);

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

	
	//Ceiling
	tp.CreateDisplayList(XZ, 310, 1000, 1000, 1000, 13000, -45000, 23, 11);
	
	//NEEDS FIXING
	glNewList(311, GL_COMPILE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(1000.0, 13000.0, -45000.0);
	glTexCoord2f(0.0, 10.0);
	glVertex3f(24000.0, 13000.0, -45000.0);
	glTexCoord2f(10.0, 10.0);
	glVertex3f(16500.0, 13000.0, -54000.0);
	glTexCoord2f(10.0, 0.0);
	glVertex3f(8500.0, 13000.0, -54000.0);
	glEnd();
	glEndList();

}

// PICKUPS
//////////////////////////////////////////////////////////////////////////////////////////////////

void DisplayWrathWorld::setUpPowerups()
{
	Pickups h1, h2, h3 ,h4;
	Pickups s1, s2, s3;
	Pickups a1, a2, a3, a4, a5, a6, a7, a8, a9;

	h1.setPickup(13000, 10100, -6500, 250);
	h2.setPickup(18000, 10100, -11500, 250);
	h3.setPickup(17500, 10100, -22500, 250);
	h4.setPickup(12500, 10100, -52000, 250);

	s1.setPickup(6500, 10100, -7500, 250);
	s2.setPickup(18000, 10100, -16000, 250);
	s3.setPickup(13500, 10100, -52000, 250);

	a1.setPickup(18000, 10100, -6500, 250);
	a2.setPickup(8000, 10100, -6500, 250);
	a3.setPickup(6500, 10100, -8500, 250);
	a4.setPickup(13500, 10100, -16000, 250);
	a5.setPickup(7500, 10100, -22000, 250);
	a6.setPickup(17500, 10100, -19500, 250);
	a7.setPickup(12500, 10100, -31000, 250);
	a8.setPickup(2250, 10100, -36000, 250);
	a9.setPickup(22500, 10100, -36000, 250);

	hPowerup.push_back(h1);
	hPowerup.push_back(h2);
	hPowerup.push_back(h3);
	hPowerup.push_back(h4);

	sPowerup.push_back(s1);
	sPowerup.push_back(s2);
	sPowerup.push_back(s3);

	aPowerup.push_back(a1);
	aPowerup.push_back(a2);
	aPowerup.push_back(a3);
	aPowerup.push_back(a4);
	aPowerup.push_back(a5);
	aPowerup.push_back(a6);
	aPowerup.push_back(a7);
	aPowerup.push_back(a8);
	aPowerup.push_back(a9);
}

void DisplayWrathWorld::displayHealth()
{
	for (int i = 0; i < hPowerup.size(); i++)
	{
		tp.CreateDisplayList(XY, 312, hPowerup[i].getSize(), hPowerup[i].getSize(), hPowerup[i].getX(), hPowerup[i].getY(), hPowerup[i].getZ(), 1.0, 1.0);
		tp.CreateDisplayList(XY, 313, hPowerup[i].getSize(), hPowerup[i].getSize(), hPowerup[i].getX(), hPowerup[i].getY(), hPowerup[i].getZ() - hPowerup[i].getSize(), 1.0, 1.0);
		tp.CreateDisplayList(YZ, 314, hPowerup[i].getSize(), hPowerup[i].getSize(), hPowerup[i].getX(), hPowerup[i].getY(), hPowerup[i].getZ() - hPowerup[i].getSize(), 1.0, 1.0);
		tp.CreateDisplayList(YZ, 315, hPowerup[i].getSize(), hPowerup[i].getSize(), hPowerup[i].getX() + hPowerup[i].getSize(), hPowerup[i].getY(), hPowerup[i].getZ() - hPowerup[i].getSize(), 1.0, 1.0);
		tp.CreateDisplayList(XZ, 316, hPowerup[i].getSize(), hPowerup[i].getSize(), hPowerup[i].getX(), hPowerup[i].getY() + hPowerup[i].getSize(), hPowerup[i].getZ() - hPowerup[i].getSize(), 1.0, 1.0);

		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(HEALTH));
		for (int i = 312; i <= 313; ++i) glCallList(i);

		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(HEALTH_YZ));
		for (int i = 314; i <= 316; ++i) glCallList(i);
	}
}

void DisplayWrathWorld::displayShields()
{
	for (int i = 0; i < sPowerup.size(); i++)
	{
		tp.CreateDisplayList(XY, 317, sPowerup[i].getSize(), sPowerup[i].getSize(), sPowerup[i].getX(), sPowerup[i].getY(), sPowerup[i].getZ(), 1.0, 1.0);
		tp.CreateDisplayList(XY, 318, sPowerup[i].getSize(), sPowerup[i].getSize(), sPowerup[i].getX(), sPowerup[i].getY(), sPowerup[i].getZ() - sPowerup[i].getSize(), 1.0, 1.0);
		tp.CreateDisplayList(YZ, 319, sPowerup[i].getSize(), sPowerup[i].getSize(), sPowerup[i].getX(), sPowerup[i].getY(), sPowerup[i].getZ() - sPowerup[i].getSize(), 1.0, 1.0);
		tp.CreateDisplayList(YZ, 320, sPowerup[i].getSize(), sPowerup[i].getSize(), sPowerup[i].getX() + sPowerup[i].getSize(), sPowerup[i].getY(), sPowerup[i].getZ() - sPowerup[i].getSize(), 1.0, 1.0);
		tp.CreateDisplayList(XZ, 321, sPowerup[i].getSize(), sPowerup[i].getSize(), sPowerup[i].getX(), sPowerup[i].getY() + sPowerup[i].getSize(), sPowerup[i].getZ() - sPowerup[i].getSize(), 1.0, 1.0);

		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SHIELD));
		for (int i = 317; i <= 318; ++i) glCallList(i);

		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SHIELD_YZ));
		for (int i = 319; i <= 321; ++i) glCallList(i);
	}
}

void DisplayWrathWorld::displayAmmo()
{
	for (int i = 0; i < aPowerup.size(); i++)
	{
		tp.CreateDisplayList(XY, 322, aPowerup[i].getSize(), aPowerup[i].getSize(), aPowerup[i].getX(), aPowerup[i].getY(), aPowerup[i].getZ(), 1.0, 1.0);
		tp.CreateDisplayList(XY, 323, aPowerup[i].getSize(), aPowerup[i].getSize(), aPowerup[i].getX(), aPowerup[i].getY(), aPowerup[i].getZ() - aPowerup[i].getSize(), 1.0, 1.0);
		tp.CreateDisplayList(YZ, 324, aPowerup[i].getSize(), aPowerup[i].getSize(), aPowerup[i].getX(), aPowerup[i].getY(), aPowerup[i].getZ() - aPowerup[i].getSize(), 1.0, 1.0);
		tp.CreateDisplayList(YZ, 325, aPowerup[i].getSize(), aPowerup[i].getSize(), aPowerup[i].getX() + aPowerup[i].getSize(), aPowerup[i].getY(), aPowerup[i].getZ() - aPowerup[i].getSize(), 1.0, 1.0);
		tp.CreateDisplayList(XZ, 326, aPowerup[i].getSize(), aPowerup[i].getSize(), aPowerup[i].getX(), aPowerup[i].getY() + aPowerup[i].getSize(), aPowerup[i].getZ() - aPowerup[i].getSize(), 1.0, 1.0);

		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(AMMO));
		for (int i = 322; i <= 323; ++i) glCallList(i);

		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(AMMO_YZ));
		for (int i = 324; i <= 326; ++i) glCallList(i);
	}
}

void DisplayWrathWorld::collectionCheck()
{
	for (int i = 0; i < hPowerup.size(); i++)
	{
		if (player.getHealth() < player.getMaxHealth())
		{
			hPowerup[i].checkCollision(cam.getX(), cam.getZ());

			if (hPowerup[i].getGath())
			{
				hPowerup.erase(hPowerup.begin() + i);
				player.incrementHealth();
			}
		}
	}

	for (int i = 0; i < sPowerup.size(); i++)
	{
		if (player.getShields() < player.getMaxShield())
		{
			sPowerup[i].checkCollision(cam.getX(), cam.getZ());

			if (sPowerup[i].getGath())
			{
				sPowerup.erase(sPowerup.begin() + i);
				player.incrementShields();
			}
		}
	}

	for (int i = 0; i < aPowerup.size(); i++)
	{
		aPowerup[i].checkCollision(cam.getX(), cam.getZ());

		if (aPowerup[i].getGath())
		{
			aPowerup.erase(aPowerup.begin() + i);
		}
	}
}

// END OF PICKUPS
//////////////////////////////////////////////////////////////////////////////////////////////////

void DisplayWrathWorld::drawUI()
{
	//health bar
	tp.CreateDisplayList(0, 350, 50.0, 50.0, 0.0, 0.0, 0.0, player.getHealth(), 1.0);

	//shield bar
	tp.CreateDisplayList(0, 351, 50.0, 50.0, 0.0, 0.0, 0.0, player.getShields(), 1.0);

	//boss health bar
	tp.CreateDisplayList(0, 353, 10.0, 50.0, 0.0, 0.0, 0.0, boss.getHealth(), 1.0);
	//tp.CreateDisplayList(0, 353, 20.0, 50.0, 0.0, 0.0, 0.0, boss.getHealth(), 1.0);

	//boss name
	tp.CreateDisplayList(0, 354, 200.0, 50.0, 0.0, 0.0, 0.0, 1.0, 1.0);

	//weapon
	tp.CreateDisplayList(0, 355, 646 * 2.25, 387 * 2.25, 0.0, 0.0, 0.0, 1.0, 1.0);

	//player hit
	tp.CreateDisplayList(0, 356, 1920, 1080, 0.0, 0.0, 0.0, 1.0, 1.0);

	//transparent to stop line in gun texture bug
	tp.CreateDisplayList(0, 357, 1100, 300, 0.0, 0.0, 0.0, 1.0, 1.0);

	//hitmarker
	tp.CreateDisplayList(0, 358, 50, 50, 0.0, 0.0, 0.0, 1.0, 1.0);

	//ammo
	tp.CreateDisplayList(0, 352, 100.0, 100.0, 0.0, 0.0, 0.0, 1.0, 1.0);
	tp.CreateDisplayList(0, 359, 100.0, 100.0, 0.0, 0.0, 0.0, 1.0, 1.0);

	//reserve ammo
	tp.CreateDisplayList(0, 360, 50.0, 50.0, 0.0, 0.0, 0.0, 1.0, 1.0);
	tp.CreateDisplayList(0, 361, 50.0, 50.0, 0.0, 0.0, 0.0, 1.0, 1.0);
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
	drawInnerPortals();
	drawRoom1Walls();		//11-41
	drawServerWalls();
	drawPowerWalls();
	drawBossRoom();

	//286-291 used in drawEnemies()

	//last number used: 326 (24/10/2020)
}