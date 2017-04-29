#include "ManlyBomber.hpp"

ManlyBomber::ManlyBomber()
    :Hero(1.0f, -2.6f, 4.0f, "manlyBomber.png")
{
    vertices = new float[30]
    {
        // Coordinates          // Texture coordinates
        -0.05f, -0.05f, 0.05f,  0.0f, 0.0f,
        0.05f, -0.05f, 0.05f,   1.0f, 0.0f,
        0.05f, 0.05f, 0.05f,    1.0f, 1.0f,

        -0.05f, -0.05f, 0.05f,  0.0f, 0.0f,
        -0.05f, 0.05f, 0.05f,   0.0f, 1.0f,
        0.05f, 0.05f, 0.05f,    1.0f, 1.0f
    };
}

ManlyBomber::~ManlyBomber()
{}

void ManlyBomber::specialAction()
{

}

void ManlyBomber::idle()
{

}
