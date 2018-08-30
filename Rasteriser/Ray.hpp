//
//  Ray.hpp
//  Rasteriser
//
//  Created by Finn Petrie on 23/08/18.
//  Copyright © 2018 Finn Petrie. All rights reserved.
//

#ifndef Ray_hpp
#define Ray_hpp

#include <stdio.h>
#include "Point.hpp"
#include "Direction.hpp"
#include "Triangle.hpp"
#include "Camera.hpp"


class Ray {
private:
    Point point;
    Direction direction;
public:
    Ray(Point p, Direction d);
    int rayTriangleIntersection(Triangle t) const;
    Direction getDirection() const;
    void print() const;
    Vector directionise() const;
    Point getPoint() const;
};

#endif /* Ray_hpp */
