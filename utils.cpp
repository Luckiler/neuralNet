#include "utils.h"

#include <algorithm>

unsigned int randSeed;

float clamp(float n, float lower, float upper) {
  return std::max(lower, std::min(n, upper));
}

void initRand(unsigned int seed) {
  generator.seed(seed);
}

double genRandd(double minValue, double maxValue) {
  std::uniform_real_distribution<double> dist(minValue, maxValue);
  return clamp(dist(generator), minValue, maxValue);
}

int genRand(int minValue, int maxValue) {
  std::uniform_int_distribution<int> dist(minValue, maxValue);
  return clamp(dist(generator), minValue, maxValue);
}
