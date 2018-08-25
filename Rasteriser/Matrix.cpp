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
Matrix::Matrix(){
    Matrix::Matrix(4);
}
Matrix::Matrix(size_t square): rows(square), columns(square), mat(rows*columns, {}){
    printf("squre initialiser");
}

Matrix::Matrix(size_t r, size_t c) : rows(r), columns(c), mat(rows*columns, {}){
}



//incorrect, quick hack - this sorta presumes the functionality of a vector in the matrix class-
//high coupling. Sort this out.
Matrix::Matrix(size_t r, size_t c, double x, double y, double z): rows(r), columns(c), mat(rows*columns) {
    mat = {x, y, z};
}

Matrix::Matrix(const Matrix &n): mat(n.mat), rows(n.rows), columns(n.columns){

}
/** an implementation of homogenous coordinates -- could do this better, look into it*/
Matrix::Matrix(size_t r, size_t c, double x, double y, double z, double w): rows(r), columns(c), mat(rows*columns) {
    mat = {x, y, z, w};
   }

void Matrix::diagonalise(std::vector<double> data){
    assert((data.size() * data.size()) == rows*columns);
    printf("Data sizze: %f", data.size());
    printf("data columns, data rows, %f %f\n", rows, columns);
    for(int i = 0; i < data.size(); ++i){
        printf("Representation: %d", getRepresentation(i, i));
        mat[getRepresentation(i,i)] = data[i];
    }
}


void Matrix::print(){
    for(size_t i = 0; i < rows*columns; ++i){
        if(i%columns == 0){
            printf("\n");
        }
        printf("%f  ", mat[i]);
      
    }
}
size_t Matrix::getRepresentation(int i, int j) const{
    return i*columns + j;
}


double Matrix::getElement(int i, int j){
    return mat[getRepresentation(i, j)];
}

 double Matrix::getElement(int i) const{
    return mat[i];
}

size_t Matrix::getColumns() const{
    return columns;
}

size_t Matrix::getRows() const{
    return rows;
}
//fix this
  Matrix operator*( const Matrix& lhs, const Matrix& rhs){
    assert(lhs.getColumns() == rhs.getRows());
     printf("Here\n");
    Matrix A(lhs.getRows(), rhs.getColumns());
//      A.print();
        for(int i = 0; i < lhs.getRows(); ++i){
            for(int j = 0; j < rhs.getColumns(); ++j){
                printf("In the jth loop");
                for(int p = 0; p < rhs.getColumns(); p++){
                    A.mat[A.getRepresentation(i, p)] += lhs.mat[lhs.getRepresentation(i, j)] * rhs.mat[rhs.getRepresentation(j, p)];
                }
            }
        }
     printf("We get out\n");
     return A;
}


Matrix operator+(const Matrix &lhs, const Matrix& rhs){
    assert(lhs.columns == rhs.columns && lhs.rows == rhs.rows);
    Matrix A(rhs.rows);
    for(int i = 0; i < lhs.rows; ++i){
        for(int j = 0; j < lhs.columns; ++j){
            A.mat[A.getRepresentation(i, j)] = lhs.mat[lhs.getRepresentation(i, j)] + rhs.mat[rhs.getRepresentation(i, j)];
        }
    }
    return A;
}
/**could do better - could write a scalar multiplication function which inverts all elements of n's matrix and use the
operator+ with the reference of n inverted. Using the A - B = A + (-B) result*/
Matrix operator-(const Matrix& lhs, const Matrix &rhs){
    assert(lhs.columns == rhs.columns && lhs.rows == rhs.rows);
    Matrix A(lhs.rows);
    for(int i = 0; i < lhs.rows; ++i){
        for(int j = 0; j < rhs.columns; ++j){
            A.mat[A.getRepresentation(i, j)] = lhs.mat[lhs.getRepresentation(i, j)] - rhs.mat[rhs.getRepresentation(i, j)];
        }
    }
    
    return A;
}

Matrix operator*(const Matrix &n, double S){
    Matrix A(n);
    for(int i = 0; i < n.rows*n.columns;  ++i){
        A.mat[i] *= S;
    }
    return A;
}
