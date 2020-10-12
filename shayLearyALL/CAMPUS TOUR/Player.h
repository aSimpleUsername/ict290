//Player class - Child class of entity, sharing health and shields
#pragma once

#include "Entity.h"

class Player : public Entity
{
public:
	Player();

	inline void updateLocation(double x, double y, double z) { m_location = Point3D(x, y, z); }
	inline Point3D* getPlayerLocationPointer() { return(&m_location); }

private:

};

