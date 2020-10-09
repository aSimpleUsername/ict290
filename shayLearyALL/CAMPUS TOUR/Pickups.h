//Stores various pickups and powerup locations
#include <string>

struct collect
{
	double xMin;
	double xMax;
	double zMin;
	double zMax;
	bool gathered;
};

class Pickups
{
public:
	Pickups();
	
	void setHealthBox(int index, double minX, double maxX, double minZ, double maxZ);

	void setShieldBox(int index, double minX, double maxX, double minZ, double maxZ);

	void setAmmoBox(int index, double minX, double maxX, double minZ, double maxZ);

	void removeHealthUp(int index);

	void removeShieldUp(int index);

	void removeAmmoUp(int index);

	void checkHealthUp(double xPos, double yPos, double zPos);

	bool getGathered(int index);

private:
	collect healthUp[5];
	collect shieldUp[5];
	collect ammoUp[5];
};

