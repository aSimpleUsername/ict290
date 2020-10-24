//Entity class - Parent class of player and enemy, containing increments, setters and getters for health
//Version 2
#pragma once

#include <GL/glut.h>
#include "point3D.h"
#include "projectile.h"

class Entity
{
public:
	//constructors
	Entity(double x, double y, double z);		//constructs entity on the given location
	Entity();

	//getters & setters
	inline int getHealth() { return m_health; }
	inline int getShields() { return m_shields; }
	inline void setHealth(int health) { m_health = health; }
	inline void setShields(int shields) { m_shields = shields; }
	void incrementHealth();
	void incrementShields();
	void decreaseHealth();
	void decreaseShields();
	inline Point3D getLocation() { return m_location; }
	inline float GetX() { return m_location.x; }
	inline float GetY() { return m_location.y; }
	inline float GetZ() { return m_location.z; }
	inline int getMaxHealth() { return MAX_HEALTH; }
	inline int getMaxShield() { return MAX_SHIELD; }

protected:
	Point3D m_location;

	int m_health;
	int m_shields;

private:
	int const MAX_HEALTH = 10;
	int const MAX_SHIELD = 10;
};

