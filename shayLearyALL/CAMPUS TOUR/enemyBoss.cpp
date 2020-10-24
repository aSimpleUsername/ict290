#include "enemyBoss.h"

EnemyBoss::EnemyBoss(double xmin, double xmax, double zmin, double zmax, double y)	// constructs from bound
{
	m_topSpeed = 20;
	m_rotationSpeed = 0.025;
	m_timer = 0;
	m_fireRate = 500;
	m_heading = (Point3D(0.0, 0.0, 0.0));
	m_state = PATROL;
	m_scale = 450;

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

	m_health = 50;
	m_shields = 0;

	m_patrolTarget = Point3D(0.0, m_location.y, 0.0);
	setBounds(xmin, xmax, zmin, zmax);

	updateHitBox(m_location.x, m_location.y, m_location.z);
}