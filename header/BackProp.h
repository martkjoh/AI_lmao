#pragma once

#include "Network.h"
#include <vector>

struct Data
{
    vector<Matrix *> x;
    vector<Matrix *> y;
};

// A calss to hold the gradient of a cost function

// TODO: rename the classes
class DelVec
{
    private:
        vector<Matrix *> dw;
        vector<Matrix *> db;
        int l;
        int * L;

        Matrix getVal(int i) const;

    public:


        DelVec(NeuralNet & net);
        DelVec(const DelVec & rhs);
        ~DelVec();

        Matrix * operator[](int i);
        // Returning DelVec causes segfault
        void operator+= (const DelVec & rhs);
        void operator*= (const float & rhs);
        void operator= (DelVec rhs);


        void printDims();

    friend class Del;
};

class Del
{
    private:
        DelVec delC;

        int * L;
        int l;

        float C(Matrix a, Matrix y);
        Matrix dC(Matrix a, Matrix y);

        void avBackProp(NeuralNet & net, Data d);
        void backProp(NeuralNet & net, Matrix * y, DelVec & del);
        void adjustWeights(NeuralNet & net);
        float test(NeuralNet & net, Data d);

    public:
        Del(NeuralNet & net) : delC{net}, L{net.L}, l{net.l} {}
        
        void SGD(NeuralNet & net, Data d, int m);
        void reset() {delC *= 0;}
        void printDims() {delC.printDims();}

    friend class DelVec;
};


// Free functions
// 
// Fere functions to work with the classes aboce

void train(NeuralNet & net, Data d, int n, int m);

void test(NeuralNet & net, Data d);

Data slice(Data d, int n, int m);

void shuffleData(Data & d);

// TODO: Funciton that guesses number based on selected image file