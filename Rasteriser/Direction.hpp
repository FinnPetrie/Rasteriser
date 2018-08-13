//
//  Direction.hpp
//  Rasteriser
//
//  Created by Finn Petrie on 8/08/18.
//  Copyright © 2018 Finn Petrie. All rights reserved.
//

#ifndef Direction_hpp
#define Direction_hpp

#include <stdio.h>
#include "Vector.hpp"
class Direction: public Vector{
    private:
    static constexpr double w = 0.0;
    public:
    Direction(double x, double y, double z);
};

#endif /* Direction_hpp */
