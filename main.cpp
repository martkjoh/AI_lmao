#include "Network.h"

int main()
{
    // srand (time(NULL));
    float d[] = {
        4,
        2,
        2,
        1
    };

    float d2[] = {
        1
    };

    Matrix L{4, 1, d};

    NeuralNet N(L);  

    Matrix in = rand(4, 1);
    Matrix y(1, 1, d2);
    N.activate(in);
    N.printNet();
    cout << C(N.getOutput(), y);
    return 0;
}