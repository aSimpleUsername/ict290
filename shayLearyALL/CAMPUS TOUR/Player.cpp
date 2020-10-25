#include "Player.h"

Player::Player()
{
	
	setHealth(10);
	setShields(10);
	setAmmo(MAX_AMMO);
	setReserveAmmo(MAX_AMMO_RESERVE);
}

void Player::incrementAmmo()
{
	if (ammo < MAX_AMMO)
	{
		ammo++;
	}
	else if (ammoReserve < MAX_AMMO_RESERVE)
	{
		ammoReserve++;
	}
}

void Player::decreaseAmmo()
{
	if (ammo > 0)
	{
		ammo--;
	}
}

int Player::getAmmo()
{
	return ammo;
}

void Player::setAmmo(int a)
{
	ammo = a;
}

int Player::getReserveAmmo()
{
	return ammoReserve;
}

void Player::setReserveAmmo(int a)
{
	ammoReserve = a;
}

void Player::reload()
{
	ammoReserve = ammoReserve - (MAX_AMMO - ammo);
	ammo = MAX_AMMO;
}