//  AABH.h
//  Header file for the AABB class
//  Dynamic Array used to store the co-ordinates of the bounding boxes used for collsion 
//  detection.  The array is only used initially before being copied into AABB Linked Lists.
//  The array is then terminated.
//  
//  I created this class originally before using linked lists to store the BB info. But decided
//  to keep it has the stored data can be easily copied across into different linked lists
//  in any prefered order. (i.e. the data is copied into across into linked lists for different
//  quadrants)
//
//  Shay Leary, March 2005
//--------------------------------------------------------------------------------------

#ifndef AABB_H
#define AABB_H

//--------------------------------------------------------------------------------------

#include <iostream>
#include <math.h>
#include <gl/glut.h>

//--------------------------------------------------------------------------------------
/**
    * @class AABB
    * @brief Class that defines the paramaters of the Bounding Boxes
    * @author Group Team No Name 2
    * @version
    * @date 14 Sep 20
 */
class AABB
{
private:
	/// stores x,y,z co-ordinates
	struct XYZ 
	{ 
		GLdouble x, y, z; 
	}; 
	/// stores max and min values of co-ordinates
	struct BoundingBox 
	{ 
		XYZ max; 
		XYZ min; 
	}; 
	/// dynamic array to store info
	BoundingBox *m_BBox;
	// number of BB created (i.e. array size)
	int m_NoOfBoxes;
    /**
        * @brief Deletes arrays and clears memory
        * @param tempArray - bounding box to clear
        * @return void
    */
	void ClearBB (BoundingBox* &tempArray);

	//----------------------------------------------------------------------------------

    // Privatised copy constructor and assignment operator
    AABB (const AABB &aabb) {};
    AABB &operator = (const AABB &aabb) {};

public:
	AABB () {}
    virtual ~AABB () {ClearBB(m_BBox);}
	
	//----------------------------------------------------------------------------------
	//  Set Methods
	//----------------------------------------------------------------------------------
    /**
        * @brief Sets max x of bounding box
        * @param tempIndex - index of bounding box
        * @param tempX - Max x of bounding box
        * @return void
    */
	void SetMaxX(const int & tempIndex, const GLdouble &tempX) {m_BBox[tempIndex].max.x = tempX;}
    /**
        * @brief Sets min x of bounding box
        * @param tempIndex - index of bounding box
        * @param tempX - Min x of bounding box
        * @return void
    */
	void SetMinX(const int & tempIndex, const GLdouble &tempX) {m_BBox[tempIndex].min.x = tempX;}
    /**
        * @brief Sets max y of bounding box
        * @param tempIndex - index of bounding box
        * @param tempY - Max y of bounding box
        * @return void
    */
	void SetMaxY(const int & tempIndex, const GLdouble &tempY) {m_BBox[tempIndex].max.y = tempY;}
    /**
        * @brief Sets min y of bounding box
        * @param tempIndex - index of bounding box
        * @param tempY - Min y of bounding box
        * @return void
    */
	void SetMinY(const int & tempIndex, const GLdouble &tempY) {m_BBox[tempIndex].min.y = tempY;}
    /**
        * @brief Sets max z of bounding box
        * @param tempIndex - index of bounding box
        * @param tempY - Max z of bounding box
        * @return void
    */
	void SetMaxZ(const int & tempIndex, const GLdouble &tempZ) {m_BBox[tempIndex].max.z = tempZ;}
    /**
        * @brief Sets min z of bounding box
        * @param tempIndex - index of bounding box
        * @param tempY - Min z of bounding box
        * @return void
    */
	void SetMinZ(const int & tempIndex, const GLdouble &tempZ) {m_BBox[tempIndex].min.z = tempZ;}
	/**
        * @brief Sets size of bounding box
        * @param tempSize - size of bounding box
        * @return void
    */
    void SetNoBoundingBoxes(const int & tempSize);

	//----------------------------------------------------------------------------------
	//  Get Methods
	//----------------------------------------------------------------------------------
	/**
        * @brief Gets max x of bounding box
        * @param tempIndex - index of Bounding Box
        * @return GLdouble
    */
    GLdouble GetMaxX (const int & tempIndex) {return m_BBox[tempIndex].max.x;}
    /**
        * @brief Gets min x of bounding box
        * @param tempIndex - index of Bounding Box
        * @return GLdouble
    */
	GLdouble GetMinX (const int & tempIndex) {return m_BBox[tempIndex].min.x;}
    /**
        * @brief Gets max y of bounding box
        * @param tempIndex - index of Bounding Box
        * @return GLdouble
    */
	GLdouble GetMaxY (const int & tempIndex) {return m_BBox[tempIndex].max.y;}
    /**
        * @brief Gets min y of bounding box
        * @param tempIndex - index of Bounding Box
        * @return GLdouble
    */
	GLdouble GetMinY (const int & tempIndex) {return m_BBox[tempIndex].min.y;}
    /**
        * @brief Gets max z of bounding box
        * @param tempIndex - index of Bounding Box
        * @return GLdouble
    */
	GLdouble GetMaxZ (const int & tempIndex) {return m_BBox[tempIndex].max.z;}
    /**
        * @brief Gets min z of bounding box
        * @param tempIndex - index of Bounding Box
        * @return GLdouble
    */
	GLdouble GetMinZ (const int & tempIndex) {return m_BBox[tempIndex].min.z;}
	/**
        * @brief Gets number of bounding boxes
        * @return int
    */
    int GetNoBoundingBoxes () {return m_NoOfBoxes;}
};

#endif
//--------------------------------------------------------------------------------------