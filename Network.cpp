#include <cmath>
#include "Network.h"

using namespace std;

Layer::Layer(int n, int m, Layer * next) : 
    n{n}, m{m}, next{next}, neurons{n, 1}, biases{rand(n, 1)}, weights{rand(m, n)} {}


void Layer::updateLayer(Layer * former)
{
    neurons = f((weights * former->neurons) + biases);
}


// Network

Network::Network(Matrix L) : L{L}, output{new Layer{*L[L.shape().m - 1], *L[L.shape().m - 2]}}
{
    Layer * current = output;
    for (int i = 1; i < L.shape().m - 1; i++)
    {
        current = new Layer{*L[L.shape().m - 1 - i], *L[L.shape().m - 2 - i], current};
    }
    input = new Layer{*L[0], *L[0], current};
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