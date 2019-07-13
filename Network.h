#include "Matrix.h"

class Layer
{
    private:
        // n is neurons in current layer, m is in the former
        int n, m;
        Matrix neurons;
        Matrix biases;
        Matrix weights;

        void updateLayer(Layer former);

    public:
        Layer(int n, int m);

}   



// Free functions
//
// Functions used by the network, layers, or other related functions

Matrix f(Matrix x);