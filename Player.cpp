#include "Player.hpp"

Player::Player(const glm::vec3& initialPosition, const Heroes selectedHero)
    :position(initialPosition)
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
    glBufferData(GL_ARRAY_BUFFER, 36 * sizeof(GLfloat), hero->vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    glGenTextures(1, &playerTexture);
    glBindTexture(GL_TEXTURE_2D, playerTexture);

    // Some settings for the texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Read texture from file
    int texWidth;
    int texHeight;
    /*unsigned char* playerImage = SOIL_load_image(hero->texturePath, &texWidth, &texHeight, 0, SOIL_LOAD_RGB);

    // Fill texture with read data
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, playerImage);

    // Generate mipmaps
    glGenerateMipmap(GL_TEXTURE_2D);

    // Properly delete image data
    SOIL_free_image_data(playerImage);*/
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
