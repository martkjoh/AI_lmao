#include <Magick++.h>
#include "Matrix.h"
#include <string>

using namespace Magick;
using namespace std;


void imToMat(Image & im, Matrix * M);

void matToIm(Image & im, Matrix * M);

void getData(vector<Matrix *> & x, vector<Matrix *> &y, int n);
