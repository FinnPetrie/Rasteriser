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
    public:
    Point(double x, double y, double z);
    Point();
    Point(const Matrix& r);
    Point(const Vector& r);
    double operator()(int index) override;
};
#endif /* Point_hpp */
