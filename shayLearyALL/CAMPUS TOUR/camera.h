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
/**
	* @class Camera
	* @brief Class that controls the Camera
	* @author Group Team No Name 2
	* @version
	* @date
*/
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
	/**
		* @brief Gets Camera look X
		* @return GLdouble
	*/
	GLdouble GetLX() { return m_lookX; }
	/**
		* @brief Gets Camera look Y
		* @return GLdouble
	*/
	GLdouble GetLY() { return m_lookY; }
	/**
		* @brief Gets Camera look Z
		* @return GLdouble
	*/
	GLdouble GetLZ() { return m_lookZ; }
	/**
		* @brief Gets Camera X
		* @return GLdouble
	*/
	GLdouble getX () {return m_x;}
	/**
		* @brief Gets Camera Y
		* @return GLdouble
	*/
	GLdouble getY () {return m_y;}
	/**
		* @brief Gets Camera Z
		* @return GLdouble
	*/
	GLdouble getZ () {return m_z;}	
	/**
		* @brief Gets AABB Max X
		* @param tempIndex - index of AABB
		* @return GLdouble
	*/
	GLdouble GetAABBMaxX (const int & tempIndex) {return m_colDetect.GetAABBMaxX (tempIndex);}
	/**
		* @brief Gets AABB Min X
		* @param tempIndex - index of AABB
		* @return GLdouble
	*/
	GLdouble GetAABBMinX (const int & tempIndex) {return m_colDetect.GetAABBMinX (tempIndex);}
	/**
		* @brief Gets AABB Max Y
		* @param tempIndex - index of AABB
		* @return GLdouble
	*/
	GLdouble GetAABBMaxY (const int & tempIndex) {return m_colDetect.GetAABBMaxY (tempIndex);}
	/**
		* @brief Gets AABB Min Y
		* @param tempIndex - index of AABB
		* @return GLdouble
	*/
	GLdouble GetAABBMinY (const int & tempIndex) {return m_colDetect.GetAABBMinY (tempIndex);}
	/**
		* @brief Gets AABB Max Z
		* @param tempIndex - index of AABB
		* @return GLdouble
	*/
	GLdouble GetAABBMaxZ (const int & tempIndex) {return m_colDetect.GetAABBMaxZ (tempIndex);}
	/**
		* @brief Gets AABB Min Z
		* @param tempIndex - index of AABB
		* @return GLdouble
	*/
	GLdouble GetAABBMinZ (const int & tempIndex) {return m_colDetect.GetAABBMinZ (tempIndex);}
	/**
		* @brief position the camera
		* @param tempX - X of the camera
		* @param tempY - Y of the camera
		* @param tempZ - Z of the camera
		* @param tempAngle - angle of the camera
		* @return void
	*/
	void Position (GLdouble const & tempX,
				   GLdouble const & tempY,
				   GLdouble const & tempZ,
				   GLdouble const & tempAngle);
	/**
		* @brief prints position to camera
		* @return void
	*/
	void printPosition(void);
	/**
		* @brief checks if ok to move
		* @return void
	*/
	void CheckCamera();
	/**
		* @brief Used to pass direction to move or rotate in z direction
		* @param tempMove - Z value to move
		* @return void
	*/
	void DirectionFB(int const & tempMove);
	/**
		* @brief Used to pass direction to move or rotate in x direction
		* @param tempMove - X value to move
		* @return void
	*/
	void DirectionLR(int const & tempMove);
	/**
		* @brief Used to pass direction to move or rotate in Y direction
		* @param tempMove - Y value to move
		* @return void
	*/
	void DirectionUD(int const & tempMove);

	/**
		* @brief Rotates Camera
		* @param x - X value to rotate
		* @param y - Y value to rotate
		* @param width - width of camera
		* @param height - height of camera
		* @return void
	*/
	void RotateCamera(int x, int y, int width, int height);

	/**
		* @brief Displays Map
		* @param screenWidth - width of screen
		* @param screenHeight - height of screen
		* @param tempImage - image of map
		* @return void
	*/
	void DisplayMap(const int & screenWidth, const int & screenHeight, 
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
	
	/**
		* @brief checking if ok to move on X
		* @return bool
	*/
	bool MoveFBOK();
	/**
		* @brief checking if ok to move on Y
		* @return bool
	*/
	bool MoveLROK();
	/**
		* @brief checking if ok to move on Z
		* @return bool
	*/
	bool MoveUDOK();
	/**
		* @brief apply movements on x
		* @return void
	*/
	void MoveFB();
	/**
		* @brief apply movements on y
		* @return void
	*/
	void MoveLR();
	/**
		* @brief apply movements on z
		* @return void
	*/
	void MoveUD();

	/**
		* @brief overloaded function for setting plains
		* @param moveX - x position of plane
		* @param moveZ - z position of plane
		* @return void
	*/
	void SetPlains(const int & moveX, const int & moveZ);
	/**
		* @brief resets camera
		* @return void
	*/
	void ResetXYZ();
	/**
		* @brief displays new view
		* @return void
	*/
	void callGLLookAt();

	bool m_CollisionDetectionOn;

	// objects
	Collision m_colDetect;
	CameraMap m_map;
	PlainLinkedList m_Plain;

	CEasySound *es;
	CSound* stepSound;

	//----------------------------------------------------------------------------------

    // Privatised copy constructor and assignment operator
    Camera (const Camera &cam) {};
    //Camera &operator = (const Camera &cam) {};
};

#endif