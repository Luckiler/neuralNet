#ifndef NET_H
#define NET_H

#include "neuron.h"

#include <vector>
#include <cstdlib>

class net {
 public:
  // % of mods
  int changeChance = 60;
  int changeQnt = 20;

  long int ticksLived = 0;
  float fitness = 0;

  float aiPosX = 0;
  float aiPosY = 0;
  float aiColorR = 0.1;
  float aiColorG = 0.1;
  float aiColorB = 0.1;

  // the actual net structure
  std::vector<neuron*> neurons;

  // input layer
  std::vector<float> inputLayer;
  // output layer
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

  void updateInput(float newInputValue, int inputId);

  double getOutput(int i);
  double getFitness();

  void evolve();

 private:
};

#endif
