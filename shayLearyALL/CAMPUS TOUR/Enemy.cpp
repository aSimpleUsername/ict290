#include "Enemy.h"

Enemy::Enemy(double x, double y, double z)
	: Entity(x, y, z)
{
	setHealth(1);
	setShields(1);
}