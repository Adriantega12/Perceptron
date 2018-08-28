#ifndef TRAININGMODULE_H
#define TRAININGMODULE_H

#include <QLabel>

#include <vector>

class TrainingModule{
    private:
        struct Data {
            double x;
            double y;
            int type;
            };

        double learningRate;
        double theta;
        double weight1;
        double weight2;

        std::vector<Data> trainingSet;

    public:
        static const int RED = 0;
        static const int BLUE = 1;

        TrainingModule();

        void addData( double, double, int );

        void setup( double, double, double );
        void update( unsigned int, int );

        int perceptWeight( unsigned int );
        double linearCombination( double, double, unsigned int );

        int getDataTypeAt( unsigned int );
        unsigned int getSizeOfTrainingSet();
        double getLearningRate();
        double getWeight1();
        double getWeight2();

    };

#endif // TRAININGMODULE_H
