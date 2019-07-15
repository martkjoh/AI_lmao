#include "Network.h"
#include <vector>


// A calss to hold the gradient of a cost function

class DelVec
{
    private:
        vector<Matrix *> vec;
        int l;
        int * L;

    public:
        DelVec(NeuralNet & net);
        ~DelVec();

        Matrix operator[](int i) {return * vec[i];} 
    
    friend class Del;
};

class Del
{
    private:
        DelVec delC;
        int l;
        int * L;

        Matrix C(Matrix a, Matrix y);
        Matrix dC(Matrix a, Matrix y);

        DelVec makeVec(NeuralNet & net);
        DelVec backProp(NeuralNet & net, Matrix * y);
        void avBackProp(NeuralNet & net, vector<Matrix *> data, vector<Matrix *> y);
        void addDel(DelVec & delR, DelVec & delL);

    public:
        Del(NeuralNet & net) : delC{makeVec(net)}, l{net.l}, L{net.L} {}
    
    friend class l;
};