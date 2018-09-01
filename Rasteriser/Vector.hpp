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
#include <string>

class Vector: public Matrix{
    
    public:
    
    Vector(size_t n, double x, double y, double z);
    Vector(size_t n, double x, double y, double z, double w);
    Vector(double x, double y, double z);
    Vector(size_t n);
    Vector();
    Vector(double x, double y, double z, size_t n, std::string s);
    Vector(Vector v, double w);
    Vector(Vector const &v);
    double dot(const Vector& r) const;
    Vector cross(const Vector& r)const;
    void print() const override;
    double getElement(int i, int j) override;
    double magnitude() const;
    Vector direction() const;
    Vector toColumn(const Vector &from) const;
    //void operator +=(const Vector &rhs);
    virtual double operator()(int index);
    void normalised();
};



Vector operator+(const Vector &lhs, const Vector &rhs);
Vector operator-(const Vector &lhs, const Vector &rhs);
Vector operator-(const Vector &rhs);
Vector operator*(double scalar, const Vector &rhs);
Vector operator*(const Vector &rhs, double scalar);
Vector operator/(const Vector &lhs, double scalar);
Vector operator/=(const Vector &lhs, double);
Vector operator+=(const Vector &lhs, const Vector &rhs);
Vector operator+=(const Vector &lhs, double rhs);
#endif /* Vector_h */
