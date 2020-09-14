/*
Author: Vlad Kennebury
Date: 11/09/2020

ICT290 Assignment 1
Portal Class Header - Sets the location and dimesnions of a portal, and checks whether 
a collision between the player and the portal is made.

*/

/**
	* @class Portal
	* @brief Sets the location and dimesnions of a portal, and checks whether 
			a collision between the player and the portal is made.
	* @author Group Team No Name 2
	* @version 1
	* @date 14/09/2020
*/

#ifndef PORTAL_H
#define PORTAL_H

#include "camera.h"

class Portal
{
public:

	/**
		* @brief Constructor, sets all default values
		
	*/
	Portal();

	/**
		* @brief Collects and store camera position
		* @param xPos - Position on x axis
		* @param yPos - Position on y axis
		* @param zPos - Position on z axis
		* @return void
	*/
	void setLocation(double xPos, double yPos, double zPos);

	/**
		* @brief Collects and stores dimesions on all axis's of the portal
		* @param xSize - Difference on x axis
		* @param ySize - Difference on y axis
		* @param zSize - Difference on z axis
		* @return void
	*/
	void portalDimensions(double xSize, double ySize, double zSize);

	/**
		* @brief Checks for collision of player of portal position.	
				Returns true if collision of portal occurs, otherwise returns false
		* @param xStart - Position of bound on the x axis
		* @param yStart - Position of bound on the y axis
		* @param zStart - Position of bound on the z axis
		* @return bool
	*/
	bool createPortal(double xStart, double yStart, double zStart);

private:
	
	///Position of player on the x axis
	double xPlayer;
	///Position of player on the y axis
	double yPlayer;
	///Position of player on the z axis
	double zPlayer;

	///Size of portal across x axis
	double xDim;
	///Size of portal across y axis
	double yDim;
	///Size of portal across z axis
	double zDim;
};

#endif // !PORTAL_H
