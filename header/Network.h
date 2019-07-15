#include "Matrix.h"

class Layer
{
    protected:
        // n is neurons in current layer, m is in the former
        int n, m;
        
        Matrix activation;
        Matrix biases;
        Matrix weights;

        Layer * next;
        Layer * last;


    public:

        Layer(int n, int m, Layer * next = nullptr);
        Layer(int n, int m, Layer * next, bool in);

        void updateLayer(Layer * former);

        Layer * getNext() const {return next;}
        Layer * getLast() const {return last;}
        void setLast(Layer * last = nullptr) {this->last = last;}
        int width() const {return n;}
        float getVal(int j) {return activation[j][0];}
        Matrix getVals() {return activation;}
        void printLayer();

        void setNeurons(Matrix data){activation = data;}
};


class NeuralNet
{
    private:
        int * L;
        int l;
        
        Layer * output;
        Layer * input;

    public:
        NeuralNet(int * L, int l);
        ~NeuralNet();

        void printNet() const;
        Matrix activate(Matrix data);
        Matrix getOutput() {return output->getVals();}

    friend class DelVec; 
    friend class Del;
};


// Free functions
//
// Functions used by the NeuralNet, layers, or other related functions

Matrix f(Matrix x);
Matrix df(Matrix x);
