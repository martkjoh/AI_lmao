#include "../header/BackProp.h"

DelVec::DelVec(NeuralNet & net) : L{net.L}, l{net.l}
{
    db.push_back(new Matrix(L[0], L[0]));
    dw.push_back(new Matrix(L[0], 1));
    for (int i = 1; i < l; i++)
    {
        db.push_back(new Matrix(L[i - 1], L[i]));
        dw.push_back(new Matrix(L[i], 1)); 
    }
}

DelVec::~DelVec()
{
    for (int i = 0; i < l; i++)
    {
        delete db[i];
        delete dw[i];
    }
}

Matrix DelVec::getVal(int i) const
{
    if (i < l)
        return * db[i];
    else
        return * dw[i - l];
}     


Matrix DelVec::operator[](int i) 
{
    if (i < l)
        return * db[i];
    else
        return * dw[i - l];
} 

DelVec DelVec::operator+= (const DelVec & rhs)
{
    for (int i = 1; i < l; i++)
    {
        (*this)[i] += rhs.getVal(i);
    }
    return *this;
}

DelVec DelVec::operator*= (const float & rhs)
{
    for (int i = 1; i < l; i++)
    {
        (*this)[i] *= rhs;
    }
    return *this;
}

// Class Del

float Del::C(Matrix a, Matrix y)
{
    Matrix d = a - y;
    return (d *d)[0][0] * (1 / d.m());
}

Matrix Del::dC(Matrix a, Matrix y)
{
    Matrix d = a - y;
    return d * (2 / d.m());
}


DelVec Del::backProp(NeuralNet & net, Matrix * y) 
{
    DelVec delta = DelVec(net);
    Layer * current(net.output);
    Layer * next;
    delta[l - 1 + l] = dC(current->a(), current->z()).hadProd(df(current->z()));
    for (int i = l - 1 + l - 1; i > l; i--)
    {
        next = current;
        current = current->getLast();
        delta[i] = df(current->z()).hadProd(next->w().T() * delta[i + 1]);
    }

    current = net.input;
    for (int i = 1; i < l; i++)
    {
        delta[i] = delta[i + l] * current->a().T();
        current = current->getNext();
    }
    
    return delta;
}

void Del::avBackProp(NeuralNet & net, vector<Matrix *> x, vector<Matrix *> y)
{
    int n = x.size();
    for (int i = 0; i < n; i++)
    {
        net.activate(*x[i]);
        DelVec del = backProp(net, y[i]);
        delC += del; 
    }
    delC *= 1 / n;
}

void Del::adjustWeights(NeuralNet & net)
{
    Layer * current = net.output;
    for (int i = 1; i < l; i++)
    {
        current->biases -= delC[i];
        current->weights -= delC[l + i]; 
    }
}


void Del::train(NeuralNet & net, vector<Matrix *> x, vector<Matrix *> y, int m)
{
    int n = x.size();
    auto xIt = x.begin();
    auto yIt = y.begin();
    for (int i = 0; i < n % m; i++)
    {
        reset();
        vector<Matrix *> xSlice = vector<Matrix *>(xIt + i * m, xIt + (i +1) * m);  
        vector<Matrix *> ySlice = vector<Matrix *>(yIt + i * m, yIt + (i +1) * m);
        avBackProp(net, xSlice, ySlice);
    }
}

float Del::test(NeuralNet & net, vector<Matrix *> x, vector<Matrix *> y)
{
    int n = x.size();
    float s = 0;
    for (int i = 0; i < n; i++)
    {
        net.activate(*x[i]);
        s += C(net.getOutput(), y[i]);
    }
    return s / (n * 1.);
}