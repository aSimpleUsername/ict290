#pragma once

#include "AABBNode.H"

class Enemy{
		
	public:
		Enemy(float x, float y, float z);
		Enemy();
		virtual ~Enemy();
		void getAABB();
		void drawEnemy();
		void SetPosition(float x,float y,float z);
	private:
		void updateHitBox(float x, float y, float z);
		float x, y, z;
		AABBNode hitBox;
};

