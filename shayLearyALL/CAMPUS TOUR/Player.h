//Player class - Child class of entity, sharing health and shields
#pragma once

#include "Entity.h"

	/**
	* @class Player
	* @brief Class that defines a player - extends Entity 
	* @author Group Team No Name 2
	* @version 1.0
	* @date 26 Oct 20
	*/
class Player : public Entity
{
public:
	// constructor //
	Player();
	
	// setters and getters //
	inline void updateLocation(double x, double y, double z) { m_location = Point3D(x, y, z); }
	inline Point3D* getPlayerLocationPointer() { return(&m_location); }
	inline void resetHealth() { m_health = MAX_HEALTH; }
	inline void resetShields() { m_shields = MAX_HEALTH; }

	int getAmmo();
	void setAmmo(int a);
	void setReserveAmmo(int a);
	int getReserveAmmo();
	int getMaxReserveAmmo();
	// end setters and getters //


		/**
		* @brief increments ammo
		*/
	void incrementAmmo();

		/**
		* @brief decreases ammo
		*/
	void decreaseAmmo();

		/**
		* @brief logic to reload players weapon
		*/
	void reload();

private:
	int const MAX_HEALTH = 10;
	int ammo;
	int ammoReserve;
	int const MAX_AMMO = 30;
	int const MAX_AMMO_RESERVE = 150;
};

