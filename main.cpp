#include "Network.h"

int main()
{
    Matrix L{4, 1, 5};
    NeuralNet N(L);
 
    float d[] = {
        0.1534,
        0.3559,
        0.9913,
        0.2355,
        0.0345
    };
 
    Matrix data(5, 1, d);
    N.activate(data);
    N.printNet();
    return 0;
}