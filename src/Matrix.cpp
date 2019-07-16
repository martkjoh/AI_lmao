#include "../header/Matrix.h"

Matrix::Matrix(int m, int n, float fill) : Matrix{Shape{m, n}, fill} {}
Matrix::Matrix(int m, int n, float * d) : s{m, n}, data{new float[s.n * s.m]} 
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            data[i * n + j] = d[i * n + j];
        }
    }
}

Matrix::Matrix() : Matrix(0, 0) {}
Matrix::Matrix(Shape s, float fill) : s{s},  data{new float[s.n * s.m]}
    {for (int i = 0; i < size(); i++) {data[i] = fill;}}
Matrix::Matrix(const Matrix &other) : s{other.s}, data{new float[s.n * s.m]}
    {for (int i = 0; i < size(); i++) {data[i] = other.data[i];}}

Matrix::~Matrix() {delete[] data;}

float * Matrix::operator[](int i) {return &data[s.n * i];}

Matrix Matrix::operator*=(const Matrix &rhs)
{
    if (this->s.n != rhs.s.m) 
    {
        cout << "incompatible dimensions, mat mul" << endl;
        throw 1;
    }

    Matrix A(this->s.m, rhs.s.n);
    float s;
    for (int i = 0; i < this->s.m; i++)
    {
        for (int j = 0; j < rhs.s.n; j++)
        {
            s = 0;
            for (int k = 0; k < this->s.n; k++) 
            {
                s += this->getVal(i, k) * rhs.getVal(k, j);
            }
            A[i][j] = s;
        }
    }
    return A;
}

Matrix Matrix::operator*=(const float &rhs)
{
    for (int i = 0; i < this->s.m; i++)
    {
        for (int j = 0; j < this->s.n; j++)
        {
            data[j + s.n * i] *= rhs;
        }
    }
    return *this;
}


Matrix Matrix::operator+= (const Matrix &rhs)
{
    if (!(this->shape() == rhs.shape()))
    {
        cout << "incompatible dimensions, addition" << endl;
        throw 1;
    }

    for (int i = 0; i < s.m; i++)
    {
        for (int j = 0; j < s.n; j++) {(*this)[i][j] += rhs.getVal(i, j);}
    }
    return *this;
}

Matrix Matrix::operator-=(Matrix rhs)
{
    return (*this) += -rhs;
}

Matrix Matrix::operator- ()
{
    for (int i = 0; i < size(); i++)
    {
        data[i] = -data[i];
    }
    return *this;
}

Matrix Matrix::operator= (Matrix rhs)
{
    swap(rhs.data, data);
    return *this;
}


void Matrix::print()
{
    for (int i = 0; i < s.m; i++)
    {
        for (int j = 0; j < s.n; j++)
        {
            cout << setw(7) << left << setprecision(5) << (*this)[i][j] << " ";
        }
        cout << "\n";
    }
    cout << endl;
}

int Matrix::size() {return s.m * s.n;}
float Matrix::getVal(int i, int j) const {return data[j + s.n * i];}
Shape Matrix::shape() const {return s;}

Matrix Matrix::hadProd(const Matrix & rhs)
{
    if (!(this->shape() == rhs.shape()))
    {
        cout << "incompatible dimensions, hadProd" << endl;
        throw 1;
    }

    for (int i = 0; i < s.m; i++)
    {
        for (int j = 0; j < s.n; j++)
        {
            data[j + s.n * i] *= rhs.getVal(i, j);
        }
    }
    return *this;
}


Matrix Matrix::T() const
{
    Matrix T{s.n, s.m};
    for (int i = 0; i < s.m; i++)
    {
        for (int j = 0; j < s.n; j++)
        {
            T[j][i] = getVal(i, j);
        }
    }
    return T;
}


// Opperators to use on Matrices

Matrix operator* (Matrix lhs, const Matrix &rhs) {return lhs *= rhs;}
Matrix operator+ (Matrix lhs, const Matrix &rhs) {return lhs += rhs;}
Matrix operator- (Matrix lhs, const Matrix &rhs) {return lhs -= rhs;}
Matrix operator* (Matrix lhs, const float &rhs) {return lhs *= rhs;}



// Helper functions for matrices

Matrix rand(int M, int N, float min, float max)
{
    Matrix A{M, N};
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++) 
        {
            A[i][j] = ((float)rand() / RAND_MAX) * (max - min) + min;
        }
    }
    return A;
}
