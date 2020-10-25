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


#include <irrKlang.h>
#pragma comment(lib, "irrKlang.lib")

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
#define NUM_0						33
#define NUM_1						34
#define NUM_2						35
#define NUM_3						36
#define NUM_4						37
#define NUM_5						38
#define NUM_6						39
#define NUM_7						40
#define NUM_8						41
#define NUM_9						42
#define WIN							43
#define LOSE						44
#define T_WINDOW					45
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
	std::vector<Point3D> maxWallPoints;
	std::vector<Point3D> minWallPoints;
	bool DisplayMap = false;	
	bool DisplayWelcome = false;
	bool DisplayExit = false;
	bool lose = false;
	irrklang::ISoundEngine *engine;
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

	void SetWallPoints();

	void reduceAmmo();

	void ammoCheck();

	void reload();

	void ammoLogic();
	
	void WinState();
	
	void LoseState();

	int grabAmmo();
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

	static int const NUM_ENEMIES = 41;
	Enemy enemies[NUM_ENEMIES] = {	Enemy(7000, 11000, 0, 2500, 10550),				// room 1
									Enemy(7000, 15000, -3000, 0, 10550),			// room 1
									Enemy(11000, 15000, 0, 2500, 10550),			// room 1
									Enemy(15000, 18900, -3000, 2500, 10550),		// room 1

									Enemy(9000, 17000, -4400, -3800, 10550),		// server room 
									Enemy(7100, 8900, -9200, -3800, 10550),			// server room 
									Enemy(9000, 17000, -9100.0, -8400, 10550),		// server room 
									Enemy(17100, 18900, -9200, -3800, 10550),		// server room 
									Enemy(9000, 17000, -7000, -6100, 10550),		// server room 

									Enemy(8000, 10000, -12250, -13200, 10550),		// window room 
									Enemy(10000, 12000, -12250, -13200, 10550),		// window room 
									Enemy(12000, 14000, -12250, -13200, 10550),		// window room  
									Enemy(14000, 16000, -12250, -13200, 10550),		// window room 
																					
									Enemy(8000, 10000, -18000, -16500, 10550),		// room 4
									Enemy(10000, 12900, -18000, -16500, 10550),		// room 4 
									Enemy(13000, 15800, -16000, -15500, 10550),		// room 4 
									Enemy(10000, 12900, -15500, -13900, 10550),		// room 4
									Enemy(8000, 10000, -15500, -13900, 10550),		// room 4
									Enemy(14100, 16000, -18000, -16500, 10550),		// room 4 
									Enemy(16000, 18900, -18000, -16500, 10550),		// room 4 
									Enemy(16000, 18900, -15300, -13900, 10550),		// room 4
									Enemy(14100, 16000, -15500, -13900, 10550),		// room 4

									Enemy(16000, 18500, -23000, -21700, 10550),		// electric room
									Enemy(16000, 18500, -21700, -21300, 10550),		// electric room
									Enemy(16000, 18500, -21300, -19000, 10550),		// electric room
									Enemy(13500, 16000, -23000, -21700, 10550),		// electric room
									Enemy(13500, 16000, -21700, -21300, 10550),		// electric room
									Enemy(13500, 16000, -21300, -19000, 10550),		// electric room
									Enemy(11000, 13500, -23000, -21700, 10550),		// electric room
									Enemy(11000, 13500, -21700, -21300, 10550),		// electric room
									Enemy(11000, 13500, -21300, -19000, 10550),		// electric room

									Enemy(6200, 9700, -39200, -34500, 10550),		// boss room
									Enemy(1300, 8200, -42800, -41100, 10550),		// boss room
									Enemy(1300, 9700, -44600, -42800, 10550),		// boss room
									Enemy(8700, 10300, -53500, -50800, 10550),		// boss room
									Enemy(14800, 16300, -53500, -44600, 10550),		// boss room
									Enemy(15000, 23800, -44600, -42800, 10550),		// boss room
									Enemy(16700, 23800, -42800, -41100, 10550),		// boss room
									Enemy(15000, 18800, -41100, -34800, 10550),		// boss room
									Enemy(11100, 12450, -34200, -32200, 10550),		// boss room
									Enemy(12450, 13800, -34200, -32200, 10550),		// boss room
									};

	EnemyBoss boss = EnemyBoss(9500, 15500, -49000, -36000, 10550);


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

	void drawWindows();

	void displayWindows();
};

#endif DISPLAYWRATHWORLD_H