#include "Weapon.h"

void Weapon::takeAmmo(int amount){
    totalAmmo -= amount;
}
void Weapon::addAmmo(int amount){
    totalAmmo += amount;
}
void Weapon::shoot(ObjPicking<Enemy> enemies){
    
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
