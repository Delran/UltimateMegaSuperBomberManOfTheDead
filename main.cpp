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
Camera camera (glm::vec3 (0.0f, 0.0f, 3.0f), glm::vec3 (0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 45.0f);

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

    // Reorient the camera with the mouse offset
    camera.processMouseMovement(xOffset, yOffset, deltaTime);
}

/* --- Movement function --- */

void doMovement()
{
    // Move the camera in the chosen direction
    if (keys[GLFW_KEY_W])
    {
        camera.processKeyboard(CameraMovement::FORWARD, deltaTime);
    }
    if (keys[GLFW_KEY_S])
    {
        camera.processKeyboard(CameraMovement::BACKWARD, deltaTime);
    }
    if (keys[GLFW_KEY_A])
    {
        camera.processKeyboard(CameraMovement::LEFT, deltaTime);
    }
    if (keys[GLFW_KEY_D])
    {
        camera.processKeyboard(CameraMovement::RIGHT, deltaTime);
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

    GLfloat vertices[] =
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
        glm::vec3 (0.0f, 0.5f, 0.0f),
        glm::vec3 (0.0f, -0.5f, 0.0f)
    };

    // Buffers generation
    GLuint vbo;
    GLuint vao;

    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);

    // Fill VBO with data and then bind VBO to VAO
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

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
        glBindVertexArray(vao);

        // Draw both squares
        for (unsigned i = 0; i < 2; i++)
        {
            // Send model matrix to shader program
            glm::mat4 model;
            model = glm::translate(model, positions[i]);
            glUniformMatrix4fv(glGetUniformLocation(shaderProgram.program, "model"), 1, GL_FALSE, glm::value_ptr(model));

            // Draw 3D object in VBO
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }

        // Draw rotating square

        // Send model matrix to shader program
        glm::mat4 model;
        model = glm::rotate(model, glm::radians(20.0f * (GLfloat)glfwGetTime()), glm::vec3(0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram.program, "model"), 1, GL_FALSE, glm::value_ptr(model));

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
