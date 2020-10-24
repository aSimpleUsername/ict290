#pragma once

#include <GL/glut.h>
#include <string>

class UserInterface
{
public:
	bool hit = false;							// true when player hits enemy

	void playerHealth(int playerHealth);		//displays player health
	void info(double x, double y, double z);	//displays useful info
	void hitmarker();							//displays thing when hit

private:
	void renderText(float x, float y, void* font, std::string string);
	double m_timer;

};

