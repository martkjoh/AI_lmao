#include <cmath>
#include "../header/Network.h"


using namespace std;

Layer::Layer(int n, int m, Layer * next) : 
    n{n}, m{m}, next{next}, neurons{n, 1}, biases{rand(n, 1)}, weights{rand(n, m)} {}

Layer::Layer(int n, int m, Layer * next, bool in) : Layer(n, m, next)
{
    if (in) {weights = Matrix{m, n};}
}

void Layer::updateLayer(Layer * former)
{
    neurons = f(weights * former->neurons + biases);
}

void Layer::printLayer()
{
    cout << "weights:" << endl;
    weights.print();
    cout << "activation" << endl;
    neurons.print();
    cout << "bias" << endl;
    biases.print();
}

void Layer::setNeurons(Matrix data)
{
    neurons = data;
}


// NeuralNet

// TODO: Clean up this mess
NeuralNet::NeuralNet(Matrix L) : L{L}, output{new Layer{(int)L[L.shape().m - 1][0], (int)L[L.shape().m - 2][0]}}
{
    Layer * current = output;
    for (int i = 1; i < L.shape().m - 1; i++)
    {
        current = new Layer{(int)L[L.shape().m - 1 - i][0], (int)L[L.shape().m - 2 - i][0], current};
    }
    input = new Layer{(int)L[0][0], (int)L[0][0], current, true};
}

NeuralNet::~NeuralNet()
{
    Layer * current = input;
    Layer * next = current->getNext();
    do{
        delete current;
        current = next;
        next = current->getNext();
    }
    while (next != nullptr);
    delete current;
}

void NeuralNet::printNet() const
{
    Layer * current = input;
    do{
        current->printLayer();
        cout << endl << endl;
        current = current->getNext();
    } 
    while(current != nullptr);
}


Matrix NeuralNet::activate(Matrix data)
{
    input->setNeurons(data);
    Layer * last = input;
    Layer * current = input->getNext();
    do{
        current->updateLayer(last);
        last = current;
        current = last->getNext();
    }
    while (current != nullptr);
    return output->getVals();
}

// Free functions
//
// Functions used by the network, layers, or other related functions

Matrix f(Matrix x)
{
    for (int i = 0; i < x.shape().m; i++)
    {
        for (int j = 0; j < x.shape().n; j++)
        {
            x[i][j] = 1 / (1 + exp(-x[i][j]));
        }
    }
    return x;
}

float C(Matrix a, Matrix y)
{
    Matrix d = a - y;
    return (d.T() * d)[0][0] / d.shape().m;
}