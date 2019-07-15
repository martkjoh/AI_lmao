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
        ~DelVec();

        Matrix operator[](int i);
        DelVec operator+= (const DelVec & rhs);
        DelVec operator*= (const float & rhs);

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

        void reset() {delC *= 0;}

        void avBackProp(NeuralNet & net, vector<Matrix *> x, vector<Matrix *> y);
        DelVec backProp(NeuralNet & net, Matrix * y);
        void adjustWeights(NeuralNet & net);


    public:
        Del(NeuralNet & net) : delC{net}, L{net.L}, l{net.l} {}

        void train(NeuralNet & net, vector<Matrix *> x, vector<Matrix *> y, int m);
        float test(NeuralNet & net, vector<Matrix *> x, vector<Matrix *> y);
        
    friend class DelVec;
};