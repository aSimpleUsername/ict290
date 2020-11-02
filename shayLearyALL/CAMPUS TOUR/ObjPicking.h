#pragma once
#include <math.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <vector>
#include "point3D.h"
#include "AABBNode.h"
#include "camera.h"
/**
    * @class ObjPicking
    * @brief Class that handles the ray casting to differant objects
    * @author Group Team No Name 2
    * @version 1.0
    * @date 26 Oct 20
    */
template <class T>
class ObjPicking {
public:
    ObjPicking() {
    }
    virtual ~ObjPicking() {
        clearBuffer();
    }
    /**
        * @brief returns size of buffer
        * @return int
     */
    int size();
    /**
        * @brief adds an object to the buffer
     */
    void addObjectToBuffer(T* object);
    /**
        * @brief gets a pointer to object from the buffer
        * @param object
        * @return T*
     */
    T* getObjectFromBuffer(int index) { return objBuffer[index]; }
    /**
        * @brief Detects collision with sphere
        * @param rayX
        * @param rayY
        * @param rayZ
        * @param camX
        * @param camY
        * @param camZ
        * @return bool
     */
    bool detectCollisionWithSphere(float rayX, float rayY, float rayZ, float camX, float camY, float camZ);
    /**
        * @brief Detects collisions with OBB
        * @param ray
        * @param camPos
        * @param obbPoints
        * @param enemyLocation
        * @param distance
        * @return bool
        */
    bool detectCollisionWithOBB(Point3D ray, Point3D camPos, std::vector<Point3D> obbPoints, Point3D enemyLocation, float& distance);
    /**
        * @brief Detects collisions with AABB
        * @param ray
        * @param camPos
        * @param abbMin
        * @param abbMax
        * @param enemyLocation
        * @param distance
        * @return bool
        */
    bool detectCollisionWithAABB(Point3D ray, Point3D camPos, Point3D aabbMin, Point3D aabbMax, Point3D enemyLocation, float& distance);
    /**
        * @brief Detects collisions with boxes
        * @param ray
        * @param camPos
        * @param maxPoints
        * @param minPoints
        * @return bool
        */
    T* checkCollisionWithBox(Point3D ray, Point3D camPos, std::vector<Point3D> maxPoints, std::vector<Point3D> minPoints);
private:
    /**
        * @brief removes an object to the buffer
        * @param index
     */
    void removeObjectFromBuffer(int index);
    /**
        * @brief clears the buffer
     */
    void clearBuffer();
    ///object buffer 
    std::vector<T*> objBuffer;

};

template <class T>
int ObjPicking<T>::size()
{
    return objBuffer.size();
}

template <class T>
bool ObjPicking<T>::detectCollisionWithSphere(float rayX, float rayY, float rayZ, float camX, float camY, float camZ) {
    for (int i = 1; i < 10000; i++) {
        float rayXStep = (rayX * i) + camX;
        float rayYStep = (rayY * i) + camY;
        float rayZStep = (rayZ * i) + camZ;
        for (int i = 0; i < objBuffer.size(); i++) {
            float tempX = objBuffer[i]->GetX();
            float tempY = objBuffer[i]->GetY();
            float tempZ = objBuffer[i]->GetZ();
            float tempRad = objBuffer[i]->GetRadius();
            float dist = sqrt(pow(tempX - rayXStep, 2) + pow(tempY - rayYStep, 2) + pow(tempZ - rayZStep, 2));
            if (dist < objBuffer[i]->GetRadius())
                return true;
        }
    }
    return false;
}

