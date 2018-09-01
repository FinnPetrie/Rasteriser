//
//  BSDF.cpp
//  Rasteriser
//
//  Created by Finn Petrie on 31/08/18.
//  Copyright © 2018 Finn Petrie. All rights reserved.
//

#include "BSDF.hpp"


BSDF::BSDF(Colour k) : k_L(k){
}

BSDF::BSDF(): k_L(Colour(0,0,0)){
    
}

BSDF::BSDF(double x, double y, double z) : k_L(Colour(x, y, z)){
    
}

Colour BSDF::evaluateFiniteScatteringDensity(const Vector &w_i, const Vector &w_o) const{
    return k_L / M_PI;
}



void BSDF::operator=(const BSDF &rhs){
    this->k_L = rhs.k_L;
}

