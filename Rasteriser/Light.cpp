//
//  Light.cpp
//  Rasteriser
//
//  Created by Finn Petrie on 25/08/18.
//  Copyright © 2018 Finn Petrie. All rights reserved.
//

#include "Light.hpp"


Light::Light(): location(Point(0,0,0)), emittance(Colour()){
}

Light::Light(Point l, Colour c) : location(l), emittance(c){
}
