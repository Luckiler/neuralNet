#ifndef NEURON_H
#define NEURON_H

#include "utils.h"

#include <vector>

class neuron
{
    private:
        struct inputValue
        {
            float value = 0;
            float weight = 0;
        };


        float bias;///<Bias used in the sigma calculations

        double sigm(double x);
        double calcDelta();

    public:

        int id;///<The neuron UUID

        float position[2] = {0.0, 0.0};///<Position in the net (for rendering)

        bool isConnected = false;///Used  to make sure all the neurons have at least one input

        double value = 0; ///<The neuron computed value (0 if not calculated)

        std::vector<neuronConnection> connections;///<List of all the connections for this neuron

        //These values are not in the connections vector because the values here
        //are dynamic across the net existence. The connections are fixed
        std::vector<inputValue> inputValues;///<List of all the input values with their weight

        neuron();

        /**
         *   Sets up the neuron values
         *
         *   @param ID - the neuron will be assigned this ID
         */
        void initialze(int ID);

        /**
         *  Creates a connection with another neuron from wich this neuron will
         *  pick the value as input.
         *
         *  @param connectID - The ID of the neuron it will connect to.
         */
        void connect(int connectID);

        /**
         *  Used for rendering. Abritrary position in a huge space. Needs to be
         *  scaled down for proper visualisation.
         */
        void setPos();

        /**
         *  Adds a value to the input list used in sigma calculation
         *
         *  @param newInput - The new value to be added
         *  @param newInputWeight - The weight of this input (used in the calculation)
         */
        void addInput(double newInputValue, double newInputWeight);

        /**
         *  Clears the input list
         */
        void clearInputs();

        void activate();

        /**
         *  Called when rebulding a net from a previous one.
         *  This simulates a mutation in the neuron, provoquing
         *  evolution.
         *
         *  @param oldBias - The bias in the parent (previous version) of
         *  this neuron neuron.
         *
         *  @param changeProb - Probability of changes hapening in this neuron.
         *  in /1000
         *
         *  @param changeQnt - If a change occurs, /100 of the previous value
         *  to change
         */
        void evolve(float oldBias, int changeChance, int changeQnt);
};

#endif
