#include "net.h"

#include <vector>
#include <stdio.h>
#include <cstdlib>

net::net()
{
}

void net::create(int NbroNeurons, int NbroInputs, int NbroOutputs)
{
    for(int i = 0; i < NbroNeurons; i++)
    {
        neuron* newNeuron = new neuron;
        newNeuron->id = i;
        net::neurons.push_back(newNeuron);
    }

    for(int i = 0; i < NbroInputs; i++)
    {
        net::inputLayer.push_back(0.0);
    }

    for(unsigned int i = 0; i < NbroOutputs; i++)
    {
        neuron* newNeuron = new neuron;

        net::outputLayer.push_back(newNeuron);
    }
}

void net::initialize()
{
    ///creates connections between neurons
    for(unsigned int i = 0; i < net::neurons.size(); i++)
    {
        while(!net::neurons[i]->isConnected)
        {
            for(unsigned int j = 0; j < net::neurons.size(); j++)
            {
                int connect = std::rand() % 10;

                if(connect < 1 && j != net::neurons[i]->id)
                {
                    net::neurons[i]->connect(j);
                    net::neurons[i]->isConnected = true;
                }

                int inputConnect = std::rand() % 100;
                if(inputConnect < 1)
                {
                    int inputID = std::rand() % (net::inputLayer.size());
                    net::neurons[i]->connect(-(inputID + 1));
                    net::neurons[i]->isConnected = true;
                }
            }
        }
    }

    ///creates the connections between the output layer and the neurons
    for(unsigned int i = 0; i < net::outputLayer.size(); i++)
    {
        for(unsigned int j = 0; j < net::neurons.size(); j++)
        {
            int connect = std::rand() % 10;

            if(connect < 1)
            {
                net::outputLayer[i]->connect(j);
            }
        }
    }
}

void net::activate()
{
    for(unsigned int i = 0; i < net::neurons.size(); i++)
    {
        if(net::neurons[i]->inputValues.size() != net::neurons[i]->connections.size())
        {
            net::neurons[i]->clearInputs();

            for(unsigned int j = 0; j < net::neurons[i]->connections.size(); j++)
            {
                if(net::neurons[i]->connections[j].id < 0)
                {
                    net::neurons[i]->addInput(net::inputLayer[-net::neurons[i]->connections[j].id],
                                             net::neurons[i]->connections[j].weight);
                } else
                {
                    net::neurons[i]->addInput(net::neurons[net::neurons[i]->connections[j].id]->value,
                                             net::neurons[i]->connections[j].weight);
                }
            }
        }

        net::neurons[i]->activate();
    }
}

double net::getOutput(int i)
{
    if(net::outputLayer[i]->inputValues.size() != net::outputLayer[i]->connections.size())
    {
        printf("Clearing outputs");

        net::outputLayer[i]->clearInputs();

        for(unsigned int j = 0; j < net::outputLayer[i]->connections.size(); j++)
        {
            if(net::outputLayer[i]->connections[j].id < 0)
            {
                net::outputLayer[i]->addInput(net::inputLayer[-net::outputLayer[i]->connections[j].id],
                                         net::outputLayer[i]->connections[j].weight);
            } else
            {
                net::outputLayer[i]->addInput(net::outputLayer[net::outputLayer[i]->connections[j].id]->value,
                                         net::outputLayer[i]->connections[j].weight);
            }
        }
    }

    net::outputLayer[i]->activate();
    return net::outputLayer[i]->value;
}
