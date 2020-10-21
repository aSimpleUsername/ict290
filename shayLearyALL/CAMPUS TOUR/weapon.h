#ifndef WEAPON_H
#define WEAPON_H

#include "ObjPicking.h"
#include "Enemy.h"
#include "point3D.h"
#include <iostream>
class Weapon {
    private:
        int totalAmmo;
        int magazine;
        void takeAmmo(int amount);
    public:
        Weapon();
        void addAmmo(int amount);
        void shoot(Point3D ray, Point3D camPos, ObjPicking<Enemy> enemies);
        void reload();
        void drawWeapon();

        int getAmmo();
};
#endif //!WEAPON_H