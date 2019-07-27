#include "header/BackProp.h"
#include "header/DataPrep.h"

int main()
{
    srand (time(NULL));
    
    int nTest = 1e2;  // Max 1e4
    int nTrain = 6e2; // Max 6e4
    string trainPath = "data/train/";
    string testPath = "data/test/";
    Data testData = getData(testPath, nTest);
    Data trainData = getData(trainPath, nTrain);

    int l = 4;
    int L[l] = {784, 20, 20, 10};
    NeuralNet N(L, l);
    N.printShape();
    trainNN(N, 20, 10, trainData.x, trainData.y);
    testNN(N, testData.x, testData.y);

    return 0;
}