template <class T>
bool ObjPicking<T>::detectCollisionWithOBB(Point3D ray, Point3D camPos, std::vector<Point3D> obbPoints, Point3D enemyLocation, float& distance) {
    float tMin = 0.0f;
    float tMax = 10000000000.0f;
    Point3D delta = enemyLocation - camPos;
    Point3D axis[3];

    axis[0] = obbPoints[7] - obbPoints[4];
    axis[0] = axis[0].normalise();

    axis[1] = obbPoints[5] - obbPoints[4];
    axis[1] = axis[1].normalise();

    axis[2] = obbPoints[0] - obbPoints[4];
    axis[2] = axis[2].normalise();

    for (int i = 0; i < 3; i++) {
        float t1, t2;
        float e = axis[i].dot(delta);
        float f = axis[i].dot(ray);
        //will crash if dont check for near 0
        if (abs(f) > 1e-20f)
        {
            t1 = ((e + objBuffer[0]->getScale()) / f);
            t2 = ((e - objBuffer[0]->getScale()) / f);
            if (t1 > t2) { // if wrong order
                std::swap(t1, t2);
            }
            if (t2 < tMax)
                tMax = t2;
            if (t1 > tMin)
                tMin = t1;
            if (tMax < tMin)
                return false;
        }
        distance = tMin;
    }
    return true;
}
template <class T>
bool ObjPicking<T>::detectCollisionWithAABB(Point3D ray, Point3D camPos, Point3D aabbMin, Point3D aabbMax, Point3D enemyLocation, float& distance) {
    float tMin = 0.0f;
    float tMax = 10000000000.0f;
    Point3D delta = enemyLocation - camPos;
    Point3D axis[3];

    axis[0] = Point3D(1, 0, 0);
    axis[0] = axis[0].normalise();

    axis[1] = Point3D(0, 1, 0);
    axis[1] = axis[1].normalise();

    axis[2] = Point3D(0, 0, 1);
    axis[2] = axis[2].normalise();
    float max[3] = { aabbMax.x, 100000, aabbMax.z };
    float min[3] = { aabbMin.x, 0, aabbMin.z };
    for (int i = 0; i < 3; i++) {
        float t1, t2;
        float e = axis[i].dot(delta);
        float f = axis[i].dot(ray);
        //will crash if dont check for near 0
        if (abs(f) > 1e-20f)
        {
            t1 = ((e + ((max[i] - min[i]) / 2) -100) / f);
            t2 = ((e - ((max[i] - min[i]) / 2) + 100) / f);
            if (t1 > t2) { // if wrong order
                std::swap(t1, t2);
            }
            if (t2 < tMax)
                tMax = t2;
            if (t1 > tMin)
                tMin = t1;
            if (tMax < tMin)
                return false;
        }
        distance = tMin;
    }
    return true;
}

template <class T>
T* ObjPicking<T>::checkCollisionWithBox(Point3D ray, Point3D camPos, std::vector<Point3D> maxPoints, std::vector<Point3D> minPoints) {
    float tempDistance = 0;
    float obbDistance = FLT_MAX;
    float wallDistance = FLT_MAX;
    int index = 0;
    for (int i = 0; i < objBuffer.size(); i++) {
        if (detectCollisionWithOBB(ray, camPos, objBuffer[i]->getAABB(), objBuffer[i]->getLocation(), tempDistance) && objBuffer[i]->getHealth() > 0) {
            if (tempDistance < obbDistance) {
                obbDistance = tempDistance;
                index = i;

            }
        }
    }
    for (int i = 0; i < maxPoints.size(); i++) {
        Point3D center = Point3D(maxPoints[i].x - ((maxPoints[i].x - minPoints[i].x) / 2), 10550, maxPoints[i].z - ((maxPoints[i].z - minPoints[i].z) / 2));
        if (detectCollisionWithAABB(ray, camPos, minPoints[i], maxPoints[i], center, tempDistance)) {
            if (tempDistance < wallDistance && tempDistance != 0) {
                wallDistance = tempDistance;

            }
        }
    }
    if (wallDistance > obbDistance && obbDistance != 0 && wallDistance != 0) {
        return objBuffer[index];
    }
    return NULL;
}
template <class T>
void ObjPicking<T>::addObjectToBuffer(T* object) {
    objBuffer.push_back(object);
}
template <class T>
void ObjPicking<T>::removeObjectFromBuffer(int index) {
    objBuffer.clear();
}
template <class T>
void ObjPicking<T>::clearBuffer() {
    objBuffer.clear();
}