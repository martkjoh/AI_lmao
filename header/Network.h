#include "Matrix.h"

// TODO: Make sublayer without weights an biases
class Layer
{
    protected:
        // n is neurons in current layer, m is in the former
        int n, m;
        
        Matrix activation;
        Matrix weightedSum;
        Matrix biases;
        Matrix weights;

        Layer * next;
        Layer * last;


    public:

        Layer(int n);
        Layer(int n, int m, Layer * last = nullptr);
        Layer(const Layer & cpy);

        Layer operator= (Layer rhs);

        void updateLayer(Layer * former);

        Layer * getNext() const {return next;}
        Layer * getLast() const {return last;}
        void setNext(Layer * next = nullptr) {this->next = next;}
        int width() const {return n;}
        float getVal(int j) {return activation[j][0];}
        Matrix a() {return activation;}
        Matrix z() {return weightedSum;}
        Matrix w() {return weights;}
        void printLayer();
        void printShape();

        void setNeurons(Matrix data){activation = data;}

    friend class Del;
};


// Neural Net

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
        void printShape() const;
        Matrix activate(Matrix data);
        Matrix getOutput() {return output->a();}

    friend class DelVec; 
    friend class Del;
};


// Free functions
//
// Functions used by the NeuralNet, layers, or other related functions

Matrix f(Matrix x);
Matrix df(Matrix x);
