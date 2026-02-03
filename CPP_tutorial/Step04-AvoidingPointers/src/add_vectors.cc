#include "vector_nd.h"

#include <iostream>

int main(int argc, char** argv)
{
    std::cout << "use default-values for construction" << std::endl;
    VectorND vec0_1;
    VectorND vec0_2{1.0};
    VectorND vec0_3{1.0, 2.0};
    std::cout << "vec0_1=" << vec0_1 << " vec0_2=" << vec0_2 << " vec0_3=" << vec0_3 << std::endl << std::endl;

    std::cout << "create object on-the-fly" << std::endl;
    VectorND vec1{1.1, 2.2, 3.3, 4.4, 5.5, 6.6};
    VectorND vec2{5.1, 5.2, 5.3, 5.4, 5.5, 5.6};
    std::cout << vec1 << " + " << vec2 << " = " << vec1 + vec2 << std::endl << std::endl;

    std::cout << "operator chaining and member-function" << std::endl;
    auto vec3 = vec1 + vec2 + vec1;
    std::cout << "vec3=" << vec3 << " norm=" << vec3.norm() << std::endl << std::endl;

    std::cout << "pass by reference" << std::endl;
    std::cout << "vec3=         " << vec3 << std::endl;
    reverse(vec3);
    std::cout << "reversed vec3=" << vec3 << std::endl << std::endl;

    std::cout << "use default-copy-constructor" << std::endl;
    auto vec4 = vec3;
    std::cout << "vec3=" << vec3 << " vec4=" << vec4 << std::endl << std::endl;

    std::cout << "copy constructor creates genuine copy not only reference to same object" << std::endl;
    std::cout << "vec3=" << vec3 << " vec3=" << vec3 << std::endl << std::endl;
    vec4.vec_[0] = 666.0;
    std::cout << "vec3=" << vec3 << " vec4=" << vec4 << std::endl << std::endl;

    std::cout << "use default-assignment-operator" << std::endl;
    std::cout << "vec1=" << vec1 << " vec2=" << vec2 << std::endl;
    vec2 = vec1;
    std::cout << "vec1=" << vec1 << " vec2=" << vec2 << std::endl << std::endl;

    std::cout << "assignment operator copies valuesand does not just reference the same object" << std::endl;
    vec2.vec_[0] = 666.0;
    std::cout << "vec2=" << vec2 << " vec1=" << vec1 << std::endl << std::endl;

    return 0;
}