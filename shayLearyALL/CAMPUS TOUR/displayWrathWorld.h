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
	Enemy enemy0 = Enemy(10000, 10550, 1000);	//room1


	GLdouble step, step2, stepLength;		// varibles used for tarnslating graphics etc


	std::vector<unsigned char>* pngImage;		// Stores raw image file

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


	void displayHealthPickups();

	void displayShieldPickups();

	void displayAmmoPickups();

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


	void drawHealthPickups();

	void drawShieldPickups();

	void drawAmmoPickups();

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