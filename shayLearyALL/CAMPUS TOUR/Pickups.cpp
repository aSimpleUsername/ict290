#include "Pickups.h"

Pickups::Pickups()
{
	for (int i = 0; i < 5; i++)
	{
		healthUp[i].gathered = false;
		shieldUp[i].gathered = false;
		ammoUp[i].gathered = false;
	}
}

void Pickups::setHealthBox(int index, double minX, double maxX, double minZ, double maxZ)
{
	healthUp[index].xMin = minX;
	healthUp[index].xMax = maxX;

	healthUp[index].zMin = minZ;
	healthUp[index].zMax = maxZ;
}

void Pickups::setShieldBox(int index, double minX, double maxX, double minZ, double maxZ)
{
	shieldUp[index].xMin = minX;
	shieldUp[index].xMax = maxX;

	shieldUp[index].zMin = minZ;
	shieldUp[index].zMax = maxZ;
}

void Pickups::setAmmoBox(int index, double minX, double maxX, double minZ, double maxZ)
{
	ammoUp[index].xMin = minX;
	ammoUp[index].xMax = maxX;

	ammoUp[index].zMin = minZ;
	ammoUp[index].zMax = maxZ;
}

void Pickups::removeHealthUp(int index)
{
	healthUp[index].gathered = true;
}

void Pickups::removeShieldUp(int index)
{
	shieldUp[index].gathered = true;
}

void Pickups::removeAmmoUp(int index)
{
	ammoUp[index].gathered = true;
}

void Pickups::checkHealthUp(double xPos, double yPos, double zPos)
{
	for (int i = 0; i < 2; i++)
	{
		if (xPos < healthUp[i].xMax && xPos > healthUp[i].xMin)
		{
			if (zPos < healthUp[i].zMax && zPos > healthUp[i].zMin)
			{
				removeHealthUp(i);
			}
		}
	}
}

bool Pickups::getGathered(int i)
{
	return healthUp[i].gathered;
}