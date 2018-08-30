//
//  Renderer.hpp
//  Rasteriser
//
//  Created by Finn Petrie on 25/08/18.
//  Copyright © 2018 Finn Petrie. All rights reserved.
//

#ifndef Renderer_hpp
#define Renderer_hpp

#include <stdio.h>
#include "Scene.hpp"
#include "Image.hpp"
#include "Camera.hpp"
#include "Ray.hpp"

class Renderer{
public:
    Renderer();
    void rayTrace(Image& image, const Scene& scene, const Camera& camera, int x0, int x1, int y0, int y1);
    Ray computeEyeRay(float x, float y, int width, int height, const Camera& camera);
    float intersect(const Ray& R, const Triangle& T, float weight[3]);
    bool sampleRayTriangle(const Scene& scene, int x, int y, const Ray& R, const Triangle& T, Colour& radiance, float& distance);
};
#endif /* Renderer_hpp */

