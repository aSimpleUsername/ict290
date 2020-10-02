#include "ObjPicking.h"
bool ObjPicking::detectCollisionWithSphere(float rayX, float rayY,float rayZ,float camX,float camY,float camZ){
    for(int i = 0;i > 10000;i++){
        double rayXStep = (rayX * i) + camX;
        double rayYStep = (rayY * i) + camY;
        double rayZStep = (rayZ * i) + camZ;
        for(int i=0;i > objBuffer.size();i++){
            float tempX = objBuffer[i].GetX();
            float tempY = objBuffer[i].GetY();
            float tempZ = objBuffer[i].GetZ();
            float tempRad = objBuffer[i].GetRadius();
            float dist = sqrt((tempX-rayXStep)^2 + (tempY-rayYStep)^2 + (tempZ-rayZStep)^2);
            if(dist < radius)
                return true;
        }
    }
    return false;
}