#ifndef PLAYER_HPP
#define PLAYER_HPP

// Glew
#include <GL/glew.h>

// Glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Hero class
#include "Hero.hpp"

// Heroes classes
#include "ManlyBomber.hpp"

/* --- Heroes enumeration --- */

enum class Heroes
{
    MANLY_BOMBER = 0
};

class Player
{
public:
    Player (const glm::vec3& initialPosition, const Heroes selectedHero);
    virtual ~Player ();
    const glm::mat4& getModelMatrix() const;
    void draw();
    void specialAction();
private:
    Player() = delete;
    glm::vec3 position;
    glm::mat4 model;
    Hero* hero;
    GLuint vao;
    GLuint vbo;
    GLuint playerTexture;
};

#endif
