#pragma once
#include <math.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <vector>
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