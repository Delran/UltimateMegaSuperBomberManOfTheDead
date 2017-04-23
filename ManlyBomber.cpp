#include "ManlyBomber.hpp"

ManlyBomber::ManlyBomber()
    :Hero(1.0f, 3.0f, "texture.png")
{
    vertices = new float[36]
    {
        // Coordinates       // Colors
        -0.1f, -0.1f, 0.1f,  0.0f, 0.0f, 1.0f,
        -0.1f, 0.1f, 0.1f,   0.0f, 0.0f, 1.0f,
        0.1f, 0.1f, 0.1f,    0.0f, 0.0f, 1.0f,

        -0.1f, -0.1f, 0.1f,  0.0f, 0.0f, 1.0f,
        0.1f, -0.1f, 0.1f,   0.0f, 0.0f, 1.0f,
        0.1f, 0.1f, 0.1f,    0.0f, 0.0f, 1.0f
    };
}

ManlyBomber::~ManlyBomber()
{

}

void ManlyBomber::specialAction()
{

}

void ManlyBomber::idle()
{

}
