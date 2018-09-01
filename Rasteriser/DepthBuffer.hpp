//
//  DepthBuffer.hpp
//  Rasteriser
//
//  Created by Finn Petrie on 2/09/18.
//  Copyright © 2018 Finn Petrie. All rights reserved.
//

#ifndef DepthBuffer_hpp
#define DepthBuffer_hpp

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
class DepthBuffer{
private:
int m_width;
int m_height;
std::vector<double> m_data;


public:
DepthBuffer(int width, int height, double n);
int width() const;
int height() const;
void set(int x, int y, const double value);
const double get(int x, int y) const;
};
#endif /* DepthBuffer_hpp */
