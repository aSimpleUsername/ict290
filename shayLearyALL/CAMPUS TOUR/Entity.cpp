#include "Entity.h"

Entity::Entity()
{
	health = 5;
	shields = 0;
}

int Entity::getHealth()
{
	return health;
}

int Entity::getShields()
{
	return shields;
}

void Entity::setHealth(int h)
{
	health = h;
}

void Entity::setShields(int s)
{
	shields = s;
}

void Entity::incrementHealth()
{
	health++;
}

void Entity::incrementShields()
{
	shields++;
}

void Entity::decreaseHealth()
{
	health--;
}

void Entity::decreaseShields()
{
	shields--;
}