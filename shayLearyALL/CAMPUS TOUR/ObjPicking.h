#pragma once
#include <math.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <vector>

template <class T>
class ObjPicking{
	struct obj{
		T object;
		int colour;
	};
public:
	ObjPicking(){
	}
	virtual ~ObjPicking(){
		clearBuffer();
	}
	void addObjectToBuffer(T object);
private:
	void removeObjectFromBuffer(int index);
	void clearBuffer();
	std::vector<T> objBuffer;

};

