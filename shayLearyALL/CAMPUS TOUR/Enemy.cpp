#include "Enemy.h"

Enemy::Enemy(double xmin, double xmax, double zmin, double zmax, double y)
	: m_topSpeed(20), m_rotationSpeed(0.035), m_timer(0), m_fireRate(500), m_heading(Point3D(0.0, 0.0, 0.0)),
	m_state(PATROL), m_scale(150)
{
	m_location = Point3D::randomPointXZ(xmin + 2 * m_scale, xmax - 2 * m_scale, zmin + 2 * m_scale, zmax - 2 * m_scale, y);		// 2*SCALE ensures that the enemy spawns inside the bounds and not on the edge
	//top 4 points going clockwise starting with front left
	m_points[0] = Point3D(m_location.x - m_scale, m_location.y + m_scale, m_location.z + m_scale);
	m_points[1] = Point3D(m_location.x - m_scale, m_location.y + m_scale, m_location.z - m_scale);
	m_points[2] = Point3D(m_location.x + m_scale, m_location.y + m_scale, m_location.z - m_scale);
	m_points[3] = Point3D(m_location.x + m_scale, m_location.y + m_scale, m_location.z + m_scale);
	//bottom 4 points going clockwise starting with front left (player is 450 units tall)
	m_points[4] = Point3D(m_location.x - m_scale, m_location.y - m_scale, m_location.z + m_scale);
	m_points[5] = Point3D(m_location.x - m_scale, m_location.y - m_scale, m_location.z - m_scale);
	m_points[6] = Point3D(m_location.x + m_scale, m_location.y - m_scale, m_location.z - m_scale);
	m_points[7] = Point3D(m_location.x + m_scale, m_location.y - m_scale, m_location.z + m_scale);

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

void Enemy::reset()
{
	m_health = MAX_HEALTH;
	m_state = PATROL;

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

std::vector<Point3D> Enemy::getAABB()
{
	std::vector<Point3D> boundingBox;
	for (int i = 0; i < POINTS_SIZE; ++i)
		boundingBox.push_back(m_points[i]);
	return boundingBox;
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

void Enemy::checkHit(Entity* target)
{
	for (int j = 0; j < MAX_PROJECTILES; ++j)
	{
		if (m_projectiles[j].m_location.distance(target->getLocation()) < 200)
		{
			if (target->getShields() > 0)
			{
				target->decreaseShields();
			}
			else
			{
				target->decreaseHealth();
			}
			m_projectiles[j].m_location = Point3D(0.0, 0.0, 0.0);
			m_projectiles[j].m_heading = Point3D(0.0, 0.0, 0.0);
		}
	}
}

void Enemy::calculateHeading()
{
	Point3D frontCenter;
	frontCenter.x = (m_points[0].x + m_points[3].x) / 2;
	frontCenter.y = m_location.y;
	frontCenter.z = (m_points[0].z + m_points[3].z) / 2;

	m_heading = frontCenter - m_location;
}

//rotates all points around the center point
void Enemy::rotateEntity(double rotationSpeed)
{
	for (int i = 0; i < POINTS_SIZE; ++i)
	{
		double x1 = m_points[i].x - m_location.x;
		double z1 = m_points[i].z - m_location.z;

		double x2 = x1 * cos(rotationSpeed) - z1 * sin(rotationSpeed);
		double z2 = x1 * sin(rotationSpeed) + z1 * cos(rotationSpeed);

		m_points[i].x = x2 + m_location.x;
		m_points[i].z = z2 + m_location.z;
	}
}

void Enemy::accelerate(float topSpeed)
{
	calculateHeading();

	if (topSpeed > 0 && m_acceleration < topSpeed)
		m_acceleration += 0.5;

	if (topSpeed < 0 && m_acceleration > topSpeed)
		m_acceleration -= 0.5;

	for (int i = 0; i < POINTS_SIZE; ++i)
		m_points[i] = m_points[i] + m_heading.normalise() * m_acceleration;
	m_location = m_location + m_heading.normalise() * m_acceleration;
}

void Enemy::decelerate()
{
	calculateHeading();
	if (m_acceleration > 0)
		m_acceleration -= 0.5;

	if (m_acceleration < 0)
		m_acceleration += 0.5;

	for (int i = 0; i < POINTS_SIZE; ++i)
		m_points[i] = m_points[i] + m_heading.normalise() * m_acceleration;
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

		if (m_health < MAX_HEALTH)
			m_state = ATTACK;
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
			if (canMove(m_topSpeed*2))
				accelerate(m_topSpeed);
			else
				decelerate();
		}
		else if (m_location.distance(*m_enemyPosition) < 2500)   //back up if player gets too close
		{
			if (canMove(-m_topSpeed*2))
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