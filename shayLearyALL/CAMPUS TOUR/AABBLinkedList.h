//  AABBLinkedList.h
//  Header file for the AABBLinkedList class
//  Linked List used to store nodes (AABBNode) which contain the co-ordinates of the 
//  boundings boxes which are used for the collsion detection.
//
//	The program splits the world into four quadrants and creates a linked list to
//  store the bounding box details for each
//
//  Author:  Shay Leary
//  March 2005
//--------------------------------------------------------------------------------------

#ifndef AABBLINKED_LIST_H
#define AABBLINKED_LIST_H

//--------------------------------------------------------------------------------------

#include "AABBNode.h"
#include <gl/glut.h>

//--------------------------------------------------------------------------------------

class AABBLinkedList
{
public:
	// constructor creates pointer to first node
	AABBLinkedList() {m_first = new AABBNode;}

	virtual ~AABBLinkedList() {Clear();}

	//----------------------------------------------------------------------------------
	/**
		* @brief Clears linked list and frees memory
		* @return void
	*/
	void Clear();

	
	/**
		* @brief Adds a node to the start of the linked list
		* @param maxX - maximum x
		* @param minX - minimum x
		* @param maxY - maximum y
		* @param minY - minimum y
		* @param maxZ - maximum z
		* @param minZ - minimum z
		* @return bool
	*/
	bool AddToStart (GLdouble maxX, GLdouble minX, GLdouble maxY,
				     GLdouble minY, GLdouble maxZ, GLdouble minZ);
	/**
		* @brief Set the values of the node data
		* @param ptrCount - Pointer of AABB
		* @param maxX - maximum x
		* @param minX - minimum x
		* @param maxY - maximum y
		* @param minY - minimum y
		* @param maxZ - maximum z
		* @param minZ - minimum z
		* @return void
	*/
	void SetData(const int &ptrCount,
				 const GLdouble maxX, const GLdouble minX,
				 const GLdouble maxY, const GLdouble minY,
				 const GLdouble maxZ, const GLdouble minZ);

	//----------------------------------------------------------------------------------
	//  Get Methods
	//----------------------------------------------------------------------------------
	/**
		* @brief Gets Max X of AABB
		* @param ptrCount - Pointer of AABB
		* @return GLdouble
	*/
	GLdouble GetMaxX (int ptrCount);
	/**
		* @brief Gets Min X of AABB
		* @param ptrCount - Pointer of AABB
		* @return GLdouble
	*/
	GLdouble GetMinX (int ptrCount);
	/**
		* @brief Gets Max Y of AABB
		* @param ptrCount - Pointer of AABB
		* @return GLdouble
	*/
	GLdouble GetMaxY (int ptrCount);
	/**
		* @brief Gets Min Y of AABB
		* @param ptrCount - Pointer of AABB
		* @return GLdouble
	*/
	GLdouble GetMinY (int ptrCount);
	/**
		* @brief Gets Max Z of AABB
		* @param ptrCount - Pointer of AABB
		* @return GLdouble
	*/
	GLdouble GetMaxZ (int ptrCount);
	/**
		* @brief Gets Min Z of AABB
		* @param ptrCount - Pointer of AABB
		* @return GLdouble
	*/
	GLdouble GetMinZ (int ptrCount);
	/**
		* @brief Returns size of AABB list
		* @return int
	*/
	int GetListSize ();
	/**
		* @brief Return the address of the link to the next node in the list
		* @return AABBNode
	*/
    AABBNode *GetNext () const {return m_first->GetNext();}
	/**
		* @brief // Return the address of the link to the first node in the list
		* @return AABBNode
	*/
	AABBNode *GetFirst() const {return m_first;}

//--------------------------------------------------------------------------------------

private:
	/// pointer to first node in list
	AABBNode *m_first;
	/**
		* @brief Used to Clear Memory
		* @param before - node before one to be deleted
		* @return void
	*/
	void Delete (AABBNode *before);

	// Privatised copy constructor and assignment operator
	AABBLinkedList (const AABBLinkedList &ll) {};
	AABBLinkedList &operator = (const AABBLinkedList &ll) {};
};

#endif

//--------------------------------------------------------------------------------------