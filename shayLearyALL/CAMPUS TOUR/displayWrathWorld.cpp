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
	cam.Position(10000, 10000.0, 10000.0, 180.0);

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
	cam.SetAABBMaxX(0, 35879.0);
	cam.SetAABBMinX(0, 33808.0);
	cam.SetAABBMaxZ(0, 22096.0);
	cam.SetAABBMinZ(0, 4688.0);
	// current AABB array size = 5
	// change array size with cam.SetNoBoundingBoxes() found in myinit()
}

void DisplayWrathWorld::CreateTextures()
{
	glEnable(GL_DEPTH_TEST);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// set texture count
	tp.SetTextureCount(256);

	image = tp.LoadTexture("data/bricks1.raw", 128, 128);
	tp.CreateTexture(WALL_BRICK_YZ, image, 128, 128);

	image = tp.LoadTexture("data/bricks2.raw", 128, 128);
	tp.CreateTexture(WALL_BRICK_XY, image, 128, 128);

	image = tp.LoadTexture("data/bricks2edge.raw", 128, 128);
	tp.CreateTexture(WALL_BRICK_XY_END, image, 128, 128);

	image = tp.LoadTexture("data/bricks1edge.raw", 128, 128);
	tp.CreateTexture(WALL_BRICK_YZ_END, image, 128, 128);

	image = tp.LoadTexture("data/bricks075.raw", 128, 128);
	tp.CreateTexture(WALL_BRICK_3_4, image, 128, 128);

	image = tp.LoadTexture("data/brick87.raw", 128, 128);
	tp.CreateTexture(WALL_BRICK_XY_87WIDTH, image, 128, 128);

	image = tp.LoadTexture("data/brickgap.raw", 128, 32);
	tp.CreateTexture(WALL_BRICK_GAP_YZ, image, 128, 32);

	image = tp.LoadTexture("data/brickgap2.raw", 128, 32);
	tp.CreateTexture(WALL_BRICK_GAP2_YZ, image, 128, 32);

	image = tp.LoadTexture("data/bricksecsign.raw", 256, 128);
	tp.CreateTexture(WALL_BRICK_SEC_SIGN, image, 256, 128);

	image = tp.LoadTexture("data/brickshadow.raw", 128, 128);
	tp.CreateTexture(SHADOW_BRICK, image, 128, 128);

	image = tp.LoadTexture("data/bricksUSD.raw", 128, 128);
	tp.CreateTexture(WALL_BRICK_USD_YZ, image, 128, 128);

	image = tp.LoadTexture("data/wallgap1.raw", 8, 128);
	tp.CreateTexture(WALL_GAP_1, image, 8, 128);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void DisplayWrathWorld::DrawBackdrop()
{
	DisplayBricks();
	glColor3f(1.0, 0.0, 0.0);
	glutSolidSphere(5.0, 20.0, 20.0);
	printf("Backdrop\n");
}

void DisplayWrathWorld::DisplayBricks()
{
	// WALL_BRICK_YZ
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_YZ));
	for (int i = 101; i < 111; i++) glCallList(i);
	for (int i = 112; i < 126; i++) glCallList(i);
	for (int i = 191; i < 195; i++) glCallList(i);
	for (int i = 583; i < 586; i++) glCallList(i);	// new courtyard calls
	glPushMatrix();
	glTranslatef(0.0, 0.0, 1920.0);
	glCallList(1);
	glCallList(2);
	glCallList(3);
	glPopMatrix();
	glCallList(4);
	glCallList(5);
	glCallList(6);
	glCallList(7);
	glCallList(598);
	glCallList(599);

	// bricks with security sign
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_SEC_SIGN));
	glCallList(398);

	// WALL_BRICK_USD_YZ
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_USD_YZ));
	for (int i = 200; i < 202; i++) glCallList(i);
	glCallList(188);


	// WALL_BRICK_XY
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_XY));
	for (int i = 135; i < 165; i++) glCallList(i);
	for (int i = 217; i < 222; i++) glCallList(i);
	for (int i = 586; i < 590; i++) glCallList(i);		// new courtyard calls
	glPushMatrix();
	glTranslatef(0.0, 1024.0, 0.0);
	glCallList(152);
	glPopMatrix();
	for (int i = 195; i < 198; i++) glCallList(i);
	glCallList(392);


	// WALL_BRICK_GAP_YZ
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_GAP_YZ));
	for (int i = 180; i < 182; i++) glCallList(i);
	glPushMatrix();
	glTranslatef(0.0, 1024.0, 0.0);
	glCallList(180);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 0.0, -1920.0);
	glCallList(181);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_GAP2_YZ));
	glCallList(182);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_GAP_1));
	for (int i = 183; i < 185; i++) glCallList(i);

	// WALL_BRICK_XY_END
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_XY_END));
	for (int i = 165; i < 168; i++) glCallList(i);
	glCallList(134);
	glCallList(185);
	glCallList(187);
	glCallList(399);
	glPushMatrix();
	glTranslatef(-32.0, 0.0, 640.0);
	glCallList(399);
	glPopMatrix();
	step = -832.0;
	for (int i = 0; i < 2; i++)
	{
		glPushMatrix();
		glTranslatef(0.0, 0.0, step);
		glCallList(166);
		glPopMatrix();
		step += 1920;
	}
	glPushMatrix();
	glTranslatef(0.0, 0.0, 321.0);
	glCallList(167);
	glPopMatrix();
	for (int i = 131; i < 132; i++) glCallList(i);
	glCallList(132);
	glPushMatrix();
	glTranslatef(0.0, 0.0, 960.0);
	glCallList(132);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 0.0, 8640.0);
	glCallList(132);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 0.0, 9600.0);
	glCallList(132);
	glPopMatrix();
	glCallList(133);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_XY_87WIDTH));
	glCallList(130);
	glCallList(186);

	// WALL_BRICK_YZ_END
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_YZ_END));
	for (int i = 126; i < 130; i++) glCallList(i);
	glPushMatrix();
	glTranslatef(-896.0, 0.0, 0.0);
	glCallList(128);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 1088.0, 0.0);
	glCallList(129);
	glCallList(168);
	glPopMatrix();
	for (int i = 168; i < 170; i++) glCallList(i);
	glCallList(390);
	glCallList(391);
	glCallList(393);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_3_4));
	glCallList(189);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SHADOW_BRICK));
	glCallList(190);
}

