//Player class - Child class of entity, sharing health and shields
#pragma once

#include "Entity.h"

class Player : public Entity
{
public:
	Player();

	inline void updateLocation(double x, double y, double z) { m_location = Point3D(x, y, z); }
	inline Point3D* getPlayerLocationPointer() { return(&m_location); }
	inline void resetHealth() { m_health = MAX_HEALTH; }
	void incrementAmmo();
	void decreaseAmmo();
	int getAmmo();
	void setAmmo(int a);
	void setReserveAmmo(int a);
	int getReserveAmmo();
	void reload();

private:
	int const MAX_HEALTH = 10;
	int ammo;
	int ammoReserve;
	int const MAX_AMMO = 30;
	int const MAX_AMMO_RESERVE = 100;
};

