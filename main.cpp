/**
 * This is an attemps of using a neural network without layers. It seems like a
 * better simulation of an actual brain.
 * @author Luckiler
 */

#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <vector>

#include <GL/glut.h>

#include "neuron.h"
#include "net.h"
#include "rendering.h"

bool generateNewNet = true;

float zoom = 10;
float winRatio;
int winX;
int winY;

float renderSize;

int NuberOfNeurons;

bool changeZoom = true;

net *network;

float clamp(float n, float lower, float upper) {
  return std::max(lower, std::min(n, upper));
}

void processNormalKeys(unsigned char key, int x, int y) {

	if (key == 27)
	{
		delete network;
		exit(0);
    }
    if(key ==  'a')
    {
        network->activate();

        std::cout << "Network activated" << std::endl;

        for(unsigned int i = 0; i < network->outputLayer.size(); i++)
        {
            std::cout << "Out 1 : " << network->getOutput(i) << " ";
        }
        std::cout << std::endl;
    }
}

void processSpecialKeys(int key, int x, int y) {
    int mod = glutGetModifiers();

	switch(key) {
        case GLUT_KEY_UP :
            if(mod == GLUT_ACTIVE_CTRL)
            {
                zoom -= zoom * 0.1;
                changeZoom = true;
            }
            else
            {
                glMatrixMode(GL_PROJECTION);
                glTranslated(0.0, -0.1 * zoom, 0.0);
            }
            break;
        case GLUT_KEY_DOWN :
            if(mod == GLUT_ACTIVE_CTRL)
            {
                zoom += zoom * 0.1;
                changeZoom = true;
            }
            else
            {
                glMatrixMode(GL_PROJECTION);
                glTranslated(0.0, 0.1 * zoom, 0.0);
            }
            break;
        case GLUT_KEY_LEFT :
            glMatrixMode(GL_PROJECTION);
            glTranslated(0.1 * zoom, 0.0, 0.0);
            break;
        case GLUT_KEY_RIGHT :
            glMatrixMode(GL_PROJECTION);
            glTranslated(-0.1 * zoom, 0.0, 0.0);
            break;
	}
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    if(changeZoom)
    {
        glViewport(0, 0, winX, winY);

        glMatrixMode(GL_PROJECTION);

        glLoadIdentity();
        glOrtho(-winRatio * zoom, winRatio * zoom, -zoom, zoom, -1, 1);
        glMatrixMode(GL_MODELVIEW);

        changeZoom = false;
    }

    if(generateNewNet)
    {

        network = new net();
        network->create(NuberOfNeurons, 7, 3);
        network->initialize();
        generateNewNet = false;
    }

    render::neuralNet(network, renderSize);

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    if(h == 0)
		h = 1;

	winX = w;
	winY = h;

	winRatio = 1.0 * w / h;

    glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
	glOrtho(-winRatio * zoom, winRatio * zoom, -zoom, zoom, -1, 1);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    std::cout << "Number of neurons: ";
    std::cin >> NuberOfNeurons;
    std::cout << "Size of the net: ";
    std::cin >> renderSize;
    std::cout << "Seed :";
    int seed;
    std::cin >> seed;
    std::srand(seed);

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE |GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(500,400);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Tests");

    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(reshape);

    glutIgnoreKeyRepeat(0);
    glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);

    glutMainLoop();
}
