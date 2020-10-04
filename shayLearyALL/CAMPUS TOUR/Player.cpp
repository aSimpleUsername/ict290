#include "Player.h"

Player::Player(double x, double y, double z)
	: Entity(x, y, z)
{
	
	setHealth(5);
	setShields(0);
}