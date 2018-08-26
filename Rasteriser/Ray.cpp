//
//  Ray.cpp
//  Rasteriser
//
//  Created by Finn Petrie on 23/08/18.
//  Copyright © 2018 Finn Petrie. All rights reserved.
//

#include "Ray.hpp"
#define UNSTABLE -1
#define RAY_MISSES_PLANE 0
#define INTERSECTION 1

Ray::Ray(Point p, Direction d) : direction(d), point(p){
}

int Ray::rayTriangleIntersection(Triangle t) const{
    Vector edgeBA = t.getVertices(1) - t.getVertices(0);
    Vector edgeCA = t.getVertices(2) - t.getVertices(0);
    Vector n = edgeBA.cross(edgeCA);
    Vector AB = n.cross(t.getVertices(1) - t.getVertices(0));
    double dividend = (t.getVertices(2) - t.getVertices(0)).dot(AB);
    AB = AB/dividend;
    Vector AC = n.cross(t.getVertices(0) - t.getVertices(2));
//    printf("\n\n\n, our AC");
    AC.print();
    dividend = (t.getVertices(1) - t.getVertices(0)).dot(AC);
//    printf("\n\nPast AC Dividend\n\n");
    AC = AC/dividend;
    
    
    Vector d(this->direction.Matrix::getElement(0), this->direction.Matrix::getElement(1), this->direction.Matrix::getElement(2));
    double u = n.dot(d);
    if(std::abs(u) < 0.00001){
        return UNSTABLE;
    }
    Vector p(this->point.Matrix::getElement(0), this->point.Matrix::getElement(1), this->point.Matrix::getElement(2));
    double term = (t.getVertices(0) - p).dot(n);
    term /= u;
    
    if( term < 0){
        return RAY_MISSES_PLANE;
    }
    
    
    Point Q = this->point + term*this->direction;
    
    Point bary = t.barycentric(Q);
    if((1 > bary.Matrix::getElement(0) || bary.Matrix::getElement(0) < 0 ) || (1 > bary.Matrix::getElement(1) || bary.Matrix::getElement(1) < 0) || (1 > bary.Matrix::getElement(2) || bary.Matrix::getElement(2) < 0)){
        return RAY_MISSES_PLANE;
    } else{
        return INTERSECTION;
    }
}

