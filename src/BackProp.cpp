#include "../header/BackProp.h"

DelVec::DelVec(NeuralNet & net) : L{net.L}, l{net.l}
{
    dw.push_back(new Matrix(L[0], L[0]));
    db.push_back(new Matrix(L[0], 1));
    for (int i = 1; i < l; i++)
    {
        dw.push_back(new Matrix(L[i], L[i - 1]));
        db.push_back(new Matrix(L[i], 1)); 
    }
}

DelVec::DelVec(const DelVec & rhs)
{
    l = rhs.l;
    for (int i = 0; i < l; i++)
        L[i] = rhs.L[i];
    for (int i = 0; i < l; i++)
    {
        dw.push_back(new Matrix(L[i], L[i - 1]));
        db.push_back(new Matrix(L[i], 1));
        *dw[i] = *rhs.dw[i];
        *db[i] = *rhs.db[i];
    }
}

DelVec::~DelVec()
{
    for (int i = 0; i < l; i++)
    {
        delete dw[i];
        delete db[i];
    }
}

Matrix DelVec::getVal(int i) const
{
    if (i < l)
        return * dw[i];
    else
        return * db[i - l];
}     


Matrix * DelVec::operator[](int i) 
{
    if (i < l)
        return dw[i];
    else
        return db[i - l];
} 

void DelVec::operator+= (const DelVec & rhs)
{
    for (int i = 1; i < l; i++)
    {
        *db[i] += *(rhs.db[i]);
        *dw[i] += *(rhs.dw[i]);
    }
}

void DelVec::operator*= (const float & rhs)
{
    for (int i = 1; i < l; i++)
    {
        *db[i] *= rhs;
        *dw[i] *= rhs;
    }
}

void DelVec::operator= (DelVec rhs)
{
    l = rhs.l;
    for (int i = 0; i < l; i++)
        L[i] = rhs.L[i];
    swap(dw, rhs.dw);
    swap(db, rhs.db);  
}

void DelVec::printDims()
{
    for (int i = 0; i < l; i++)
    {
        cout << i << "; " << endl;
        cout << db[i]->m() << ", " << db[i]->n() << endl;
        cout << dw[i]->m() << ", " << dw[i]->n() << endl;
        cout << endl;
    }
}

// Class Del

float Del::C(Matrix a, Matrix y)
{
    Matrix d = a - y;
    return (d.T() * d)[0][0] / d.m() / 2.;
}

Matrix Del::dC(Matrix a, Matrix y)
{
    Matrix d = a - y;
    return (d * (1 / d.m()));
}


void Del::backProp(NeuralNet & net, Matrix * y, DelVec & del)
{
    Layer * current(net.output);
    Layer * next;
    dC(current->a(), current->z());
    *del[l - 1 + l] = dC(current->a(), *y).hadProd(df(current->z()));
    for (int i = l - 1 + l - 1; i > l; i--)
    {
        next = current;
        current = current->getLast();
        *del[i] = df(current->z()).hadProd(next->w().T() * *del[i + 1]);
    }

    current = net.input;
    for (int i = 1; i < l; i++)
    {
        *del[i] = (*del[i + l]) * current->a().T();
        current = current->getNext();
    }

}

void Del::avBackProp(NeuralNet & net, vector<Matrix *> x, vector<Matrix *> y)
{
    int n = x.size();
    DelVec del{net};
    for (int i = 0; i < n; i++)
    {
        net.activate(*x[i]);
        backProp(net, y[i], del);
        delC += del;
        del *= 0;
    }
    delC *= 1. / n;
}

void Del::adjustWeights(NeuralNet & net)
{
    Layer * current = net.input->getNext();
    for (int i = 1; i < l; i++)
    {
        current->biases -= *delC[i + l];
        current->weights -= *delC[i];
        current = current->getNext();
    }
}


void Del::train(NeuralNet & net, vector<Matrix *> x, vector<Matrix *> y, int m)
{
    int n = x.size();
    auto xIt = x.begin();
    auto yIt = y.begin();
    for (int i = 0; i < n / m; i++)
    {
        reset();
        vector<Matrix *> xSlice = vector<Matrix *>(xIt + i * m, xIt + (i + 1) * m - 1);  
        vector<Matrix *> ySlice = vector<Matrix *>(yIt + i * m, yIt + (i + 1) * m - 1);
        avBackProp(net, xSlice, ySlice);
        adjustWeights(net);
        cout << test(net, x, y) << endl;
    }
}

float Del::test(NeuralNet & net, vector<Matrix *> x, vector<Matrix *> y)
{
    int n = x.size();
    float s = 0;
    for (int i = 0; i < n; i++)
    {
        net.activate(*x[i]);
        s += C(net.getOutput(), *y[i]);
    }
    return s / n;
}