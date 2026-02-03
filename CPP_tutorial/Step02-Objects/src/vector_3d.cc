#include "vector_3d.h"

#include <iostream>
#include <cmath>

Vector3D::Vector3D(double x, double y, double z) : x_(x), y_(y), z_(z)
{
}

double Vector3D::norm() const
{
    return std::sqrt(x_*x_+y_*y_+z_*z_);
}

Vector3D operator+(const Vector3D& lhs, const Vector3D& rhs)
{
    return Vector3D{lhs.x_ + rhs.x_, lhs.y_ + rhs.y_, lhs.z_ + rhs.z_};
}

std::ostream& operator<<(std::ostream& os, const Vector3D& vec)
{
    os << "<" << vec.x_ << "," << vec.y_ << "," << vec.z_ << ">";
    return os;
}

void reverse(Vector3D& vec)
{
    std::swap(vec.x_, vec.z_);
}

void cant_reverse(Vector3D vec)
{
    std::swap(vec.x_, vec.z_);
}