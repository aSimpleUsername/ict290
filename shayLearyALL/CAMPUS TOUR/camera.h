//  camera.h
//  Header file for the camera class
//	Allows the camera to be navigated around the world. 
//	Also sets Plains, Bounding Boxes and view Maps
//
//  Shay Leary, March 2005
//--------------------------------------------------------------------------------------
#ifndef CAMERA_H
#define CAMERA_H

#define PI 3.1415962654

#include <stdio.h>	// for printPostion()
#include "collision.h"
#include "cameraMap.h"
#include "PlainLinkedList.h"
#include "EasySound.h"

//--------------------------------------------------------------------------------------

class Camera
{
public:

	Camera();
	virtual ~Camera() {es->Unload(stepSound);}

	//----------------------------------------------------------------------------------
	
	//----------------------------------------------------------------------------------
	//  Set Methods
	//----------------------------------------------------------------------------------
	// sets initial value for bounding boxes (in the array AABB)
	/**
		* @brief Sets Max X of AABB
		* @param tempIndex - index of AABB
		* @param tempX - max x of AABB
		* @return void
	*/
	void SetAABBMaxX(const int & tempIndex, const GLdouble &tempX) {m_colDetect.SetAABBMaxX(tempIndex, tempX);}
	/**
		* @brief Sets Min X of AABB
		* @param tempIndex - index of AABB
		* @param tempX - max x of AABB
		* @return void
	*/
	void SetAABBMinX(const int & tempIndex, const GLdouble &tempX) {m_colDetect.SetAABBMinX(tempIndex, tempX);}
	/**
		* @brief Sets Max Y of AABB
		* @param tempIndex - index of AABB
		* @param tempY - max y of AABB
		* @return void
	*/
	void SetAABBMaxY(const int & tempIndex, const GLdouble &tempY) {m_colDetect.SetAABBMaxY(tempIndex, tempY);}
	/**
		* @brief Sets Min Y of AABB
		* @param tempIndex - index of AABB
		* @param tempY - min y of AABB
		* @return void
	*/
	void SetAABBMinY(const int & tempIndex, const GLdouble &tempY) {m_colDetect.SetAABBMinY(tempIndex, tempY);}
	/**
		* @brief Sets Max Z of AABB
		* @param tempIndex - index of AABB
		* @param tempY - max z of AABB
		* @return void
	*/
	void SetAABBMaxZ(const int & tempIndex, const GLdouble &tempZ) {m_colDetect.SetAABBMaxZ(tempIndex, tempZ);}
	/**
		* @brief Sets Min Z of AABB
		* @param tempIndex - index of AABB
		* @param tempY - min z of AABB
		* @return void
	*/
	void SetAABBMinZ(const int & tempIndex, const GLdouble &tempZ) {m_colDetect.SetAABBMinZ(tempIndex, tempZ);}
	/**
		* @brief Sets the rotate speed of X
		* @param tempSpeed - speed to set X
		* @return void
	*/
	void SetXRotateSpeed (const GLdouble &tempSpeed) {m_xrotateSpeed = tempSpeed;}
	/**
		* @brief Sets the rotate speed of Y
		* @param tempSpeed - speed to set Y 
		* @return void
	*/
	void SetYRotateSpeed(const GLdouble& tempSpeed) {m_yrotateSpeed = tempSpeed;}
	/**
		* @brief Sets the move speed
		* @param tempSpeed - speed to set movement too
		* @return void
	*/
	void SetMoveSpeed (const GLdouble &tempSpeed) {m_moveSpeed = tempSpeed;}

	// COLLSION DETECTION FUNCTIONS
	// set collision detection (TRUE = on)
	/**
		* @brief Sets collsion detection
		* @param tempCol - boolean value of colision detection
		* @return void
	*/
	void SetCollisionDetectionOn (const bool &tempCol) {m_CollisionDetectionOn = tempCol;}
	/**
		* @brief Sets number of bounding boxes
		* @param tempSize - number of bounding boxes
		* @return void
	*/
	void SetNoBoundingBoxes(const int & tempSize) {m_colDetect.SetNoBoundingBoxes(tempSize);}
	/**
		* @brief Sets the co-ordinates of the world
		* @param tempX - x world coordinate
		* @param tempZ - z world coordinate
		* @return void
	*/
	void SetWorldCoordinates (const GLdouble &tempX, const GLdouble &tempZ);
	/**
		* @brief Creates a linked list for each quadrant of the world and places the bounding box data in each.
		* @return void
	*/
	void InitiateBoundingBoxes() {m_colDetect.CreateLinkedList();}
	/**
		* @brief Sets the co-ordinate of each plain
		* @param tempType - plain type
		* @param tempXs - X coodinate start
		* @param tempXe - X coodinate end
		* @param tempYs - Y coodinate start
		* @param tempYe - Y coodinate end
		* @param tempZs - Z coodinate start
		* @param tempZe - Z coodinate end
		* @return void
	*/
	void SetPlains (const int tempType,
				    const GLdouble tempXs, const GLdouble tempXe,
				    const GLdouble tempYs, const GLdouble tempYe,
				    const GLdouble tempZs, const GLdouble tempZe);

