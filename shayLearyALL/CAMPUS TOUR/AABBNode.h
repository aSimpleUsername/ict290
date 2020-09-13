//  AABBNODE.h
//  Header file for the AABBNODE class
//  Stores details for each bounding box used for collsion detection.  Each node is stored
//  in each link of the AABB Linked List

//  Shay Leary, March 2005
//--------------------------------------------------------------------------------------

#ifndef AABBNODE_H
#define AABBNODE_H

#include <vector>
#include <gl/glut.h>

//--------------------------------------------------------------------------------------

class AABBNode
{
public:
	AABBNode () {Clear();}
    virtual ~AABBNode () {Clear();}

	//----------------------------------------------------------------------------------
	/**
		* @brief Clears node
		* @return void
	*/
	void  Clear();

	//----------------------------------------------------------------------------------
	//  Get Methods
	//----------------------------------------------------------------------------------
	/**
		* @brief Gets Max X of node
		* @return GLdouble
	*/
	GLdouble GetMaxX () {return m_BBox.max.x;}
	/**
		* @brief Gets Min X of node
		* @return GLdouble
	*/
	GLdouble GetMinX () {return m_BBox.min.x;}
	/**
		* @brief Gets Max Y of node
		* @return GLdouble
	*/
	GLdouble GetMaxY () {return m_BBox.max.y;}
	/**
		* @brief Gets Min Y of node
		* @return GLdouble
	*/
	GLdouble GetMinY () {return m_BBox.min.y;}
	/**
		* @brief Gets Max Z of node
		* @return GLdouble
	*/
	GLdouble GetMaxZ () {return m_BBox.max.z;}
	/**
		* @brief Gets Min Z of node
		* @return GLdouble
	*/
	GLdouble GetMinZ () {return m_BBox.min.z;}
	/**
		* @brief Return the address of the link to the next node in the list
		* @return AABBNode
	*/
    AABBNode *GetNext () const {return m_next;}

	//----------------------------------------------------------------------------------
	//  Set Methods
	//----------------------------------------------------------------------------------
	/**
		* @brief Sets Data
		* @param maxX - maximum x
		* @param minX - minimum x
		* @param maxY - maximum y
		* @param minY - minimum y
		* @param maxZ - maximum z
		* @param minZ - minimum z
		* @return void
	*/
	void SetData(const GLdouble maxX, const GLdouble minX,
				 const GLdouble maxY, const GLdouble minY,
				 const GLdouble maxZ, const GLdouble minZ);

	/**
		* @brief  Set the address of the link to the next node in the list
		* @param next - next node
		* @return void
	*/
    void SetNext (AABBNode *next) {m_next = next;}

private:
    /// The address of the next node in the list
    AABBNode *m_next;

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
	/// stores info on Bounding Box
	BoundingBox m_BBox;

	//----------------------------------------------------------------------------------

    // Privatised copy constructor and assignment operator
    AABBNode (const AABBNode &newNode) {};
    AABBNode &operator = (const AABBNode &newNode) {};
};

#endif
//--------------------------------------------------------------------------------------