//
//  Colour.hpp
//  Rasteriser
//
//  Created by Finn Petrie on 23/08/18.
//  Copyright © 2018 Finn Petrie. All rights reserved.
//
#ifndef Colour_hpp
#define Colour_hpp

#include <stdio.h>
#include "Vector.hpp"
#include <assert.h>



class Colour{
public:

    double red, green, blue, alpha;
    Colour(double r, double g, double b);
    Colour(double r, double g, double b, double alpha);
    Colour();
    Colour(Vector v);
    void print() const;
};
Colour operator*(const Colour &lhs, const Colour &rhs);
Colour operator+(const Colour &lhs, const Colour &rhs);
Colour operator-(const Colour &lhs, const Colour &rhs);
Colour operator-(const Colour &rhs);
Colour operator*(double scalar, const Colour &rhs);
Colour operator*(const Colour &rhs, double scalar);
Colour operator/(const Colour &lhs, double scalar);
Colour operator/=(const Colour &lhs, double);
Colour operator+=(const Colour &lhs, const Colour &rhs);
Colour operator+=(const Colour &lhs, double rhs);


#endif /* Colour_hpp */
