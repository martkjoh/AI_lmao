#include "Matrix.h"

class Layer
{
    private:
        // n is neurons in current layer, m is in the former
        int n, m;
        Matrix neurons;
        Matrix biases;
        Matrix weights;

        Layer * next;

        void updateLayer(Layer * former);

    public:
        Layer(int n, int m, Layer * next = nullptr);
};


class Network
{
    private:
        Layer * input;
        Layer * output;
        Matrix L;

    public:
        Network(Matrix L);
};

// Free functions
//
// Functions used by the network, layers, or other related functions

Matrix f(Matrix x);