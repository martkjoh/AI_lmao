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

    train(net, d, timesTrainig, batchNum);

    net.saveNet(name);
}

void testNN(string name)
{
    NeuralNet net(name);
    Data d = getData(DataType::TEST);
    test(net, d.x, d.y);
}