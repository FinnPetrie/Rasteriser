//
//  Camera.hpp
//  Rasteriser
//
//  Created by Finn Petrie on 13/08/18.
//  Copyright © 2018 Finn Petrie. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include <stdio.h>
#include "Point.hpp"
#include "Direction.hpp"
class Camera{
    
    Matrix MVP;
    Matrix Perspective;
    Point position;
    Vector bases[3];
    Vector AB;
    Vector A, B, C;
    Camera(Direction look, Direction vUP,  );
    
};
#endif /* Camera_hpp */
