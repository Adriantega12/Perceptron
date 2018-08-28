#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include <vector>

class Perceptron {
    public:
    enum Type {
        RED,
        BLUE
        };

        Perceptron();

        void setup( double, double );

        void update();

        void addData( double, double, Type );

        int getSizeOfDataVector();
        double valueAt( int );

        void setWeight1( double );
        void setWeight2( double );

        double getWeight1();
        double getWeight2();

    private:
        double weight1;
        double weight2;

        struct Pair {
            double key;
            double value;
            Type type;
            };

        std::vector<Pair> data;
    };

#endif // PERCEPTRON_H
