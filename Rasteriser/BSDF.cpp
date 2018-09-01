//
//  BSDF.cpp
//  Rasteriser
//
//  Created by Finn Petrie on 31/08/18.
//  Copyright © 2018 Finn Petrie. All rights reserved.
//

#include "BSDF.hpp"
#include <algorithm>


BSDF::BSDF(Colour k) : k_L(k), k_G(Colour(0.5f, 0.5f, 0.5)), s(10.0f){
}

BSDF::BSDF(): k_L(Colour(0,0,0)){
    
}

BSDF::BSDF(double x, double y, double z) : k_L(Colour(x, y, z)){
    
}


BSDF::BSDF(Colour l, Colour g, float scatter) : k_L(l), k_G(g), s(scatter){
    
}
Colour BSDF::evaluateFiniteScatteringDensity(const Vector &w_i, const Vector &w_o, const Vector& n) const{
    const Vector w_H = (w_i + w_o).direction();
    return(k_L + k_G * ((s + 8.0f) * powf(std::max(0.0, w_H.dot(n)), s)/8.0f)/ M_PI);
}

void BSDF::setNormal(Vector &normal) const {
    //this->n = normal;
}
void BSDF::print() const{
    k_L.print();
    
}

void BSDF::operator=(const BSDF &rhs){
    this->k_L = rhs.k_L;
}

