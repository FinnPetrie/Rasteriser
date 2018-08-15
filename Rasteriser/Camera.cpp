//
//  Camera.cpp
//  Rasteriser
//
//  Created by Finn Petrie on 13/08/18.
//  Copyright © 2018 Finn Petrie. All rights reserved.
//

#include "Camera.hpp"

Camera::Camera(Vector look, Vector vUP, Vector p,  double far, double horizontalFoV, double verticalFoV){

    position = p;
    Vector n = -look;
    double magnitude = look.magnitude();
    bases[0] = n/magnitude;
    Vector vPrime = vUP - (vUP.dot(bases[0]))*bases[0];
    bases[1] = vPrime/vPrime.magnitude();
    bases[2] = bases[1].cross(bases[0]);
    AB = tan(horizontalFoV/2)*far;
    A = p - far*bases[0];
    B = A + tan((horizontalFoV*M_PI/180)/2)*bases[2]*far;
    C = A + far*bases[1];
    //perspective = matrix 4x4(diagonal entries = 1/(ftan(fieldofView/2), 1/ftan(thetav/2), 1/f, 1, matrix 4*4 with rows 0->2 = our bases,, matrix 4*4 with 4th column = -P;
    
    printf("Our debug: 1st, AB, 2nd A, 3rd B, 4th C, 5th position\n%f:", AB);
    A.print();
    B.print();
    C.print();
    position.print();
    double aNegB = (A-B).magnitude();
    printf("aNegB %f\n", aNegB);
    for(int i =0 ; i < 3; ++i){
        printf("Our %dth bases: ", i);
        bases[i].print();
    }
    std::vector<double> tangents;
    tangents.push_back(1/(far*tan(horizontalFoV*M_PI/180)));
    tangents.push_back(1/(far*tan(verticalFoV*M_PI/180)));
    tangents.push_back(1/far);
    tangents.push_back(1);
    viewVolume.diagonalise(tangents);
    printf("Our view volume\n");
    viewVolume.print();
    
}
