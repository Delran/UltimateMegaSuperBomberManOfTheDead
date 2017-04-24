#include "Hero.hpp"

Hero::Hero (const float _speed, const float _bombHoldingTime, const std::string& _texturePath)
    :speed(_speed), bombHoldingTime(_bombHoldingTime), texturePath(_texturePath)
{}

Hero::~Hero()
{
    delete[] vertices;
}
