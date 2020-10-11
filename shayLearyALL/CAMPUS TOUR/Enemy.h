#pragma once

#include <GL/glut.h>
#include "AABBNode.H"
#include "Entity.h"

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

	//additions
	void seek(Point3D targetPosition);										//seeks target position
	void patrol(double xmin, double xmax, double zmin, double zmax);		//patrols within given bounds
	void drawProjectiles();													//TODO: make private
	void shoot();															//TODO: make private, and add to state machine
	double m_timer;															//TODO: make private

private:
	void updateHitBox(float x, float y, float z);
	float radius = 300;
	AABBNode hitBox;

	//additions
	Point3D m_p1, m_p2, m_p3, m_p4, m_p5, m_p6, m_p7, m_p8;				//the points that make up the box
	Point3D m_heading;
	double m_topSpeed, m_rotationSpeed;
	double m_acceleration;

	Point3D m_patrolTarget;

	int m_projectileCount;
	static const int MAX_PROJECTILES = 5;
	Projectile m_projectiles[MAX_PROJECTILES];

	double m_fireRate;

	void rotateEntity(double rotationSpeed);
	void calculateHeading();
	void accelerate(float topSpeed);
};