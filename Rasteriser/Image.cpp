//
//  Image.cpp
//  Rasteriser
//
//  Created by Finn Petrie on 23/08/18.
//  Copyright © 2018 Finn Petrie. All rights reserved.
//

#include "Image.hpp"

Image::Image(int width, int height) : m_width(width), m_height(height), m_data(width*height){}

int Image::width() const{
    return m_width;
}

int Image::height() const{
    return m_height;
}

void Image::set(int x, int y, const Colour &value){
    m_data[x+y * m_width] = value;
}

const Colour& Image::get(int x, int y) const{
    return m_data[x + y * m_width];
}

void Image::save(const std::string& filename, float displayConstant) const{
    FILE* file = fopen(filename.c_str(), "wt");
    fprintf(file, "P3 %d %d 255\n", m_width, m_height);
    printf("Saving image\n");
    for(int y = 0; y < m_height; ++y){
        fprintf(file, "\n# y = %d\n", y);
        for(int x = 0; x < m_width; ++x){
            const Colour c(get(x,y));
//            printf("in our inner loop\n");
            fprintf(file, "%d %d %d\n", PPMGammaEncode(c.mat[0], displayConstant),
                    PPMGammaEncode(c.mat[1], displayConstant), PPMGammaEncode(c.mat[2],
                        displayConstant));
        }
    }
    fclose(file);
}


int Image::PPMGammaEncode(float radiance, float displayConstant) const{
    return int(pow(std::min(1.0f, std::max(0.0f, radiance * displayConstant)), 1.0f/2.2f) * 255.0f);
}

    
    
