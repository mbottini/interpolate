#include "interpolate.h"
#include <iostream>

int main() {
    Point p1, p2, p3, p4;
    p1.x = -9;
    p1.y = 5;
    p2.x = -4;
    p2.y = 2;
    p3.x = -1;
    p3.y = -2;
    p4.x = 7;
    p4.y = 9;

    std::vector<Point> vec = {p1, p2, p3, p4};

    std::cout << lagrange_interpolate(vec) << "\n";

    return 0;
}
