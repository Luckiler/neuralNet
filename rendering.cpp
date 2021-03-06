#include "net.h"
#include "neuron.h"
#include "rendering.h"

#include <stdio.h>

#include <GL/glut.h>

namespace render {
float _neuronSize = 0.3;

/// renders the connections for the hidden neurons
void neuralNet(net *rendNetwork, float rendNetSize) {

  for (unsigned int i = 0; i < rendNetwork->neurons.size(); i++) {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslated(rendNetwork->neurons[i]->position[0] * rendNetSize,
                 rendNetwork->neurons[i]->position[1] * rendNetSize,
                 0);
    for (unsigned int j = 0; j < rendNetwork->neurons[i]->connections.size();
         j++) {
      int connectedID = rendNetwork->neurons[i]->connections[j].id;

      if (connectedID < 0) {
        glLoadIdentity();

        glBegin(GL_LINES);
        glColor3f(0, 1, 0);
        //glLineWidth(10);
        glVertex3d(
          -rendNetSize / 2,
          -(connectedID + 1) - 1.0 * (rendNetwork->inputLayer.size() - 1) / 2,
          0);
        glVertex3d(
          rendNetwork->neurons[i]->position[0] * rendNetSize,
          rendNetwork->neurons[i]->position[1] * rendNetSize,
          0);
        glEnd();
      } else {
        glLoadIdentity();

        glColor3f(rendNetwork->neurons[connectedID]->color[0], rendNetwork->neurons[connectedID]->color[1], rendNetwork->neurons[connectedID]->color[2]);

        glBegin(GL_LINES);
        glVertex3d(
            rendNetwork->neurons[i]->position[0] * rendNetSize,
            rendNetwork->neurons[i]->position[1] * rendNetSize,
            0);
        glVertex3d(
          rendNetwork->neurons[connectedID]->position[0] * rendNetSize,
          rendNetwork->neurons[connectedID]->position[1] * rendNetSize,
          0);
        glEnd();
      }
    }
}

  for (unsigned int i = 0; i < rendNetwork->neurons.size(); i++) {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslated(rendNetwork->neurons[i]->position[0] * rendNetSize,
                 rendNetwork->neurons[i]->position[1] * rendNetSize,
                 0);

    glColor3f(rendNetwork->neurons[i]->color[0], rendNetwork->neurons[i]->color[1], rendNetwork->neurons[i]->color[2]);

    square(_neuronSize);
  }

  for (unsigned int i = 0; i < rendNetwork->inputLayer.size(); i++) {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslated(-rendNetSize / 2,
                 i - 1.0 * (rendNetwork->inputLayer.size() - 1) / 2, 0);

    glColor3f(0, 1, 0);

    square(_neuronSize);
  }


for (unsigned int i = 0; i < rendNetwork->outputLayer.size(); i++) {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    for (unsigned int j = 0;
         j < rendNetwork->outputLayer[i]->connections.size(); j++) {
      int connectedID = rendNetwork->outputLayer[i]->connections[j].id;

      glLoadIdentity();

      glColor3f(rendNetwork->neurons[connectedID]->color[0], rendNetwork->neurons[connectedID]->color[1], rendNetwork->neurons[connectedID]->color[2]);

      glBegin(GL_LINES);
      glVertex3d(rendNetSize / 2,
                 i - 1.0 * (rendNetwork->outputLayer.size() - 1) / 2, 0);
      glVertex3d(rendNetwork->neurons[connectedID]->position[0] * rendNetSize,
                 rendNetwork->neurons[connectedID]->position[1] * rendNetSize,
                 0);
      glEnd();

    }
  }

  /// renders the output layer
  for(unsigned int i = 0; i < rendNetwork->outputLayer.size(); i++) {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslated(rendNetSize / 2,
                 i - 1.0 * (rendNetwork->outputLayer.size() - 1) / 2, 0);

    glColor3f(1, 0, 0);

    square(_neuronSize);
  }
}

void square(float eSize) {
  float pos = eSize / 2;
  glMatrixMode(GL_MODELVIEW);
  glBegin(GL_QUADS);
  glVertex3f(pos, -pos, 0.0);
  glVertex3f(pos, pos, 0.0);
  glVertex3f(-pos, pos, 0.0);
  glVertex3f(-pos, -pos, 0.0);
  glEnd();
}
}
