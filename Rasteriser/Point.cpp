//
//  Point.cpp
//  Rasteriser
//
//  Created by Finn Petrie on 8/08/18.
//  Copyright © 2018 Finn Petrie. All rights reserved.
//

#include "Point.hpp"


Point::Point(double x, double y, double z): Vector(4, x, y, z, w){
    
}


Point::Point(const Vector& r) : Vector(r, w){
    
}
