#include "header/BackProp.h"
#include "header/dataPrep.h"

int main()
{
    srand (time(NULL));
    
    vector<Matrix *> x;
    vector<Matrix *> y;
    
    int n = 1000;
    int m = 10;
    getData(x, y, n);
     
    int l = 4;
    int L[l] = 
    {
        28 * 28,
        100,
        100,
        10
    };

    NeuralNet N(L, l);
    Del delC(N);

    cout << delC.test(N, x, y) << endl;
    // N.activate(*x[4]);
    N.getOutput().print();
    // delC.train(N, x, y, m);
    cout << delC.test(N, x, y) << endl;

    return 0;
}