#pragma once

#include <Magick++.h>
#include <string>
#include "Interface.h"
#include "Matrix.h"

using namespace Magick;
using namespace std;

// Number of pictures used for training
static int TRAING_SIZE = 4e3;
// Number of pictures used for testing
static int TESTING_SIZE = 1e3;

struct Data{
    vector<Matrix *> x;
    vector<Matrix *> y;
};

enum DataType{TEST, TRAIN};

void imToMat(Image & im, Matrix * M);

void matToIm(Image & im, Matrix * M);

void loadData(Data & d, string path, int n);

Data getData(DataType DT = DataType::TRAIN);

void shuffleData(Data & d);

Data slice(Data d, int n, int m);
