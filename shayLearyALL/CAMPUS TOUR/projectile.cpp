#include "projectile.h"

Projectile::Projectile()
{
	m_location = Point3D(double(0.0), 10450, double(0.0));
	m_heading = Point3D(double(0.0), 10450, double(0.0));
}

Projectile::Projectile(Point3D location, Point3D heading)
{
	m_location = location;
	m_heading = heading;
}


void Projectile::drawProjectile()
{
	m_location.x += m_heading.normalise().x * 30;		// 30 = speed
	m_location.z += m_heading.normalise().z * 30;

	glPushMatrix();
	glTranslated(m_location.x, m_location.y, m_location.z);
	glutSolidSphere(20, 20, 20);
	glLoadIdentity();
	glPopMatrix();
}