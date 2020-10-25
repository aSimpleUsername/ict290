// displayWrathWorld.cpp - displays the world of Wrath
// Author: Group Team No Name 2
// 14 Sep 20

#ifndef DISPLAYWRATHWORLD_H
#define DISPLAYWRATHWORLD_H

#include <vector>
#include "camera.h"
#include "texturedPolygons.h"
#include "Portal.h"
#include "Pickups.h"
//Classes for hit detection (enemy can be changed for your class)
#include "ObjPicking.h"
#include "Enemy.h"
#include "enemyBoss.h"
#include "Player.h"
#include "userInterface.h"
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
#define ELECTRICITY					15
#define VENT						16
#define SERVER						17
#define SERVER_YZ					18
#define ENEMY_FRONT					19
#define ENEMY_BACK					20
#define ENEMY_SIDE					21
#define PORTAL_2					22	
#define BOSS_FRONT					23
#define BOSS_BACK					24
#define GUN							25
#define BOSS_NAME					26
#define BOSS_HEALTH					27
#define PLAYER_HEALTH				28
#define PLAYER_SHIELD				29
#define PLAYER_HIT					30
#define TRANSPARENT_1				31
#define HITMARKER					32

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
	UserInterface ui;
	ObjPicking<Enemy> enemyObjects;
	ObjPicking<EnemyBoss> enemyBossObject;
	unsigned char* image = NULL;
	std::vector<Pickups> hPowerup;
	std::vector<Pickups> sPowerup;
	std::vector<Pickups> aPowerup;

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
		* @brief respawns player
		*/
	void respawn();

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
	
	//portals
	void elecPortal();

	void postElecPortal();

	void servPortalR();

	void servPortalL();

	void bossPortalL();

	void bossPortalR();

	void electricFloor(float maxX, float minX, float maxZ, float minZ);

	void electricFloorCheck();

	// NEW
	////////////////////////////////////////////////////////////////////////
	void setUpPowerups();

	void displayHealth();

	void displayShields();

	void displayAmmo();

	void collectionCheck();

	void drawUI();

private:
	Portal stepsReturn;
	Portal serverPortal1;
	Portal serverPortal2;
	Portal electricityPortal;
	Portal postElectricityPortal;
	Portal bossPortal1;
	Portal bossPortal2;

	//Enemy can be changed for whatever class

	GLdouble step, step2, stepLength;		// varibles used for tarnslating graphics etc
	//Enemy can be changed for whatever class 

	Player player;

	static int const NUM_ENEMIES = 9;
	Enemy enemies[NUM_ENEMIES] = {	Enemy(7000, 11000, 0, 2500, 10550),				// room 1
									Enemy(7000, 15000, -3100, 0, 10550),			// room 1
									Enemy(11000, 15000, 0, 2500, 10550),			// room 1
									Enemy(15000, 19000, -3100, 2500, 10550),		// room 1
									Enemy(9000, 17000, -4500, -3800, 10550),		// server room 
									Enemy(7000, 9000, -9200, -3800, 10550),			// server room 
									Enemy(9000, 17000, -9200.0, -8300, 10550),		// server room 
									Enemy(17000, 19000, -9200, -3800, 10550),		// server room 
									Enemy(9000, 17000, -7100, -6000, 10550),		// server room 
									};

	EnemyBoss boss = EnemyBoss(9500, 15500, -49000, -36500, 10550);


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

	void displayPowerWalls();

	void displayBossRoom();

	////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////

	void displayInnerPortals();

		/**
		* @brief displays enemies 
		*/
	void displayEnemies();

		/**
		* @brief displays boss
		*/
	void displayBoss();

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

	void drawPowerWalls();

	void drawBossRoom();

	////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////

	void drawInnerPortals();

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