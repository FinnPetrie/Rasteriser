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
    double FoVx, FoVy, zFar;
    
    public:
    Camera(Vector look, Vector vUP, Vector p,  double far, double horizontalFoV, double verticalFoV);
    void BasisComposition();
    void Perspective();
    void Translation();
    void ViewVolume();
    double getFoVx() const;
    double getFoVy() const;
    double getZFar() const;
    
    
    
};
#endif /* Camera_hpp */
