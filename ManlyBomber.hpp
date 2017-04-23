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
