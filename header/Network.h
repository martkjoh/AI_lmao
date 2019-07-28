#pragma once

#include "Matrix.h"
#include <iostream>
#include <fstream>

// Layer

class Layer
{
    protected:
        // n is neurons in current layer, m is in the former
        int n, m;
        Matrix activation, weightedSum, biases, weights;
        Layer * next;
        Layer * last;

    public:

        Layer(int n = 0);
        Layer(int n, int m, Layer * last = nullptr);
        Layer(const Layer & cpy);

        Layer operator= (Layer rhs);
        friend ofstream& operator<<(ofstream & os, const Layer & rhs);

        void updateLayer(Layer * former);
        Layer * getNext() const {return next;}
        Layer * getLast() const {return last;}
        void setNext(Layer * next = nullptr) {this->next = next;}
        int width() const {return n;}
        float getVal(int j) {return activation[j][0];}
        Matrix a() {return activation;}
        Matrix z() {return weightedSum;}
        Matrix w() {return weights;}
        void printLayer();
        void printShape();
        void setNeurons(Matrix data){activation = data;}


    friend class Del;
    friend class NeuralNet;
};


// Neural Net

class NeuralNet
{
    public:
        int * L;
        int l;
        
        Layer * output;
        Layer * input;

    public:
        NeuralNet(int * L, int l);
        NeuralNet(string path = "net");
        ~NeuralNet();

        void printNet() const;
        void printShape() const;
        Matrix activate(Matrix data);
        Matrix getOutput() {return output->a();}
        // TODO: include only the weights an biases in .ai, and remove first layer
        void saveNet(string path = "net");

    friend class DelVec; 
    friend class Del;
};


// Free functions

Matrix f(Matrix x);
Matrix df(Matrix x);
