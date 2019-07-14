#include "Network.h"

int main()
{
    // srand (time(NULL));
    float d[] = {
        3,
        4,
        2
    };

    float d2[] = {
        1,
        0
    };

    Matrix L{3, 1, d};

    NeuralNet N(L);  

    Matrix in = rand(3, 1);
    Matrix y(2, 1, d2);
    N.activate(in);
    N.printNet();
    cout << C(N.getOutput(), y);
    return 0;
}