//
//  Camera.cpp
//  Rasteriser
//
//  Created by Finn Petrie on 13/08/18.
//  Copyright © 2018 Finn Petrie. All rights reserved.
//

#include "Camera.hpp"

Camera::Camera(Direction look, Direction vUP, Position p,  Vector f, double fieldOfView, ){
    bases[0] = -look/look.magnitude();
    Vector vPrime = vUP - bases[0]*(vUP.dot(bases[0]));
    bases[1] = vPrime/vPrime.magnitude();
    bases[2] = bases[1].cross(bases[0]);
    AB = f*tan(fieldOfView/2);
    A = p - f*bases[0];
    B = A + f*tan(fieldOfView/2)*bases[2];
    C = A + f*bases[1];
    //perspective = matrix 4x4(diagonal entries = 1/(ftan(fieldofView/2), 1/ftan(thetav/2), 1/f, 1, matrix 4*4 with rows 0->2 = our bases,, matrix 4*4 with 4th column = -P;
    
}