	//----------------------------------------------------------------------------------
	//  Get Methods-
	//----------------------------------------------------------------------------------
	GLdouble GetLR () {return m_x;}
	GLdouble GetUD () {return m_y;}
	GLdouble GetFB () {return m_z;}	
	GLdouble GetAABBMaxX (const int & tempIndex) {return m_colDetect.GetAABBMaxX (tempIndex);}
	GLdouble GetAABBMinX (const int & tempIndex) {return m_colDetect.GetAABBMinX (tempIndex);}
	GLdouble GetAABBMaxY (const int & tempIndex) {return m_colDetect.GetAABBMaxY (tempIndex);}
	GLdouble GetAABBMinY (const int & tempIndex) {return m_colDetect.GetAABBMinY (tempIndex);}
	GLdouble GetAABBMaxZ (const int & tempIndex) {return m_colDetect.GetAABBMaxZ (tempIndex);}
	GLdouble GetAABBMinZ (const int & tempIndex) {return m_colDetect.GetAABBMinZ (tempIndex);}
	
	// position the camera
	void Position (GLdouble const & tempX,
				   GLdouble const & tempY,
				   GLdouble const & tempZ,
				   GLdouble const & tempAngle);
	
	// print postion to camera
	void printPosition(void);

	// check whether ok to move
	void CheckCamera();

	// Used to pass direction to move or rotate  (i.e. 1, -1 or 0)
	void DirectionFB(int const & tempMove);
	void DirectionLR(int const & tempMove);
	void DirectionUD(int const & tempMove);

	// Rotates the camera
	void RotateCamera(int x, int y, int width, int height);

	// display map
	void DisplayMap(const int & screenWidth, const int & screenHeight, 
		            const GLuint & tempImage);
	// display welcome screen
	void DisplayWelcomeScreen (const int & screenWidth, const int & screenHeight,
							   const int & tempExit, const GLuint & tempImage);
	// display no exit
	void DisplayNoExit (const int & screenWidth, const int & screenHeight, 
						const GLuint & tempImage);
	Camera& operator = (const Camera& other);
private:

	//steep incline increments
	GLdouble m_incrementX;
	GLdouble m_incrementZ;
	int m_No_Plains;
	int m_plainNo;
	GLdouble m_plainHeight;

	// rotation variables
	GLdouble m_rotateAngleLR;
	GLdouble m_deltaAngleLR;
	GLdouble m_rotateAngleUD;	
	GLdouble m_deltaAngleUD;

	// movement variables
	GLdouble m_x, m_y, m_z, m_zLast, m_xLast;
	GLdouble m_lookX, m_lookY,m_lookZ;
	GLdouble m_lookXX, m_lookYY, m_lookZZ;
	GLdouble m_deltaMoveLR;
	GLdouble m_deltaMoveFB;
	GLdouble m_deltaMoveUD;
	GLdouble m_direction;

	// movement speed (step size)
	GLdouble m_xrotateSpeed;
	GLdouble m_yrotateSpeed;
	GLdouble m_moveSpeed;
	
	// is it ok to move
	bool MoveFBOK();
	bool MoveLROK();
	bool MoveUDOK();

	// move around the world
	void MoveFB();
	void MoveLR();
	void MoveUD();

	// overloaded function for setting plain
	void SetPlains(const int & moveX, const int & moveZ);

	// resets camera
	void ResetXYZ();
	// display new view
	void callGLLookAt();

	bool m_CollisionDetectionOn;

	// objects
	Collision m_colDetect;
	CameraMap m_map;
	PlainLinkedList m_Plain;

	// These functions were set up to climb stairs, but are not used.
	// The Plain object is used instead
	void ClimbSteps(GLdouble stepStart, GLdouble stepFinish, GLdouble stepHeight, GLdouble stepWidth, int noSteps);
	void CheckSteps();

	CEasySound *es;
	CSound* stepSound;

	//----------------------------------------------------------------------------------

    // Privatised copy constructor and assignment operator
    Camera (const Camera &cam) {};
    //Camera &operator = (const Camera &cam) {};
};

#endif