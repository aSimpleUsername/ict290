#include "Enemy.h"

Enemy::Enemy(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
	updateHitBox(x, y, z);
}
Enemy::Enemy() {
	this->x = 0;
	this->y = 0;
	this->z = 0;
}
Enemy::~Enemy() {

}
void Enemy::updateHitBox(float x, float y, float z){
	hitBox.SetData(x + 1, x, y + 1, y, z + 1, z);
}
void Enemy::drawEnemy() {
	glPushMatrix();
	glTranslatef(x, y, z);
	glColor3f(1, 0, 0);
	glutSolidSphere(300, 50, 50);
	glPopMatrix();
	std::cout << "drawn enemy" << x << " " << y << " " << z << " " << std::endl;
}
void Enemy::getAABB() {

}
void Enemy::SetPosition(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
	updateHitBox(x, y, z);
}