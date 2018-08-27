#include "trainingmodule.h"

TrainingModule::TrainingModule() {

    }

void TrainingModule::setup(double w1, double w2, double lr) {
    weight1 = w1;
    weight2 = w2;
    learningRate = lr;
    }

void TrainingModule::addData( double x, double y, int t ) {
    Data data = { x, y, t };
    trainingSet.push_back( data );
    }

void TrainingModule::update( unsigned int index, int error ) {
    weight1 = weight1 + learningRate * error * trainingSet.at(index).x;
    weight2 = weight2 + learningRate * error * trainingSet.at(index).y;
    }

int TrainingModule::perceptWeight( unsigned int j ) {
    if (weight1 * trainingSet.at(j).x + weight2 * trainingSet.at(j).y >= 0) {
        return 1;
        }

    return 0;
    }

int TrainingModule::getDataTypeAt( unsigned int j ) {
    return trainingSet.at(j).type;
    }

unsigned int TrainingModule::getSizeOfTrainingSet() {
    return trainingSet.size();
    }

double TrainingModule::getLearningRate() {
    return learningRate;
    }

double TrainingModule::getWeight1() {
    return weight1;
    }

double TrainingModule::getWeight2() {
    return weight2;
    }
