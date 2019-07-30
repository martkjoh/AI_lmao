#pragma once

#include "DataPrep.h"
#include "Network.h"
#include "BackProp.h"
#include <string>

// Parameters for the neural network
// 
// Number of layers in the network
static const int l = 4;
// Numbers of nodes in each layer
static int L[l] = {784, 16, 16, 10};

void makeNN(string name);

void trainNN(string nameint, int timesTrainig = 1, int batchNum = 10);

void testNN(string name);

void guessNubmer(string name, string path);

void Interface(int argc, char ** argv);
