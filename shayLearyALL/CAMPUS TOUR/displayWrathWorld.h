// displayWrathWorld.cpp - displays the world of Wrath
// Author: Group Team No Name 2
// 14 Sep 20

#ifndef DISPLAYWRATHWORLD_H
#define DISPLAYWRATHWORLD_H

#include "camera.h"
#include "texturedPolygons.h"
#include "Portal.h"
#include "Pickups.h"
//Classes for hit detection (enemy can be changed for your class)
#include "ObjPicking.h"
#include "Enemy.h"
#include "Player.h"
// TEXTURE IMAGE AXISES
#define XY		0
#define XZ		1
#define YZ		2
#define YZ_FLIP 3
#define XY_FLIP 4

// Textures
#define WELCOME_SCREEN				1
#define EXIT_SCREEN					2
#define GROUND_PLANE				3
#define SPACE_1						4
#define PORTAL_1					5
#define SPACESHIP_WALL_1			6
#define SPACESHIP_WALL_1_YZ			7
#define CIRCUIT						8
#define HEALTH						9
#define SHIELD  					10
#define AMMO						11
#define HEALTH_YZ					12
#define SHIELD_YZ 					13
#define AMMO_YZ						14

	/**
	* @class displayWrathWorld
	* @brief Class that defines how the wrath world will be displayed
	* @author Group Team No Name 2
	* @version 1.0
	* @date 14 Sep 20
	*/
class DisplayWrathWorld
{
public:
	Camera cam;		
	TexturedPolygons tp;
	Pickups pick;
	
	unsigned char* image = NULL;

	bool DisplayMap = false;	
	bool DisplayWelcome = false;
	bool DisplayExit = false;
	
		/**
		* @brief initialises Wrath World
		*/
	void myinit();

		/**
		* @brief calls private display functions to draw the scene
		*/
	void DrawBackdrop();

		/**
		* @brief deletes image and clears memory
		* @param tempImage - to delete
		*/
	void DeleteImageFromMemory(unsigned char* tempImage);	// deletes image and clears memory

		/**
		* @brief defines the return portal collision to Shays World
		* @return  if player is withing the bounds of portal
		*/
	bool stairsReturnPortal();

	// collision

	void collisionCheck();

	// health

	void setHealth();

	void healthChecksDraw();

	void healthChecksDisplay();

	// shields

	void setShields();

	void shieldChecksDraw();

	void shieldChecksDisplay();

	//ammo

	void setAmmo();

	void ammoChecksDraw();

	void ammoChecksDisplay();

private:
	Portal stepsReturn;
	//Enemy can be changed for whatever class 

	Player player;
	ObjPicking<Enemy> enemyObjects; 

	static int const NUM_ENEMIES = 4;
	Enemy enemies[NUM_ENEMIES] = {	Enemy(7000, 11000, 0, 2500, 10550),				// room 1
									Enemy(7000, 15000, -3500, 0, 10550),			// room 1
									Enemy(11000, 15000, 0, 2500, 10550),			// room 1
									Enemy(15000, 19000, -3500, 2500, 10550) };		// room 1

	std::vector<unsigned char>* pngImage;		// Stores raw image file


		/**
		* @brief initilises enemies
		*/
	void initEnemies();

		/**
		* @brief displays the skybox
		*/
	void displaySkyBox();

		/**
		* @brief displays the ground plane
		*/
	void displayGroundPlane();

		/**
		* @brief displays the portal
		*/
	void displayPortal();


		/**
		* @brief displays the walls
		*/
	void displayRoom1Walls();

		/**
		* @brief displays the server walls
		*/
	void displayServerWalls();

	////////////////////////////////////////////////////////////////////

	void displayHealthPickups();
	void displayHealthPickups1();
	void displayHealthPickups2();
	void displayHealthPickups3();
	void displayHealthPickups4();
	void displayHealthPickups5();
	void displayHealthPickups6();

	void displayShieldPickups();
	void displayShieldPickups1();
	void displayShieldPickups2();
	void displayShieldPickups3();
	void displayShieldPickups4();
	void displayShieldPickups5();
	void displayShieldPickups6();

	void displayAmmoPickups();
	void displayAmmoPickups1();
	void displayAmmoPickups2();
	void displayAmmoPickups3();
	void displayAmmoPickups4();
	void displayAmmoPickups5();
	void displayAmmoPickups6();

	////////////////////////////////////////////////////////////////////

		/**
		* @brief displays enemies 
		*/
	void displayEnemies();

		/**
		* @brief calls functions to create display lists
		*/
	void CreateTextureList();

		/**
		* @brief draws the skybox
		*/
	void drawSkyBox();

		/**
		* @brief draws the ground plane
		*/
	void drawGroundPlane();

		/**
		* @brief draws the portal plane
		*/
	void drawPortal();

		/**
		* @brief draws the walls
		*/
	void drawRoom1Walls();

		/**
		* @brief draws the server walls
		*/
	void drawServerWalls();

	////////////////////////////////////////////////////////////////////

	void drawHealthPickups();
	void drawHealthPickups1();
	void drawHealthPickups2();
	void drawHealthPickups3();
	void drawHealthPickups4();
	void drawHealthPickups5();
	void drawHealthPickups6();

	void drawShieldPickups();
	void drawShieldPickups1();
	void drawShieldPickups2();
	void drawShieldPickups3();
	void drawShieldPickups4();
	void drawShieldPickups5();
	void drawShieldPickups6();

	void drawAmmoPickups();
	void drawAmmoPickups1();
	void drawAmmoPickups2();
	void drawAmmoPickups3();
	void drawAmmoPickups4();
	void drawAmmoPickups5();
	void drawAmmoPickups6();

	////////////////////////////////////////////////////////////////////

		/**
		* @brief loads images and creates texture
		*/
	void CreateTextures();
	
		/**
		* @brief creates bounding boxes for collsion detection
		*/
	void CreateBoundingBoxes();
};

#endif DISPLAYWRATHWORLD_H