#include "Network.h"
#include <vector>


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

        void avBackProp(NeuralNet & net, vector<Matrix *> x, vector<Matrix *> y);
        void backProp(NeuralNet & net, Matrix * y, DelVec & del);
        void adjustWeights(NeuralNet & net);
        float test(NeuralNet & net, vector<Matrix *> x, vector<Matrix *> y);

    public:
        Del(NeuralNet & net) : delC{net}, L{net.L}, l{net.l} {}
        
        // TODO: Make actually stochasic (picking of vector slices)
        void SGD(NeuralNet & net, vector<Matrix *> x, vector<Matrix *> y, int m);
        void reset() {delC *= 0;}
        void printDims() {delC.printDims();}

    friend class DelVec;
};


// Free functions
// 
// Fere functions to work with the classes aboce

void trainNN(NeuralNet & net, int n, int m, vector<Matrix *> x, vector<Matrix *> y);

void testNN(NeuralNet & net, vector<Matrix *> x, vector<Matrix *> y);


// TODO: Funciton that guesses number based on selected image file