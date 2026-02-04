#pragma once

#include <iostream>
#include <deque>

struct VectorND
{
    std::deque<double> vec_;

    // Declare (default-)constructor
    VectorND();
    VectorND(std::initializer_list<double> values);

    // calculate the norm of this vector
    double norm() const;
};

// addition operator for 2 vectors
VectorND operator+(const VectorND& lhs, const VectorND& rhs);

// stream operator for a vector
std::ostream& operator<<(std::ostream& os, const VectorND& vec);

void reverse(VectorND& vec);
