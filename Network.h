#include "Matrix.h"

class Layer
{
    protected:
        // n is neurons in current layer, m is in the former
        int n, m;
        Matrix neurons;
        Matrix biases;
        Matrix weights;

        Layer * next;

    public:
        Layer(int n, int m, Layer * next = nullptr);
        Layer(int n, int m, Layer * next, bool in);

        void updateLayer(Layer * former);

        Layer * getNext() const {return next;}
        int width() const {return n;}
        float getVal(int j) {return neurons[j][0];}
        Matrix getVals() {return neurons;}
        void printLayer();

        void setNeurons(Matrix data);

};


class NeuralNet
{
    private:
        Layer * input;
        Layer * output;
        Matrix L;

    public:
        NeuralNet(Matrix L);
        ~NeuralNet();

        void printNet() const;
        Matrix activate(Matrix data);
};

// Free functions
//
// Functions used by the NeuralNet, layers, or other related functions

Matrix f(Matrix x);