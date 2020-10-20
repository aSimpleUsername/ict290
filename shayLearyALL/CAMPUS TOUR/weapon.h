#ifndef WEAPON_H
#define WEAPON_H

#include "ObjPicking.h"
#include "Enemy.h"
class Weapon {
    private:
        int totalAmmo;
        int magazine;
        void takeAmmo(int amount);
    public:
        void addAmmo(int amount);
        void shoot(ObjPicking<Enemy> enemies);
        void reload();
        void drawWeapon();

        int getAmmo();
};
#endif //!WEAPON_H