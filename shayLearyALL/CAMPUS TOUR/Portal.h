/*
Author: Vlad Kennebury
Date: 11/09/2020

ICT290 Assignment 1
Portal Class Header - Sets the location and dimesnions of a portal, and checks whether 
a collision between the player and the portal is made.

*/

#ifndef PORTAL_H
#define PORTAL_H

#include "camera.h"

class Portal
{
public:

	//Constructor, sets all default values
	Portal();

	//Collects and stores the position of the player
	void setLocation(double xPos, double yPos, double zPos);

	//Collects and stores the dimensions of the portal on x,y,z axis
	void portalDimensions(double xSize, double ySize, double zSize);

	//Checks for collision of player of portal position.
	//Returns true if collision of portal occurs, otherwise returns false
	bool createPortal(double xStart, double yStart, double zStart);

private:
	
	//Position of player on the x axis
	double xPlayer;
	//Position of player on the y axis
	double yPlayer;
	//Position of player on the z axis
	double zPlayer;

	//Size of portal across x axis
	double xDim;
	//Size of portal across y axis
	double yDim;
	//Size of portal across z axis
	double zDim;
};

#endif // !PORTAL_H
