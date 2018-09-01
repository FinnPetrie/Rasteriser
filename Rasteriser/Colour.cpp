//
//  Colour.cpp
//  Rasteriser
//
//  Created by Finn Petrie on 23/08/18.
//  Copyright © 2018 Finn Petrie. All rights reserved.
//

#include "Colour.hpp"

Colour::Colour(double r, double g, double b) : Colour(r, g, b, 0){
    //printf("red:%f, green: %f, blue: %f\n", r,g,b);
}

Colour::Colour(double r, double g, double b, double a) : red(r), green(g), blue(b), alpha(a){
    
}

Colour::Colour() : Colour(0,0,0){
    
}


Colour::Colour(Vector v) : Colour(v.mat[0], v.mat[1], v.mat[2]){
    
}

void Colour::print() const{
    printf("red: %f\ngreen: %f\nblue: %f\nalpha: %f\n", red, green, blue, alpha) ;
}



Colour operator*(const Colour &lhs, const Colour &rhs){
    //printf("red *red %f, green * green %f, blue * blue %f\n", (lhs.red * rhs.red), (lhs.green * rhs.green), (lhs.blue * rhs.blue));
    Colour result((lhs.red * rhs.red), (lhs.green * rhs.green), (lhs.blue * rhs.blue));
        return result;
}

Colour operator+(const Colour &lhs, const Colour &rhs){
    Colour result(lhs.red + rhs.red, lhs.green + rhs.green, lhs.blue + rhs.blue);
    return result;

}
Colour operator-(const Colour &lhs, const Colour &rhs){
    Colour result(lhs.red - rhs.red, lhs.green - rhs.green, lhs.blue  -rhs.blue);
    return result;
    
}
Colour operator-(const Colour &rhs){
    Colour result(-rhs.red, -rhs.green, -rhs.blue);
    return result;
    
}
Colour operator*(double scalar, const Colour &rhs){
   // printf("Calling scalr colour");
    Colour result(scalar* rhs.red, scalar * rhs.green, scalar * rhs.blue);
    return result;
    
}
Colour operator*(const Colour &rhs, double scalar){
   // printf("calling colur scalar");
    Colour result(scalar * rhs.red, scalar * rhs.green, scalar * rhs.blue);
    return result;
    
}
Colour operator/(const Colour &lhs, double scalar){
   // printf("division operator, red, green, blue: %f %f %f", lhs.red/scalar, lhs.green/scalar, lhs.blue/scalar);
    Colour result(lhs.red / scalar, lhs.green /scalar, lhs.blue /scalar);
    return result;
    
}

Colour operator+=(const Colour &lhs, const Colour &rhs){
    return lhs + rhs;
    
}
Colour operator+=(const Colour &lhs, double rhs){
    Colour result(lhs.red + rhs, lhs.green + rhs, lhs.blue + rhs);
    return result;
    
}

