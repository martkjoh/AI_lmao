#include "Network.h"
#include <vector>


// A calss to hold the gradient of a cost function

class DelVec
{
    private:
        vector<Matrix *> db;
        vector<Matrix *> dw;
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
        int * L;
        int l;

        float C(Matrix a, Matrix y);
        Matrix dC(Matrix a, Matrix y);

        void avBackProp(NeuralNet & net, vector<Matrix *> x, vector<Matrix *> y);
        void backProp(NeuralNet & net, Matrix * y, DelVec & del);
        void adjustWeights(NeuralNet & net);


    public:
        DelVec delC;

        Del(NeuralNet & net) : delC{net}, L{net.L}, l{net.l} {}

        void reset() {delC *= 0;}

        void train(NeuralNet & net, vector<Matrix *> x, vector<Matrix *> y, int m);
        float test(NeuralNet & net, vector<Matrix *> x, vector<Matrix *> y);
        void printDims() {delC.printDims();}

    friend class DelVec;
};