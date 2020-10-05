<<<<<<< HEAD
#include "AABBNode.H"

class Enemy{
		
	public:
		Enemy(float x, float y, float z);
		Enemy();
		Enemy(const Enemy& obj);
		virtual ~Enemy();
		void getAABB();
		void drawEnemy();
		void SetPosition(float x,float y,float z);
		float GetX() { return x;}
		float GetY() { return y;}
		float GetZ() { return z;}
		float GetRadius() { return radius; }
private:
		void updateHitBox(float x, float y, float z);
		float x, y, z;
		float radius = 300;
		AABBNode hitBox;
=======
//Enemy class - Child class of entity, sharing health and shields

#include "Entity.h"

class Enemy : public Entity
{
public:
	Enemy(double x, double y, double z);

private:

>>>>>>> parent of 0a161b5... Updating with hitreg
};

