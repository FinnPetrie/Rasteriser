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

Scene::Scene(std::vector<Triangle> t, Light l): triangles(t), light(l){
    
}

std::vector<Triangle>Scene::getTriangles() const{
    return triangles;
}

std::vector<Light>Scene::getLights() const{
    return lights;
}


void Scene::printTriangles() const{
    for(int i = 0; i < triangles.size(); ++i){
        triangles[i].printVertices();
    }
}

void Scene::printLights() const{
    light.print();
}
