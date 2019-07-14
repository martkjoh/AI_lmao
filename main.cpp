#include "Network.h"

int main()
{
    Matrix L{4, 1, 5};
    // NeuralNet N(L);
    float d[] {
        1.,
        0.3,
        0.543,
        0.149,
        0.34
    };
    Matrix data(5, 1, d);
    // N.activate(data);
    // N.printNet();
    return 0;
}