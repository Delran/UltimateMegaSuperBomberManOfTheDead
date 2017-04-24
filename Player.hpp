#ifndef PLAYER_HPP
#define PLAYER_HPP

// Glew
#include <GLEW/glew.h>

// Soil
#include <SOIL/SOIL.h>

// Glm
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

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
    Player (const glm::vec3&, const Heroes);
    virtual ~Player ();
    const glm::mat4& getModelMatrix() const;
    const GLuint getTexture() const;
    void draw();
    void specialAction();
    void move();
private:
    Player() = delete;
    glm::vec3 position;
    glm::mat4 model;
    Hero* hero;
    GLuint vao;
    GLuint vbo;
    GLuint texture;
};

#endif
