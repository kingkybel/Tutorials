#include "vector_3d.h"

#include <iostream>

int main(int argc, char** argv)
{
    std::cout << "use default-values for construction" << std::endl;
    Vector3D vec0_1;
    Vector3D vec0_2{1.0};
    Vector3D vec0_3{1.0,2.0};
    std::cout << "vec0_1=" << vec0_1  << " vec0_2=" << vec0_2  << " vec0_3=" << vec0_3 << std::endl << std::endl;

    std::cout << "create object on-the-fly" << std::endl;
    Vector3D vec1{1.1, 2.2, 3.3};
    Vector3D vec2{5.1, 5.2, 5.3};
    std::cout << vec1 << " + " << vec2 << " = " << vec1 + vec2 << std::endl << std::endl;

    std::cout << "chain operators and use member-function" << std::endl;
    auto vec3 = vec1 + vec2 + vec1;
    std::cout << "vec3=" << vec3 << " norm=" << vec3.norm() << std::endl << std::endl;

    std::cout << "pass by reference" << std::endl;
    std::cout << "before: vec3=" << vec3 << std::endl;
    reverse(vec3);
    std::cout << "successfully reversed vec3=" << vec3 << std::endl << std::endl;

    std::cout << "pass by value" << std::endl;
    std::cout << "before: vec3=" << vec3 << std::endl;
    cant_reverse(vec3);
    std::cout << "vec3 unchanged=" << vec3 << std::endl << std::endl;

    std::cout << "use default-copy-constructor" << std::endl;
    std::cout << "vec1=" << vec1  << " vec2=" << vec2  << std::endl << std::endl;
    vec2 = vec1;
    std::cout << "vec1=" << vec1  << " vec2=" << vec2  << std::endl << std::endl;

    std::cout << "copy constructor creates genuine copy not only reference to same object" << std::endl;
    std::cout << "vec1=" << vec1  << " vec2=" << vec2  << std::endl << std::endl;
    vec2.x_ = 666.0;
    std::cout << "vec1=" << vec1  << " vec2=" << vec2  << std::endl << std::endl;

    Vector3D* p_vec = &vec2;

    return 0;
}