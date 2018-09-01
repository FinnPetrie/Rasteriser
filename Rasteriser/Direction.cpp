//
//  Direction.cpp
//  Rasteriser
//
//  Created by Finn Petrie on 8/08/18.
//  Copyright © 2018 Finn Petrie. All rights reserved.
//

#include "Direction.hpp"

Direction::Direction(double x, double y, double z) : Vector(4, x, y, z, 0){

}

Direction::Direction() : Vector(4, 0, 0, 0, 0){

}

Direction::Direction(Vector v): Vector(v, 0){
    
}
