#include "trainingmodule.h"

void TrainingModule::updateSlopeAndIntercept() {
    slope = -(weight0/weight2)/(weight0/weight1);
    intercept = /*-*/weight0/weight2;
    }

TrainingModule::TrainingModule() {

    }

void TrainingModule::setup(double w0, double w1, double w2, double lr) {
    weight0 = w0;
    weight1 = w1;
    weight2 = w2;
    learningRate = lr;
    updateSlopeAndIntercept();
    }

void TrainingModule::addData( double x, double y, int t ) {
    Data data = { x, y, t };
    trainingSet.push_back( data );
    }

void TrainingModule::update( unsigned int index, int error ) {
    weight0 = weight0 + learningRate * error * (-1);
    weight1 = weight1 + learningRate * error * trainingSet.at(index).x;
    weight2 = weight2 + learningRate * error * trainingSet.at(index).y;
    updateSlopeAndIntercept();
    }

int TrainingModule::perceptWeight( unsigned int j ) {
    if (-1 * weight0 + weight1 * trainingSet.at(j).x + weight2 * trainingSet.at(j).y >= 0) {
        return 1;
        }

    return 0;
    }

double TrainingModule::linearCombination( double w1, double w2, unsigned int j ) {
    return -1 * /*theta*/1 + w1 * trainingSet.at(j).x + w2 * trainingSet.at(j).y;
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

double TrainingModule::getWeight0() {
    return weight0;
    }

double TrainingModule::getWeight1() {
    return weight1;
    }

double TrainingModule::getWeight2() {
    return weight2;
    }

double TrainingModule::getSlope() {
    return slope;
    }

double TrainingModule::getIntercept() {
    return intercept;
    }
