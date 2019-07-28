#include "../header/BackProp.h"

DelVec::DelVec(NeuralNet & net) : L{net.L}, l{net.l}
{
    dw.push_back(new Matrix(0, 0));
    db.push_back(new Matrix(0, 0));
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

    dw.push_back(new Matrix(0, 0));
    db.push_back(new Matrix(0, 0));
    for (int i = 1; i < l; i++)
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
    return (d.T() * d)[0][0] / 2.;
}

Matrix Del::dC(Matrix a, Matrix y)
{
    Matrix d = a - y;
    return d;
}


void Del::backProp(NeuralNet & net, Matrix * y, DelVec & del)
{
    Layer * current(net.output);    // equivalent to index i
    Layer * next;                   // equivalent to index i + 1
    *del[l - 1 + l] = dC(current->a(), *y).hadProd(df(current->z()));
    for (int i = l - 2 + l; i > l; i--)
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
        float eta = 1;
        current->biases -= *delC[i + l] * eta;
        current->weights -= *delC[i] * eta;
        current = current->getNext();
    }
}

void Del::SGD(NeuralNet & net, vector<Matrix *> x, vector<Matrix *> y, int m)
{
    int n = x.size();
    auto xIt = x.begin();
    auto yIt = y.begin();
    for (int i = 0; i < n / m; i++)
    {
        reset();
        vector<Matrix *> xSlice = vector<Matrix *>(xIt + i * m, xIt + (i + 1) * m - 1);  
        vector<Matrix *> ySlice = vector<Matrix *>(yIt + i * m, yIt + (i + 1) * m - 1);
        for (int i = 0; i < 10; i++) 
        {        
            avBackProp(net, xSlice, ySlice);
            adjustWeights(net);
        }
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

// Free functions
// 
// Fere functions to work with the classes aboce

// n is the number of time to train the network,
// m is the number of baches the training data is seperated into
void trainNN(NeuralNet & net, int n, int m, vector<Matrix *> x, vector<Matrix *> y)
{
    cout << "Training neural network" << endl;
    Del delC(net);
    for (int i = 0; i < n; i++)
    {
        delC.SGD(net, x, y, m);
        cout << (100 * (i + 1)) / n << "%" << endl;
    }
}

void testNN(NeuralNet & net, vector<Matrix *> x, vector<Matrix *> y)
{
    float correct = 0;
    int n = x.size();
    Matrix guess;
    Matrix answ;
    for (int i = 0; i < n; i++)
    {
        answ = *y[i];
        net.activate(*x[i]);
        guess = net.getOutput();
        if (answ.absMaxIndex() == guess.absMaxIndex()) 
            correct += 1;
    }
    cout << "AI_lmao gjettet " << 100 * correct / n << "% riktig" << endl;
}
