//Stores various pickups and powerup locations
#include <string>
#include "point3D.h"

class Pickups
{
public:
	Pickups();
	//NEW
	/////////////////////////////////////////////////////////////////////////////

	int getSize();

	double getX();

	double getY();

	double getZ();

	void setGathT();

	bool getGath();

	void setPickup(double xValue, double yValue, double zValue, int sizeValue);

	void checkCollision(Point3D playerPos);

private:
	//NEW
	/////////////////////////////////////////////////////////////////////////////
	int size;
	double x;
	double y;
	double z;
	bool gath;
};

