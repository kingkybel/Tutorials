#include "vector_nd_ptr.h"

#include <cmath>
#include <exception>
#include <iostream>
#include <string>

size_t VectorNDPtr::count_ = 0UL;  // number of existing vectors

// #define TASK2
#define TASK3
#define TASK4

VectorNDPtr::VectorNDPtr() : pVec_(nullptr)
{
    name_ = "DefaultConstructed" + std::to_string(++count_);
#ifdef TASK2
    std::cout << __PRETTY_FUNCTION__ << ": this=" << (size_t)(this) << ", name=" << name_ << std::endl;
#endif
}

VectorNDPtr::VectorNDPtr(const std::string& name, std::initializer_list<double> values) : name_(name)
{
    sz_      = values.size();    // number of elements given to the constructor
    pVec_    = new double[sz_];  // allocate enough space for all the given elements
    size_t i = 0UL;
    // copy the values into the allocated memory
    for(auto it = values.begin(); it != values.end(); ++it, ++i)
        pVec_[i] = *it;
#ifdef TASK2
    std::cout << __PRETTY_FUNCTION__ << ": this=" << (size_t)(this) << ", name=" << name_ << std::endl;
#endif
}

VectorNDPtr::~VectorNDPtr()
{
#ifdef TASK2
    std::cout << __PRETTY_FUNCTION__ << ": this=" << (size_t)(this) << ", name=" << name_ << std::endl;
    std::cout << __PRETTY_FUNCTION__ << ": trying to delete pVec_=" << (size_t)(pVec_) << std::endl << std::endl;
#endif
    delete[] pVec_;
    sz_ = 0UL;
}

#ifdef TASK3
// copy-constructor
VectorNDPtr::VectorNDPtr(const VectorNDPtr& rhs)
{
    #ifdef TASK2
    std::cout << __PRETTY_FUNCTION__ << ": this=" << (size_t)(this) << ", name=" << name_ << std::endl;
    #endif

    #ifdef TASK4
    // Task 4: implement the copy-constructor correctly
    sz_   = rhs.sz_;
    pVec_ = new double[sz_];
    for(size_t i = 0; i < sz_; ++i)
        pVec_[i] = rhs.pVec_[i];
    name_ = rhs.name_ + "_copy";
    #endif
}

// copy-assignment
VectorNDPtr& VectorNDPtr::operator=(const VectorNDPtr& rhs)
{
    #ifdef TASK2
    std::cout << __PRETTY_FUNCTION__ << ": this=" << (size_t)(this) << ", name=" << name_ << std::endl;
    #endif

    #ifdef TASK4
    // Task 4: implement the copy-assignment correctly
    if(this != &rhs)
    {
        delete[] pVec_;
        sz_   = rhs.sz_;
        pVec_ = new double[sz_];
        for(size_t i = 0; i < sz_; ++i)
            pVec_[i] = rhs.pVec_[i];
        name_ = rhs.name_ + "_assigned";
    }
    #endif
    return *this;
}
#endif  // TASK3

double VectorNDPtr::norm() const
{
    double reval{};
    if(nullptr == pVec_)
        return reval;
    for(auto i = 0; i < sz_; ++i)
        reval += pVec_[i] * pVec_[i];
    return std::sqrt(reval);
}

VectorNDPtr operator+(const VectorNDPtr& lhs, const VectorNDPtr& rhs)
{
    if(lhs.sz_ != rhs.sz_)
        throw std::runtime_error("vectors are not of the same length");
    auto reval  = VectorNDPtr{};
    reval.pVec_ = new double[lhs.sz_];
    reval.name_ = lhs.name_ + "_plus_" + rhs.name_;

    // set the size of the new vector
    reval.sz_ = lhs.sz_;

    // componentwise add
    for(size_t i = 0; i < lhs.sz_; ++i)
        reval.pVec_[i] = lhs.pVec_[i] + rhs.pVec_[i];
    reval.sz_ = lhs.sz_;

#ifdef TASK2
    std::cout << __PRETTY_FUNCTION__ << ": reval=" << (size_t)(&reval) << ", name=" << reval.name_ << std::endl;
#endif

    return reval;
}

std::ostream& operator<<(std::ostream& os, const VectorNDPtr& vec)
{
    os << "<";
    if(vec.sz_ > 0)
    {
        for(size_t i = 0; i < vec.sz_ - 1; ++i)
            os << vec.pVec_[i] << ",";
        os << vec.pVec_[vec.sz_ - 1];
    }
    os << ">";
    return os;
}

void reverse(VectorNDPtr& vec)
{
    if(vec.sz_ > 1)
        for(size_t i = 0; i < vec.sz_ / 2; ++i)
            std::swap(vec.pVec_[i], vec.pVec_[vec.sz_ - i - 1]);
}