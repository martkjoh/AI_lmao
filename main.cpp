#include "Network.h"

int main()
{
    Matrix L{4, 1, 5}; 
    for (int i = 0; i < 1e7; i++)
    {
        L = rand(4, 1);
        NeuralNet N{L};  
    }

    return 0;
}