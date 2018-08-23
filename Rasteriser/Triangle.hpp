//
//  Triangle.hpp
//  Rasteriser
//
//  Created by Finn Petrie on 22/08/18.
//  Copyright © 2018 Finn Petrie. All rights reserved.
//

#ifndef Triangle_hpp
#define Triangle_hpp

#include <stdio.h>
#include "Vector.hpp"
#endif /* Triangle_hpp */

class Triangle{
    private:
    Vector vertices[3];
    public:
    Triangle(Vector v[3]);
    Triangle(Vector a1, Vector a2, Vector a3);
    double area();
    Vector barycentric(const Vector& p);
};
