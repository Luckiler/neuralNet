#include "neuron.h"
#include "net.h"

#include <math.h>
#include <cstdlib>
#include <stdio.h>

neuron::neuron()
{
    neuron::setPos();
}

void neuron::evolve(float oldBias, int changeChance, int changeQnt)
{
    int x = rand() % 100;

    if(x < changeChance)
    {
        neuron::bias = (oldBias - changeQnt) + (rand() % (changeQnt * 2000)) / 100000;
        printf("Neuron initialized with mutated values\n");
    }
    else
    {
        neuron::bias = oldBias;
        printf("Neuron initialized with inherited values\n");
    }
}

void neuron::initialze(int ID)
{
    neuron::id = ID;
    neuron::bias = 1.0 * (std::rand() % 1000) / 100;
}

void neuron::connect(int connectID)
{
    neuronConnection tempConnect;
    tempConnect.id = connectID;
    tempConnect.weight = 1.0 * (std::rand() % 1000) / 100;

    neuron::connections.push_back(tempConnect);
}

void neuron::setPos()
{
    neuron::position[0] = 1.0 * (rand() % 1000000) - 500000;
    neuron::position[1] = 1.0 * (rand() % 1000000) - 500000;
}

void neuron::addInput(double newInputValue, double newInputWeight)
{
    inputValue newInput = {newInputWeight, newInputWeight};

    neuron::inputValues.push_back(newInput);
}

void neuron::clearInputs()
{
    neuron::inputValues.clear();
}

void neuron::activate()
{
    value = neuron::calcDelta();
    printf("Neuron Value : %f\n", neuron::value);
}

double neuron::sigm(double x)
{
    return 1 / (1 + exp(-x));
}

double neuron::calcDelta()
{
    double x = 0;
    for(int i = 0; i < neuron::inputValues.size(); i++)
    {
        x += neuron::inputValues[i].value * neuron::inputValues[i].weight;
    }
    x -= neuron::bias;
    return neuron::sigm(x);
}
