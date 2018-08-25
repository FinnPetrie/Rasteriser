//
//  Image.hpp
//  Rasteriser
//
//  Created by Finn Petrie on 23/08/18.
//  Copyright © 2018 Finn Petrie. All rights reserved.
//

#ifndef Image_hpp
#define Image_hpp

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "Colour.hpp"
#include <functional>
#include <cmath>


#endif /* Image_hpp */

class Image{
    
private:
    int m_width;
    int m_height;
    std::vector<Colour> m_data;
    
    int PPMGammaEncode(float radiance, float displayConstant) const;
    
public:
    Image(int width, int height);
    int width() const;
    int height() const;
    void set(int x, int y, const Colour& value);
    const Colour& get(int x, int y) const;
    void save(const std::string& filename, float displatConstat = 15.0f) const;
};
