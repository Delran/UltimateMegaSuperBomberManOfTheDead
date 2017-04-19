/* --- Includes --- */

// Standard libraries
#include <iostream>

// Glew
#include <GL/glew.h>

// Glfw
#include <GLFW/glfw3.h>

// Glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// My libraries
#include "Shader.hpp"
#include "Camera.hpp"

/* --- Constants --- */

// Window size
const GLuint WIDTH = 800;
const GLuint HEIGHT = 600;

/* --- Global variables --- */

// Movement vector
glm::vec3 movement;

// Keyboard keys
bool keys[1024];

// Time between 2 frames
GLfloat deltaTime = 0.0f;
GLfloat lastFrameTime = 0.0f;

// Mouse variables
bool firstMouseCallback = true;
GLfloat lastX;
GLfloat lastY;

// Camera
Camera camera (glm::vec3 (0.0f, 0.0f, 2.0f), glm::vec3 (0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 45.0f);

/* --- Key callback function --- */

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // Close window if ESCAPE is pressed
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    // if a key is pressed it is active while it isn't released
    else if (action == GLFW_PRESS)
    {
        keys[key] = true;
    }
    else if (action == GLFW_RELEASE)
    {
        keys[key] = false;
    }
}

/* --- Mouse callback function --- */

void mouseCallback(GLFWwindow* window, double xPos, double yPos)
{
    // To avoid a first huge mouse movement when the mouse enters the window, we get the offset tafter the second frame
    if(firstMouseCallback)
    {
        lastX = xPos;
        lastY = yPos;
        firstMouseCallback = false;
    }

    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;

    lastX = xPos;
    lastY = yPos;
}

/* --- Movement function --- */

void doMovement()
{
    // Move the camera in the chosen direction
    if (keys[GLFW_KEY_W])
    {
        movement += (glm::vec3 (0.0f, 1.0f, 0.0f) * deltaTime);
        if (movement.y > 0.25f)
        {
            movement.y = 0.25f;
        }
    }
    if (keys[GLFW_KEY_S])
    {
        movement -= (glm::vec3 (0.0f, 1.0f, 0.0f) * deltaTime);
        if (movement.y < -0.25f)
        {
            movement.y = -0.25f;
        }
    }
    if (keys[GLFW_KEY_A])
    {
        movement -= (glm::vec3 (1.0f, 0.0f, 0.0f) * deltaTime * 2.0f);
        if (movement.x < -1.375f)
        {
            movement.x = -1.375f;
        }
    }
    if (keys[GLFW_KEY_D])
    {
        movement += (glm::vec3 (1.0f, 0.0f, 0.0f) * deltaTime * 2.0f);
        if (movement.x > 1.375f)
        {
            movement.x = 1.375f;
        }
    }
}

/* --- Main function --- */

