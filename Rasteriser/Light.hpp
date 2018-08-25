//
//  Light.hpp
//  Rasteriser
//
//  Created by Finn Petrie on 25/08/18.
//  Copyright © 2018 Finn Petrie. All rights reserved.
//

#ifndef Light_hpp
#define Light_hpp

#include <stdio.h>
#include "Point.hpp"
#include "Colour.hpp"

#endif /* Light_hpp */

class Light{
private:
    Point location;
    Colour emittance;
    
public:
    
    Light();
    Light(Point l, Colour c);
};
