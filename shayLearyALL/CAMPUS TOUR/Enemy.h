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
	//Enemy(double x, double y, double z);									// constructs from location
	Enemy(double xmin, double xmax, double zmin, double zmax, double y);	// constructs from bounds
	Enemy();
	Enemy(const Enemy& obj);
	virtual ~Enemy();

	std::vector<Point3D> getAABB();

	// setters and getters 
	void SetPosition(float x, float y, float z);
	inline float GetRadius() { return radius; }
	void setBounds(double xmin, double xmax, double zmin, double zmax);
	//void patrol() { patrol(m_bounds.xmin, m_bounds.xmax, m_bounds.zmin, m_bounds.zmax); }		// calls private patrol(), if needed move to .cpp file. delete if still commented
	inline void setEnemyPosition(Point3D* enemyPosition) { m_enemyPosition = enemyPosition; }
	inline Point3D* getPoints() { return(m_points); }
	//inline int getPointsSize() { return(POINTS_SIZE); }	// if still commented delete


	void seek(Point3D targetPosition);										//seeks target position															//patrols within given bounds
	void drawProjectiles();													//TODO: make private
	void shoot();															//TODO: make private, and add to state machine
	double m_timer;															//TODO: make private

	void stateMachine();
	void checkHit(Entity* target);

private:
	void updateHitBox(float x, float y, float z);
	float radius = 300;
	AABBNode hitBox;

	static const int SCALE = 150;
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