#include "../header/BackProp.h"

DelVec::DelVec(NeuralNet & net) : L{net.L}, l{net.l}
{
    vec[0] = new Matrix(0, 0);
    vec[l] = new Matrix(0, 0);
    for (int i = 1; i < l; i++)
    {
        vec[i] = new Matrix(L[i - 1], L[i]);
        vec[i + l] = new Matrix(L[i], 0); 
    }
}

DelVec::~DelVec()
{
    for (int i = 0; i < l; i++)
    {
        delete vec[i];
        delete vec[i + l];
    }
}


// Class Del

Matrix Del::C(Matrix a, Matrix y)
{
    Matrix d = a - y;
    return (d.HadProd(d)) * (1 / d.m());
}

Matrix Del::dC(Matrix a, Matrix y)
{
    Matrix d = a - y;
    return d * (2 / d.m());
}


DelVec Del::backProp(NeuralNet & net, Matrix * y) 
{
    DelVec delta = DelVec(net);
    delta[l] = dC(net.output->getVals(), *y);

    return delta;
}

void Del::avBackProp(NeuralNet & net, vector<Matrix *> data, vector<Matrix *> y)
{
    int n = data.size();
    for (int i = 0; i < n; i++)
    {
        net.activate(*data[0]);
        DelVec del = backProp(net, y[i]);
        addDel(delC, del); 

    }
}

void Del::addDel(DelVec & delR, DelVec & delL)
{
    for (int i = 1; i < delR.l; i++)
    {
        delR[i] += delL[i];
    }
}