int main(int argc, char const *argv[])
{
    // Starting GLFW context
    std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;
    glfwInit();

    // Some GLFW settings
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Game", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Cursor mode
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Activates V-sync
    glfwSwapInterval(1);

    // Set callback functions
    glfwSetKeyCallback(window, keyCallback);
    glfwSetCursorPosCallback(window, mouseCallback);

    // GLEW initialization before any OpenGL operation
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    // Create a viewport in the window
    int winWidth;
    int winHeight;
    glfwGetFramebufferSize(window, &winWidth, &winHeight);
    glViewport(0, 0, winWidth, winHeight);

    // Enable depth control to avoid z-buffer issues
    glEnable(GL_DEPTH_TEST);

    // Creating a shader program and use it
    Shader shaderProgram ("vertexShader.glsl", "fragmentShader.glsl");
    shaderProgram.use();

    GLfloat square[] =
    {
        // Coords               // Colors
        -0.1f, -0.1f, 0.0f,     1.0f, 0.5f, 0.2f,
        -0.1f, 0.1f, 0.0f,      1.0f, 0.5f, 0.0f,
        0.1f, 0.1f, 0.0f,       0.8f, 0.5f, 0.2f,

        -0.1f, -0.1f, 0.0f,     1.0f, 0.5f, 0.2f,
        0.1f, -0.1f, 0.0f,      0.8f, 0.5f, 0.0f,
        0.1f, 0.1f, 0.0f,       0.8f, 0.5f, 0.2f
    };

    glm::vec3 positions[] =
    {
        // Coords
        glm::vec3 (0.0f, 0.75f, 0.0f),
        glm::vec3 (0.0f, -0.75f, 0.0f)
    };

    // Buffers generation
    GLuint vboSquare;
    GLuint vaoSquare;

    glGenBuffers(1, &vboSquare);
    glGenVertexArrays(1, &vaoSquare);

    // Fill VBO with data and then bind VBO to VAO
    glBindVertexArray(vaoSquare);

    glBindBuffer(GL_ARRAY_BUFFER, vboSquare);
    glBufferData(GL_ARRAY_BUFFER, sizeof(square), square, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    GLfloat upBackground[] =
    {
        // Coords               // Colors
        -2.0f, 0.4f, -0.1f,     0.0f, 0.0f, 1.0f,
        -2.0f, 1.5f, -0.1f,     0.0f, 0.0f, 1.0f,
        2.0f, 1.5f, -0.1f,      0.0f, 0.0f, 1.0f,

        -2.0f, 0.4f, -0.1f,     0.0f, 0.0f, 1.0f,
        2.0f, 0.4f, -0.1f,      0.0f, 0.0f, 1.0f,
        2.0f, 1.5f, -0.1f,      0.0f, 0.0f, 1.0f
    };

    // Buffers generation
    GLuint vboUpBackground;
    GLuint vaoUpBackground;

    glGenBuffers(1, &vboUpBackground);
    glGenVertexArrays(1, &vaoUpBackground);

    // Fill VBO with data and then bind VBO to VAO
    glBindVertexArray(vaoUpBackground);

    glBindBuffer(GL_ARRAY_BUFFER, vboUpBackground);
    glBufferData(GL_ARRAY_BUFFER, sizeof(upBackground), upBackground, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    GLfloat downBackground[] =
    {
        // Coords               // Colors
        -2.0f, -0.4f, -0.1f,    1.0f, 0.0f, 0.0f,
        -2.0f, -1.5f, -0.1f,    1.0f, 0.0f, 0.0f,
        2.0f, -1.5f, -0.1f,     1.0f, 0.0f, 0.0f,

        -2.0f, -0.4f, -0.1f,    1.0f, 0.0f, 0.0f,
        2.0f, -0.4f, -0.1f,     1.0f, 0.0f, 0.0f,
        2.0f, -1.5f, -0.1f,     1.0f, 0.0f, 0.0f
    };

    // Buffers generation
    GLuint vboDownBackground;
    GLuint vaoDownBackground;

    glGenBuffers(1, &vboDownBackground);
    glGenVertexArrays(1, &vaoDownBackground);

    // Fill VBO with data and then bind VBO to VAO
    glBindVertexArray(vaoDownBackground);

    glBindBuffer(GL_ARRAY_BUFFER, vboDownBackground);
    glBufferData(GL_ARRAY_BUFFER, sizeof(downBackground), downBackground, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Update delta time
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrameTime;
        lastFrameTime = currentFrame;

        // Callbacks
        glfwPollEvents();
        doMovement();

        // Clear window
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Send projection matrix to shader program
        glm::mat4 projection;
        projection = glm::perspective(camera.getFov(), (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram.program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

        // Send view matrix to shader program
        glm::mat4 view;
        view = camera.getViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram.program, "view"), 1, GL_FALSE, glm::value_ptr(view));

        // Bind VAO
        glBindVertexArray(vaoSquare);

        // Draw player square

        // Send model matrix to shader program
        glm::mat4 modelPlayer;
        modelPlayer = glm::translate(modelPlayer, positions[0]);
        modelPlayer = glm::translate(modelPlayer, movement);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram.program, "model"), 1, GL_FALSE, glm::value_ptr(modelPlayer));

        // Draw 3D object in VBO
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // Draw other player square

        glm::mat4 modelOtherPlayer;
        modelOtherPlayer = glm::translate(modelOtherPlayer, positions[1]);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram.program, "model"), 1, GL_FALSE, glm::value_ptr(modelOtherPlayer));

        // Draw 3D object in VBO
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // Draw bomb square

        // Send model matrix to shader program
        glm::mat4 modelBomb;
        modelBomb = glm::rotate(modelBomb, glm::radians(360.0f * (GLfloat)glfwGetTime()), glm::vec3(0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram.program, "model"), 1, GL_FALSE, glm::value_ptr(modelBomb));

        // Draw 3D object in VBO
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // Unbind VAO
        glBindVertexArray(0);

        // Draw up background

        // Bind VAO
        glBindVertexArray(vaoUpBackground);

        // Send model matrix to shader program
        glm::mat4 modelUpBackground;
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram.program, "model"), 1, GL_FALSE, glm::value_ptr(modelUpBackground));

        // Draw 3D object in VBO
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // Unbind VAO
        glBindVertexArray(0);

        // Draw down background

        // Bind VAO
        glBindVertexArray(vaoDownBackground);

        // Send model matrix to shader program
        glm::mat4 modelDownBackground;
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram.program, "model"), 1, GL_FALSE, glm::value_ptr(modelDownBackground));

        // Draw 3D object in VBO
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // Unbind VAO
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

    // Close window and finish program
    glfwTerminate();
    return 0;
}
