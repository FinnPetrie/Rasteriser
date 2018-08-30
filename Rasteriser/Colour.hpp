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


class Colour : public Vector{
public:
    Colour(double r, double g, double b);
    Colour(double r, double g, double b, double alpha);
    Colour();
    Colour(Vector v);
};

#endif /* Colour_hpp */
