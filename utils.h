#ifndef UTILS_H
#define UTILS_H

#include <algorithm>

static std::mt19937 generator;

struct neuronConnection {
  int id = -1000;
  float weight = 0;
};

void initRand(unsigned int seed);

double genRandd(double minValue, double maxValue);

int genRand(int minValue, int maxValue);

float clamp(float n, float lower, float upper);

#endif
