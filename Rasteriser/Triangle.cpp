//
//  Triangle.cpp
//  Rasteriser
//
//  Created by Finn Petrie on 22/08/18.
//  Copyright © 2018 Finn Petrie. All rights reserved.
//

#include "Triangle.hpp"


Triangle::Triangle(Vector v[3], Colour c){
    for(int i = 0; i < 3; ++i){
        vertices[i] = v[i];
    }
    Colour colour = c;
    for(int i = 0; i < 3; ++i){
        vertices[i].print();
    }
    
}
Triangle::Triangle(Vector v[3], Colour c, BSDF k) : bsdf(k){
    for(int i = 0; i < 3; ++i){
        vertices[i] = v[i];
    }
    Colour colour = c;
    for(int i = 0; i < 3; ++i){
        vertices[i].print();
    }
    
}
Triangle::Triangle(Vector a1, Vector a2, Vector a3){
    vertices[0] = a1;
    vertices[1] = a2;
    vertices[2] = a3;
    for(int i = 0; i < 3; ++i){
        vertices[i].print();
    }
}


Triangle::Triangle(Vector v[3], Vector n[3], BSDF b) : bsdf(b){
    for(int i = 0; i < 3; ++i){
        vertices[i] = v[i];
        normals[i] = n[i];
    }
}
double Triangle::area(){
    Vector parrallelogram = (vertices[1] - vertices[0]).cross(vertices[2] - vertices[0]);
    double parArea = parrallelogram.magnitude();
    return parArea/2;
}

void Triangle::printVertices() const{
    for(int i =0 ; i < 3; ++i){
        vertices[i].print();
        normals[i].print();
    }
}


void Triangle::printBSDF() const{
    bsdf.print();
}
Vector Triangle::barycentric(const Vector& p){
    Triangle CAP(vertices[2], vertices[0], p);
    Triangle ABP(vertices[0], vertices[1], p);
    Triangle BCP(vertices[1], vertices[2], p);
    
    double u = CAP.area()/this->area();
    double v = ABP.area()/this->area();
    double w = BCP.area()/this->area();
    return Vector(u, v, w);
    
}

Vector Triangle::getVertices(int i){
    assert(i <= 2);
    return vertices[i];
}

Colour Triangle::getColour() const{
    return colour;
}


Vector Triangle::normal(int i) const{
    assert(i <= 2);
    return normals[i];
    
}

Vector Triangle::vertex(int i) const{
    assert(i <= 2);
    return vertices[i];
}

const BSDF& Triangle::getBSDF() const{
    return bsdf;
}

void Triangle::setBSDF(const Vector &n) const {
    BSDF bsdf(n);
}
