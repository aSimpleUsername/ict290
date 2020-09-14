//  cameraMap.h
//  Header file for the cameraMap class
//  Displays a map and welcome screen in 2D on the screen
//  
//  Shay Leary, April 2005
//--------------------------------------------------------------------------------------

#ifndef CAMERA_MAP_H
#define CAMERA_MAP_H

#include <gl/glut.h>

//--------------------------------------------------------------------------------------

class CameraMap
{
public:
	CameraMap() {};
	virtual ~CameraMap() {};

	//----------------------------------------------------------------------------------

	/**
		* @brief Displays the map
		* @param screenWidth - width of screen
		* @param screenHeight - height of
		* @param xPos - x position of map
		* @param xPos - z position of map
		* @param tempImage - image of map
		* @return void
	*/
	void DisplayMap(const int & screenWidth, const int & screenHeight,
				    const GLdouble & xPos, const GLdouble & zPos,
					const GLuint & tempImage);
	/**
		* @brief Displays Welcome Screen
		* @param screenWidth - width of screen
		* @param screenHeight - height of
		* @param tempExit - ?
		* @param tempImage - image of welcome screen
		* @return void
	*/
	void DisplayWelcomeScreen (const int & screenWidth, const int & screenHeight, 
		                       const int & tempExit, const GLuint & tempImage);
	/**
		* @brief Displays Exit Screen
		* @param screenWidth - width of screen
		* @param screenHeight - height of
		* @param tempImage - image of exit screen
		* @return void
	*/
	void DisplayNoExit (const int & screenWidth, const int & screenHeight, 
						const GLuint & tempImage);

private:
    // Privatised copy constructor and assignment operator
    CameraMap (const CameraMap &cam) {};
    CameraMap &operator = (const CameraMap &cam) {};
};

#endif

//--------------------------------------------------------------------------------------