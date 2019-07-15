#include "header/BackProp.h"

int main()
{
    // srand (time(NULL));
    int l = 3;
    int L[l] = {
        2,
        3,
        2
    };

    float d[L[0]] = {
        3.4,
        0.345
    };
    float a[L[l - 1]] = {
        1,
        0
    };

    Matrix data(L[0], 1, d);
    Matrix y(L[l - 1], 1, a);
    NeuralNet N(L, l);
    Del delc(N);

    N.activate(data);
    // N.printNet();

    delc.backProp(N, &y);

    return 0;
}