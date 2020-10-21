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
void Weapon::shoot(Point3D ray, Point3D camPos, ObjPicking<Enemy> enemies) {
    if(enemies.checkCollisionWithBox(ray, camPos) != NULL){
        enemies.checkCollisionWithBox(ray, camPos)->decreaseHealth();
        std::cout << "hit" << std::endl;
    }
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
void Weapon::drawWeapon(){
    
}
int Weapon::getAmmo(){
    return totalAmmo;
}
