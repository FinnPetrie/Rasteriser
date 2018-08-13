//
//  Matrix.hpp
//  Rasteriser
//
//  Created by Finn Petrie on 7/08/18.
//  Copyright © 2018 Finn Petrie. All rights reserved.
//

#ifndef Matrix_h
#define Matrix_h
#include <vector>

class Matrix{
    protected:
    size_t rows, columns;
    std::vector<double> mat;
    public:
    virtual void print();
    Matrix(size_t s);
    Matrix(size_t r, size_t c);
    Matrix(size_t r, size_t c, double x, double y, double z);
    Matrix(size_t r, size_t c, double x, double y, double z, double w);
    Matrix(std::vector<double> data_);
    size_t getRepresentation(int i, int j);
    virtual double getElement(int i, int j);
    
    Matrix operator*(const Matrix& n);
    Matrix operator+(Matrix& n);
    Matrix operator-(Matrix& m);
    Matrix operator*(double S);
    
};


#endif /* Matrix_h */
