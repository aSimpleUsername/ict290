#pragma once

#define _USE_MATH_DEFINES

#include <math.h>
#include <stdlib.h>
#include <time.h>

class Point3D
{
public:
	double x, y, z;

	Point3D();		//default constructor
	Point3D(double a, double b, double c);		//overloaded constructor

	Point3D normalise();				// normalise a vecor
	double distance(Point3D other);		// find distance between 2 points
	double angle();						// find the angle of a vector
	double dot(Point3D other);			// find the dot product
	double length();					// find the length of a vector

	Point3D operator-(const Point3D& other);
	Point3D operator*(const double multiplyer);
	Point3D operator+(const Point3D& other);
	Point3D operator+(double other);
	bool operator==(const Point3D& other);

	static Point3D randomPointXZ(int xmin, int xmax, int zmin, int zmax, int y);
	static int randomInt(int range);
};
