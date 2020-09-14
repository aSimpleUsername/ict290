//  PlainLinkedList.h
//  Header file for the PlainLinkedList class
//  Linked List used to store nodes (PlainNode) which contain the co-ordinates of the 
//  of each plain used in the program.
//
//	The program will split the world into four quadrants and creates a linked list to
//  store the bounding box details for each
//
//  Author:  Shay Leary
//  April 2005
//--------------------------------------------------------------------------------------

#ifndef PLAINLINKED_LIST_H
#define PLAINLINKED_LIST_H

//--------------------------------------------------------------------------------------

#include "PlainNode.h"

//--------------------------------------------------------------------------------------
/**
	* @class PlainLinkedList
	* @brief Class that defines the links between the Plain Nodes
	* @author Group Team No Name 2
	* @version
	* @date 14 Sep 20
 */
class PlainLinkedList
{
public:
	// constructor creates pointer to first node
	PlainLinkedList() {m_first = new PlainNode;}

	virtual ~PlainLinkedList() {Clear();}

	//----------------------------------------------------------------------------------
	/**
		* @brief Clears linked list and frees memory
		* @return void
	*/
	void Clear();
	/**
		* @brief add a node to the start of the linked list
		* @param tempType - type of plain
		* @param tempXs - x start
		* @param tempXe - x end
		* @param tempYs - y start
		* @param tempYe - y end
		* @param tempZs - z start
		* @param tempZe - z end
		* @return bool
	*/
	bool AddToStart (const int tempType,
				     const GLdouble tempXs, const GLdouble tempXe,
				     const GLdouble tempYs, const GLdouble tempYe,
				     const GLdouble tempZs, const GLdouble tempZe);
	/**
		* @brief set the values of the node data
		* @param ptrCount - the pointer of the node
		* @param tempType - type of data
		* @param tempXs - x start
		* @param tempXe - x end
		* @param tempYs - y start
		* @param tempYe - y end
		* @param tempZs - z start
		* @param tempZe - z end
		* @return void
	*/
	void SetData(const int &ptrCount, const int tempType,
				 const GLdouble tempXs, const GLdouble tempXe,
				 const GLdouble tempYs, const GLdouble tempYe,
				 const GLdouble tempZs, const GLdouble tempZe);

	//----------------------------------------------------------------------------------
	//  Get Methods
	//----------------------------------------------------------------------------------
	/**
		* @brief Gets Type
		* @param ptrCount - the pointer of the node
		* @return GLdouble
	*/
	GLdouble GetType (int ptrCount);
	/**
		* @brief Gets starting x
		* @param ptrCount - the pointer of the node
		* @return GLdouble
	*/
	GLdouble GetXstart (int ptrCount);
	/**
		* @brief Gets ending x
		* @param ptrCount - the pointer of the node
		* @return GLdouble
	*/
	GLdouble GetXend (int ptrCount);
	/**
		* @brief Gets starting y
		* @param ptrCount - the pointer of the node
		* @return GLdouble
	*/
	GLdouble GetYstart (int ptrCount);
	/**
		* @brief Gets ending x
		* @param ptrCount - the pointer of the node
		* @return GLdouble
	*/
	GLdouble GetYend (int ptrCount);
	/**
		* @brief Gets starting z
		* @param ptrCount - the pointer of the node
		* @return GLdouble
	*/
	GLdouble GetZstart (int ptrCount);
	/**
		* @brief Gets ending z
		* @param ptrCount - the pointer of the node
		* @return GLdouble
	*/
	GLdouble GetZend (int ptrCount);
	/**
		* @brief Gets size of the plains list
		* @return int
	*/
	int GetListSize ();
	/**
		* @brief Return the address of the link to the next node in the list
		* @return PlainNode
	*/
    PlainNode *GetNext () const {return m_first->GetNext();}
	/**
		* @brief Return the address of the link to the first node in the list
		* @return PlainNode
	*/
	PlainNode *GetFirst() const {return m_first;}


//--------------------------------------------------------------------------------------

private:
	// pointer to first node in list
	PlainNode *m_first;
	/**
		* @brief Used to Clear Memory
		* @param before - node before one to be deleted
		* @return void
	*/
	void Delete (PlainNode *before);

	// Privatised copy constructor and assignment operator
	PlainLinkedList (const PlainLinkedList &array) {};
	PlainLinkedList &operator = (const PlainLinkedList &array) {};
};

#endif

//--------------------------------------------------------------------------------------