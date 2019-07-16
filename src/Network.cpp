#include <cmath>
#include "../header/Network.h"

using namespace std;


Layer::Layer(int n, int m, Layer * next) : 
    n{n}, m{m}, next{next}, activation{n, 1}, weightedSum{n, 1}, biases{rand(n, 1)}, weights{rand(n, m, -0.5, 0.5)} {}

Layer::Layer(int n, int m, Layer * next, bool in) : 
    n{n}, m{m}, next{next}, activation{n, 1}, weightedSum{n, 1}, biases{n, 1}, weights{n, m} {}

Layer::Layer(const Layer & cpy) : Layer(cpy.n, cpy.m, cpy.next, true)
{
    this->weightedSum = cpy.weightedSum;
    this->activation = cpy.activation;
    this->biases = cpy.biases;
    this->weights = cpy.weights;
}

Layer Layer::operator= (Layer rhs) 
{
    this->n = rhs.n;
    this->m = rhs.m;
    this->next = rhs.next;
    this->weightedSum = rhs.weightedSum;
    this->activation = rhs.activation;
    this->biases = rhs.biases;
    this->weights = rhs.weights;
    return *this;
}


void Layer::updateLayer(Layer * former)
{
    weightedSum = weights * former->activation + biases;
    activation = f(weightedSum);
}

void Layer::printLayer()
{
    cout << "weights:" << endl;
    weights.print();
    cout << "activation" << endl;
    activation.print();
    cout << "bias" << endl;
    biases.print();
}


// NeuralNet

NeuralNet::NeuralNet(int * L, int l) : L{L}, l{l}, output{new Layer{L[l - 1], L[l - 2]}}
{
    Layer * current = output;
    Layer * next = nullptr;
    for (int i = 1; i < l - 1; i++)
    {
        next = new Layer{L[l - 1 - i], L[l - 2 - i], current};
        current->setLast(next);
        current = next;
    }
    input = new Layer{L[0], L[0], current, true};
    current->setLast(input);
    input->setLast();
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
    return output->a();
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
            x[i][j] = 1. / (1 + exp(-x[i][j]));
        }
    }
    return x;
}

Matrix df(Matrix x)
{
    for (int i = 0; i < x.shape().m; i++)
    {
        for (int j = 0; j < x.shape().n; j++)
        {
            x[i][j] = exp(-x[i][j]) / pow((1 + exp(-x[i][j])), 2);
        }
    }
    return x;
}
