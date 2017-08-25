#ifndef NET_H
#define NET_H


#include "neuron.h"

#include <vector>
#include <cstdlib>


class net
{
    public:

        //both are int because of % calculations
        //probability in x/1000
        int changeChance = 600;
        int changeQnt = 50;


        //the actual net structure
        std::vector<neuron*> neurons;

        //input layer
        std::vector<float> inputLayer;
        //output layer
        std::vector<neuron*> outputLayer;

        net();

        /**
         * Creates the neural network.
         *
         * @param NbroNeurons - The number of hidden layers
         * @param NbroInputs - The number of possible inputs the network can get
         * values from
         * @param NbroOutputs - The number of possible outputs the network can
         * generate
         */
        void create(int NbroNeurons, int NbroInputs, int NbroOutputs);
/**
        Initializes all the values of the neural network
*/
        void initialize();

        void activate();

        double getOutput(int i);

    private:

};

#endif
