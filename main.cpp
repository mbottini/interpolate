#include "interpolate.h"
#include <iostream>

int main() {
    Point p1, p2, p3;
    p1.x = 1;
    p1.y = 1;
    p2.x = 2;
    p2.y = 4;
    p3.x = 3;
    p3.y = 9;

    std::vector<Point> vec = {p1, p2, p3};

    std::cout << lagrange_interpolate(vec) << "\n";

    return 0;
}
