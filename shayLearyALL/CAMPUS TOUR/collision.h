//  collsion.h
//  Header file for the collision class
// 
//
//  Shay Leary, March 2005
//--------------------------------------------------------------------------------------
#ifndef COLLISION_H
#define COLLISION_H

//--------------------------------------------------------------------------------------

#include "AABB.h"
#include "AABBLinkedList.h"

//--------------------------------------------------------------------------------------

class Collision
{
public:

	Collision() {}
	virtual ~Collision() {}

	//----------------------------------------------------------------------------------
	//  Set Methods
	//----------------------------------------------------------------------------------
	/**
		* @brief Sets AABB MaxX
		* @param tempIndex - index of the AABB
		* @param tempX - max x of AABB
		* @return void
	*/
	void SetAABBMaxX(const int & tempIndex, const double &tempX) {m_AABB.SetMaxX(tempIndex, tempX);}
	/**
		* @brief Sets AABB MinX
		* @param tempIndex - index of the AABB
		* @param tempX - min x of AABB
		* @return void
	*/
	void SetAABBMinX(const int & tempIndex, const double &tempX) {m_AABB.SetMinX(tempIndex, tempX);}
	/**
		* @brief Sets AABB MaxY
		* @param tempIndex - index of the AABB
		* @param tempY- max y of AABB
		* @return void
	*/
	void SetAABBMaxY(const int & tempIndex, const double &tempY) {m_AABB.SetMaxY(tempIndex, tempY);}
	/**
		* @brief Sets AABB MinY
		* @param tempIndex - index of the AABB
		* @param tempY- min y of AABB
		* @return void
	*/
	void SetAABBMinY(const int & tempIndex, const double &tempY) {m_AABB.SetMinY(tempIndex, tempY);}
	/**
		* @brief Sets AABB MaxZ
		* @param tempIndex - index of the AABB
		* @param tempZ- max z of AABB
		* @return void
	*/
	void SetAABBMaxZ(const int & tempIndex, const double &tempZ) {m_AABB.SetMaxZ(tempIndex, tempZ);}
	/**
		* @brief Sets AABB MinZ
		* @param tempIndex - index of the AABB
		* @param tempZ- min z of AABB
		* @return void
	*/
	void SetAABBMinZ(const int & tempIndex, const double &tempZ) {m_AABB.SetMinZ(tempIndex, tempZ);}
	/**
		* @brief Sets world X of object
		* @param tempX - world x of AABB
		* @return void
	*/
	void SetWorldX(const double &tempX) {m_worldSizeX = tempX;}
	/**
		* @brief Sets world Z of object
		* @param tempZ - world z of AABB
		* @return void
	*/
	void SetWorldZ(const double &tempZ) {m_worldSizeZ = tempZ;}
	/**
		* @brief Sets number of bounding boxes
		* @param tempSize - number of AABB
		* @return void
	*/
	void SetNoBoundingBoxes(const int & tempSize) {m_AABB.SetNoBoundingBoxes(tempSize);}

	//----------------------------------------------------------------------------------
	//  Returns Methods
	//----------------------------------------------------------------------------------
	/**
		* @brief Returns Max x of bounding box
		* @param tempIndex - index of AABB
		* @return double
	*/
	double GetAABBMaxX (const int & tempIndex) {return m_AABB.GetMaxX (tempIndex);}
	/**
		* @brief Returns Min x of bounding box
		* @param tempIndex - index of AABB
		* @return double
	*/
	double GetAABBMinX (const int & tempIndex) {return m_AABB.GetMinX (tempIndex);}
	/**
		* @brief Returns Max y of bounding box
		* @param tempIndex - index of AABB
		* @return double
	*/
	double GetAABBMaxY (const int & tempIndex) {return m_AABB.GetMaxY (tempIndex);}
	/**
		* @brief Returns Min y of bounding box
		* @param tempIndex - index of AABB
		* @return double
	*/
	double GetAABBMinY (const int & tempIndex) {return m_AABB.GetMinY (tempIndex);}
	/**
		* @brief Returns Max z of bounding box
		* @param tempIndex - index of AABB
		* @return double
	*/
	double GetAABBMaxZ (const int & tempIndex) {return m_AABB.GetMaxZ (tempIndex);}
	/**
		* @brief Returns Min z of bounding box
		* @param tempIndex - index of AABB
		* @return double
	*/
	double GetAABBMinZ (const int & tempIndex) {return m_AABB.GetMinZ (tempIndex);}
	/**
		* @brief Returns number of bounding boxes
		* @return int
	*/
	int GetNoBoundingBoxes() {return m_AABB.GetNoBoundingBoxes();}
	/**
		* @brief Checks for collision returns true if occoured
		* @param endX - x to check collision
		* @param endY - y to check collision
		* @param endZ - z to check collision
		* @return bool
		*/
	bool Collide (double endX, double endY, double endZ);
	/**
		* @brief  reads the BB info from AABB (dynamic array) and creates a Linked List with AABB data
		* @return void
	*/
	void CreateLinkedList();

private:
	// initially stores BB info in AABB (dynamic array) before copying to Linked List
	AABB m_AABB;

	// lists to store bounding box info in each quadrant
	AABBLinkedList m_list[4];

	// Stores the list size of each linked list
	// Set to 4 has the world is split into 4 quadrants
	int m_listSize[4];

	// stores world co-ordinates
	double m_worldSizeX;
	double m_worldSizeZ;

	// 
	/**
		* @brief  checks if collsion occurred (called from Collide)
		* @param index - index of AABB to check
		* @param endX - x to check collision
		* @param endY - y to check collision
		* @param endZ - z to check collision
		* @return bool
	*/
	bool CheckCollision(int index, double endX, double endY, double endZ);

	//----------------------------------------------------------------------------------

    // Privatised copy constructor and assignment operator
    Collision (const Collision &coll) {};
    Collision &operator = (const Collision &coll) {};
};

#endif
//--------------------------------------------------------------------------------------