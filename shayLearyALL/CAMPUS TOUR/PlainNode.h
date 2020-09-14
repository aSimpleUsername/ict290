//  PlainNode.h
//  Header file for the PlainNode class
//  Stores details for each plain.  Each node is stored in each link of the Plain Linked List

//  Shay Leary, April 2005
//--------------------------------------------------------------------------------------

#ifndef PLAINNODE_H
#define PLAINNODE_H

//--------------------------------------------------------------------------------------

#include <iostream>
#include <math.h>
#include <gl/glut.h>
/**
	* @class PlainNode
	* @brief Set of functions and parameters to hold the plain data
	* @author Group Team No Name 2
	* @version
	* @date 14 Sep 20
 */
class PlainNode
{

public:
	PlainNode () {Clear();}
    virtual ~PlainNode () {Clear();}

	//----------------------------------------------------------------------------------
	/**
		* @brief Used to Clear a node
		* @return void
	*/
	void  Clear   ();

	//----------------------------------------------------------------------------------
	//  Get Methods
	//----------------------------------------------------------------------------------
	/**
		* @brief Returns the Type
		* @return GLdouble
	*/
	GLdouble GetType () {return m_type;}
	/**
		* @brief Returns the X Start
		* @return GLdouble
	*/
	GLdouble GetXstart () {return m_xPlainStart;}
	/**
		* @brief Returns the X End
		* @return GLdouble
	*/
	GLdouble GetXend () {return m_xPlainEnd;}
	/**
		* @brief Returns the Y Start
		* @return GLdouble
	*/
	GLdouble GetYstart () {return m_yPlainStart;}
	/**
		* @brief Returns the Y End
		* @return GLdouble
	*/
	GLdouble GetYend () {return m_yPlainEnd;}
	/**
		* @brief Returns the Z Start
		* @return GLdouble
	*/
	GLdouble GetZstart () {return m_zPlainStart;}
	/**
		* @brief Returns the Z End
		* @return GLdouble
	*/
	GLdouble GetZend () {return m_zPlainEnd;}
	/**
		* @brief Return the address of the link to the next node in the list
		* @return PlainNode
	*/
    PlainNode *GetNext () const {return m_next;}

	//----------------------------------------------------------------------------------
	//  Set Methods
	//----------------------------------------------------------------------------------
	/**
		* @brief Set the values of the node data
		* @param tempType - type of data
		* @param tempXs - x start
		* @param tempXe - x end
		* @param tempYs - y start
		* @param tempYe - y end
		* @param tempZs - z start
		* @param tempZe - z end
		* @return void
	*/
	void SetData(const int tempType,
				 const GLdouble tempXs, const GLdouble tempXe,
				 const GLdouble tempYs, const GLdouble tempYe,
				 const GLdouble tempZs, const GLdouble tempZe);
	/**
		* @brief Set the address of the link to the next node in the list
		* @param next - pointer of the next node
		* @return void
	*/
    void SetNext (PlainNode *next) {m_next = next;}

private:
    // The address of the next node in the list
    PlainNode *m_next;

	// Stores type of plain:
	// (0: flat plane)
	// (1: incline from z to y)
	// (2: incline from x to y)
	GLdouble m_type;
	

	// stores start and end co-ordinates of plane on x, y and z axis
	GLdouble m_xPlainStart, m_xPlainEnd;
	GLdouble m_yPlainStart, m_yPlainEnd;
	GLdouble m_zPlainStart, m_zPlainEnd;

	//----------------------------------------------------------------------------------

    // Privatised copy constructor and assignment operator
    PlainNode (const PlainNode &newNode) {};
    PlainNode &operator = (const PlainNode &newNode) {};
};

#endif

//--------------------------------------------------------------------------------------