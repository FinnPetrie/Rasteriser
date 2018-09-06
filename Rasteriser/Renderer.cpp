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
#include "DepthBuffer.hpp"
#include "Vector2.hpp"

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
//                    printf("t = %d", t);
                    const Triangle& T = scene.triangles[t];
                    //T.printBSDF();
                    //T.printVertices();
                    if (sampleRayTriangle(scene, x, y, R, T, L_o, distance)) {
                       // L_o.print();
                        image.set(x, y, L_o);
                        
                    }
                }
            }
        }
}

void Renderer::rasterize(Image& image, const Scene& scene, const Camera& camera){
    const int w = image.width(), h = image.height();
    DepthBuffer depthBuffer(w, h, INFINITY);
    // For each triangle
 
    for (unsigned int t = 0; t < scene.triangles.size(); ++t) {
        const Triangle& T = scene.triangles[t];
        
        /** int x0 = 0;
         int x1 = w;
         int y0 = 0;
         int y1 = h;
        */
        
        Vector2 V[3];
        int x0, y0, x1, y1;
        computeBoundingBox(T, camera, image, V, x0, y0, x1, y1);
        
         // Vertex attributes, divided by -z
         float vertexW[3];
        Vector vertexNw[3];
         Vector vertexPw[3];        for(int v = 0; v <3; ++v){
            const float w = -1.0f / T.vertex(v).mat[2];
            vertexW[v] = w;
            vertexPw[v] = T.vertex(v) * w;
            vertexNw[v] = T.normal(v) * w;
        }
    
      
        
        
        // For each pixel
        for (int y = y0; y < y1; ++y) {
            for (int x = x0; x < x1; ++x) {
                
                
                // The pixel center
                const Vector2 Q(x + 0.5f, y + 0.5f);
                // 2D Barycentric weights
                const float weight2D[3] =
                {bary2D(V[0], V[1], V[2], Q),
                    bary2D(V[1], V[2], V[0], Q),
                    bary2D(V[2], V[0], V[1], Q)};
                
                if ((weight2D[0]>0) && (weight2D[1]>0) && (weight2D[2]>0)) {
                    // Interpolate depth
                    float w = 0.0f;
                    for (int v = 0; v < 3; ++v) {
                       // printf("Our weights i: %f\n", weight2D[v]);
                        w += weight2D[v] * vertexW[v];
                    }
                    // Interpolate projective attributes, e.g., P’, n’
                    Vector Pw;
                    Vector nw;
                    for (int v = 0; v < 3; ++v) {
                        Pw = Pw + (weight2D[v] * vertexPw[v]);
                        nw = nw + (weight2D[v] * vertexNw[v]);
                    }
                    //Pw.print();
                    //nw.print();
                    // Recover interpolated 3D attributes; e.g., P’ -> P, n’ -> n
                    const Vector& P = Pw / w;
                    const Vector& n = nw / w;
                   // P.print();
                    //n.print();
                    const float depth = -P.mat[2];
                    // We could also use depth = z-axis distance: depth = -P.z
                    // Depth test
                    if (depth < depthBuffer.get(x, y)) {
                        // Shade
                        Colour  L_o;
                        const Vector& w_o = -P.direction();
                        // Make the surface normal have unit length
                        const Vector& unitN = n.direction();
                        
                        shade(scene, T, P, unitN, w_o, L_o);
                        depthBuffer.set(x, y, depth);
                        image.set(x, y, L_o);
                    }
                }
            }
        }
    }
}


Vector Renderer::perspectiveProjection(const Vector& P, int width, int height,
                           const Camera& camera) {
    // Project onto z = -1
    Vector Q((-P.mat[0] / P.mat[2]), (-P.mat[1] / P.mat[2]));
    //Q.print();
    printf("\n\n");
    const double aspect = double(height) / width;
    // Compute the side of a square at z = -1 based on our
    // horizontal left-edge-to-right-edge field of view
    const double s = -2.0f * tan(camera.getFoVx() * 0.5f);
    Q.mat[0] = width * (-Q.mat[0] / s + 0.5f);
    Q.mat[1] = height * (Q.mat[1] / (s * aspect) + 0.5f);
    //Q.print();
    return Q;
}

