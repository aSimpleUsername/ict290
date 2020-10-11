#include "Enemy.h"

Enemy::Enemy(double x, double y, double z)
	: m_topSpeed(10), m_rotationSpeed(0.025), m_timer(0), m_fireRate(500)
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

	m_health = 5;
	m_shields = 0;

	m_position = Point3D(x, y, z);
	m_patrolTarget = Point3D(0.0, y, 0.0);

	updateHitBox(x, y, z);
}

Enemy::Enemy()
{

}

Enemy::Enemy(const Enemy& obj) 
{
	this->m_position = obj.m_position;
}

Enemy::~Enemy()
{

}

void Enemy::updateHitBox(float x, float y, float z)
{
	hitBox.SetData(x + 1, x, y + 1, y, z + 1, z);
}

void Enemy::drawEnemy()
{
	// *** Remove once charlie makes hit ray work withg box *** //
	glPushMatrix();
	glTranslatef(m_position.x, m_position.y, m_position.z);
	glColor3f(1, 0, 0);
	glutSolidSphere(300, 50, 50);
	glPopMatrix();
	// *** *** *** *** *** *** *** *** *** *** *** *** *** *** //

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

void Enemy::getAABB()
{

}

void Enemy::SetPosition(float x, float y, float z)
{
	this->m_position.x = x;
	this->m_position.y = y;
	this->m_position.z = z;
	updateHitBox(x, y, z);
}

void Enemy::shoot()
{
	if (m_projectileCount == MAX_PROJECTILES - 1)
		m_projectileCount = 0;

	m_projectiles[m_projectileCount].m_location = m_position;
	m_projectiles[m_projectileCount].m_heading = m_heading;

	++m_projectileCount;
}

void Enemy::drawProjectiles()
{
	for (int i = 0; i < MAX_PROJECTILES; ++i)
		m_projectiles[i].drawProjectile();
}

void Enemy::calculateHeading()
{
	Point3D frontCenter;
	frontCenter.x = (m_p1.x + m_p4.x) / 2;
	frontCenter.y = m_position.y;
	frontCenter.z = (m_p1.z + m_p4.z) / 2;

	m_heading = frontCenter - m_position;
}

//rotates all points around the center point
void Enemy::rotateEntity(double rotationSpeed)
{
	Point3D* pArray[] = { &m_p1, &m_p2, &m_p3, &m_p4, &m_p5, &m_p6, &m_p7, &m_p8 };

	for (int i = 0; i < 8; ++i)
	{
		double x1 = pArray[i]->x - m_position.x;
		double z1 = pArray[i]->z - m_position.z;

		double x2 = x1 * cos(rotationSpeed) - z1 * sin(rotationSpeed);
		double z2 = x1 * sin(rotationSpeed) + z1 * cos(rotationSpeed);

		pArray[i]->x = x2 + m_position.x;
		pArray[i]->z = z2 + m_position.z;
	}
}

void Enemy::accelerate(float topSpeed)
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
	m_position = m_position + m_heading.normalise() * m_acceleration;
}

void Enemy::seek(Point3D targetPosition)
{
	Point3D newHeading;
	newHeading.x = (targetPosition.x - m_position.x);
	newHeading.z = (targetPosition.z - m_position.z);
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

void Enemy::patrol(double xmin, double xmax, double zmin, double zmax)
{
	if (m_patrolTarget == Point3D(0.0, m_position.y, 0.0) || m_position.distance(m_patrolTarget) < 500)
		m_patrolTarget = Point3D::randomPointXZ(xmin, xmax, zmin, zmax, m_position.y);

	seek(m_patrolTarget);
}