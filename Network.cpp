#include <cmath>
#include "Network.h"

using namespace std;

Layer::Layer(int n, int m) : 
    n{n}, m{m}, neurons{n, 1}, biases{rand(n, 1)}, weights{rand(m, n)} 
{}

void Layer::updateLayer(Layer former)
{
    neurons = f((weights * former.neurons) + biases)
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
            x = 1 / (1 + exp(-x[i][j]))
        }
    }
    return x;
}