void Renderer::computeBoundingBox(const Triangle& T, const Camera& camera, const Image& image, Vector V[3], int& x0, int& y0, int& x1, int& y1){
    
    Vector2 high(image.width(), image.height());
    Vector2 low(0, 0);
    
    //printf("Magnitudes: low - %f, high - %f", low.magnitude(), high.magnitude());
    
    for(unsigned int v = 0; v < 3; ++v){
        const Vector& X = perspectiveProjection(T.vertices[v], image.width(), image.height(), camera);
        //printf("\n\nmag X: %f \n\n", X.magnitude());
        V[v] = X;
        if((X.mat[0] > 0 && X.mat[0] < image.width()) && (X.mat[1] > 0 && X.mat[1] < image.height() )){
            if(X.mat[0] < low.mat[0]){
                low.mat[0] = X.mat[0];
            } if(X.mat[1] < low.mat[1]) {
                low.mat[1] = X.mat[1];
            }
            if(X.mat[0] > high.mat[0]){
                high.mat[0] = X.mat[0];
            }if(X.mat[1] > high.mat[1]){
                high.mat[1] = X.mat[1];
            }
        }
        
    }
    /*if(high.max(X)) {
     //if the projection is in frame
     if((w >= X.mat[0]) && (h >= X.mat[1])){
     high = X;
     T.vertices[v].print();
     printf("Our height");
     high.print();
     }
     }if(low.min(X)) {
     //if the projection is in frame
     if((w >= X.mat[0]) && (h >= X.mat[1])){
     
     printf("Our low");
     T.vertices[v].print();
     
     low = X;
     low.print();
     }
     */
    
    
    x1 = (int)ceil(high.mat[0]);
    y1 = (int)ceil(high.mat[1]);
    x0 = (int)floor(low.mat[0]);
    y0 = (int)floor(low.mat[1]);
    
    
    
    
    
}
float Renderer::lineDistance2D(const Vector2& A, const Vector2& B, const Vector2& Q){
    const Vector2 n(A.mat[1]- B.mat[1], B.mat[0] - A.mat[0]);
    const float d = A.mat[0] * B.mat[1] - B.mat[0] * A.mat[1];
    return (n.dot(Q) + d) / n.magnitude();
}

float Renderer::bary2D(const Vector2& A, const Vector2& B, const Vector2& C, const Vector2& Q){
    return lineDistance2D(B, C, Q)/lineDistance2D(B, C, A);
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
    const Vector& q = R.getDirection().cross(e2);
    const float a = e1.dot(q);
    const Vector& s = R.getPoint() - T.vertex(0);
    const Vector& r = s.cross(e1);
//    printf("These are our vectors: \n");
//    e1.print();
//    e2.print();
//    q.print();
//    s.print();
//    r.print();

    // Barycentric vertex weights
    
    weight[1] = s.dot(q) / a;
    weight[2] = R.directionise().dot(r) / a;
    weight[0] = 1.0f - (weight[1] + weight[2]);
//    printf("%f\n", weight[1] + weight[2] + weight[0]);
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
        //printf("a hit!\n");
        return dist;
    }
}


