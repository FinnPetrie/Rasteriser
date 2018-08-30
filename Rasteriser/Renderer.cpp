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
    /** Trace eye rays with origins in the box from [x0, y0] to (x1, y1).*/
        // For each pixel
        for (int y = y0; y < y1; ++y) {
            for (int x = y0; x < x1; ++x) {
                // Ray through the pixel
                const Ray& R = computeEyeRay(x + 0.5f, y + 0.5f, image.width(),
                                             image.height(), camera);
                R
                // Distance to closest known intersection
                float distance = INFINITY;
                Colour L_o;
                // For each triangle
                for (unsigned int t = 0; t < scene.triangles.size(); ++t){
                    const Triangle& T = scene.triangles[t];
                    if (sampleRayTriangle(scene, x, y, R, T, L_o, distance)) {
                        image.set(x, y, L_o);
                    }
                }
            }
        }
}

Ray Renderer::computeEyeRay(float x, float y, int width, int height, const Camera& camera) {
    
    const float aspect = float(height)/width;
    
    float s = -2.0f * tan(camera.getFoVx() * 0.5f);
    
    const Vector& start = Vector((x/width - 0.5f)* s, -(y/height - 0.5f) * s * aspect, 1.0f) * camera.getZFar();
    
    return Ray(Point(start), Direction(start));
    
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
    // Debugging intersect: set to white on any intersection
    radiance = Colour(1, 1, 1);
    // Debugging barycentric
//    radiance = Colour(weight[0], weight[1], weight[2]) / 15;
    
    return true;
}

//void shade(const Scene& scene, const Triangle& T, const Point& P,
//           const Vector& n, const Vector& w_o, Colour& L_o) {
//    L_o = Colour(0.0f, 0.0f, 0.0f);
//    // For each direction (to a light source)
//    for (unsigned int i = 0; i < scene.lights.size(); ++i) {
//        const Light& light = scene.lights[i];
//        const Vector& offset = light.position - P;
//        const float distanceToLight = offset.length();
//        const Vector3& w_i = offset / distanceToLight;
//        if (visible(P, w_i, distanceToLight, scene)) {
//            const Radiance3& L_i = light.power / (4 * PI * square(distanceToLight));
//        } }
//}
//// Scatter the light
//L_o += L_i *
//T.bsdf(n).evaluateFiniteScatteringDensity(w_i, w_o) *
//max(0.0, dot(w_i, n));
//}
