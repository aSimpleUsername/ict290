#pragma once

#include <GL/glut.h>
#include "AABBNode.H"
#include "Entity.h"
#include <vector>

// Enemy states
#define DEAD	0
#define PATROL	1  
#define ATTACK	2

class Enemy : public Entity {

public:
	Enemy(double xmin, double xmax, double zmin, double zmax, double y);	// constructs from bounds
	Enemy();
	Enemy(const Enemy& obj);
	virtual ~Enemy();

	std::vector<Point3D> getAABB();

	// setters and getters 
	void SetPosition(float x, float y, float z);
	inline float GetRadius() { return radius; }
	void setBounds(double xmin, double xmax, double zmin, double zmax);
	inline void setEnemyPosition(Point3D* enemyPosition) { m_enemyPosition = enemyPosition; }
	inline Point3D* getPoints() { return(m_points); }
	inline int getScale() { return m_scale; }
	inline Projectile* getProjectiles(int index) { return &m_projectiles[index]; }

	void reset();
	void seek(Point3D targetPosition);										//seeks target position															//patrols within given bounds
	static const int MAX_PROJECTILES = 10;
	void drawProjectiles();													//TODO: make private
	void shoot();															//TODO: make private, and add to state machine
	double m_timer;															//TODO: make private

	void stateMachine();
	void checkHit(Entity* target);

protected:
	void updateHitBox(float x, float y, float z);
	float radius = 300;
	AABBNode hitBox;

	int m_scale;
	Point3D m_heading;
	double m_topSpeed, m_rotationSpeed;
	double m_acceleration;
	int m_maxHealth;

	Point3D m_patrolTarget;
	Point3D* m_enemyPosition;

	int m_projectileCount;
	Projectile m_projectiles[MAX_PROJECTILES];

	double m_fireRate;

	int m_state;

	void rotateEntity(double rotationSpeed);
	void calculateHeading();
	void accelerate(float topSpeed);
	void decelerate();
	void patrol(double xmin, double xmax, double zmin, double zmax);
	bool canMove(double speed);		// checks if the next move will be out of bounds

	struct
	{
		double xmin;
		double xmax;
		double zmin;
		double zmax;
	}m_bounds;

	// points that make up the 
	static const int POINTS_SIZE = 8;
	Point3D m_points[POINTS_SIZE];
};