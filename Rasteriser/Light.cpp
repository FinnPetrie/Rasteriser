//
//  Light.cpp
//  Rasteriser
//
//  Created by Finn Petrie on 25/08/18.
//  Copyright © 2018 Finn Petrie. All rights reserved.
//

#include "Light.hpp"


Light::Light(){
    printf("Coming here from light");

    Point p(0,0,0);
    location = p;
    location.print();
    Colour c(1,1,1);
    
    emittance = c;
    

}

Light::Light(Point l, Colour c) : location(l), emittance(c){
}


const Colour& Light::getEmittance() const{
    return emittance;
}

const Point& Light::getLocation() const{
    return location;
}

void  Light::print() const{
    printf("Our emittance: ");
    this->emittance.print();
    printf("\n");
    printf("Our location: ");
    this->location.print();
    
}
