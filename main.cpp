/* --- Includes --- */

// Standard libraries
#include <iostream>

// Glew
#include <GLEW/glew.h>

// Glfw
#include <GLFW/glfw3.h>

// Glm
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

// My libraries
#include "Shader.hpp"
#include "Camera.hpp"
#include "Player.hpp"

/* --- Constants --- */

// Window size
const GLuint WIDTH = 1920;
const GLuint HEIGHT = 1080;

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
Camera camera (glm::vec3 (0.0f, 0.0f, 2.0f), glm::vec3 (0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 45.0f);

// Player
Player* player;

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

    /*GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;*/

    lastX = xPos;
    lastY = yPos;
}

/* --- Movement function --- */

void doMovement()
{
    // Move the camera in the chosen direction
    if (keys[GLFW_KEY_W])
    {
        player->jump();
    }
    if (keys[GLFW_KEY_A])
    {
        player->move(Direction::LEFT, deltaTime);
    }
    if (keys[GLFW_KEY_D])
    {
        player->move(Direction::RIGHT, deltaTime);
    }
    if (keys[GLFW_KEY_Q])
    {
        player->specialAction();
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
    glfwWindowHint(GLFW_SAMPLES, 16);

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Game", glfwGetPrimaryMonitor(), nullptr);
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

    /* --- BACKGROUND --- */

    GLfloat vertices[]
    {
        -2, -2, 0,  0.0f, 0.0f,
        2, -2, 0,   0.1f, 0.0f,
        2, 2, 0,    0.1f, 1.0f,

        -2, -2, 0,  0.0f, 0.0f,
        -2, 2, 0,   0.0f, 1.0f,
        2, 2, 0,    0.1f, 1.0f
    };

    GLuint vboBack;
    GLuint vaoBack;

    glGenBuffers(1, &vboBack);
    glGenVertexArrays(1, &vaoBack);

    glBindVertexArray(vaoBack);

    glBindBuffer(GL_ARRAY_BUFFER, vboBack);
    glBufferData(GL_ARRAY_BUFFER, 30 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    GLuint texture;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Some settings for the texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Read texture from file
    int texWidth;
    int texHeight;
    unsigned char* backgroundImage = SOIL_load_image("background.png", &texWidth, &texHeight, 0, SOIL_LOAD_RGBA);

    // Fill texture with read data
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, backgroundImage);

    // Generate mipmaps
    glGenerateMipmap(GL_TEXTURE_2D);

    // Properly delete image data
    SOIL_free_image_data(backgroundImage);

    // Unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);

    /* --- === --- */

    // Player
    player = new Player (glm::vec3(0.0f, 0.0f, 0.0f), Heroes::MANLY_BOMBER);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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

        /* --- BACKGROUND --- */

        glm::mat4 model;
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram.program, "model"), 1, GL_FALSE, glm::value_ptr(model));

        glBindTexture(GL_TEXTURE_2D, texture);

        glBindVertexArray(vaoBack);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        glBindVertexArray(0);

        glBindTexture(GL_TEXTURE_2D, 0);

        /* --- === --- */

        //Draw player
        player->idle(deltaTime);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram.program, "model"), 1, GL_FALSE, glm::value_ptr(player->getModelMatrix()));
        player->draw();

        glfwSwapBuffers(window);
    }

    // Delete player
    delete player;

    // Close window and finish program
    glfwTerminate();
    return 0;
}
