#include "perceptron.h"

Perceptron::Perceptron() {

    }

void Perceptron::setup( double w1, double w2 ) {
    weight1 = w1;
    weight2 = w2;
    }

void Perceptron::update() {

    }

void Perceptron::addData( double x, double y, Type t ) {
    Pair d;
    d.key = x;
    d.value = y;
    d.type = t;

    data.push_back( d );
    }

int Perceptron::getSizeOfDataVector() {
    return data.size();
    }

double Perceptron::valueAt( int j ) {
    return data.at(j);
    }

void Perceptron::setWeight1( double w1 ) {
    weight1 = w1;
    }

void Perceptron::setWeight2( double w2 ) {
    weight2 = w2;
    }

double Perceptron::getWeight1() {
    return weight1;
    }

double Perceptron::getWeight2() {
    return weight2
    }
