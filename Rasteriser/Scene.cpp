//
//  Scene.cpp
//  Rasteriser
//
//  Created by Finn Petrie on 25/08/18.
//  Copyright © 2018 Finn Petrie. All rights reserved.
//

#include "Scene.hpp"


Scene::Scene(std::vector<Triangle> t, std::vector<Light> l) : triangles(t), lights(l){
    
}

std::vector<Triangle>Scene::getTriangles() const{
    return triangles;
}

std::vector<Light>Scene::getLights() const{
    return lights;
}
