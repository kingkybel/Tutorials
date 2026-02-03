#pragma once

#include <iostream>

struct Vector3D
{
    double x_{};
    double y_{};
    double z_{};

    // Declare (default-)constructor
    Vector3D(double x = double{}, double y = double{}, double z = double{});

    // calculate the norm of this vector
    double norm() const;
};

// addition operator for 2 vectors
Vector3D operator+(const Vector3D& lhs, const Vector3D& rhs);

// stream operator for a vector
std::ostream& operator<<(std::ostream& os, const Vector3D& vec);

// reverse the vector by reference
void reverse(Vector3D& vec);

// this function will not reverse the vector
void cant_reverse(Vector3D vec);

