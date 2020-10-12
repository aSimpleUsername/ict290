#pragma once

#include <GL/glut.h>
#include "AABBNode.H"
#include "Entity.h"

#define DEAD	0
#define PATROL	1
#define ATTACK	2

class Enemy : public Entity {

public:
	Enemy(double x, double y, double z);
	Enemy();
	Enemy(const Enemy& obj);
	virtual ~Enemy();
	void getAABB();
	void drawEnemy();
	void SetPosition(float x, float y, float z);
	inline float GetRadius() { return radius; }
	void setBounds(double xmin, double xmax, double zmin, double zmax);
	//void patrol() { patrol(m_bounds.xmin, m_bounds.xmax, m_bounds.zmin, m_bounds.zmax); }		// calls private patrol(), if needed move to .cpp file. delete if not needed
	inline void setEnemyPosition(Point3D* enemyPosition) { m_enemyPosition = enemyPosition; }

	void seek(Point3D targetPosition);										//seeks target position															//patrols within given bounds
	void drawProjectiles();													//TODO: make private
	void shoot();															//TODO: make private, and add to state machine
	double m_timer;															//TODO: make private

	void stateMachine();

private:
	void updateHitBox(float x, float y, float z);
	float radius = 300;
	AABBNode hitBox;

	Point3D m_p1, m_p2, m_p3, m_p4, m_p5, m_p6, m_p7, m_p8;				//the points that make up the box
	Point3D m_heading;
	double m_topSpeed, m_rotationSpeed;
	double m_acceleration;

	Point3D m_patrolTarget;
	Point3D* m_enemyPosition;

	int m_projectileCount;
	static const int MAX_PROJECTILES = 5;
	Projectile m_projectiles[MAX_PROJECTILES];

	double m_fireRate;

	int m_state;

	void rotateEntity(double rotationSpeed);
	void calculateHeading();
	void accelerate(float topSpeed);
	void decelerate();
	void patrol(double xmin, double xmax, double zmin, double zmax);		

	struct
	{
		double xmin;
		double xmax;
		double zmin;
		double zmax;
	}m_bounds;
};