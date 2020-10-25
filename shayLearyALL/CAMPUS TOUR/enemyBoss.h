#pragma once

#include "Enemy.h"

class EnemyBoss : public Enemy {

public:
	EnemyBoss(double xmin, double xmax, double zmin, double zmax, double y);

private:
	int MAX_HEALTH = 50;
};

