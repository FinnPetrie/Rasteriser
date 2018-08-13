//
//  Vector.hpp
//  Rasteriser
//
//  Created by Finn Petrie on 7/08/18.
//  Copyright © 2018 Finn Petrie. All rights reserved.
//

#ifndef Vector_h
#define Vector_h
#include "Matrix.hpp"
#include <cmath>

class Vector: public Matrix{
    
    public:
    
    Vector(size_t n, double x, double y, double z);
    Vector(size_t n, double x, double y, double z, double w);
    Vector(double x, double y, double z);
    Vector(size_t n);
    double dot(const Vector& r);
    const Vector cross(const Vector& r);
    void print() override;
    double getElement(int i, int j) override;
    double magnitude();
    
    Vector operator*(Vector &n) ;
    Vector operator+(Vector &n);
    Vector operator-(Vector &n);
    Vector operator-();
    Vector operator*(double scalar);
    Vector operator/(double scalar);
};

#endif /* Vector_h */
