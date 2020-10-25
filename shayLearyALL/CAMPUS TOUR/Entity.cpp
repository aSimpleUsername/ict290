#include "Entity.h"

Entity::Entity(double x, double y, double z)
	: m_health(5), m_shields(0), m_location(Point3D(0, 0, 0))
{

}

Entity::Entity()
	: m_location(Point3D(0, 0, 0))
{

}

void Entity::incrementHealth() 
{
	if (m_health < MAX_HEALTH)
	{
		m_health++;
	}
}

void Entity::incrementShields()
{
	if (m_shields < MAX_SHIELD)
	{
		m_shields++;
	}
}

void Entity::decreaseHealth()
{
	if (m_health > 0)
	{
		m_health--;
	}
}

void Entity::decreaseShields()
{
	if (m_shields > 0)
	{
		m_shields--;
	}
}