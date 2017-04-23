#ifndef MANLYBOMBER_HPP
#define MANLYBOMBER_HPP

#include "Hero.hpp"

class ManlyBomber : public Hero
{
public:
    ManlyBomber();
    virtual ~ManlyBomber();
private:
    virtual void specialAction();
    virtual void idle();
};

#endif
