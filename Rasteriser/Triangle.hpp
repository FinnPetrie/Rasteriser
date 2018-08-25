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
#include "Colour.hpp"
#include <assert.h>

class Triangle{
    private:
    Vector vertices[3];
    Colour colour;
    public:
    Triangle(Vector v[3], Colour c);
    Triangle(Vector a1, Vector a2, Vector a3);
    double area();
    Vector barycentric(const Vector& p);
    Vector getVertices(int i);
    Colour getColour() const;
};

#endif /* Triangle_hpp */
