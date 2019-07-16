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
    Del delC(N);

    // int s = 100;
    // DelVec d{N};
    // for (int i = 0; i < s; i++)
    // {
    //     N.activate(*x[0]);
    //     delC.backProp(N,y[0], d);
    //     delC.adjustWeights(N);
    //     // delC.reset();
    //     cout << delC.test(N, x, y) << endl;
    // }
    for (int i = 0; i < 100; i++)
        delC.train(N, xTrain, yTrain, m);
    cout << delC.test(N, x, y) << endl;

    for (int i = 0; i < 20; i++)
    {
       N.activate(*x[i]);
        N.getOutput().print();
        (*y[i]).T().print();
        cout << endl;          
    }
    
    return 0;
}