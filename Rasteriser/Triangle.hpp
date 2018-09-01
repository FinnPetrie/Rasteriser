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
#include "BSDF.hpp"

class Triangle{
public:
    Vector vertices[3];
    Vector normals[3];
    const Colour colour;
    BSDF bsdf;
    public:
    Triangle(Vector v[3], Colour c);
    Triangle(Vector v[3], Colour c, BSDF b);

    Triangle(Vector a1, Vector a2, Vector a3);
    Triangle(Vector v[3], Vector n[3], BSDF b);
    double area();
    Vector barycentric(const Vector& p);
    Vector getVertices(int i);
    Colour getColour() const;
    void printVertices() const;
    Vector normal(int i) const;
    Vector vertex(int i) const;
    const BSDF& getBSDF() const;
    void setBSDF(const Vector& n) const;
};

#endif /* Triangle_hpp */
