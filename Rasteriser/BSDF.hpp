//
//  BSDF.hpp
//  Rasteriser
//
//  Created by Finn Petrie on 31/08/18.
//  Copyright © 2018 Finn Petrie. All rights reserved.
//

#ifndef BSDF_hpp
#define BSDF_hpp

#include <stdio.h>
#include "Colour.hpp"

class BSDF{
public:
    Colour k_L;
    Colour k_G;
    float s;
    //Vector n;
    
public:
    BSDF(Colour k);
    BSDF();
    
    BSDF(Colour k, Colour l, float scatter);
    BSDF(double x, double y, double z);
    /** Returns f = L_o / (L_i * w_i.dot(n)) assuming
     incident and outgoing directions are both in the
     positive hemisphere above the normal */
    Colour evaluateFiniteScatteringDensity(const Vector& w_i, const Vector& w_o, const Vector& n) const;
    Colour getk_L() const;
    void print() const;
    void setNormal(Vector &n) const;
    
    void operator=(const BSDF& rhs);

};

#endif /* BSDF_hpp */
