#pragma once

#define _USE_MATH_DEFINES

#include <math.h>
#include <stdlib.h>
#include <time.h>


	/**
	* @class Point3D
	* @brief Class that defines a 3D point and some common math functions
	* @author Group Team No Name 2
	* @version 1.0
	* @date 26 Oct 20
	*/
class Point3D
{
public:

		/**
		* @brief default constructor
		*/
	Point3D();

		/**
		* @brief constructs a Point3D given an x, y, z value
		* @param a (temp x)
		* @param b (temp y)
		* @param z (temp z)
		*/
	Point3D(double a, double b, double c);		//overloaded constructor

		/**
		* @brief returns the normalised vector
		* @return the normalised point
		*/
	Point3D normalise();

		/**
		* @brief returns the distance to respective point
		* @param other the other point
		* @return the distance to other point
		*/
	double distance(Point3D other);

		/**
		* @brief returns the angle of a vector
		* @return the angle of vector
		*/
	double angle();

		/**
		* @brief finds the dot product of 2 points
		* @param other the other point
		* @return the dot product
		*/
	double dot(Point3D other);

		/**
		* @brief finds the length of a vector
		* @return the length of vector
		*/
	double length();

		/**
		* @brief overloaded - operator
		* @param other the other point
		* @return result
		*/
	Point3D operator-(const Point3D& other);

		/**
		* @brief overloaded * operator
		* @param multiplyer 
		* @return result
		*/
	Point3D operator*(const double multiplyer);

		/**
		* @brief overloaded + operator
		* @param other the other point
		* @return result
		*/
	Point3D operator+(const Point3D& other);

		/**
		* @brief overloaded + operator
		* @param other a double to add to the point
		* @return result
		*/
	Point3D operator+(double other);

		/**
		* @brief overloaded == operator
		* @param other the other point
		* @return true if equal, otherwise false
		*/
	bool operator==(const Point3D& other);

		/**
		* @brief returns a random point within bounds
		* @param xmin minimum x value
		* @param xmax maximum x value
		* @param zmin minimum x value
		* @param zmax maximum x value
		* @param y set y value
		* @return random point
		*/
	static Point3D randomPointXZ(int xmin, int xmax, int zmin, int zmax, int y);

		/**
		* @brief returns a random int within range
		* @param range for random numnber (0 - range)
		*/
	static int randomInt(int range);

	double x, y, z;
};
