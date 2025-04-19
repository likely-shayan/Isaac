#include <iostream>
#include "vector2d.hpp"
#include "vector3d.hpp"

using namespace Issac;

int main() {
        
    std::cout << "Hello World" << std::endl;

    vector2d x(1, 2);
    vector2d y(3, 4);
    vector2d z = x + y;

    std::cout << z.print() << std::endl;
    std::cout << y.magnitude() << std::endl;
    std::cout << vector2d::dot(x, y) << std::endl;

    vector3d _x(1, 2, 3);
    vector3d _y(4, 5, 6);
    vector3d _z = _x + _y;

    std::cout << _z.print() << std::endl;
    std::cout << _y.magnitude() << std::endl;
    std::cout << vector3d::dot(_x, _y) << std::endl;

    vector3d i(1, 0, 0);
    vector3d j(0, 1, 0);
    vector3d k = vector3d::cross(i, j);

    std::cout << k.print() << std::endl;

    return 0;
}