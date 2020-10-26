#pragma once

#include <GL/glut.h>
#include "AABBNode.H"
#include "Entity.h"
#include <vector>
#include <irrKlang.h>
#pragma comment(lib, "irrKlang.lib")

// Enemy states
#define DEAD	0
#define PATROL	1  
#define ATTACK	2

		/**
		* @class Enemy
		* @brief Class that defines an Enemy
		* @author Group Team No Name 2
		* @version 1.0
		* @date 26 Oct 20
		*/
class Enemy : public Entity {

public:
	// constructors //
	Enemy(double xmin, double xmax, double zmin, double zmax, double y);	// constructs from bounds
	Enemy();
	Enemy(const Enemy& obj);
	virtual ~Enemy();
	// end constructors //


	// setters and getters
	std::vector<Point3D> getAABB(); 
	void SetPosition(float x, float y, float z);
	inline float GetRadius() { return radius; }
	void setBounds(double xmin, double xmax, double zmin, double zmax);
	inline void setEnemyPosition(Point3D* enemyPosition) { m_enemyPosition = enemyPosition; }
	inline Point3D* getPoints() { return(m_points); }
	inline int getScale() { return m_scale; }
	inline Projectile* getProjectiles(int index) { return &m_projectiles[index]; }
	inline void setState(int state) { m_state = state; }
	// end setters and getters //

		/**
		* @brief resets enemy
		*/
	void reset();

		/**
		* @brief seeks target
		* @param targetPosition 
		*/
	void seek(Point3D targetPosition);																																								

		/**
		* @brief runs state machine
		* @param engine to allow shooting to sound
		*/
	void stateMachine(irrklang::ISoundEngine *engine);

		/**
		* @brief checks if the enemy hit the target
		* @param target a pointer to the entity to check
		*/
	bool checkHit(Entity* target);

	static const int MAX_PROJECTILES = 10;
protected:

		/**
		* @brief updates hit box
		* @param x
		* @param y
		* @param z
		*/
	void updateHitBox(float x, float y, float z);

		/**
		* @brief rotates entity
		* @param rotationSpeed the speed to rotate
		*/
	void rotateEntity(double rotationSpeed);

		/**
		* @brief calculates the heading of the enemy
		*/
	void calculateHeading();

		/**
		* @brief accelerates the enemy to it's top speed
		* @param topSpeed
		*/
	void accelerate(float topSpeed);

		/**
		* @brief decelerates the enemy
		*/
	void decelerate();

		/**
		* @brief patrols withing bounds. seeks to random point, if there find another.
		* @param xmin minimum x value
		* @param xmax maximumn x value
		* @param zmin minimum z value
		* @param zmax maximumn z value
		*/
	void patrol(double xmin, double xmax, double zmin, double zmax);

		/**
		* @brief checks if the next move will be out of bounds
		* @param speed the speed of the enemy
		* @return true if enenmy can move, otherwise, false
		*/
	bool canMove(double speed);		

		/**
		* @brief draws projectiles
		*/
	void drawProjectiles();

		/**
		* @brief logic for enemy to shoot
		*/
	void shoot();

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
	double m_timer;

	int m_state;

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