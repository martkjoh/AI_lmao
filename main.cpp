#include "header/BackProp.h"

int main()
{
    // srand (time(NULL));
    int l = 3;
    int L[l] = {
        2,
        3,
        1
    };

    float d[L[0]] = {
        3.4,
        0.345
    };

    vector<Matrix *> x;
    vector<Matrix *> y;
    int n = 11;
    int m = 2;

    NeuralNet N(L, l);
    Del delC(N);

    for (int i = 0; i < n; i++)
    {
        x.push_back(new Matrix(rand(L[0], 1)));
        y.push_back(new Matrix(rand(L[l - 1], 1)));
    }

    delC.train(N, x, y, m);
    delC.printDims();

    // cout << delC.test(N, x, y) << endl;

    return 0;
}