//
//  main.cpp
//  Rasteriser
//
//  Created by Finn Petrie on 7/08/18.
//  Copyright © 2018 Finn Petrie. All rights reserved.
//

#include <iostream>
#include "Matrix.hpp"
#include "Vector.hpp"
#include "Camera.hpp"

int main(int , const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    Matrix m(3, 2);
    m.mat[m.getRepresentation(0, 0)] = 1;
    m.mat[m.getRepresentation(1,1)] = 1;
    m.mat[m.getRepresentation(2,1)] = 1;
    m.print();

    Matrix ton(2,2);
    ton.mat[ton.getRepresentation(0,0)] = 1;
    ton.mat[ton.getRepresentation(1,1)] = 1;
     Matrix q = m * ton;
    printf("this is q:\n");
    q.print();
    
//    m.print();
    Vector look(0,0, -1);
    Vector up(0,1,0);
    Vector position(0,0,0);
//    p.print();
//    p.print();
    Vector t(3, 0, 1);
//    t.print();
//    double q = p.dot(t);
//    printf("%f: our inner product.\n", q);
//    Vector cross = p.cross(t);
//    cross.print();
//    Vector n = q*p;
//     n.print();
    double far = 10.0;
    double s = 0.75;
    double vert = 0.55;
    Camera c(look, up, position, far, s, vert);
    //    printf("%f this is our dot product\n", q);
    
    return 0;
}
