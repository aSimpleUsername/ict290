#pragma once

#include <GL/glut.h>
#include <string>

class UserInterface
{
public:
	bool m_hit = false;							// true when player hits enemy
	bool m_playerHit = false;					// true when player is hit

	void playerHealth(int playerHealth);		//displays player health
	void playerShield(int playerShield);		//displays player shield
	void info(double x, double y, double z);	//displays useful info
	void hitmarker(const int& screenWidth, const int& screenHeight,
		const GLuint& tempImage);							//displays thing when hit
	void healthBar(const int& screenWidth, const int& screenHeight,
		const GLuint& tempImage);
	void shieldBar(const int& screenWidth, const int& screenHeight,
		const GLuint& tempImage);
	void ammoCount1(const int& screenWidth, const int& screenHeight,
		const GLuint& tempImage);
	void ammoCount2(const int& screenWidth, const int& screenHeight,
		const GLuint& tempImage);
	void rAmmoCount0(const int& screenWidth, const int& screenHeight,
		const GLuint& tempImage);
	void rAmmoCount1(const int& screenWidth, const int& screenHeight,
		const GLuint& tempImage);
	void rAmmoCount2(const int& screenWidth, const int& screenHeight,
		const GLuint& tempImage);
	void bossHealthBar(const int& screenWidth, const int& screenHeight,
		const GLuint& tempImage);
	void bossName(const int& screenWidth, const int& screenHeight,
		const GLuint& tempImage);
	void weapon(const int& screenWidth, const int& screenHeight,
		const GLuint& tempImage);
	void playerHit(const int& screenWidth, const int& screenHeight,
		const GLuint& tempImage);
	void transparent(const int& screenWidth, const int& screenHeight,
		const GLuint& tempImage);
	void context(const int& screenWidth, const int& screenHeight,
		const GLuint& tempImage);

private:
	void renderText(float x, float y, void* font, std::string string);
	double m_hitTimer;
	double m_playerHitTimer;

};

