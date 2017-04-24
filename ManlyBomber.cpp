#include "ManlyBomber.hpp"

ManlyBomber::ManlyBomber()
    :Hero(1.0f, 3.0f, "manlyBomber.jpg")
{
    vertices = new float[30]
    {
        // Coordinates       // Texture coordinates
        -0.1f, -0.1f, 0.1f,  0.0f, 0.0f,
        0.1f, -0.1f, 0.1f,   1.0f, 0.0f,
        0.1f, 0.1f, 0.1f,    1.0f, 1.0f,

        -0.1f, -0.1f, 0.1f,  0.0f, 0.0f,
        -0.1f, 0.1f, 0.1f,   0.0f, 1.0f,
        0.1f, 0.1f, 0.1f,    1.0f, 1.0f
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
