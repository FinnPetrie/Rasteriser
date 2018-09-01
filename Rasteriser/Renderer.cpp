//
//  Renderer.cpp
//  Rasteriser
//
//  Created by Finn Petrie on 25/08/18.
//  Copyright © 2018 Finn Petrie. All rights reserved.
//

#include "Renderer.hpp"
#include <cmath>
#include <algorithm>

Renderer::Renderer(){
    
}

void Renderer::rayTrace(Image &image,  const Scene &scene, const Camera &camera, int x0, int x1, int y0, int y1){
    /** Trace eye rays with origins in the box from [x0, y0] to (x1, y1).*/
        // For each pixel
        for (int y = y0; y < y1; ++y) {
            for (int x = y0; x < x1; ++x) {
                // Ray through the pixel
                const Ray& R = computeEyeRay(x + 0.5f, y + 0.5f, image.width(),
                                             image.height(), camera);
            
                // Distance to closest known intersection
                float distance = INFINITY;
                Colour L_o;
                // For each triangle
                for (unsigned int t = 0; t < scene.triangles.size(); ++t){
                    const Triangle& T = scene.triangles[t];
                    //T.printVertices();
                    if (sampleRayTriangle(scene, x, y, R, T, L_o, distance)) {
                        printf("This is our colour:");
                        L_o.print();
                        image.set(x, y, L_o);
                        
                    }
                }
            }
        }
}

Ray Renderer::computeEyeRay(float x, float y, int width, int height, const Camera& camera) {
    
    const float aspect = float(height)/width;
    
    float s = -2.0f * tan(camera.getFoVx() * 0.5f);
    
    const Vector& start = Vector((x/width - 0.5f)* s, -(y/height - 0.5f) * s * aspect, 1.0f) * camera.getZNear();
    const Vector& direct = start.direction();
    return Ray(Point(start), Direction(direct));
    
}


float Renderer::intersect(const Ray& R, const Triangle& T, float weight[3]) {
    const Vector& e1 = T.vertex(1) - T.vertex(0);
    const Vector& e2 = T.vertex(2) - T.vertex(0);
    const Vector& q = R.directionise().cross(e2);
    const float a = e1.dot(q);
    const Vector& s = R.getPoint() - T.vertex(0);
    const Vector& r = s.cross(e1);
    
    // Barycentric vertex weights
    
    weight[1] = s.dot(q) / a;
    weight[2] = R.directionise().dot(r) / a;
    weight[0] = 1.0f - (weight[1] + weight[2]);
    const float dist = e2.dot(r) / a;
    static const float epsilon = 1e-7f;
    static const float epsilon2 = 1e-10;
    if ((a <= epsilon) || (weight[0] < -epsilon2) ||
        (weight[1] < -epsilon2) || (weight[2] < -epsilon2) ||
        (dist <= 0.0f)) {
        // The ray is nearly parallel to the triangle, or the
        // intersection lies outside the triangle or behind
        // the ray origin: "infinite" distance until intersection.
        return INFINITY;
    } else {
        
        //printf("Intersection");
        return dist;
    }
}


bool Renderer::sampleRayTriangle(const Scene& scene, int x, int y, const Ray& R, const Triangle& T, Colour& radiance, float& distance) {
    
     float weight[3];
    const float d = intersect(R, T, weight);
    
     if (d >= distance) {
         return false;

        }
    
     // This intersection is closer than the previous one
     distance = d;
    
     // Intersection point
     const Point& P = R.getPoint() + R.getDirection() * d;
    
     // Find the interpolated vertex normal at the intersection
     const Vector& n = (T.normal(0) * weight[0] +
                            T.normal(1) * weight[1] +
                        T.normal(2) * weight[2]).direction();
    
     const Vector& w_o = -R.directionise();
    
   shade(scene, T, P, n, w_o, radiance);
    // Debugging intersect: set to white on any intersection
   // radiance = Colour(1, 1, 1);
    //printf("woo we got a hit");
    // Debugging barycentric
 // radiance = Colour(weight[1], weight[0], weight[2]);
    
    return true;
}

void Renderer::shade(const Scene& scene, const Triangle& T, const Point& P,
           const Vector& n, const Vector& w_o, Colour& L_o) {
   // L_o = Colour(0.0f, 0.0f, 0.0f);
    // For each direction (to a light source)
    for (unsigned int i = 0; i < scene.lights.size(); ++i) {
        const Light& light = scene.lights[i];
        //light.print();
        Vector intersection(P.mat[0],P.mat[1], P.mat[2]);
        const Vector& offset = light.getLocation() - intersection;
       // const Vector reoffset(offset.mat[0], offset.mat[1], offset.mat[2]);
        const float distanceToLight = offset.magnitude();
        const Vector& w_i = offset / distanceToLight;
        if (visible(P, w_i, distanceToLight, scene)) {
            const Colour& L_i = light.getEmittance() / (4 * M_PI * distanceToLight*distanceToLight);
            //L_i.print();
    
// Scatter the light
            //T.setBSDF(n);
            const Colour& bs = T.getBSDF().evaluateFiniteScatteringDensity(w_i, w_o);
            const Colour& cool = L_i*bs;
            //column.print();
            double check = L_i.dot(bs);
            
            //printf("%f our check <<__\n\n", check);
            L_o +=  cool * std::max(0.0, w_i.dot(n)); //max(0.0, w_i.dot(n));
           // printf("\n\nL_o in the shade routine:");
            //L_o.print();
           // printf("\n\n");
        }
    }
    
}

bool Renderer::visible(const Point& p, const Vector& weight, const float f, const Scene& scene){
    return true;
}
