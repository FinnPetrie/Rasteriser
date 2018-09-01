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
private:
    double red, green, blue, alpha;
public:
    Colour(double r, double g, double b);
    Colour(double r, double g, double b, double alpha);
    Colour();
    Colour(Vector v);

};
Colour operator*(Colour &lhs, Colour &rhs)


#endif /* Colour_hpp */
