#pragma once

#include <GL/glut.h>
#include <string>

	/**
	* @class UserInterface
	* @brief Class that defines how the user interface will be displayed
	* @author Group Team No Name 2
	* @version 2.0
	* @date 26 Oct 20
	*/
class UserInterface
{
public:
		/**
		* @brief displays player health 
		* @param playerHealth
		*/
	void playerHealth(int playerHealth);

		/**
		* @brief displays player shields
		* @param playerShield
		*/		
	void playerShield(int playerShield);

		/**
		* @brief displays player location
		* @param player location x, y, z
		*/
	void info(double x, double y, double z);

		/**
		* @brief displays indicator that player hit enemy
		* @param screenWidth
		* @param screenHeight
		* @oaram tempImage the image to display
		*/
	void hitmarker(const int& screenWidth, const int& screenHeight,
		const GLuint& tempImage);

		/**
		* @brief displays player health bar
		* @param screenWidth
		* @param screenHeight
		* @oaram tempImage the image to display
		*/
	void healthBar(const int& screenWidth, const int& screenHeight,
		const GLuint& tempImage);

		/**
		* @brief displays player shield bar
		* @param screenWidth
		* @param screenHeight
		* @oaram tempImage the image to display
		*/
	void shieldBar(const int& screenWidth, const int& screenHeight,
		const GLuint& tempImage);

		/**
		* @brief displays first digit in rounds in current magazine
		* @param screenWidth
		* @param screenHeight
		* @oaram tempImage the image to display
		*/
	void ammoCount1(const int& screenWidth, const int& screenHeight,
		const GLuint& tempImage);

		/**
		* @brief displays second digit in rounds in current magazine
		* @param screenWidth
		* @param screenHeight
		* @oaram tempImage the image to display
		*/
	void ammoCount2(const int& screenWidth, const int& screenHeight,
		const GLuint& tempImage);

		/**
		* @brief displays first digit in rounds in reserve
		* @param screenWidth
		* @param screenHeight
		* @oaram tempImage the image to display
		*/
	void rAmmoCount0(const int& screenWidth, const int& screenHeight,
		const GLuint& tempImage);

		/**
		* @brief displays second digit in rounds in reserve
		* @param screenWidth
		* @param screenHeight
		* @oaram tempImage the image to display
		*/
	void rAmmoCount1(const int& screenWidth, const int& screenHeight,
		const GLuint& tempImage);

		/**
		* @brief displays third digit in rounds in reserve
		* @param screenWidth
		* @param screenHeight
		* @oaram tempImage the image to display
		*/
	void rAmmoCount2(const int& screenWidth, const int& screenHeight,
		const GLuint& tempImage);

		/**
		* @brief displays boss health bar
		* @param screenWidth
		* @param screenHeight
		* @oaram tempImage the image to display
		*/
	void bossHealthBar(const int& screenWidth, const int& screenHeight,
		const GLuint& tempImage);

		/**
		* @brief displays boss name
		* @param screenWidth
		* @param screenHeight
		* @oaram tempImage the image to display
		*/
	void bossName(const int& screenWidth, const int& screenHeight,
		const GLuint& tempImage);

		/**
		* @brief displays weapon
		* @param screenWidth
		* @param screenHeight
		* @oaram tempImage the image to display
		*/
	void weapon(const int& screenWidth, const int& screenHeight,
		const GLuint& tempImage);

		/**
		* @brief displays visual indicator that player has been hit by enemy
		* @param screenWidth
		* @param screenHeight
		* @oaram tempImage the image to display
		*/
	void playerHit(const int& screenWidth, const int& screenHeight,
		const GLuint& tempImage);

		/**
		* @brief displays a transparent image (to cover an anomaly)
		* @param screenWidth
		* @param screenHeight
		* @oaram tempImage the image to display
		*/
	void transparent(const int& screenWidth, const int& screenHeight,
		const GLuint& tempImage);

		/**
		* @brief displays story context
		* @param screenWidth
		* @param screenHeight
		* @oaram tempImage the image to display
		*/
	void context(const int& screenWidth, const int& screenHeight,
		const GLuint& tempImage);

	bool m_hit = false;							// true when player hits enemy
	bool m_playerHit = false;					// true when player is hit
private:

		/**
		* @brief renders text to screen using bitmap
		* @param x
		* @param y
		* @param font the font to use
		* @param string the string to display
		*/
	void renderText(float x, float y, void* font, std::string string);

	double m_hitTimer;
	double m_playerHitTimer;

};

