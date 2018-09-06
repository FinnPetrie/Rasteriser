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
    /**
    
    Vector vertices[3];
    vertices[0] = Vector(0, 1, -2);
    vertices[1] = Vector(-1.9, -1, -2);
    vertices[2] = Vector(1.6, -0.5, -2);
    Vector normals[3];
    normals[0] = Vector(0, 0.6, 1).direction();
    normals[1] = Vector(-0.4, -0.4, 1.0).direction();
    normals[2] = Vector(0.4, -0.4, 1.0).direction();
    BSDF green(Colour(0, 1, 0) * 0.8, Colour(1,1,1) * 0.2, 100);
    
    Triangle t(vertices, normals, green);
    
    
    
    Vector verts[3];
    verts[0] = Vector(-1.9, -1, -2);
    verts[1] = Vector(0, 1, -2);
    verts[2] = Vector(1.6, -0.5, -2);
    Vector norms[3];
    norms[0] = Vector(-0.4, -0.4, 1.0).direction();
    norms[1] = Vector(0, 0.6, 1).direction();
    norms[2] = Vector(0.4, -0.4, 1.0).direction();
   // BSDF green(Colour(0,1,0) * 0.8, Colour(1,1,1) * 0.2, 100);
    Triangle triOne(vertices, normals, green);
    
    
    
    const float groundY = -1.0;
    const Colour groundColour = Colour(1,1,1) * 0.8;
    Vector verticesGround[3];
    verticesGround[0] = Vector(-10, groundY, -10);
    verticesGround[1] = Vector(-10, groundY, -0.01);
    verticesGround[2] = Vector(10, groundY, -0.01);
    Vector normalsGround[3];
    normalsGround[0] = Vector(0,1,0);
    normalsGround[1] = Vector(0,1,0);
    normalsGround[2] = Vector(0,1,0);
    BSDF grey(groundColour, groundColour, 0);
    Triangle groundOne(verticesGround, normalsGround, grey);
    
    
    
    Vector verticesGroundTwo[3];
    verticesGroundTwo[0] = Vector(-10, groundY, -10);
    verticesGroundTwo[1] = Vector(10, groundY, -0.01);
    verticesGroundTwo[2] = Vector(-10, groundY, -10);
    Triangle groundWound(verticesGroundTwo, normalsGround, grey);
    
   // printf("\n\n\n");*/
    std::vector<Triangle> triangles;
   /** triangles.push_back(t);
    triangles.push_back(triOne);
    triangles.push_back(groundOne);
    triangles.push_back(groundWound);
    triangles.push_back(tri);
    triangles[0].printVertices();
   */
    //printf("\n\n\n");


    Point light_Local(0,1,0);
    Colour light_Bright(1,1,1);
    Light l(Point(1,3,1), Colour(50,50,50));
   // l.print();
   // printf("our fucking light^^ \n\n\n\n");
    std::vector<Light>lights;
    lights.push_back(l);
    //lights[0].print();
    //printf("our fucking light in the vecvtor^^^^^\n\n\n\n");
    Scene ourScene(triangles, lights);
    //ourScene.light.print();
   // ourScene.printLights();
   // printf("\n\n\nOur triangles\n");
    //ourScene.printTriangles();
    //printf("\n\n\n");
    
    
    
    
//    t.print();
//    double q = p.dot(t);
//    printf("%f: our inner product.\n", q);
//    Vector cross = p.cross(t);
//    cross.print();
//    Vector n = q*p;
//     n.print();
    
    
    Renderer r;
    //r.makeTrianglePlusGroundScene(ourScene);
    Camera ourCamera(look, up, position);
    Image ourImage(640, 480);
    Point p(0,2,0);
    //p.print();
   // r.makeOneTriangleScene(ourScene);
    r.makeTrianglePlusGroundScene(ourScene);
   // r.rayTrace(ourImage, ourScene, ourCamera, 0, ourImage.width(), 0,  ourImage.height());
    r.rasterize(ourImage, ourScene, ourCamera);
//        printf("%f this is our dot product\n", q);
    ourImage.save("ourImage.ppm", 2.2f);
    return 0;
}
