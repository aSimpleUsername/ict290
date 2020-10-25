#include "Weapon.h"
Weapon::Weapon() {
    totalAmmo = 60;
    magazine = 30;
}
void Weapon::takeAmmo(int amount){
    totalAmmo -= amount;
}
void Weapon::addAmmo(int amount){
    totalAmmo += amount;
}

bool Weapon::shoot(Point3D ray, Point3D camPos, ObjPicking<Enemy> enemies, std::vector<Point3D> maxPoints, std::vector<Point3D> minPoints) {
    if (enemies.checkCollisionWithBox(ray, camPos, maxPoints,minPoints) != NULL){
        enemies.checkCollisionWithBox(ray, camPos, maxPoints, minPoints)->decreaseHealth();
        return true;
    }
    else
        return false;
}

bool Weapon::shoot(Point3D ray, Point3D camPos, ObjPicking<EnemyBoss> enemies, std::vector<Point3D> maxPoints, std::vector<Point3D> minPoints) {
    if (enemies.checkCollisionWithBox(ray, camPos, maxPoints, minPoints) != NULL) {
        enemies.checkCollisionWithBox(ray, camPos, maxPoints, minPoints)->decreaseHealth();
        return true;
    }
    else
        return false;
}


void Weapon::reload(){
    totalAmmo += magazine;
    magazine = 0;
    totalAmmo -= 30;
    if(totalAmmo <= 0){
        magazine = 30 + totalAmmo;
        totalAmmo = 0;
    }
    else{
        magazine = 30;
    }
}

