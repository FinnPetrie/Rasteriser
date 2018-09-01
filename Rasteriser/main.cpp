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
#include "Colour.hpp"
#include "Triangle.hpp"
#include "Scene.hpp"
#include "Renderer.hpp"
#include "Image.hpp"

int main(int , const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
//    Matrix m(3, 2);
//    m.mat[m.getRepresentation(0, 0)] = 1;
//    m.mat[m.getRepresentation(1,1)] = 1;
//    m.mat[m.getRepresentation(2,1)] = 1;
//    m.print();
//
//    Matrix ton(2,2);
//    ton.mat[ton.getRepresentation(0,0)] = 1;
//    ton.mat[ton.getRepresentation(1,1)] = 1;
//     Matrix q = m * ton;
//    printf("this is q:\n");
//    q.print();
    
//    m.print();
    Vector look(0,0, -1);
    Vector up(0,1,0);
    Vector position(0,0,0);
//    p.print();
//    p.print();
    
    
    Vector t(0, 1, -2);
    Vector s(-1.9, -1, -2);
    Vector g(1.6, -0.5, -2);
    Vector v[3] = {t, s, g};
    
    Vector normal1(0.0, 0.6, 1.0);
    normal1 = normal1.direction();
    Vector normal2(-0.4, 0.4, 1.0);
    normal2 = normal2.direction();
    Vector normal3(0.4, -0.4, 1.0);
    normal3 = normal3.direction();
    
    Vector normals[3] = {normal1, normal2, normal3};
    for(int i =0 ; i < 3; ++i){
        printf("Vertices: ");
        v[i].print();
        printf("Normals: ");
        normals[i].print();
    }
    Colour c(0.5, 0, 0);
    Colour k_L(0, 0, 0.8);
    BSDF k(k_L);
    Triangle tri(v, normals, k);
    tri.printVertices();
    std::vector<Triangle> triangles;
    triangles.push_back(tri);
    triangles[0].printVertices();

    Point light_Local(0,1,0);
    Colour light_Bright(1,1,1);
    Light l(Point(0,1,0), Colour(10,10,10));
    l.print();
    printf("our fucking light^^ \n\n\n\n");
    std::vector<Light>lights;
    lights.push_back(l);
    lights[0].print();
    printf("our fucking light in the vecvtor^^^^^\n\n\n\n");
    Scene ourScene(triangles, lights);
    ourScene.light.print();
    ourScene.printLights();
    printf("\n\n\nOur triangles\n");
    ourScene.printTriangles();
    printf("\n\n\n");
    
    
    
    
//    t.print();
//    double q = p.dot(t);
//    printf("%f: our inner product.\n", q);
//    Vector cross = p.cross(t);
//    cross.print();
//    Vector n = q*p;
//     n.print();
    
    
    Renderer r;
    Camera ourCamera(look, up, position);
    Image ourImage(640, 480);
    r.rayTrace(ourImage, ourScene, ourCamera, 0, ourImage.width(), 0, ourImage.height());
//        printf("%f this is our dot product\n", q);
    ourImage.save("ourImage.ppm", 2.2f);
    return 0;
}
