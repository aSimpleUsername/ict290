#pragma once
#include <math.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <vector>
#include "point3D.h"
//this comment is to make shit work
template <class T>
class ObjPicking{
public:
    ObjPicking() {
    }
	virtual ~ObjPicking(){
		clearBuffer();
	}
    int size();

	void addObjectToBuffer(T *object);
    T* getObjectFromBuffer(int index) { return objBuffer[index]; }
	bool detectCollisionWithSphere(float rayX, float rayY,float rayZ,float camX,float camY,float camZ);
    bool detectCollisionWithBox(Point3D ray, Point3D camPos, std::vector<Point3D> obbPoints,Point3D enemyLocation);
    T* checkCollisionWithBox(Point3D ray, Point3D camPos);
private:
	void removeObjectFromBuffer(int index);
	void clearBuffer();
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
            float dist = sqrt(pow(tempX - rayXStep,2) + pow(tempY - rayYStep,2) + pow(tempZ - rayZStep,2));
            if (dist < objBuffer[i]->GetRadius())
                return true;
        }
    }
    return false;
}

template <class T>
bool ObjPicking<T>::detectCollisionWithBox(Point3D ray, Point3D camPos, std::vector<Point3D> obbPoints, Point3D enemyLocation) {
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

    for (int i = 0; i < 3;i++) {
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
    }
    return true;
}
template <class T>
T* ObjPicking<T>::checkCollisionWithBox(Point3D ray, Point3D camPos) {
    for(int i = 0; i < objBuffer.size();i++) {
        if (detectCollisionWithBox(ray, camPos, objBuffer[i]->getAABB(), objBuffer[i]->getLocation()) &&
                objBuffer[i]->getHealth() > 0) {
            return objBuffer[i];
        }
    }
    return NULL;
}
template <class T>
void ObjPicking<T>::addObjectToBuffer(T* object) {
    objBuffer.push_back(object);
}
template <class T>
void ObjPicking<T>::removeObjectFromBuffer(int index){
    objBuffer.clear();
}
template <class T>
void ObjPicking<T>::clearBuffer() {
    objBuffer.clear();
}