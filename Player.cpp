#include "Player.hpp"

Player::Player(const glm::vec3& initialPosition, const Heroes selectedHero)
    :position(initialPosition)
{
    switch (selectedHero)
    {
        case Heroes::MANLY_BOMBER:
            hero = new ManlyBomber;
            break;
    }

    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    const float* vertices = hero->getVertices();
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

Player::~Player(){}

void Player::draw()
{
    hero->idle();

    glBindVertexArray(vao);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindVertexArray(0);
}

void Player::specialAction()
{
    hero->specialAction();
}

const glm::mat4& Player::getModelMatrix() const
{
    return model;
}
