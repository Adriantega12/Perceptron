#ifndef TRAININGMODULE_H
#define TRAININGMODULE_H

#include <QLabel>

#include <vector>
#include <random>
#include <chrono>

class TrainingModule{
    private:
        struct Data {
            double x;
            double y;
            int type;
            };

        double learningRate;
        double weight0;
        double weight1;
        double weight2;
        double slope;
        double intercept;

        std::vector<Data> trainingSet;

        void updateSlopeAndIntercept();

    public:
        static const int RED = 0;
        static const int BLUE = 1;

        TrainingModule();

        void addData( double, double, int );

        void setup( double, double, double, double );
        void update( unsigned int, int );

        int perceptWeight( unsigned int );
        double linearCombination( double, double, unsigned int );

        int getDataTypeAt( unsigned int );
        unsigned int getSizeOfTrainingSet();
        double getLearningRate();
        double getWeight0();
        double getWeight1();
        double getWeight2();
        double getSlope();
        double getIntercept();

        static double generateRandomDoubleNumber(double, double);

    };

#endif // TRAININGMODULE_H
