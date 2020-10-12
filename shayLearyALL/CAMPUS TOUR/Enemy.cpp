#include "Enemy.h"

Enemy::Enemy(double x, double y, double z)
	: m_topSpeed(10), m_rotationSpeed(0.025), m_timer(0), m_fireRate(500), m_heading(Point3D(0.0, 0.0, 0.0)),
		m_state(PATROL)
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

	m_location = Point3D(x, y, z);
	m_patrolTarget = Point3D(0.0, y, 0.0);

	updateHitBox(x, y, z);
}

Enemy::Enemy(double xmin, double xmax, double zmin, double zmax, double y)
	: m_topSpeed(10), m_rotationSpeed(0.025), m_timer(0), m_fireRate(500), m_heading(Point3D(0.0, 0.0, 0.0)),
	m_state(PATROL)
{
	m_location = Point3D::randomPointXZ(xmin, xmax, zmin, zmax, y);
	//top 4 points going clockwise starting with front left
	m_p1 = Point3D(m_location.x - 150, m_location.y + 200, m_location.z + 150);
	m_p2 = Point3D(m_location.x - 150, m_location.y + 200, m_location.z - 150);
	m_p3 = Point3D(m_location.x + 150, m_location.y + 200, m_location.z - 150);
	m_p4 = Point3D(m_location.x + 150, m_location.y + 200, m_location.z + 150);
	//bottom 4 points going clockwise starting with front left (player is 450 units tall)
	m_p5 = Point3D(m_location.x - 150, m_location.y - 450, m_location.z + 150);
	m_p6 = Point3D(m_location.x - 150, m_location.y - 450, m_location.z - 150);
	m_p7 = Point3D(m_location.x + 150, m_location.y - 450, m_location.z - 150);
	m_p8 = Point3D(m_location.x + 150, m_location.y - 450, m_location.z + 150);

	m_health = 5;
	m_shields = 0;

	m_patrolTarget = Point3D(0.0, m_location.y, 0.0);
	setBounds(xmin, xmax, zmin, zmax);

	updateHitBox(m_location.x, m_location.y, m_location.z);
}

Enemy::Enemy()
{

}

Enemy::Enemy(const Enemy& obj) 
{
	this->m_location = obj.m_location;
}

Enemy::~Enemy()
{

}

void Enemy::setBounds(double xmin, double xmax, double zmin, double zmax)
{
	m_bounds.xmin = xmin;
	m_bounds.xmax = xmax;
	m_bounds.zmin = zmin;
	m_bounds.zmax = zmax;
}

void Enemy::updateHitBox(float x, float y, float z)
{
	hitBox.SetData(x + 1, x, y + 1, y, z + 1, z);
}

void Enemy::drawEnemy()
{
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
	this->m_location.x = x;
	this->m_location.y = y;
	this->m_location.z = z;
	updateHitBox(x, y, z);
}

void Enemy::shoot()
{
	if (m_projectileCount == MAX_PROJECTILES - 1)
		m_projectileCount = 0;

	m_projectiles[m_projectileCount].m_location = m_location;
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
	frontCenter.y = m_location.y;
	frontCenter.z = (m_p1.z + m_p4.z) / 2;

	m_heading = frontCenter - m_location;
}

//rotates all points around the center point
void Enemy::rotateEntity(double rotationSpeed)
{
	Point3D* pArray[] = { &m_p1, &m_p2, &m_p3, &m_p4, &m_p5, &m_p6, &m_p7, &m_p8 };

	for (int i = 0; i < 8; ++i)
	{
		double x1 = pArray[i]->x - m_location.x;
		double z1 = pArray[i]->z - m_location.z;

		double x2 = x1 * cos(rotationSpeed) - z1 * sin(rotationSpeed);
		double z2 = x1 * sin(rotationSpeed) + z1 * cos(rotationSpeed);

		pArray[i]->x = x2 + m_location.x;
		pArray[i]->z = z2 + m_location.z;
	}
}

