#pragma once

#include <GL/glut.h>

#include <vector>
#include "point3D.h"
#include "collision.h"

	/**
	* @class Projectile
	* @brief Class that defines how the enemy projectiles behave
	* @author Group Team No Name 2
	* @version 1.0
	* @date 26 Oct 20
	*/
class Projectile
{
public:

		/**
		* @brief default constructor
		*/
	Projectile();

		/**
		* @brief constructs Projectile with a location and heading
		* @param location
		* @param heading
		*/
	Projectile(Point3D location, Point3D heading);

		/**
		* @brief draws projectile
		*/
	void drawProjectile();

		/**
		* @brief setter for collision object
		* @param collision the collision object
		*/
	inline void setCollision(Collision* collision) { m_collision = collision; }

	Point3D m_location;
	Point3D m_heading;
private:
	Collision* m_collision;
};