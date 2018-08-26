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
    Vector();
    Vector(Vector v, double w);
    double dot(const Vector& r);
    const Vector cross(const Vector& r);
    void print() const override;
    double getElement(int i, int j) override;
    double magnitude();
};



Vector operator+(const Vector &lhs, const Vector &rhs);
Vector operator-(const Vector &lhs, const Vector &rhs);
Vector operator-(const Vector &rhs);
Vector operator*(double scalar, const Vector &rhs);
Vector operator*(const Vector &rhs, double scalar);
Vector operator/(const Vector &lhs, double scalar);
Vector operator/=(const Vector &lhs, double);
#endif /* Vector_h */
