#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <time.h>

using namespace std;


// An object describing the shape of a matrix an M * N matrix has s.m = M, s.n = N

struct Shape
{
    int m;
    int n;

    bool operator==(const Shape &rhs) {return m == rhs.m && n == rhs.n;}
};


class Matrix
{
    private:
        Shape s;
        float* data;

    public:
        // Constructors
        Matrix();
        Matrix(int m, int n, float fill = 0);
        Matrix(int m, int n, float * d);
        Matrix(Shape s, float fill = 0);
        Matrix(const Matrix &other);
        ~Matrix();

        // Operators
        Matrix operator+=(const Matrix &rhs);
        Matrix operator-=(Matrix rhs);
        Matrix operator- ();
        Matrix operator*= (const Matrix &rhs);
        Matrix operator*= (const float &rhs);
        Matrix operator= (Matrix rhs);
        virtual float * operator[](int i);
        
        friend ofstream & operator<<(ofstream & os, const Matrix & rhs);

        // Member functions
        void print();
        int size() const;
        float getVal(int i, int j) const;
        Shape shape() const;
        int m() const {return s.m;}
        int n() const {return s.n;}
        float absMax() const;
        Shape absMaxIndex();
        Matrix hadProd(const Matrix & lhs);
        Matrix T() const;

    friend Matrix matFromString(string str);
};

// Free functions

Matrix operator* (Matrix lhs, const Matrix &rhs);
Matrix operator+ (Matrix lhs, const Matrix &rhs);
Matrix operator- (Matrix lhs, const Matrix &rhs);
Matrix operator* (Matrix lhs, const float &rhs);

Matrix rand(int M, int N, float min = 0, float max = 1);
// String fromat: m n data, where data is tab separated
Matrix matFromString(string str);
