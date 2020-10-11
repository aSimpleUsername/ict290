#include "Entity.h"

Entity::Entity(double x, double y, double z)
	: m_health(5), m_shields(0), m_location(Point3D(0, 0, 0))
{

}

Entity::Entity()
	: m_location(Point3D(0, 0, 0))
{

}