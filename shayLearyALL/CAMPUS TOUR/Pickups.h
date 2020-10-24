//Stores various pickups and powerup locations
#include <string>

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

	void checkCollision(double xPos, double zPos);

private:
	//NEW
	/////////////////////////////////////////////////////////////////////////////
	int size;
	double x;
	double y;
	double z;
	bool gath;
};

