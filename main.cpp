/**
 * This is an attempt of using a neural network without layers. It seems like a
 * better simulation of an actual brain.
 * @author Luckiler
 */

#include <stdlib.h>
#include <GL/glut.h>
#include <vector>
#include "neuron.h"
#include "net.h"
#include "rendering.h"
#include "utils.h"

bool generateNewPopulation = true;
///Window information (for glut)
float zoom = 10;
float winRatio;
int winX;
int winY;
bool changeZoom = true;
///Temporary inputs
int mouseX = 0;
int mouseY = 0;
///parameters for the population and its members
int popSize = 1;
int generation = 0;
int evolvStages = 0;
int NuberOfNeurons;
double bestFitness = 10000000000;
float renderSize = 19;
///The population itself
std::vector<net*> population;

/**
 *  Function to process the normal keyboards inputs
 */
void processNormalKeys(unsigned char key, int x, int y) {
  ///"esc"
  if (key == 27 ) {
    ///clears memory and exits the application
    population.clear();
    exit(0);
  }
  if (key == 'n') {
    ///Triggers the evolution of the current population
    generateNewPopulation = true;
  }
}
/**
 *  Function to process the special keyboards inputs
 */
void processSpecialKeys(int key, int x, int y) {
  ///CTRL, SHIFT, ALT
  int mod = glutGetModifiers();
  switch (key) {
    case GLUT_KEY_UP:
      ///Zooms in
      if (mod == GLUT_ACTIVE_CTRL) {
        zoom -= zoom * 0.1;
        changeZoom = true;
      }
      ///Moves the camera up
      else {
        glMatrixMode(GL_PROJECTION);
        glTranslated(0.0, -0.1 * zoom, 0.0);
      }
      break;
    case GLUT_KEY_DOWN:
      ///Zooms out
      if (mod == GLUT_ACTIVE_CTRL) {
        zoom += zoom * 0.1;
        changeZoom = true;
      }
      ///Moves the camera down
      else {
        glMatrixMode(GL_PROJECTION);
        glTranslated(0.0, 0.1 * zoom, 0.0);
      }
      break;
    case GLUT_KEY_LEFT:
      glMatrixMode(GL_PROJECTION);
      glTranslated(0.1 * zoom, 0.0, 0.0);
      break;
    case GLUT_KEY_RIGHT:
      glMatrixMode(GL_PROJECTION);
      glTranslated(-0.1 * zoom, 0.0, 0.0);
      break;
  }
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (changeZoom) {
    glViewport(0, 0, winX, winY);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    glOrtho(-winRatio * zoom, winRatio * zoom, -zoom, zoom, -1, 1);
    glMatrixMode(GL_MODELVIEW);

    changeZoom = false;
  }
  ///Called when changing generations
  if (generateNewPopulation) {
    double avgFitness = 0;
    ///Check if this is not the first generation
    if(population.size() > 0) {
      printf("Evolving pop\n");
      ///Calculates the average fitness of this generation
      for(unsigned int i =0; i < population.size(); i++) {
        avgFitness += population[i]->getFitness();
        ///Checks if a member of this generation had the best fitness ever
        if(population[i]->getFitness() < bestFitness) {
          bestFitness = population[i]->getFitness();
        }
      }
      avgFitness /= population.size();
      printf("avgFitness %f | best Fitness %f", avgFitness, bestFitness);
      ///Eliminates the bad individuals
      for(unsigned int i = 0; i < population.size(); i++) {
        ///Is bad if it's fitness is more than 30% worst than the best
        if(population[i]->getFitness() > (bestFitness + (bestFitness * 0.3))) {
          delete population[i];
          population.erase(population.begin() + i);
        }
      }
      ///repopulates the new generation
      while(population.size() <= popSize) {
        ///If will replace the killed member by an elder or by creating a new random one
        float test = genRandd(0, 100);
        if(test < 95) {
          int parentNet = genRand(0, population.size() - 1);
          population.push_back(population[parentNet]);
        } else {
          net* network = new net;
          network->create(NuberOfNeurons, 4, 5);
          network->initialize();
          population.push_back(network);
        }
      }
      printf("PopSize : %d\n", population.size());
      ///Makes each individual in this new population evolve
      for(unsigned int i = 0; i < population.size(); i++) {
        population[i]->evolve();
      }
      generateNewPopulation = false;
    }
    else {
      printf("Generating new pop\n");
      ///Creates as many random new neural nets as there are members in the population
      for(unsigned int i = 0; i < popSize; i++) {
        net* network = new net;
        network->create(NuberOfNeurons, 4, 5);
        network->initialize();
        population.push_back(network);
        generateNewPopulation = false;
      }
    }
    ///WIP
    //Need to adapt the values (needs more investigation and testing)
    if(evolvStages % 500 == 0 || evolvStages == 0 || avgFitness < 0.1) {
      mouseX = genRandd(0, 10);
      mouseY = genRandd(0, 10);
      evolvStages ++;
    }

    for(unsigned int i = 0; i < population.size(); i++) {
      population[i]->updateInput(mouseX, 0);
      population[i]->updateInput(mouseY, 1);
  }
  }


  /*for(unsigned int i = 0; i < population.size(); i++) {
    glTranslated(3, 3, 0);
    render::neuralNet(population[i], renderSize);
  }*/
  glMatrixMode(GL_MODELVIEW);

  for(unsigned int i = 0; i < population.size(); i++) {
    population[i]->activate();
    glLoadIdentity();
    glTranslated(population[i]->aiPosX, population[i]->aiPosY, 0);
    glColor3f(population[i]->aiColorR, population[i]->aiColorG, population[i]->aiColorB);
    render::square(0.5);
    glLoadIdentity();
    glBegin(GL_LINES);
      glVertex3d(population[i]->aiPosX, population[i]->aiPosY, 0);
      glVertex3d(mouseX, mouseY, 0);
    glEnd();
  }

  simTick++;

  if(simTick > 100) { generateNewPopulation = true; simTick = 0;}

  glutSwapBuffers();
}

void reshape(int w, int h) {
  if (h == 0) h = 1;

  winX = w;
  winY = h;

  winRatio = 1.0 * w / h;

  glViewport(0, 0, w, h);

  glMatrixMode(GL_PROJECTION);

  glLoadIdentity();
  glOrtho(-winRatio * zoom, winRatio * zoom, -zoom, zoom, -1, 1);
  glMatrixMode(GL_MODELVIEW);
}

void mouseClick(int x, int y) {
  mouseX = x;
  mouseY = y;
  for(unsigned int i = 0; i < population.size(); i++) {
    population[i]->updateInput(x, 0);
    population[i]->updateInput(y, 1);
  }
}

int main(int argc, char** argv) {
  std::cout << "Number of neurons: ";
  std::cin >> NuberOfNeurons;
  std::cout << "Population size: ";
  std::cin >> popSize;
  std::cout << "Seed :";
  unsigned int seed;
  std::cin >> seed;
  initRand(seed);

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);
  glEnable(GLUT_MULTISAMPLE);
  glutInitWindowSize(500, 400);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Tests");

  glutDisplayFunc(display);
  glutIdleFunc(display);
  glutReshapeFunc(reshape);

  glutIgnoreKeyRepeat(0);
  glutKeyboardFunc(processNormalKeys);
  glutSpecialFunc(processSpecialKeys);
  //glutPassiveMotionFunc(mouseClick);

  glutMainLoop();
}
