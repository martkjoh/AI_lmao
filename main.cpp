#include "header/Network.h"

int main()
{

    Matrix M = rand(2, 2);
    Matrix N = rand(2, 2);
    M.print();
    M *= 2;
    M.print();
    (M * 2).print();
    N.print();
    M.HadProd(N).print();
    // srand (time(NULL));
    // int l = 3;
    // int L[l] = {
    //     2,
    //     3,
    //     2
    // };

    // float d[L[0]] = {
    //     3.4,
    //     0.345
    // };
    // Matrix data(L[0], 1, d);
    // NeuralNet N(L, l);
    // N.activate(data);
    // N.printNet();

    return 0;
}