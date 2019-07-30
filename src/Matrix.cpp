#include "../header/Matrix.h"


// Constructors
// 
// Different constructors for the Matrix class, as well as the destructor

Matrix::Matrix() : Matrix(0, 0) {}
Matrix::Matrix(int m, int n, float fill) : Matrix(Shape{m, n}, fill) {}
Matrix::Matrix(int m, int n, float * d) : s{m, n}, data{new float[s.n * s.m]} 
{
    if (n == 0 || m == 0){s.m = 0; s.n = 0;}
    for (int i = 0; i < size(); i++){data[i] = d[i];}
}
Matrix::Matrix(Shape s, float fill) : s{s},  data{new float[s.n * s.m]}
{
    if (s.n == 0 || s.m == 0){s.m = 0;s.n = 0;}
    for (int i = 0; i < size(); i++) {data[i] = fill;}
}
Matrix::Matrix(const Matrix &other) : s{other.s}, data{new float[s.n * s.m]}
{
    if (s.n == 0 || s.m == 0){s.m = 0;s.n = 0;}
    for (int i = 0; i < size(); i++) {data[i] = other.data[i];}
}

Matrix::~Matrix() {delete[] data;}


// Operators
// 
// Operators for manipulating matrices

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
    s = rhs.s; 
    swap(rhs.data, data);
    return *this;
}

float * Matrix::operator[](int i) {return &data[s.n * i];}

ofstream& operator<<(ofstream & os, const Matrix & rhs)
{
    os << rhs.m() << " " << rhs.n() << "\t";
    for (int i = 0; i < rhs.size(); i++)
    {
        os << rhs.data[i] << "\t";
    }
    os << "\n";
    return os;
}


// Member functions
// 
// Member functions for the matrix class

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

int Matrix::size() const {return s.m * s.n;}
float Matrix::getVal(int i, int j) const {return data[j + s.n * i];}
Shape Matrix::shape() const {return s;}

// returns a array of the index of the larges elemet by absolute value
Shape Matrix::absMaxIndex()
{
    Shape index{0, 0};
    float max = 0;
    for (int i = 0; i < s.m; i++)
    {
        for (int j = 0; j < s.n; j++)
        {
            if (max < abs(getVal(i, j)))
            {
                max = abs(getVal(i, j));
                index.m = i;
                index.n = j;
            }
        }
    }
    return index;
}

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
    Matrix T(s.n, s.m);
    for (int i = 0; i < s.m; i++)
    {
        for (int j = 0; j < s.n; j++)
        {
            T[j][i] = getVal(i, j);
        }
    }
    return T;
}


// Free fucntions
// 
// Functions defined outside the Matrix class to use with matrices


// Opperators to use on Matrices

Matrix operator* (Matrix lhs, const Matrix &rhs) {return lhs *= rhs;}
Matrix operator+ (Matrix lhs, const Matrix &rhs) {return lhs += rhs;}
Matrix operator- (Matrix lhs, const Matrix &rhs) {return lhs -= rhs;}
Matrix operator* (Matrix lhs, const float &rhs) {return lhs *= rhs;}


// Helper functions for matrices

Matrix rand(int M, int N, float min, float max)
{
    Matrix A(M, N);
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++) 
        {
            A[i][j] = ((float)rand() / RAND_MAX) * (max - min) + min;
        }
    }
    return A;
}

Matrix matFromString(string str)
{
    string tmp;
    stringstream ss(str);
    ss >> tmp;
    int m = stoi(tmp);
    ss >> tmp;
    int n = stoi(tmp);
    float data[m * n];
    for (int i = 0; i < m * n; i++)
    {
        ss >> tmp;
        data[i] = stof(tmp);
    }
    Matrix M(m, n, data);
    return M;
}