void Enemy::accelerate(float topSpeed)
{
	calculateHeading();

	if (topSpeed > 0 && m_acceleration < topSpeed)
		m_acceleration += 0.5;

	if (topSpeed < 0 && m_acceleration > topSpeed)
		m_acceleration -= 0.5;

	m_p1 = m_p1 + m_heading.normalise() * m_acceleration;
	m_p2 = m_p2 + m_heading.normalise() * m_acceleration;
	m_p3 = m_p3 + m_heading.normalise() * m_acceleration;
	m_p4 = m_p4 + m_heading.normalise() * m_acceleration;
	m_p5 = m_p5 + m_heading.normalise() * m_acceleration;
	m_p6 = m_p6 + m_heading.normalise() * m_acceleration;
	m_p7 = m_p7 + m_heading.normalise() * m_acceleration;
	m_p8 = m_p8 + m_heading.normalise() * m_acceleration;
	m_location = m_location + m_heading.normalise() * m_acceleration;
}


void Enemy::decelerate()
{
	calculateHeading();
	if (m_acceleration > 0)
		m_acceleration -= 0.5;

	if (m_acceleration < 0)
		m_acceleration += 0.5;

	m_p1 = m_p1 + m_heading.normalise() * m_acceleration;
	m_p2 = m_p2 + m_heading.normalise() * m_acceleration;
	m_p3 = m_p3 + m_heading.normalise() * m_acceleration;
	m_p4 = m_p4 + m_heading.normalise() * m_acceleration;
	m_p5 = m_p5 + m_heading.normalise() * m_acceleration;
	m_p6 = m_p6 + m_heading.normalise() * m_acceleration;
	m_p7 = m_p7 + m_heading.normalise() * m_acceleration;
	m_p8 = m_p8 + m_heading.normalise() * m_acceleration;
	m_location = m_location + m_heading.normalise() * m_acceleration;
}

void Enemy::seek(Point3D targetPosition)
{
	Point3D newHeading;
	newHeading.x = (targetPosition.x - m_location.x);
	newHeading.z = (targetPosition.z - m_location.z);
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
	if (m_patrolTarget == Point3D(0.0, m_location.y, 0.0) || m_location.distance(m_patrolTarget) < 500)
		m_patrolTarget = Point3D::randomPointXZ(xmin, xmax, zmin, zmax, m_location.y);

	seek(m_patrolTarget);
}

void Enemy::stateMachine()
{
	// Death State
	if (m_health <= 0)
		m_state = DEAD;

	// Patrol State
	if (m_state == PATROL)
	{
		patrol(m_bounds.xmin, m_bounds.xmax, m_bounds.zmin, m_bounds.zmin);
		accelerate(m_topSpeed / 2);

		if (m_location.distance(*m_enemyPosition) < 5000)   //attack if close to enemy
			m_state = ATTACK;

		// TO DO create attack if hit state change
	}

	// Attack State
	if (m_state == ATTACK)
	{
		seek(*m_enemyPosition);
		drawProjectiles();

		if (glutGet(GLUT_ELAPSED_TIME) > m_timer)
			shoot();

		if (m_location.distance(*m_enemyPosition) > 3000)
		{
			if (canMove(m_topSpeed))
				accelerate(m_topSpeed);
			else
				decelerate();
		}
		else if (m_location.distance(*m_enemyPosition) < 2500)   //back up if player gets too close
		{
			if (canMove(-m_topSpeed))
				accelerate(-m_topSpeed);
			else
				decelerate();
		}
		else
			decelerate();

	}
	if (glutGet(GLUT_ELAPSED_TIME) > m_timer)
		m_timer += m_fireRate;
}

bool Enemy::canMove(double speed)
{
	return((m_location + m_heading.normalise() * speed * 10).x > m_bounds.xmin &&
		(m_location + m_heading.normalise() * speed * 10).x < m_bounds.xmax &&
		(m_location + m_heading.normalise() * speed * 10).z > m_bounds.zmin &&
		(m_location + m_heading.normalise() * speed * 10).z < m_bounds.zmax);
}