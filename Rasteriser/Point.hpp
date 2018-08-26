//
//  Point.hpp
//  Rasteriser
//
//  Created by Finn Petrie on 8/08/18.
//  Copyright © 2018 Finn Petrie. All rights reserved.
//

#ifndef Point_hpp
#define Point_hpp

#include <stdio.h>
#include "Vector.hpp"
#include "Direction.hpp"


class Point: public Vector{
    private:
    double w = 1.0;
    public:
    Point(double x, double y, double z);
    Point(const Matrix& r);
    Point(const Vector& r);
};
#endif /* Point_hpp */
