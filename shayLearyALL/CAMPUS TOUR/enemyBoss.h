#pragma once

#include "Enemy.h"

/**
* @class EnemyBoss
* @brief Class that defines an EnemyBoss - extends Enemy. Just constructs different to an enenmy
* @author Group Team No Name 2
* @version 1.0
* @date 26 Oct 20
*/
class EnemyBoss : public Enemy {

public:
	// constructor
	EnemyBoss(double xmin, double xmax, double zmin, double zmax, double y);		// constructs of bounds


private:
	int MAX_HEALTH = 100;
};

