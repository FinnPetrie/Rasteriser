//
//  Colour.cpp
//  Rasteriser
//
//  Created by Finn Petrie on 23/08/18.
//  Copyright © 2018 Finn Petrie. All rights reserved.
//

#include "Colour.hpp"

Colour::Colour(double r, double g, double b) : Colour(r, g, b, 0){
    
}

Colour::Colour(double r, double g, double b, double a) : red(r), green(g), blue(b), alpha(a)){
    
}

Colour::Colour() : Colour(0,0,0){
    
}


Colour::Colour(Vector v) : Colour(v.mat[0], v.mat[1], v.mat[2]){
    
}

Colour Colour::operator*( Colour &rhs){
    assert(this->mat.size() == rhs.mat.size());
    Colour result;
    for(int i =0 ; i < result.mat.size(); ++i){
        result.mat[i] = this->mat[i] * rhs.mat[i];
    }
    return result;
}
