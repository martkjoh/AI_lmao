#include "header/Network.h"

int main()
{
    // srand (time(NULL));
    int l = 3;
    int L[l] = {
        2,
        3,
        2
    };
    NeuralNet N(L, l);
    N.printNet();

    return 0;
}