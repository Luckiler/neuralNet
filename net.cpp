#include "net.h"

#include <vector>
#include <stdio.h>
#include <cstdlib>
#include <random>

net::net() {}

void net::create(int NbroNeurons, int NbroInputs, int NbroOutputs) {
  for (int i = 0; i < NbroNeurons; i++) {
    neuron* newNeuron = new neuron;
    newNeuron->initialze(i);
    net::neurons.push_back(newNeuron);
  }

  for (int i = 0; i < NbroInputs; i++) {
    net::inputLayer.push_back(0.0);
  }

  for (int i = 0; i < NbroOutputs; i++) {
    neuron* newNeuron = new neuron;
    newNeuron->initialze(i);
    net::outputLayer.push_back(newNeuron);
  }
}

void net::initialize() {

  /// creates connections between neurons
  for (unsigned int i = 0; i < net::neurons.size(); i++) {
    while (!net::neurons[i]->isConnected) {
      for (int j = 0; j < net::neurons.size(); j++) {
        float connect = genRandd(0, 100);

        if (connect < 10 && j != net::neurons[i]->id) {
          net::neurons[i]->connect(j);
          net::neurons[i]->isConnected = true;
        }

        float inputConnect = genRandd(0, 100);
        if (inputConnect < 1) {
          int inputID = genRand(0, net::inputLayer.size() - 1);
          net::neurons[i]->connect(-(inputID + 1));
          net::neurons[i]->isConnected = true;
        }
      }
    }
  }

  /// creates the connections between the output layer and the neurons
  for (unsigned int i = 0; i < net::outputLayer.size(); i++) {
    while(!net::outputLayer[i]->isConnected) {
      for (unsigned int j = 0; j < net::neurons.size(); j++) {
        int connect = genRandd(0, 100);

        if (connect < 0.5) {
          net::outputLayer[i]->connect(j);
          net::outputLayer[i]->isConnected = true;
        }
      }
    }
  }
}

void net::activate() {
  for (unsigned int i = 0; i < net::neurons.size(); i++) {
    net::neurons[i]->clearInputs();
    for (unsigned int j = 0; j < net::neurons[i]->connections.size(); j++) {
      if (net::neurons[i]->connections[j].id < 0) {
        net::neurons[i]->addInput(net::inputLayer[-net::neurons[i]->connections[j].id - 1],
                                  net::neurons[i]->connections[j].weight);
      }
      else {
        net::neurons[i]->addInput(net::neurons[net::neurons[i]->connections[j].id]->value,
                                  net::neurons[i]->connections[j].weight);
      }
    }
    net::neurons[i]->activate();

    aiPosX = aiPosX + net::getOutput(0) / 100;
    aiPosX = clamp(aiPosX, -10, 10);
    aiPosY = aiPosY + net::getOutput(1) / 100;
    aiPosY = clamp(aiPosY, -10, 10);

    updateInput(aiPosX, 2);
    updateInput(aiPosX, 3);

    ticksLived += 1;
    fitness += sqrt(pow(aiPosX - net::inputLayer[0], 2) + pow(aiPosY - net::inputLayer[1], 2));

    aiColorR = clamp(net::getOutput(2), 0.1, 1);
    aiColorG = clamp(net::getOutput(3), 0.1, 1);
    aiColorB = clamp(net::getOutput(4), 0.1, 1);
  }
}

void net::updateInput(float newInputValue, int inputId) {
  if(inputId < net::inputLayer.size()) {
    net::inputLayer[inputId] = newInputValue;
  } else {
    printf("\t\t\t\tError: input Id out of range\n");
  }
}

double net::getOutput(int i) {
    net::outputLayer[i]->clearInputs();

    for (unsigned int j = 0; j < net::outputLayer[i]->connections.size(); j++) {
      if (net::outputLayer[i]->connections[j].id < 0) {
        net::outputLayer[i]->addInput(
          net::inputLayer[-net::outputLayer[i]->connections[j].id],
          net::outputLayer[i]->connections[j].weight);
      } else {
        net::outputLayer[i]->addInput(
          net::neurons[net::outputLayer[i]->connections[j].id]->value,
          net::outputLayer[i]->connections[j].weight);
      }
    }

  net::outputLayer[i]->activate();
  return net::outputLayer[i]->value;
}

double net::getFitness() { return net::fitness / net::ticksLived; }

void net::evolve() {
  net::aiPosX = 0;
  net::aiPosY = 0;
  net::aiColorR = 0.1;
  net::aiColorG = 0.1;
  net::aiColorB = 0.1;
  net::ticksLived = 0;
  net::fitness = 0;
  for(unsigned int i = 0; i < neurons.size(); i++) {
    net::neurons[i]->evolve(net::changeChance, net::changeQnt);
  }
  ///Will it create a new new neuron in the net
  float newNeuronPrb = genRandd(0, 100);
  if(newNeuronPrb < 0.5) {
    neuron* newNeuron = new neuron;
    int newNeuronId = net::neurons.size()
    newNeuron->initialze(newNeuronId);
    net::neurons.push_back(newNeuron);
    ///Will this neuron connect to the others
    for (int j = 0; j < net::neurons.size(); j++) {
      float connect = genRandd(0, 100);
      if (connect < 10 && j != newNeuronId) {
        net::neurons[newNeuronId]->connect(j);
        net::neurons[newNeuronId]->isConnected = true;
      }
    }
    ///Will this neuron connect to the input layer
    float inputConnect = genRandd(0, 100);
    if (inputConnect < 1) {
      int inputID = genRand(0, net::inputLayer.size() - 1);
      net::neurons[i]->connect(-(inputID + 1));
      net::neurons[i]->isConnected = true;
    }
  }
}

