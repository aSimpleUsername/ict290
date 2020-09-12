/*
Author: Vlad Kennebury
Date: 11/09/2020

ICT290 Assignment 1
Portal Class Implementation - Sets the location and dimesnions of a portal, and checks whether
a collision between the player and the portal is made.

*/

#include "Portal.h"

Portal::Portal()
{
	xPlayer = 0;
	yPlayer = 0;
	zPlayer = 0;

	xDim = 0;
	yDim = 0;
	zDim = 0;
}

void Portal::setLocation(double xPos, double yPos, double zPos)
{
	xPlayer = xPos;
	yPlayer = yPos;
	zPlayer = zPos;
}

void Portal::portalDimensions(double xSize, double ySize, double zSize)
{
	xDim = xSize;
	yDim = ySize;
	zDim = zSize;
}

//Starts need to be larger than (start - dim). Example - xPlayer < 4000 && xPlayer > 3000
bool Portal::createPortal(double xStart, double yStart, double zStart)
{
	if (xPlayer < xStart && xPlayer > xStart + xDim)
	{
		if (yPlayer < yStart && yPlayer > yStart + yDim)
		{
			if (zPlayer < zStart && zPlayer > zStart + zDim)
			{
				return true;
			}
		}
	}
	return false;
}