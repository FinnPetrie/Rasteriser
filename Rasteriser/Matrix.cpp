//
//  Matrix.cpp
//  Rasteriser
//
//  Created by Finn Petrie on 7/08/18.
//  Copyright © 2018 Finn Petrie. All rights reserved.
//

#include <stdio.h>
#include "Matrix.hpp"
#include <assert.h>
Matrix::Matrix(size_t square): rows(square), columns(square), mat(rows*columns, {}){
    
}

Matrix::Matrix(size_t r, size_t c) : rows(r), columns(c), mat(rows*columns, {}){
}


//incorrect, quick hack - this sorta presumes the functionality of a vector in the matrix class-
//high coupling. Sort this out.
Matrix::Matrix(size_t r, size_t c, double x, double y, double z): rows(r), columns(c), mat(rows*columns) {
    mat = {x, y, z};
}

/** an implementation of homogenous coordinates -- could do this better, look into it*/
Matrix::Matrix(size_t r, size_t c, double x, double y, double z, double w): rows(r), columns(c), mat(rows*columns) {
    mat = {x, y, z, w};
   }

void Matrix::print(){
    for(size_t i = 0; i < rows*columns; ++i){
        if(i%columns == 0){
            printf("\n");
        }
        printf("%f  ", mat[i]);
      
    }
}
size_t Matrix::getRepresentation(int i, int j){
    return i*columns + j;
}
double Matrix::getElement(int i, int j){
    return mat[getRepresentation(i, j)];
}

  Matrix Matrix::operator*(const Matrix& n){
    assert(columns == n.rows);
     printf("Here\n");
    Matrix A(rows, n.columns);
     double sum;
        for(int i = 0; i < A.rows; ++i){
            for(int j = 0; j < A.columns; ++j){
                sum = 0.0;
                printf("In the jth loop");
                for(int p = 0; p < columns; p++){
                    sum += mat[getRepresentation(i, j)] * n.mat[getRepresentation(j, i)];
                }
            A.mat.push_back(sum);
            }
        }
     printf("We get out\n");
     return A;
}


Matrix Matrix::operator+(Matrix& n){
    assert(columns == n.columns && rows == n.rows);
    Matrix A(rows);
    for(int i = 0; i < rows; ++i){
        for(int j = 0; j < columns; ++j){
            A.mat[getRepresentation(i, j)] = mat[getRepresentation(i, j)] + n.mat[getRepresentation(i, j)];
        }
    }
    return A;
}
/**could do better - could write a scalar multiplication function which inverts all elements of n's matrix and use the
operator+ with the reference of n inverted. Using the A - B = A + (-B) result*/
Matrix Matrix::operator-(Matrix &n){
    assert(columns == n.columns && rows == n.rows);
    Matrix A(rows);
    for(int i = 0; i < rows; ++i){
        for(int j = 0; j < columns; ++j){
            A.mat[getRepresentation(i, j)] = mat[getRepresentation(i, j)] - n.mat[getRepresentation(i, j)];
        }
    }
    return A;
}

Matrix Matrix::operator*(double S){
    Matrix A = *this;
    for(int i = 0; i < rows*columns;  ++i){
        mat[i] *= S;
    }
    return A;
}
