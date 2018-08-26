//
//  Renderer.cpp
//  Rasteriser
//
//  Created by Finn Petrie on 25/08/18.
//  Copyright © 2018 Finn Petrie. All rights reserved.
//

#include "Renderer.hpp"

Renderer::Renderer(){
    
}

void Renderer::rayTrace(Image &image,  const Scene &scene, const Camera &camera, int x0, int x1, int y0, int y1){
    for(int y = y0; y < y1; ++y){
        for(int x = y0; x < x1; ++x){
            
            const Ray& R = computeEyeRay(x + 0.5f, y + 0.5f, image.width(), image.height(), camera);
            
            float distance = INFINITY;
            Colour L_o;
//            printf("\n\n\nthese are our triangles\n");
//            scene.printTriangles();
//            printf("\n\n\n");
            for(unsigned int t= 0 ; t < scene.triangles.size(); ++t){
//                printf("T %ud\n", t);
                const Triangle& T = scene.triangles[t];
//                printf("\n\n");
////                T.printVertices();
//                printf("\n\n\n");
                if(R.rayTriangleIntersection(T)){
                    image.set(x, y, T.getColour());
                }
            }
        }
    }
    printf("Complete");
}

Ray Renderer::computeEyeRay(float x, float y, int width, int height, const Camera& camera) {
    
    const float aspect = float(height)/width;
    
    float s = -2.0f * tan(camera.getFoVx() * 0.5f);
    
    const Vector& start = Vector((x/width - 0.5f)* s, -(y/height - 0.5f) * s * aspect, 1.0f) * camera.getZFar();
    
    return Ray(Point(start), Direction(start));
    
}
