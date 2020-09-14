// displayWrathWorld.cpp - displays the world of Wrath
// Author: Group Team No Name 2
// 14 Sep 20

#ifndef DISPLAYWRATHWORLD_H
#define DISPLAYWRATHWORLD_H

#include "camera.h"
#include "texturedPolygons.h"
#include "Portal.h"

// TEXTURE IMAGE AXISES
#define XY		0
#define XZ		1
#define YZ		2
#define YZ_FLIP 3
#define XY_FLIP 4

// Wall Brick Textures
#define WELCOME_SCREEN				1
#define EXIT_SCREEN					2
#define GROUND_PLANE				3
#define SPACE_1						4
#define PORTAL_1					5

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
		* @pram the image to delete
		*/
	void DeleteImageFromMemory(unsigned char* tempImage);	// deletes image and clears memory

		/**
		* @brief defines the return portal collision to Shays World
		* @return  if player is withing the bounds of portal
		*/
	bool stairsReturnPortal();

private:
	Portal stepsReturn;	

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
		* @brief draws the portal
		*/
	void displayPortal();

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
		* @brief loads images and creates texture
		*/
	void CreateTextures();
	
		/**
		* @brief creates bounding boxes for collsion detection
		*/
	void CreateBoundingBoxes();
};

#endif DISPLAYWRATHWORLD_H