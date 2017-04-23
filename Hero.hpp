#ifndef HERO_HPP
#define HERO_HPP

#include <string>

class Hero
{
public:
    virtual ~Hero ();
    const float* getVertices() const;
    virtual void idle() = 0;
    virtual void specialAction() = 0;
private:
    Hero() = delete;

    float speed;
    float bombHoldingTime;
    std::string texturePath;
protected:
    Hero (const float _speed, const float _bombHoldingTime, const std::string& _texturePath);
    float* vertices;
};

#endif
