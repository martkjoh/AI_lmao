#include <Magick++.h>
#include "Matrix.h"
#include <string>

using namespace Magick;
using namespace std;

struct Data{
    vector<Matrix *> x;
    vector<Matrix *> y;
};

void imToMat(Image & im, Matrix * M);

void matToIm(Image & im, Matrix * M);

void loadData(Data & d, string path, int n);

Data getData(int N);

void shuffleData(Data & d);

Data slice(Data d, int n, int m);
