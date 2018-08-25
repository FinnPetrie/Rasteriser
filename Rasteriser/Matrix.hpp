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
    public:
    size_t rows, columns;
    std::vector<double> mat;
    
    
    virtual void print();
    Matrix();
    Matrix(size_t s);
    Matrix(size_t r, size_t c);
    Matrix(size_t r, size_t c, double x, double y, double z);
    Matrix(size_t r, size_t c, double x, double y, double z, double w);
    Matrix(const Matrix& n);
    Matrix(std::vector<double> data_);
    size_t getRepresentation(int i, int j) const;
    size_t getRows() const;
    size_t getColumns() const;
    virtual double getElement(int i, int j);
    virtual double getElement(int i) const;
    void diagonalise(std::vector<double> data);
   
    
};

Matrix operator*( const Matrix& lhs, const Matrix &rhs);
Matrix operator+(const Matrix& lhs, const Matrix &rhs);
Matrix operator-(const Matrix& lhs, const Matrix& rhs);
Matrix operator*(const Matrix& n, double S);


#endif /* Matrix_h */
