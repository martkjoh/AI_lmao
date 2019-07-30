#include <cmath>
#include "../header/Network.h"

using namespace std;


// Layer
// 
// A layer contains the activation, weights and biases for one layer in a deep 
// neural network. The weight and biases is generated at random. If only one integer
//  is given, a layer with just a activation matrix is created.

Layer::Layer(int n) : 
    n{n}, m{0}, last{nullptr}, activation{n, 1} {}

Layer::Layer(int n, int m, Layer * last) : 
    n{n}, m{m}, last{last}, activation{n, 1}, weightedSum{n, 1}, biases{rand(n, 1)}, 
    weights{rand(n, m, -0.5, 0.5)} 
    {}

Layer::Layer(const Layer & cpy) : Layer(cpy.n, cpy.m, cpy.next)
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

ofstream& operator<<(ofstream & os, const Layer & rhs)
{
    os << rhs.activation << rhs.weightedSum << rhs.biases << rhs.weights << "\n";
    return os;
}

void Layer::updateLayer(Layer * former)
{
    weightedSum = weights * former->activation + biases;
    activation = f(weightedSum);
}

void Layer::printLayer()
{
    cout << "activation" << endl;
    activation.print();
    cout << "weights:" << endl;
    weights.print();
    cout << "bias" << endl;
    biases.print();
}

void Layer::printShape()
{
    cout << "activation: " << setw(10)<< "weights:"<< setw(10) << "bias: " << endl;
    cout << to_string(activation.m()) + "x" + to_string(activation.n()) << setw(10);
    cout << to_string(weights.m()) + "x" + to_string(weights.n()) << setw(10);
    cout << to_string(biases.m()) + "x" + to_string(biases.n()) << setw(10) << endl;
}


// NeuralNet
// 
// A class that contains layers in a linked list. The class is constructed by first 
// constructing a inputlayer, with only an activation matrix, and the list is then
// constructed as specified by the L-array.

NeuralNet::NeuralNet(int * L, int l) : L{L}, l{l}, input{new Layer{L[0]}}
{
    Layer * current = input;
    Layer * next = nullptr;
    for (int i = 1; i < l; i++)
    {
        next = new Layer{L[i], L[i - 1], current};
        current->setNext(next);
        current = next;
    }
    output = current;
    output->setNext();
}

NeuralNet::NeuralNet(string path)
{
    ifstream fil;
    fil.open(path + ".ai");

    string str, tmp;
    getline(fil, str);
    l = stoi(str);
    
    getline(fil, str);
    stringstream ss(str);
    L = new int[l];

    for (int i = 0; i < l; i++) 
    {
        ss >> tmp;
        L[i] = stoi(tmp);
    }

    input = new Layer{L[0]};
    Layer * last = input;
    Layer * current = nullptr;
    Layer * next = nullptr;
    for (int i = 0; i < 5; i++) {getline(fil, str);}
    for (int i = 1; i < l; i++)
    {
        Layer * current = new Layer;
        getline(fil, str);
        current->activation = matFromString(str);
        getline(fil, str);
        current->weightedSum = matFromString(str);
        getline(fil, str);
        current->biases = matFromString(str);
        getline(fil, str);
        current->weights = matFromString(str);
        getline(fil, str);
        current->n = current->w().n();
        current->m = current->w().m();
        current->last = last;
        last->next = current;
        last = current;
    }
    output = last;
    output->next = nullptr;
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

float NeuralNet::sumC(Matrix a, Matrix y)
{
    Matrix d = a - y;
    return (d.T() * d)[0][0] / 2.;
}

Matrix NeuralNet::C(Matrix a, Matrix y)
{
    Matrix d = a - y;
    return d.hadProd(d) * (1 / 2.);
}

Matrix NeuralNet::dC(Matrix a, Matrix y)
{
    Matrix d = a - y;
    return d;
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

void NeuralNet::printShape() const
{
    Layer * current = input;
    do{
        current->printShape();
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

void NeuralNet::saveNet(string path)
{
    ofstream fil;
    fil.open(path + ".ai");
    fil << to_string(l) << "\n";
    
    for (int i = 0; i < l; i++) {fil << to_string(L[i]) << "\t";}
    fil << "\n";
    Layer * current = input;
    do{
        fil << *current;
        current = current->getNext();
    } 
    while(current != nullptr);
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
