//
//  Camera.hpp
//  Rasteriser
//
//  Created by Finn Petrie on 13/08/18.
//  Copyright © 2018 Finn Petrie. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include <stdio.h>
#include "Point.hpp"
#include "Direction.hpp"
#include "Matrix.hpp"


class Camera{
    
private:
    
    Matrix perspective;
    Matrix viewVolume;
    Matrix basisComposition;
    Matrix translation;
    Vector position;
    Vector bases[3];
    double AB;
    Vector A, B, C;
    double FoVx, FoVy, zFar, zNear;
    
public:
    Camera(Vector look, Vector vUP, Vector p);
    Matrix BasisComposition();
    Matrix Perspective();
    Matrix Translation();
    Matrix ViewVolume();
    double getFoVx() const;
    double getFoVy() const;
    double getZFar() const;
    double getZNear() const;
    void print() const;
    
    
    
};
#endif /* Camera_hpp */
