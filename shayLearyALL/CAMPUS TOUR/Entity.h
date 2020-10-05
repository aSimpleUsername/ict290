//Entity class - Parent class of player and enemy, containing increments, setters and getters for health
//Version 2

#include <GL/glut.h>
#include "point3D.h"
#include "projectile.h"

class Entity
{
public:
	//constructors
	Entity(double x, double y, double z);		//constructs entity on the given location

	//getters & setters
	inline int getHealth() { return m_health; }
	inline int getShields() { return m_shields; }
	inline void setHealth(int health) { m_health = health; }
	inline void setShields(int shields) { m_shields = shields; }
	inline void incrementHealth() { ++m_health; }
	inline void incrementShields() {++m_shields; }
	inline void decreaseHealth() { --m_health; }
	inline void decreaseShields() { --m_shields; }
	inline Point3D getPosition() { return m_center; }

	void seek(Point3D targetPosition);		//seeks target position
	void patrol(double xmin, double xmax, double zmin, double zmax);		//patrols within given bounds
	void drawEntity();
	void drawProjectiles();	//TODO: make private
	void shoot();			//TODO: make private, and add to state machine

	double m_timer; // make private

protected:

	Point3D m_p1, m_p2, m_p3, m_p4, m_p5, m_p6, m_p7, m_p8;		//the points that make up the box
	Point3D m_center, m_heading;

	double m_topSpeed, m_rotationSpeed;
	double m_acceleration;

	int m_health;
	int m_shields;

	Point3D m_patrolTarget;

	int m_projectileCount;
	static const int MAX_PROJECTILES = 5;
	Projectile m_projectiles[MAX_PROJECTILES];

	double m_fireRate;


	void rotateEntity(double rotationSpeed);
	void calculateHeading();
	void accelerate(float topSpeed);
};

