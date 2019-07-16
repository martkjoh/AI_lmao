#include "header/BackProp.h"

int main()
{
    srand (time(NULL));
    int l = 4;
    int L[l] = 
    {
        2,
        10,
        10,
        1
    };

    float xd1[L[0]] =
    {
        0.5,
        0
    };

    float xd2[L[0]] =
    {
        0,
        0
    };

    float yd1[L[l - 1]] = 
    {
        0
    };

    float yd2[L[l - 1]] = 
    {
        1
    };


    vector<Matrix *> x;
    vector<Matrix *> y;
    int n = 1000;
    int m = 10;

    NeuralNet N(L, l);
    Del delC(N);

    for (int i = 0; i < n / 2; i++)
    {
        x.push_back(new Matrix(L[0], 1, xd1));
        x.push_back(new Matrix(L[0], 1, xd2));
        y.push_back(new Matrix(L[l - 1], 1, yd1));
        y.push_back(new Matrix(L[l - 1], 1, yd1));
    }

    cout << delC.test(N, x, y) << endl;
    delC.train(N, x, y, m);
    cout << delC.test(N, x, y) << endl;

    return 0;
}