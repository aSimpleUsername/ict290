#pragma once

#include <GL/glut.h>

#include <vector>
#include "point3D.h"

class Projectile
{
public:

	Point3D m_location;
	Point3D m_heading;

	Projectile();
	Projectile(Point3D location, Point3D heading);
	void drawProjectile();
};