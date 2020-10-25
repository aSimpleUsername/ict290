#ifndef WEAPON_H
#define WEAPON_H

#include "ObjPicking.h"
#include "Enemy.h"
#include "enemyBoss.h"
#include "point3D.h"
#include "camera.h"
class Weapon {
    private:
        int totalAmmo;
        int magazine;
        void takeAmmo(int amount);
    public:
        Weapon();
        void addAmmo(int amount);
        bool shoot(Point3D ray, Point3D camPos, ObjPicking<Enemy> enemies, std::vector<Point3D> maxPoints, std::vector<Point3D> minPoints);
        bool shoot(Point3D ray, Point3D camPos, ObjPicking<EnemyBoss> enemies, std::vector<Point3D> maxPoints, std::vector<Point3D> minPoints);
        void reload();
};
#endif //!WEAPON_H