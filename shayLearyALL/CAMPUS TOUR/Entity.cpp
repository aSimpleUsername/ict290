#include "Entity.h"

Entity::Entity(double x, double y, double z)
	: m_health(5), m_shields(0), m_topSpeed(10), m_rotationSpeed(0.025),
		m_timer(0), m_fireRate(500)
{
	//top 4 points going clockwise starting with front left
	m_p1 = Point3D(x - 150, y + 200, z + 150);
	m_p2 = Point3D(x - 150, y + 200, z - 150);
	m_p3 = Point3D(x + 150, y + 200, z - 150);
	m_p4 = Point3D(x + 150, y + 200, z + 150);
	//bottom 4 points going clockwise starting with front left (player is 450 units tall)
	m_p5 = Point3D(x - 150, y - 450, z + 150);
	m_p6 = Point3D(x - 150, y - 450, z - 150);
	m_p7 = Point3D(x + 150, y - 450, z - 150);
	m_p8 = Point3D(x + 150, y - 450, z + 150);

	m_center = Point3D(x, y, z);
	m_patrolTarget = Point3D(0.0, y, 0.0);
}

void Entity::drawEntity()
{
	accelerate(m_topSpeed);
	drawProjectiles();
	if (glutGet(GLUT_ELAPSED_TIME) > m_timer)
		m_timer += m_fireRate;

	// top plane
    glBegin(GL_POLYGON);
    glVertex3d(m_p1.x, m_p1.y, m_p1.z);
	glVertex3d(m_p2.x, m_p2.y, m_p2.z);
	glVertex3d(m_p3.x, m_p3.y, m_p3.z);
	glVertex3d(m_p4.x, m_p4.y, m_p4.z);
    glEnd();
	// front plane
	glBegin(GL_POLYGON);
	glVertex3d(m_p1.x, m_p1.y, m_p1.z);
	glVertex3d(m_p4.x, m_p4.y, m_p4.z);
	glVertex3d(m_p8.x, m_p8.y, m_p8.z);
	glVertex3d(m_p5.x, m_p5.y, m_p5.z);
	glEnd();
	// left plane
	glBegin(GL_POLYGON);
	glVertex3d(m_p2.x, m_p2.y, m_p2.z);
	glVertex3d(m_p1.x, m_p1.y, m_p1.z);
	glVertex3d(m_p5.x, m_p5.y, m_p5.z);
	glVertex3d(m_p6.x, m_p6.y, m_p6.z);
	glEnd();
	// back plane
	glBegin(GL_POLYGON);
	glVertex3d(m_p3.x, m_p3.y, m_p3.z);
	glVertex3d(m_p2.x, m_p2.y, m_p2.z);
	glVertex3d(m_p6.x, m_p6.y, m_p6.z);
	glVertex3d(m_p7.x, m_p7.y, m_p7.z);
	glEnd();
	// right plane
	glBegin(GL_POLYGON);
	glVertex3d(m_p4.x, m_p4.y, m_p4.z);
	glVertex3d(m_p3.x, m_p3.y, m_p3.z);
	glVertex3d(m_p7.x, m_p7.y, m_p7.z);
	glVertex3d(m_p8.x, m_p8.y, m_p8.z);
	glEnd();

}

void Entity::shoot()
{
	if (m_projectileCount == MAX_PROJECTILES - 1)
		m_projectileCount = 0;

	m_projectiles[m_projectileCount].m_location = m_center;
	m_projectiles[m_projectileCount].m_heading = m_heading;

	++m_projectileCount;
}

void Entity::drawProjectiles()
{
	for (int i = 0; i < MAX_PROJECTILES; ++i)
		m_projectiles[i].drawProjectile();
}

void Entity::calculateHeading()
{
	Point3D frontCenter;
	frontCenter.x = (m_p1.x + m_p4.x) / 2;
	frontCenter.y = m_center.y;
	frontCenter.z = (m_p1.z + m_p4.z) / 2;

	m_heading = frontCenter - m_center;
}

//rotates all points around the center point
void Entity::rotateEntity(double rotationSpeed)
{
	Point3D* pArray[] = { &m_p1, &m_p2, &m_p3, &m_p4, &m_p5, &m_p6, &m_p7, &m_p8 };

	for (int i = 0; i < 8; ++i)
	{
		double x1 = pArray[i]->x - m_center.x;
		double z1 = pArray[i]->z - m_center.z;

		double x2 = x1 * cos(rotationSpeed) - z1 * sin(rotationSpeed);
		double z2 = x1 * sin(rotationSpeed) + z1 * cos(rotationSpeed);

		pArray[i]->x = x2 + m_center.x;
		pArray[i]->z = z2 + m_center.z;
	}
}

void Entity::accelerate(float topSpeed)
{
	calculateHeading();

	if (topSpeed > 0 && m_acceleration < topSpeed)
		m_acceleration += 0.1;

	if (topSpeed < 0 && m_acceleration > topSpeed)
		m_acceleration -= 0.1;

	m_p1 = m_p1 + m_heading.normalise() * m_acceleration;
	m_p2 = m_p2 + m_heading.normalise() * m_acceleration;
	m_p3 = m_p3 + m_heading.normalise() * m_acceleration;
	m_p4 = m_p4 + m_heading.normalise() * m_acceleration;
	m_p5 = m_p5 + m_heading.normalise() * m_acceleration;
	m_p6 = m_p6 + m_heading.normalise() * m_acceleration;
	m_p7 = m_p7 + m_heading.normalise() * m_acceleration;
	m_p8 = m_p8 + m_heading.normalise() * m_acceleration;
	m_center = m_center + m_heading.normalise() * m_acceleration;
}

void Entity::seek(Point3D targetPosition)
{
	Point3D newHeading;
	newHeading.x = (targetPosition.x - m_center.x);
	newHeading.z = (targetPosition.z - m_center.z);
	newHeading.normalise();

	if (m_heading.angle() > newHeading.angle())       //turn left
	{
		if (m_heading.angle() - newHeading.angle() > M_PI)        // makes it smooth if angle goes from 360 - 0 degreees
			rotateEntity(-m_rotationSpeed);
		else
			rotateEntity(m_rotationSpeed);
	}

	if (m_heading.angle() < newHeading.angle())       //turn right
	{
		if (m_heading.angle() - newHeading.angle() < -M_PI)       //  makes it smooth if angle goes from 360 - 0 degreees
			rotateEntity(m_rotationSpeed);
		else
			rotateEntity(-m_rotationSpeed);
	}
}

void Entity::patrol(double xmin, double xmax, double zmin, double zmax)
{
	if (m_patrolTarget == Point3D(0.0, m_center.y, 0.0) || m_center.distance(m_patrolTarget) < 500)
		m_patrolTarget = Point3D::randomPointXZ(xmin, xmax, zmin, zmax, m_center.y);	

	seek(m_patrolTarget);
}