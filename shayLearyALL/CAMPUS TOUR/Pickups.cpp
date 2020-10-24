#include "Pickups.h"

Pickups::Pickups()
{
	size = 0;
	x = 0;
	y = 0;
	z = 0;
	gath = false;
}

//NEW
//////////////////////////////////////////////////

int Pickups::getSize()
{
	return size;
}

double Pickups::getX()
{
	return x;
}

double Pickups::getY()
{
	return y;
}

double Pickups::getZ()
{
	return z;
}

void Pickups::setGathT()
{
	gath = true;
}

bool Pickups::getGath()
{
	return gath;
}

void Pickups::setPickup(double xValue, double yValue, double zValue, int sizeValue)
{
	x = xValue;
	y = yValue;
	z = zValue;
	size = sizeValue;
}

void Pickups::checkCollision(double xPos, double zPos)
{
	if (zPos < z && zPos > (z - size))
	{
		if (xPos < (x + size) && xPos > x)
		{
			setGathT();
		}
	}
}