void DisplayWrathWorld::DrawBricks()
{
	// WALL_BRICK_YZ
	// --------  (Face of Cancerllary Building) --------
	tp.CreateDisplayList(YZ, 1, 128.0, 128.0, 33808.0, 9872.0, 9552.0, 2.5, 7.5);		// panel 1 (above steps)
	tp.CreateDisplayList(YZ, 2, 128.0, 128.0, 33840.0, 8976.0, 5840.0, 23.625, 5.0);		// panel 1 (before steps)
	tp.CreateDisplayList(YZ, 3, 128.0, 128.0, 33808.0, 8976.0, 6480.0, 23.625, 24.0);	// panel 2 (below steps)
	tp.CreateDisplayList(YZ, 4, 128.0, 128.0, 33808.0, 10000.0, 11472.0, 1.5, 60.0);		// panel 3 (below window 1)
	tp.CreateDisplayList(YZ, 5, 128.0, 128.0, 33808.0, 10000.0, 20112.0, 1.5, 15.5);		// panel 4 (below window 2)	
	tp.CreateDisplayList(YZ_FLIP, 6, 128.0, 128.0, 33808.0, 10960.0, 9552.0, 2.0, 97.5);	// us panel 4
	tp.CreateDisplayList(YZ, 7, 128.0, 128.0, 33808.0, 10960.0, 22032.0, 2.0, 0.5);		// us panel 4 (last 1/2 brick)

	// -------- (Face of Physical Science/Shops Block) --------
	tp.CreateDisplayList(YZ, 106, 128.0, 128.0, 33808.0, 10000.0, 25344.0, 4.525, 11.0);	// panel 1 (around rusty man)
	tp.CreateDisplayList(YZ, 107, 128.0, 128.0, 33808.0, 11024.0, 25344.0, 6.5, 10.0);		// us panel 1
	tp.CreateDisplayList(YZ, 108, 128.0, 128.0, 33808.0, 11024.0, 26624.0, 2.5, 113.305);	// us panel 2
	tp.CreateDisplayList(YZ, 109, 128.0, 128.0, 33808.0, 10000.0, 27559.0, 3.5, 8.5);		// panel 3 (toilets window)
	tp.CreateDisplayList(YZ, 394, 128.0, 128.0, 33808.0, 10384.0, 27559.0, 1.0, 7.5);		// panel 3 (toilets window)
	tp.CreateDisplayList(YZ, 110, 128.0, 128.0, 33872.0, 9936.0, 28967.0, 6.5, 4.5);		// panel 4 (toilets door)
	tp.CreateDisplayList(YZ, 112, 128.0, 128.0, 33808.0, 10000.0, 33422.0, 2.0, 14.4);		// panel 5 (booth)
	tp.CreateDisplayList(YZ, 113, 128.0, 128.0, 33808.0, 10128.0, 33422.0, 3.0, 5.5);		// panel 5 (booth below window)
	tp.CreateDisplayList(YZ, 188, 128.0, 128.0, 33808.0, 10128.0, 34254.0, 3.0, 1.0);		// panel 5 (booth below window)
	tp.CreateDisplayList(YZ, 115, 128.0, 128.0, 34260.0, 10000.0, 36319.0, 2.5, 2.5);		// panel 6 (phys sci doorway)
	tp.CreateDisplayList(YZ, 191, 128.0, 128.0, 34260.0, 10256.0, 36319.0, 4.5, 1.5);		// panel 6 (phys sci doorway)
	tp.CreateDisplayList(YZ, 192, 128.0, 128.0, 34260.0, 10576.0, 36383.0, 2.0, 2.0);		// panel 6 (phys sci doorway)
	tp.CreateDisplayList(YZ, 114, 128.0, 128.0, 33808.0, 10000.0, 37855.0, 2.05, 10.51);	// panel 7 (with window)
	tp.CreateDisplayList(YZ, 116, 128.0, 128.0, 33808.0, 10128.0, 37855.0, 5.5, 1.05);		// panel 7 (with window)
	tp.CreateDisplayList(YZ, 396, 128.0, 128.0, 33808.0, 10128.0, 38111.0, 5.5, 1.0);		// panel 7 (with window)
	tp.CreateDisplayList(YZ, 397, 128.0, 128.0, 33808.0, 10512.0, 37855.0, 2.5, 3.0);		// panel 7 (with window)
	tp.CreateDisplayList(YZ, 398, 256.0, 128.0, 33808.0, 10256.0, 37983.0, 1.05, 1.1);		// panel 7 (with sign)
	tp.CreateDisplayList(YZ_FLIP, 117, 128.0, 128.0, 33808.0, 10128.0, 38560.0, 5.5, 0.5);	// panel 7 (with window)
	tp.CreateDisplayList(YZ, 118, 128.0, 128.0, 33808.0, 10128.0, 38624.0, 5.5, 4.5);		// panel 7 (with window)
	tp.CreateDisplayList(YZ, 119, 128.0, 128.0, 33808.0, 10000.0, 40615.0, 6.5, 4.0);		// panel 8 (end panel)
	tp.CreateDisplayList(YZ, 121, 128.0, 128.0, 34256.0, 9936.0, 27303.0, 3.0, 2.0);		// first doorway panel
	tp.CreateDisplayList(YZ, 193, 128.0, 128.0, 34256.0, 10576.0, 27303.0, 2.0, 2.0);		// first doorway panel
	tp.CreateDisplayList(YZ, 194, 128.0, 128.0, 34256.0, 10192.0, 27431.0, 3.5, 1.0);		// first doorway panel

	// -------- (Face of Canteen Block) --------
	tp.CreateDisplayList(YZ, 122, 128.0, 128.0, 2608.0, 10000.0, 10000.0, 7.0, 243.5);		// long downstairs panel
	tp.CreateDisplayList(YZ, 123, 128.0, 128.0, 2608.0, 10000.0, 42960.0, 7.0, 21.0);		// end downstairs panel
	tp.CreateDisplayList(YZ, 124, 128.0, 128.0, 2608.0, 11088.0, 10000.0, 7.0, 278.5);		// long upstairs panel

	// -------- (courtyard near bookshop) -------
	tp.CreateDisplayList(XY, 136, 128.0, 128.0, -25700.0, 10000.0, 42960.0, 221.2, 7.0);	// corner exit to psc block from canteen (bookshop) 136
	tp.CreateDisplayList(YZ, 583, 128.0, 128.0, -200.0, 10000.0, 29800, 14.0, 75.8);			// "Canteen Block" lower downstairs panel
	tp.CreateDisplayList(XY, 586, 128.0, 128.0, -200.0, 10000.0, 39499.0, 21.95, 14.0);		// inner downstairs wall
	tp.CreateDisplayList(XY, 587, 128.0, 128.0, -200.0, 10000.0, 41168.5, 21.95, 7.0);		// stairs outerwall (bookshop side) downstairs
	tp.CreateDisplayList(XY, 588, 128.0, 128.0, -200.0, 10000.0, 40790.0, 21.95, 14.0);		// stairs inner wall (bookshop side) downstairs wall
	tp.CreateDisplayList(XY, 589, 128.0, 128.0, -25700.0, 10000.0, 29800, 200.0, 21.0);		// courtyard wall parrallel to bookshop
	tp.CreateDisplayList(YZ, 584, 128.0, 128.0, -200.0, 10000.0, 40790.0, 14.0, 3.0);		// stairs wall joiner
	tp.CreateDisplayList(YZ, 585, 128.0, 128.0, -25700.0, 10000.0, 29800, 7.0, 90.5);		// courtyard wall parrallel to bushcourt
	tp.CreateDisplayList(YZ, 598, 128.0, 128.0, -200.0, 10900.0, 39400.0, 7.0, 11.5);		// above stairs entrance
	tp.CreateDisplayList(YZ, 599, 128.0, 128.0, 900.0, 10900.0, 39400.0, 7.0, 11.5);			// wall behind portal

	// WALL_BRICK_USD_YZ
	tp.CreateDisplayList(YZ, 200, 128.0, 128.0, 33808.0, 10576.0, 25344.0, 2.0, 1.0);		// panel 1 (around rusty man)
	tp.CreateDisplayList(YZ, 201, 128.0, 128.0, 33808.0, 10576.0, 26496.0, 2.0, 2.0);		// panel 1 (around rusty man)

	// WALL_BRICK_XY
	// --------  (Cancerllary Building) --------
	tp.CreateDisplayList(XY, 399, 128.0, 128.0, 33840.0, 8976.0, 5840.0, 0.5, 23.625);	// first corner edge (bottom of steps)
	tp.CreateDisplayList(XY, 130, 128.0, 128.0, 33808.0, 10960.0, 22096.0, 0.68, 2.0);	// below us window (end wall)
	tp.CreateDisplayList(XY, 131, 128.0, 128.0, 33808.0, 10192.0, 9552.0, 0.68, 15.5);	// above steps
	tp.CreateDisplayList(XY, 132, 128.0, 128.0, 33808.0, 10000.0, 10512.0, 0.68, 1.5);	// first door (others)
	tp.CreateDisplayList(XY, 133, 128.0, 128.0, 33808.0, 11344.0, 26624.0, 0.68, 4.0);	// next us window phys sci
	tp.CreateDisplayList(XY, 143, 128.0, 128.0, 33895.0, 10000.0, 22096.0, 15.5, 16.0);	// end wall
	tp.CreateDisplayList(XY, 186, 128.0, 128.0, 33808.0, 10000.0, 22096.0, 0.68, 1.5);	// end wall
	// --------  (Phys Science Block) -------
	tp.CreateDisplayList(XY, 197, 128.0, 128.0, 33808.0, 10640.0, 25344.0, 1.5, 1.5);		// end wall above telephones
	tp.CreateDisplayList(XY, 196, 128.0, 128.0, 33936.0, 10640.0, 25344.0, 6.0, 1.505);	// end wall above telephones
	tp.CreateDisplayList(XY, 195, 128.0, 128.0, 34576.0, 10128.0, 25344.0, 1.0, 6.5);		// next to telephones
	tp.CreateDisplayList(XY, 190, 128.0, 128.0, 34704.0, 10000.0, 25344.0, 9.5, 5.75);	// end wall behind drinks machine
	tp.CreateDisplayList(XY, 189, 128.0, 128.0, 34704.0, 10736.0, 25344.0, 9.5, 0.75);	// end wall above drinks machine
	tp.CreateDisplayList(XY, 144, 128.0, 128.0, 33808.0, 10000.0, 25344.0, 7.0, 1.6);		// end wall
	tp.CreateDisplayList(XY, 145, 128.0, 128.0, 33876.0, 9936.0, 36319.0, 3.0, 7.0);		// ps 2nd door(leftside entrance)
	tp.CreateDisplayList(XY, 146, 128.0, 128.0, 33808.0, 9936.0, 37855.0, 4.25, 7.0);		// ps 2nd door(rightside entrance)
	tp.CreateDisplayList(XY, 147, 128.0, 128.0, 33808.0, 9936.0, 26752, 4.0, 7.0);		// ps first door (left bottom)
	tp.CreateDisplayList(XY, 148, 128.0, 128.0, 33808.0, 9936.0, 27559.0, 3.5, 4.5);		// ps first door (right bottom)
	tp.CreateDisplayList(XY, 149, 128.0, 128.0, 33872.0, 10384.0, 27559.0, 3.0, 3.5);		// ps first door (right top)
	tp.CreateDisplayList(XY, 185, 128.0, 128.0, 34256.0, 10000.0, 27303.0, 0.5, 6.5);		// ps first door (1/2 inner brick)
	tp.CreateDisplayList(XY, 166, 128.0, 128.0, 33808.0, 10000.0, 29479.0, 0.5, 4.0);		// side of toilet doors phys sci
	tp.CreateDisplayList(XY, 167, 128.0, 128.0, 33808.0, 10256.0, 38239.0, 0.75, 4.5);	// side of small window phys sci
	tp.CreateDisplayList(XY_FLIP, 152, 128.0, 128.0, 33936.0, 10832.0, 25344.0, 15.5, 2.5);	// end wall panel 2 phys sci
	tp.CreateDisplayList(XY, 153, 128.0, 128.0, 33808.0, 11024.0, 25344.0, 17.5, 6.5);	// end wall panel 3 phys sci
	tp.CreateDisplayList(XY, 165, 128.0, 128.0, 34260.0, 10000.0, 36639.0, 0.7, 6.5);		// ps 2nd door(inner 1/2 brick)
	tp.CreateDisplayList(XY, 187, 128.0, 128.0, 33808.0, 10256.0, 34382.0, 0.5, 2.0);		// side of toilet doors phys sci

	// --------  (Library Block) --------
	tp.CreateDisplayList(XY, 154, 128.0, 128.0, 33616.0, 10000.0, 43056.0, 19.0, 6.0);	// first panel
	tp.CreateDisplayList(XY, 155, 128.0, 128.0, 30800.0, 10000.0, 43056.0, 15.0, 6.0);	// 2nd panel
	tp.CreateDisplayList(XY, 156, 128.0, 128.0, 27976.0, 9936.0, 43056.0, 12.0, 3.0);		// 3rd panel (next to KBLT)
	tp.CreateDisplayList(XY, 217, 128.0, 128.0, 29512.0, 9936.0, 43056.0, 10.0, 2.75);	// 3rd panel (below nexus sign)
	tp.CreateDisplayList(XY, 157, 128.0, 128.0, 24264.0, 10256.0, 43056.0, 1.5, 4.0);		// 4th panel (next to KBLT)
	tp.CreateDisplayList(XY, 218, 128.0, 128.0, 24264.0, 10000.0, 43056.0, 11.5, 2.5);	// around glass boards
	tp.CreateDisplayList(XY, 219, 128.0, 128.0, 25352.0, 10192.0, 43056.0, 3.0, 4.5);		// around glass boards
	tp.CreateDisplayList(XY, 220, 128.0, 128.0, 27976.0, 10192.0, 43056.0, 3.0, 4.5);		// around glass boards
	tp.CreateDisplayList(XY, 221, 128.0, 128.0, 29256.0, 10192.0, 43056.0, 2.0, 4.5);		// around glass boards
	tp.CreateDisplayList(XY, 158, 128.0, 128.0, 30800.0, 11024.0, 43056.0, 41.0, 6.5);	// US 1st panel
	tp.CreateDisplayList(XY, 159, 128.0, 128.0, 24264.0, 11024.0, 43056.0, 51.0, 6.5);	// US 2nd panel
	tp.CreateDisplayList(XY, 160, 128.0, 128.0, 22984.0, 10000.0, 43056.0, 9.0, 2.0);		// US 3rd panel (start of ds library)
	tp.CreateDisplayList(XY, 161, 128.0, 128.0, 10952.0, 10000.0, 43056.0, 94.0, 2.5);	// US 4th panel (under of ds library)
	tp.CreateDisplayList(XY, 162, 128.0, 128.0, 6600.0, 11024.0, 43056.0, 137.0, 2.5);	// US 4th panel (under of ds library)
	tp.CreateXtoYWindowList(434, 43056.0, 6856.0, 256.0, 10256.0, 512.0, 1.0, 1.0);		// End of DS (Map)
	tp.CreateDisplayList(XY, 433, 128.0, 128.0, 7112.0, 10640.0, 43056.0, 8.0, 1.0);		// End DS
	tp.CreateDisplayList(XY, 432, 128.0, 128.0, 7112.0, 10128.0, 43056.0, 1.5, 5.0);		// End DS
	tp.CreateDisplayList(XY, 431, 128.0, 128.0, 8072.0, 10064.0, 43056.0, 0.914, 5.5);		// End DS
	tp.CreateDisplayList(XY, 430, 128.0, 128.0, 6600.0, 10128.0, 43056.0, 2.0, 5.0);		// End DS
	tp.CreateDisplayList(XY, 163, 128.0, 128.0, 6600.0, 10000.0, 43056.0, 12.414, 2.0);	// End DS
	tp.CreateDisplayList(XY, 164, 128.0, 128.0, 6600.0, 11024.0, 43056.0, 17.29, 6.5);		// End US
	tp.CreateDisplayList(YZ, 126, 128.0, 128.0, 6600.0, 10000.0, 43056.0, 6.0, 0.5);		// end panel corner
	tp.CreateDisplayList(YZ, 125, 128.0, 128.0, 6514.0, 10000.0, 43120.0, 14.5, 20.5);		// end panel
	tp.CreateDisplayList(YZ, 127, 128.0, 128.0, 6600.0, 11024.0, 43056.0, 6.5, 0.5);		// end panel top
	tp.CreateDisplayList(YZ, 128, 128.0, 128.0, 33616.0, 9936.0, 43056.0, 6.5, 0.75);		// cgl1 side panel
	tp.CreateDisplayList(YZ, 129, 128.0, 128.0, 24264.0, 9936.0, 43056.0, 6.5, 0.5);		// gap in middle of library
	tp.CreateDisplayList(YZ, 168, 128.0, 128.0, 24136.0, 9936.0, 43056.0, 2.5, 0.5);		// gap in middle of library
	tp.CreateDisplayList(YZ, 169, 128.0, 128.0, 8813.12, 11344.0, 43056.0, 4.0, 0.5);		// edge of first us window post
	tp.CreateDisplayList(XY, 135, 128.0, 128.0, 24072.0, 10000.0, 43120.0, 1.5, 17.0);		// middle of gap
	tp.CreateDisplayList(XY, 134, 128.0, 128.0, 6514.0, 10000.0, 43120.0, 0.75, 14.5);		// end corner
	tp.CreateDisplayList(XY, 141, 128.0, 128.0, 33104.0, 10000.0, 43152.0, 1.0, 6.0);		// brick between gcl1 doors
	tp.CreateDisplayList(XY, 140, 128.0, 128.0, 34448.0, 9424.0, 43056.0, 12.5, 4.5);		// end below stairs
	tp.CreateDisplayList(YZ, 390, 128.0, 128.0, 10952.0, 10000.0, 43056.0, 2.5, 0.75);		// side of library door
	tp.CreateDisplayList(YZ, 391, 128.0, 128.0, 8189.0, 10000.0, 43056.0, 6.0, 0.5);		// side of library door
	tp.CreateDisplayList(XY, 392, 128.0, 128.0, 10952.0, 10320.0, 43152.0, 0.25, 3.5);		// side edge of library door

	// --------  (Phys Sci Building very end wall by steps) --------
	tp.CreateDisplayList(XY, 142, 128.0, 128.0, 33808.0, 10000.0, 41127.0, 11.5, 6.5);
	tp.CreateDisplayList(XY, 150, 128.0, 128.0, 33808.0, 11024.0, 41127.0, 16.5, 2.5);
	tp.CreateDisplayList(XY, 151, 128.0, 128.0, 34448.0, 9360.0, 41127.0, 6.5, 5.5);		// below window
	tp.CreateDisplayList(XY, 137, 128.0, 128.0, 35280.0, 9296.0, 41127.0, 6.0, 6.5);		// below window
	tp.CreateDisplayList(XY, 138, 128.0, 128.0, 35600.0, 10000.0, 41127.0, 3.5, 6.5);
	tp.CreateDisplayList(XY, 139, 128.0, 128.0, 33872.0, 11216.0, 41127.0, 12.5, 6.0);
	tp.CreateDisplayList(YZ_FLIP, 393, 128.0, 128.0, 33872.0, 11344.0, 41063.0, 4.0, 0.5);	// upstairs edge of window

	// WALL_BRICK_GAP_YZ
	tp.CreateDisplayList(YZ, 180, 128.0, 32.0, 33895.0, 10192.0, 22079.0, 5.0, 0.530);	// end chanc
	tp.CreateDisplayList(YZ, 181, 128.0, 32.0, 33872.0, 10512.0, 30542.0, 2.5, 0.80);	// toilets phys sci
	// WALL_BRICK_GAP2_YZ
	tp.CreateDisplayList(YZ, 182, 128.0, 32.0, 33872.0, 10512.0, 27559.0, 2.5, 0.80);	// toilets phys sci
	// WALL_GAP_1
	tp.CreateDisplayList(XY, 183, 8.0, 128.0, 30792.0, 10000.0, 43056.0, 1.0, 6.0);	// near KBLT
	tp.CreateDisplayList(XY, 184, 8.0, 128.0, 30792.0, 11024.0, 43056.0, 1.0, 6.5);	// as above but upstairs
}

//--------------------------------------------------------------------------------------
//  Create display lists
//	Numbers indicate list numbers
//--------------------------------------------------------------------------------------
void DisplayWrathWorld::CreateTextureList()
{
	DrawBricks();				// 1

	//last number used: 601
}