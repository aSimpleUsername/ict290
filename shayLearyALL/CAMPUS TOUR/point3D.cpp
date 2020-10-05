#include "point3D.h"

Point3D::Point3D() : x(0), y(0), z(0) {}
Point3D::Point3D(double a, double b, double c) : x(a), y(b), z(c) {}

bool seed_generated = false;

// normalise vector
Point3D Point3D::normalise()
{
    Point3D temp;

    double magnitude = sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
    temp.x = this->x / magnitude;
    temp.y = this->y / magnitude;
    temp.z = this->z / magnitude;

    return(temp);
}

// find distance between two points
double Point3D::distance(Point3D other)
{
    return(sqrt(pow(other.x - this->x, 2) + pow(other.y - this->y, 2) + pow(other.z - this->z, 2)));
}


double Point3D::angle()
{
    if (z < 0 || (x < 0 && z < 0))     // adding 180 or 360 deg keeps the result between 0 and 360 deg 
        return(atan(this->x / this->z) + 180 * (M_PI / 180));
    else if (x < 0)
        return(atan(this->x / this->z) + 360 * (M_PI / 180));
    else
        return(atan(this->x / this->z));
}


double Point3D::dot(Point3D other)
{
    return((this->x * other.x) + (this->y * other.y) + (this->z * other.z));
}


double Point3D::length(void)
{
    return(sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2)));
}

Point3D Point3D::operator-(const Point3D& other)
{
    Point3D result;
    result.x = this->x - other.x;
    result.y = this->y - other.y;
    result.z = this->z - other.z;

    return(result);
}

Point3D Point3D::operator*(const double multiplyer)
{
    Point3D result;
    result.x = this->x * multiplyer;
    result.y = this->y * multiplyer;
    result.z = this->z * multiplyer;
    return(result);
}

Point3D Point3D::operator+(const Point3D& other)
{
    Point3D result;
    result.x = this->x + other.x;
    result.y = this->y + other.y;
    result.z = this->z + other.z;

    return(result);
}

Point3D Point3D::operator+(double other)
{
    Point3D result;
    result.x = this->x + other;
    result.y = this->y + other;
    result.z = this->z + other;

    return(result);
}

bool Point3D::operator==(const Point3D& other)
{
    return(this->x == other.x && this->y == other.y && this->z == other.z);
}

Point3D Point3D::randomPointXZ(int xmin, int xmax, int zmin, int zmax, int y)
{
    if (!seed_generated)    // only generate seed once
    {
        srand(time(0));
        seed_generated = true; 
    }

    Point3D result;

    result.x = rand() % (xmax + 1 - xmin) + xmin;
    result.y = y;
    result.z = rand() % (zmax + 1 - zmin) + zmin;

    return result;
}