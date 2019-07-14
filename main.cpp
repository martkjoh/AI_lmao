#include "Network.h"

int main()
{
    // srand (time(NULL));
    float d[4] = {
        2,
        1
    };

    Matrix L{2, 1, d};

    NeuralNet N(L);  

    Matrix in = rand(4, 1);
    N.activate(in);
    // N.printNet();
    return 0;
}