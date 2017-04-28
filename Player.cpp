#include "Player.hpp"

Player::Player(const glm::vec3& initialPosition, const Heroes selectedHero)
    :position(initialPosition), touchedGround(true)
{
    model = glm::translate(model, position);

    switch (selectedHero)
    {
        case Heroes::MANLY_BOMBER:
            hero = new ManlyBomber;
            break;
        default:
            break;
    }

    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 30 * sizeof(GLfloat), hero->vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Some settings for the texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Read texture from file
    int texWidth;
    int texHeight;
    unsigned char* playerImage = SOIL_load_image(hero->texturePath.c_str(), &texWidth, &texHeight, 0, SOIL_LOAD_RGBA);

    // Fill texture with read data
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, playerImage);

    // Generate mipmaps
    glGenerateMipmap(GL_TEXTURE_2D);

    // Properly delete image data
    SOIL_free_image_data(playerImage);

    // Unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

Player::~Player()
{
    // Delete buffers
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

    // Delete hero
    delete hero;
}

void Player::draw()
{
    glBindTexture(GL_TEXTURE_2D, texture);

    glBindVertexArray(vao);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindVertexArray(0);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Player::specialAction()
{
    hero->specialAction();
}

void Player::move(const Direction direction, const float deltaTime)
{
    if (direction == Direction::LEFT)
    {
        position.x -= deltaTime * hero->speed;
        model = glm::translate(model, glm::vec3(-deltaTime * hero->speed, 0.0f, 0.0f));
    }
    else
    {
        position.x += deltaTime * hero->speed;
        model = glm::translate(model, glm::vec3(deltaTime * hero->speed, 0.0f, 0.0f));
    }
}

void Player::jump()
{
    if (touchedGround)
    {
        gravity.y = 4.0f;
        touchedGround = false;
    }
}

void Player::idle(const float deltaTime)
{
    if (!touchedGround)
    {
        gravity.y -= 0.3f;
    }
    if (position.y >= 0.0f)
    {
        position.y += deltaTime * gravity.y;
        model = glm::translate(model, glm::vec3(0.0f, deltaTime * gravity.y, 0.0f));
    }
    if (position.y <= 0.0f)
    {
        touchedGround = true;
        model = glm::translate(model, glm::vec3(0.0f, - position.y, 0.0f));
        position.y = 0.0f;
    }

    hero->idle();
}

const glm::mat4& Player::getModelMatrix() const
{
    return model;
}

const GLuint Player::getTexture() const
{
    return texture;
}
