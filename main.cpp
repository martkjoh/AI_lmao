#include "header/BackProp.h"
#include "header/DataPrep.h"

int main()
{
    srand (time(NULL));
    
    int nTest = 1e2;  // Max 1e4
    // int nTrain = 6e2; // Max 6e4
    string testPath = "data/test/";
    // string trainPath = "data/train/";
    Data testData = getData(testPath, nTest);
    // Data trainData = getData(trainPath, nTrain);

    // int l = 4;
    // int L[l] = {784, 20, 20, 10};
    // NeuralNet N(L, l);
    // trainNN(N, 20, 10, trainData.x, trainData.y);
    // N.saveNet();

    NeuralNet N("test");
    testNN(N, testData.x, testData.y);

    return 0;
}