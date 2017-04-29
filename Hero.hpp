#ifndef HERO_HPP
#define HERO_HPP

#include <string>
#include <iostream>

class Hero
{
friend class Player;

public:
    virtual ~Hero ();
private:
    Hero() = delete;

    virtual void idle() = 0;
    virtual void specialAction() = 0;

    float speed;
    float gravity;
    float jumpHeight;
    std::string texturePath;
protected:
    Hero (const float, const float, const float, const std::string&);
    float* vertices;
};

#endif
