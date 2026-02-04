#include "vector_nd.h"

#include <cmath>
#include <exception>
#include <iostream>

VectorND::VectorND()
{
}

VectorND::VectorND(std::initializer_list<double> values) : vec_(values)
{
}

double VectorND::norm() const
{
    double reval{};
    for(auto i = 0; i < vec_.size(); ++i)
        reval += vec_[i] * vec_[i];
    return std::sqrt(reval);
}

VectorND operator+(const VectorND& lhs, const VectorND& rhs)
{
    if(lhs.vec_.size() != rhs.vec_.size())
        throw std::runtime_error("vectors are not of the same length");
    auto reval = VectorND{};
    reval.vec_.resize(lhs.vec_.size());
    for(size_t i = 0; i < lhs.vec_.size(); ++i)
        reval.vec_[i] = lhs.vec_[i] + rhs.vec_[i];

    return std::move(reval);
}

std::ostream& operator<<(std::ostream& os, const VectorND& vec)
{
    os << "<";
    if(vec.vec_.size() > 0)
    {
        for(size_t i = 0; i < vec.vec_.size() - 1; ++i)
            os << vec.vec_[i] << ",";
        os << vec.vec_[vec.vec_.size() - 1];
    }
    os << ">";
    return os;
}

void reverse(VectorND& vec)
{
    if(vec.vec_.size() > 1)
        for(size_t i = 0; i < vec.vec_.size() / 2; ++i)
            std::swap(vec.vec_[i], vec.vec_[vec.vec_.size() - i - 1]);
}