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
    Layer * current(net.output);
    Layer * last(current->getLast());
    // ! something goes wrong here
    last->getLast();
    cout << 1;
    delta[l - 1 + l] = dC(current->a(), current->z());
    for (int i = l - 1 + l - 1; i > l; i--)
    {
        cout << 2;
        // delta[i] = df(current->z()).HadProd(next->w().T() * delta[i + 1]);
        current = last;
        cout << 3;
        // last = last->getLast();
    }

    // Layer * last(net.input);
    // for (int i = 1; i < l; i++)
    // {
    //     cout << 5;
    //     delta[i] = last->a() * delta[i];
    //     cout << 6;
    //     last = last->getNext();
    // }
    
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
