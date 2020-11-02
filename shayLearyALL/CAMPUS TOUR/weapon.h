#ifndef WEAPON_H
#define WEAPON_H

#include "ObjPicking.h"
#include "Enemy.h"
#include "enemyBoss.h"
#include "point3D.h"
#include "camera.h"

/**
    * @class Weapon
    * @brief Class that makes the weapon shoot as well as managing ammo
    * @author Group Team No Name 2
    * @version 1.0
    * @date 26 Oct 20
    */
class Weapon {
    private:
        /// Total ammo player has
        int totalAmmo;
        /// ammo currently loaded
        int magazine;
        /**
        * @brief removes the ammo from the total
        * @param ammoAmount
        */
        void takeAmmo(int amount);
    public:
        Weapon();
        /**
        * @brief adds the ammo to the total
        * @param ammoAmount
        */
        void addAmmo(int amount);
        /**
        * @brief overloaded shoot class that checks the enemies
        * @param ray
        * @param camPos
        * @param enemies
        * @param maxPoints
        * @param minPoints
        * @return bool
        */
        bool shoot(Point3D ray, Point3D camPos, ObjPicking<Enemy> enemies, std::vector<Point3D> maxPoints, std::vector<Point3D> minPoints);
        /**
        * @brief overloaded shoot class that checks the boss for a hit
        * @param ray
        * @param camPos
        * @param enemies
        * @param maxPoints
        * @param minPoints
        * @return bool
        */
        bool shoot(Point3D ray, Point3D camPos, ObjPicking<EnemyBoss> enemies, std::vector<Point3D> maxPoints, std::vector<Point3D> minPoints);
        /**
        * @brief reloads from total ammo into magazine
        */
        void reload();
};
#endif //!WEAPON_H