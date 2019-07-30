#include "../header/Interface.h"


void makeNN(string NNName)
{
    NeuralNet net(L, l);
    net.saveNet(NNName);
}

void trainNN(string name, int timesTrainig, int batchNum)
{
    NeuralNet net(name);
    Data d = getData();
    shuffleData(d);

    train(net, timesTrainig, batchNum, d.x, d.y);

    net.saveNet(name);
}

void testNN(string name)
{
    NeuralNet net(name);
    Data d = getData(DataType::TEST);
    test(net, d.x, d.y);
}