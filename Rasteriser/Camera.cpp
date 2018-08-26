//
//  Camera.cpp
//  Rasteriser
//
//  Created by Finn Petrie on 13/08/18.
//  Copyright © 2018 Finn Petrie. All rights reserved.
//

#include "Camera.hpp"

Camera::Camera(Vector look, Vector vUP, Vector p) : zNear(-0.1f), zFar(-100.0f), FoVx(M_PI/2.0f), FoVy(M_PI/2.0f){

    position = p;
    Vector n = -look;
    double magnitude = look.magnitude();
    bases[0] = n/magnitude;
    Vector vPrime = vUP - (vUP.dot(bases[0]))*bases[0];
    bases[1] = vPrime/vPrime.magnitude();
    bases[2] = bases[1].cross(bases[0]);
    AB = tan(FoVx/2)*zFar;
    A = p - zFar*bases[0];
    B = A + tan((FoVx*M_PI/180)/2)*bases[2]*zFar;
    C = A + zFar*bases[1];
    //perspective = matrix 4x4(diagonal entries = 1/(ftan(fieldofView/2), 1/ftan(thetav/2), 1/f, 1, matrix 4*4 with rows 0->2 = our bases,, matrix 4*4 with 4th column = -P;
    
//    printf("Our debug: 1st, AB, 2nd A, 3rd B, 4th C, 5th position\n%f:", AB);
//    A.print();
//    B.print();
//    C.print();
    position.print();
    double aNegB = (A-B).magnitude();
//    printf("aNegB %f\n", aNegB);
//    for(int i =0 ; i < 3; ++i){
//        printf("Our %dth bases: ", i);
//        bases[i].print();
//    }
    
    std::vector<double> tangents;
    tangents.push_back(1/(zFar*tan(FoVx*M_PI/180)));
    tangents.push_back(1/(zFar*tan(FoVy*M_PI/180)));
    tangents.push_back(1/zFar);
    tangents.push_back(1);
    Matrix viewVolume(4,4);
    viewVolume.diagonalise(tangents);
//    printf("Our view volume\n");
//    viewVolume.print();
  
    this->BasisComposition();
    this->Translation();
    
    
    
    
}


void Camera::Perspective(){
    Matrix perspective = basisComposition*translation;
    perspective = viewVolume*perspective;
    printf("our perspective matrix\n");
//    perspective.print();

    
}
void Camera::BasisComposition(){
    Matrix basisComposition(4,4);
    
    basisComposition.mat[basisComposition.getRepresentation(0,0)] = bases[0].mat[0];
    basisComposition.mat[basisComposition.getRepresentation(0,1)] = bases[0].mat[1];
    basisComposition.mat[basisComposition.getRepresentation(0,2)] = bases[0].mat[2];
    basisComposition.mat[basisComposition.getRepresentation(1,0)] = bases[1].mat[0];
    basisComposition.mat[basisComposition.getRepresentation(1,1)] = bases[1].mat[1];
    basisComposition.mat[basisComposition.getRepresentation(1,2)] = bases[1].mat[2];
    basisComposition.mat[basisComposition.getRepresentation(2,0)] = bases[2].mat[0];
    basisComposition.mat[basisComposition.getRepresentation(2,1)] = bases[2].mat[1];
    basisComposition.mat[basisComposition.getRepresentation(2,2)] = bases[2].mat[2];
    basisComposition.mat[basisComposition.getRepresentation(3,3)] = 1;
    
}

void Camera::Translation(){
    Matrix translation(4,4);
    
    std::vector<double> diagonal;
    for(int i =0 ; i < 4; i++){
        diagonal.push_back(1);
    }
    
    translation.diagonalise(diagonal);
    translation.mat[translation.getRepresentation(0,3)] = -position.mat[0];
    translation.mat[translation.getRepresentation(1,3)] = -position.mat[1];
    translation.mat[translation.getRepresentation(2,3)] = -position.mat[2];
//    printf("our translation matrix\n");
//    translation.print();
    
}

double Camera::getFoVx() const{
    return FoVx;
}

double Camera::getFoVy() const{
    return FoVy;
}

double Camera::getZFar() const{
    return zFar;
}
