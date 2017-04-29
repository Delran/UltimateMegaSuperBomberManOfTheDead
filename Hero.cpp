#include "Hero.hpp"

Hero::Hero (const float _speed, const float _gravity, const float _jumpHeight, const std::string& _texturePath)
    :speed(_speed), gravity(_gravity), jumpHeight(_jumpHeight), texturePath(_texturePath)
{}

Hero::~Hero()
{
    delete[] vertices;
}
