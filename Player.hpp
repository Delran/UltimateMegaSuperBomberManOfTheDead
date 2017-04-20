// Glew
#include <GL/glew.h>

// Glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Player
{
public:
    Player(const glm::vec3& _position);
    virtual ~Player();
    const glm::vec3& getPosition() const;
    void draw();
private:
    Player() = delete;
    glm::vec3 position;
    GLuint vbo;
    GLuint vao;
    float vertices[36]
    {
        // Coordinates          // Colors
        -0.1f, -0.1f, +0.1f,    +0.0f, +0.0f, +1.0f,
        -0.1f, +0.1f, +0.1f,    +0.0f, +0.0f, +1.0f,
        +0.1f, +0.1f, +0.1f,    +0.0f, +0.0f, +1.0f,

        -0.1f, -0.1f, +0.1f,    +0.0f, +0.0f, +1.0f,
        +0.1f, -0.1f, +0.1f,    +0.0f, +0.0f, +1.0f,
        +0.1f, +0.1f, +0.1f,    +0.0f, +0.0f, +1.0f
    };
};
