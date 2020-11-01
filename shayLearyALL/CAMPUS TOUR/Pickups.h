/*
Author: Vlad Kennebury
Date: 31/10/2020

ICT290 Assignment 2
Pickups Class Header - Stores the coordinates of a pickup object, as well as checking the collision
between the player and the pickup.

*/

/**
	* @class Pickups
	* @brief Stores the coordinates of a pickup object, as well as checking the collision
				between the player and the pickup.
	* @author Group Team No Name 2
	* @version 2
	* @date 31/10/2020
*/
#include <string>
#include "point3D.h"

class Pickups
{
public:
	
	/**
		* @brief Constructor, sets all default values
	*/
	Pickups();

	//Getters and setters
	int getSize();

	double getX();

	double getY();

	double getZ();

	void setGathT();

	bool getGath();

	/**
		* @brief Sets the location of the pickup, as well as the size in each axis
		* @param xValue - Position on the x axis
		* @param yValue - Position on the y axis
		* @param zValue - Position on the z axis
		* @param sizeValue - Size of the pickup in each of the x,y,z directions
		* @return void
	*/
	void setPickup(double xValue, double yValue, double zValue, int sizeValue);

	/**
		* @brief Checks for collision between the  player and pickup.
		* @param playerPos - Point3D object
		* @return bool
	*/
	void checkCollision(Point3D playerPos);

private:

	///Size of the pickup
	int size;
	///Starting x position
	double x;
	///Starting y position
	double y;
	///Starting z position
	double z;
	///Stores the gathered or not gathered state of the pickup
	bool gath;
};

