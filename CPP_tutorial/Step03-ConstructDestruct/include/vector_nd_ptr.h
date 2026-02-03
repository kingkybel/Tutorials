#pragma once

#include <deque>
#include <iostream>
#include <string>

// #define TASK3

struct VectorNDPtr
{
    double*       pVec_{};    // nullptr
    size_t        sz_ = 0UL;  // number of dimensions
    std::string   name_{};
    static size_t count_;  // number of existing vectors

    // Declare (default-)constructor
    VectorNDPtr();

    // declare normal constructor
    VectorNDPtr(const std::string& name, std::initializer_list<double> values);

    // declare destructor
    ~VectorNDPtr();

#ifdef TASK3
    // copy-constructor
    VectorNDPtr(const VectorNDPtr& rhs);

    // copy-assignment
    VectorNDPtr& operator=(const VectorNDPtr& rhs);
#endif  // TASK3

    // calculate the norm of this vector
    double norm() const;
};

// addition operator for 2 vectors
VectorNDPtr operator+(const VectorNDPtr& lhs, const VectorNDPtr& rhs);

// stream operator for a vector
std::ostream& operator<<(std::ostream& os, const VectorNDPtr& vec);

void reverse(VectorNDPtr& vec);
