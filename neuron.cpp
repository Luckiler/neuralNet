#include "neuron.h"
#include "net.h"
#include "utils.h"

#include <stdio.h>

neuron::neuron() {
  neuron::setPos();
  neuron::color[0] = genRandd(0, 1);
  neuron::color[1] = genRandd(0, 1);
  neuron::color[2] = genRandd(0, 1);
  }

void neuron::evolve(int changeChance, int changeQnt) {
  int x = genRandd(0, 100);

  if (x < changeChance) {
    neuron::bias += neuron::bias * (genRandd(-changeQnt / 200, changeQnt / 200) / 100);
    //printf("Neuron initialized with mutated values\n");
  } else {
    //printf("Neuron initialized with inherited values\n");
  }
}

void neuron::initialze(int ID) {
  neuron::id = ID;
  neuron::bias = genRandd(-10, 10);
  if(neuron::bias > 10 || neuron::bias < -10) {
    //printf("Bias overload\n");
  }
  neuron::value = genRandd(-10, 10);
  if(neuron::value > 10 || neuron::value < -10) {
    //printf("Value overload\n");
  }
  //printf("Neuron %d init : V = %.2f B = %.2f\n", neuron::id, neuron::value, neuron::bias);
}

void neuron::connect(int connectID) {
  neuronConnection tempConnect;
  tempConnect.id = connectID;
  tempConnect.weight = genRandd(-1 , 1);

  neuron::connections.push_back(tempConnect);
}

void neuron::setPos() {
  neuron::position[0] = genRandd(-0.5, 0.5);
  neuron::position[1] = genRandd(-0.5, 0.5);
}

void neuron::addInput(double newInputValue, double newInputWeight) {
  inputValue newInput;
  newInput.value = newInputValue;
  newInput.weight = newInputWeight;

  //printf("Added input: %.3f with a weight of %.3f\n", newInputValue, newInputWeight);

  neuron::inputValues.push_back(newInput);
}

void neuron::clearInputs() { neuron::inputValues.clear(); }

void neuron::activate() {
  value = neuron::calcDelta();
}

double neuron::sigm(double x) {
  float oldx = x;
  x = x / (1 + exp(x));
  if(x > 1 || x < -1) {
    //printf("sigm ERROR: calculated: %f | input: %f\n", x, oldx);
    return 0;
  } else {
    return x;
  }
}

double neuron::calcDelta() {
  double x = 0;
  //printf("x = ");
  for (unsigned int i = 0; i < neuron::inputValues.size(); i++) {
    x += neuron::inputValues[i].value * neuron::inputValues[i].weight;
    //printf("%d * %d |", neuron::inputValues[i].value, neuron::inputValues[i].weight);
  }
  x -= neuron::bias;
  return neuron::sigm(x);
}
