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
	if (ammoReserve > 60) {
		setReserveAmmo(90);
	}
	else {
		ammoReserve += 30;
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
	ammoReserve += ammo;
	ammo = 0;
	ammoReserve -= 30;
	if (ammoReserve <= 0) {
		ammo = 30 + ammoReserve;
		ammoReserve = 0;
	}
	else {
		ammo = 30;
	}
}

int Player::getMaxReserveAmmo()
{
	return MAX_AMMO_RESERVE;
}