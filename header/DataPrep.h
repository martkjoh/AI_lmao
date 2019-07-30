#pragma once

#include <Magick++.h>
#include <string>
#include "Interface.h"
#include "Matrix.h"
#include "BackProp.h"

using namespace Magick;
using namespace std;

// Number of pictures used for training
static int TRAING_SIZE = 6e3; // Max 6e4
// Number of pictures used for testing
static int TESTING_SIZE = 1e3; // Max 1e4

enum DataType{TEST, TRAIN};

void imToMat(Image & im, Matrix * M);

void matToIm(Image & im, Matrix * M);

void loadData(Data & d, string path, int n);

Data getData(DataType DT = DataType::TRAIN);
