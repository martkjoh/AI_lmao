#include "header/BackProp.h"
#include "header/DataPrep.h"

int main()
{
    srand (time(NULL));

    // Parameters for the neural network
    // 
    // Total number of pictures loaded 
    int N = 5e3; // Max 6e4
    // Number of pictures used for training
    int n = 4e3;
    // Number of pictures used for testing
    int m = 1e3;
    if (N < n + m)
    {
        cout << "Invalid data sizes" << endl;
        throw 1;
    }
    // Number of layers in the network
    int l = 4;
    // Numbers of nodes in each layer
    int L[l] = {784, 16, 16, 10};

    // NeuralNet net(L, l);
    NeuralNet net;

    Data d = getData(N);
    Data testData = slice(d, 0, m);
    
    d = slice(d, m, N);
    shuffleData(d);
    d = slice(d, 0, n);

    trainNN(net, 10, 10, d.x, d.y);
    net.saveNet();
    
    testNN(net, testData.x, testData.y);

    return 0;
}