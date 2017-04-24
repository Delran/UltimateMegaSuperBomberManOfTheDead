#ifndef CAMERA_H
#define CAMERA_H

/* --- Includes --- */

// Standard libraries
#include <iostream>

// Glew
#include <GLEW/glew.h>

// Glm
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

/* === CameraMovement enumeration === */

enum CameraMovement
{
    // Camera movement possibilities
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

/* === Camera class === */

class Camera
{
private:
    /* --- Variables --- */

    // Vectors
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    // Angles
    GLfloat yaw;
    GLfloat pitch;

    // FOV
    GLfloat fov;

    // Control variables
    GLfloat movementSpeed = 1.0f;
    GLfloat mouseSensitivity = 1.0f;
    GLfloat mouseScrollSensitivity = 1.0f;

    /* --- Methods --- */

    // Update vectors method
    void updateCameraVectors();

public:
    // Constructor
    Camera (glm::vec3, glm::vec3, GLfloat, GLfloat, GLfloat);

    // Get FOV method
    GLfloat getFov();

    //Get view matrix method
    glm::mat4 getViewMatrix();

    // Keyboard handle method
    void processKeyboard(CameraMovement, GLfloat);

    // Mouse handle method
    void processMouseMovement(GLfloat, GLfloat, GLfloat);

    // Mouse scroll handle method
    void processMouseScroll(GLfloat, GLfloat);
};

#endif /* end of include guard: CAMERA_H */
