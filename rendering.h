#ifndef RENDERING_H
#define RENDERING_H

#include "neuron.h"
#include "net.h"

namespace render
{
    /**
    * Renders a neural network. Renders all the layers, including neurons
    * and connections.
    *
    * @param rendnetwork - The network to render
    */
    void neuralNet(net *rendNetwork, float rendNetSize);
    /**
    * Renders a simple square.
    *
    * @param eSize - the size of the edge of the square.
    */
    void square(float eSize);
}

#endif
