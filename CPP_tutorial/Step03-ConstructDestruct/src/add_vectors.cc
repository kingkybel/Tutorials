#include "vector_nd_ptr.h"

#include <iostream>

// #define TASK1

int main(int argc, char** argv)
{
    std::cout << "create long vector" << std::endl;
    VectorNDPtr vec1{"vec1", {1.1, 2.2, 3.3, 4.4, 5.5, 6.6}};
    std::cout << "vec1 = " << vec1 << " norm=" << vec1.norm() << std::endl;
    std::cout << "reverse it" << std::endl;
    reverse(vec1);
    std::cout << "vec1 = " << vec1 << " norm=" << vec1.norm() << std::endl << std::endl;

    std::cout << "default construct vec2" << std::endl;
    VectorNDPtr vec2;  // default-construction
    std::cout << "vec2 = " << vec2 << " norm=" << vec2.norm() << std::endl << std::endl;

    std::cout << "add 2 vectors" << std::endl;
    VectorNDPtr vec3{"vec3", {0.1, 0.2, 0.3, 0.4, 0.5, 0.6}};
    std::cout << vec1 << " + " << vec3 << " = " << vec1 + vec3 << std::endl << std::endl;

#ifdef TASK1
    std::cout << "copy construct vec4 from vec1" << std::endl;
    auto vec4 = vec1;  // copy-construction!!
    std::cout << "vec4 = " << vec4 << std::endl << std::endl;

    std::cout << "assign vec2 = vec1" << std::endl;
    vec2 = vec1;  // copy-assignment!!
    std::cout << "vec1 = " << vec1 << std::endl;
    std::cout << "vec2 = " << vec2 << std::endl << std::endl;
#endif

    return 0;
}