bool Renderer::sampleRayTriangle(const Scene& scene, int x, int y, const Ray& R, const Triangle& T, Colour& radiance, float& distance) {
    
     float weight[3];
    const float d = intersect(R, T, weight);
//    printf("getting to the distance");
//    printf("\n\n\ndistance: %f", d);
     if (d >= distance) {
         return false;
         
        }
    
     // This intersection is closer than the previous one
     distance = d;
    
     // Intersection point
     const Point& P = R.getPoint() + R.getDirection() * d;
//    printf("our intersection: ");
    //P.print();
     // Find the interpolated vertex normal at the intersection
     const Vector& n = (T.normal(0) * weight[0] +
                            T.normal(1) * weight[1] +
                        T.normal(2) * weight[2]).direction();
   // printf("\nour normal: ");
    //n.print();
     const Vector& w_o = -R.directionise();
    
   shade(scene, T, P, n, w_o, radiance);
    // Debugging intersect: set to white on any intersection
   // radiance = Colour(1, 1, 1);
    //printf("woo we got a hit");
    // Debugging barycentric
    //radiance = Colour(weight[1], weight[0], weight[2]);
    
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
        if (visible(intersection, w_i, distanceToLight, scene)) {
            const Colour& L_i = light.getEmittance() / (4 * M_PI * distanceToLight*distanceToLight);
           // L_i.print();
           // printf("Are we making it in here?");
// Scatter the light
            //T.setBSDF(n);
            //T.printBSDF();
            const Colour& bs = T.bsdf.evaluateFiniteScatteringDensity(w_i, w_o, n);
            const Colour& cool = L_i*bs;
           //cool.print();
            //column.print();
            
            //printf("%f our check <<__\n\n", check);
            L_o = L_o +=  cool * std::max(0.0, w_i.dot(n)); //max(0.0, w_i.dot(n));
           // printf("\n\nL_o in the shade routine:");
           // L_o.print();
           // printf("\n\n");
        }
    }
}

void Renderer::makeOneTriangleScene(Scene& s){
    Vector vertices[3];
    vertices[0] = Vector(0, 1, -2);
    vertices[1] = Vector(-1.9, -1, -2);
    vertices[2] = Vector(1.6, -0.5, -2);
    Vector normals[3];
    normals[0] = Vector(0, 0.6, 1).direction();
    normals[1] = Vector(-0.4, -0.4, 1.0).direction();
    normals[2] = Vector(0.4, -0.4, 1.0).direction();
    BSDF green(Colour(0.8, 0, 0), Colour(0.2, 0.2, 0.2), 100);
    
    Triangle t(vertices, normals, green);
    
    s.triangles.push_back(t);
}

void Renderer::makeTrianglePlusGroundScene(Scene& s){
    makeOneTriangleScene(s);
    
    Vector vertices[3];
    vertices[0] = Vector(-1.9, -1, -2);
    vertices[1] = Vector(0, 1, -2);
    vertices[2] = Vector(1.6, -0.5, -2);
    Vector normals[3];
    normals[0] = Vector(-0.4, -0.4, 1.0).direction();
    normals[1] = Vector(0, 0.6, 1).direction();
    normals[2] = Vector(0.4, -0.4, 1.0).direction();
    BSDF green(Colour(0.8,0,0), Colour(0.2, 0.2, 0.2), 100);
    Triangle triOne(vertices, normals, green);
    
    s.triangles.push_back(triOne);
    
    const float groundY = -1.0;
    const Colour groundColour = Colour(0.8, 0.8, 0.8);
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
    
    s.triangles.push_back(groundOne);
    
    Vector verticesGroundTwo[3];
    verticesGroundTwo[0] = Vector(-10, groundY, -10);
    verticesGroundTwo[1] = Vector(10, groundY, -0.01);
    verticesGroundTwo[2] = Vector(-10, groundY, -10);
    Triangle groundWound(verticesGroundTwo, normalsGround, grey);
    s.triangles.push_back(groundWound);

}

bool Renderer::visible(const Vector& P, const Vector& direction, float distance, const Scene& scene){
    static const double rayBumpEpsilon = 1e-4;
   // Vector point(P.mat[0], P.mat[1], P.mat[2]);
    const Ray ShadowRay(P+ direction *rayBumpEpsilon, direction);
    
    distance -= rayBumpEpsilon;
    
    //test each potential shadow caster to see if it lies betweem P ad the light.
    float ignore[3];
    for(unsigned int s = 0; s < scene.getTriangles().size(); ++s){
        if(intersect(ShadowRay, scene.getTriangles()[s], ignore) < distance){
          //  printf("false intersection");
            return false;
        }
    }
    return true;
}
