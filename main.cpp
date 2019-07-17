#include "header/BackProp.h"
#include "header/dataPrep.h"

int main()
{
    srand (time(NULL));
    
    vector<Matrix *> x;
    vector<Matrix *> y;
    
    int n = 10000;
    int nTrain = (n * 9) / 10;
    int m = 100;
    getData(x, y, n);

    auto itx = x.begin();
    auto ity = y.begin();
    vector<Matrix *> xTrain = vector<Matrix *>(x.begin()  + nTrain, x.end());
    vector<Matrix *> yTrain = vector<Matrix *>(y.begin() + nTrain, y.end());
    x = vector<Matrix *>(x.begin(), x.begin() + nTrain);
    y = vector<Matrix *>(y.begin(), y.begin() + nTrain);

    int l = 4;
    int L[l] = {784, 16, 16, 10};
    NeuralNet N(L, l);

    trainNN(N, 20, 10, xTrain, yTrain);
    testNN(N, x, y);

    return 0;
}