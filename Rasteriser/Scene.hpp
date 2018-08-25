//
//  Scene.hpp
//  Rasteriser
//
//  Created by Finn Petrie on 25/08/18.
//  Copyright © 2018 Finn Petrie. All rights reserved.
//

#ifndef Scene_hpp
#define Scene_hpp

#include <stdio.h>
#include <vector>
#include "Light.hpp"
#include "Triangle.hpp"




class Scene{
private: std::vector<Triangle> triangles;
    std::vector<Light> lights;
public:
    
    Scene();
    Scene(std::vector<Triangle> t, std::vector<Light> l);
    std::vector<Triangle> getTriangles() const;
    std::vector<Light> getLights() const;
};
#endif /* Scene_hpp */
