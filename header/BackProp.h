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

    public:
        DelVec(NeuralNet & net);
        ~DelVec();

        Matrix operator[](int i) 
        {
            if (i < l)
                return * db[i];
            else
                return * dw[i - l];
        } 
    
    friend class Del;
};

class Del
{
    private:
        DelVec delC;
        int * L;
        int l;


        Matrix C(Matrix a, Matrix y);
        Matrix dC(Matrix a, Matrix y);

        void avBackProp(NeuralNet & net, vector<Matrix *> data, vector<Matrix *> y);
        void addDel(DelVec & delR, DelVec & delL);

    public:
        Del(NeuralNet & net) : delC{net}, L{net.L}, l{net.l} {}

        DelVec backProp(NeuralNet & net, Matrix * y);
    
    friend class DelVec;
};