#ifndef PLAYER_HPP
#define PLAYER_HPP

#define GLFW_KEY_A 65
#define GLFW_KEY_B 66
#define GLFW_KEY_C 67
#define GLFW_KEY_D 68
#define GLFW_KEY_E 69
#define GLFW_KEY_F 70
#define GLFW_KEY_G 71
#define GLFW_KEY_H 72
#define GLFW_KEY_I 73
#define GLFW_KEY_J 74
#define GLFW_KEY_K 75
#define GLFW_KEY_L 76
#define GLFW_KEY_M 77
#define GLFW_KEY_N 78
#define GLFW_KEY_O 79
#define GLFW_KEY_P 80
#define GLFW_KEY_Q 81
#define GLFW_KEY_R 82
#define GLFW_KEY_S 83
#define GLFW_KEY_T 84
#define GLFW_KEY_U 85
#define GLFW_KEY_V 86
#define GLFW_KEY_W 87
#define GLFW_KEY_X 88
#define GLFW_KEY_Y 89
#define GLFW_KEY_Z 90

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
friend class Hero;

public:
    Player (const glm::vec3&, const Heroes);
    virtual ~Player ();
    const glm::mat4& getModelMatrix() const;
    const GLuint getTexture() const;
    void draw();
    void specialAction();
    void move(const bool[], const float);
    void jump();
    void idle(const float);
private:
    Player() = delete;
    glm::vec3 position;
    glm::mat4 model;
    glm::vec3 jumpVector;
    bool touchedGround;
    bool onWall;
    Hero* hero;
    GLuint vao;
    GLuint vbo;
    GLuint texture;
};

#endif
