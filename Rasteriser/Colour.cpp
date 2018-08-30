//
//  Colour.cpp
//  Rasteriser
//
//  Created by Finn Petrie on 23/08/18.
//  Copyright © 2018 Finn Petrie. All rights reserved.
//

#include "Colour.hpp"

Colour::Colour(double r, double g, double b) : Vector(r, g, b){
    
}

Colour::Colour(double r, double g, double b, double alpha) : Vector(r, g, b, alpha){
    
}

Colour::Colour() : Colour(0,0,0){
    
}


Colour::Colour(Vector v) : Colour(v.mat[0], v.mat[1], v.mat[2]){
    
}
