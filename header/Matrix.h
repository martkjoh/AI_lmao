#include <iostream>
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
        Matrix(Shape s, float fill = 0);
        Matrix(int m, int n, float fill = 0);
        Matrix(int m, int n, float * d);
        Matrix();
        Matrix(const Matrix &other);
        ~Matrix();

        Matrix operator+=(const Matrix &rhs);
        Matrix operator-=(Matrix rhs);
        Matrix operator- ();
        Matrix operator*= (const Matrix &rhs);
        Matrix operator= (Matrix rhs);
        virtual float * operator[](int i);


        void print();
        int size();
        float getVal(int i, int j) const;
        Shape shape() const;
        int m() {return s.m;}
        int n() {return s.n;}
        float absMax() const;
        int getInt(int i, int j = 0) {return (int)getVal(i, j);}
        Matrix T() const;
};

// Opperators and functions to use on Matrices

Matrix operator* (Matrix lhs, const Matrix &rhs);
Matrix operator+ (Matrix lhs, const Matrix &rhs);
Matrix operator- (Matrix lhs, const Matrix &rhs);

Matrix rand(int M, int N, float min = 0, float max = 1);