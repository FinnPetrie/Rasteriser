//
//  DepthBuffer.cpp
//  Rasteriser
//
//  Created by Finn Petrie on 2/09/18.
//  Copyright © 2018 Finn Petrie. All rights reserved.
//

#include "DepthBuffer.hpp"
#include <algorithm>
DepthBuffer::DepthBuffer(int width, int height, double n) : m_width(width), m_height(height), m_data(width*height){
    std::fill(m_data.begin(),m_data.end(), n);
}

int DepthBuffer::width() const{
    return m_width;
}

int DepthBuffer::height() const{
    return m_height;
}

void DepthBuffer::set(int x, int y, const double value){
    m_data[x+y * m_width] = value;
    printf("value = %f", m_data[x+y * m_width]);
}

const double DepthBuffer::get(int x, int y) const{
    return m_data[x + y * m_width];
}




