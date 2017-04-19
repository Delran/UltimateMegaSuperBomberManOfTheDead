#include "Camera.hpp"

/* --- Update vectors function --- */

void Camera::updateCameraVectors()
{
    // Updating front vector in order to make it point in the direction made by yaw and pitch
    glm::vec3 newFront;
    newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    newFront.y = sin(glm::radians(pitch));
    newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(newFront);

    // Updating right and up vectors to get an updated 3-axis coordinate system
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}

/* --- Constructor --- */

Camera::Camera (glm::vec3 initialPosition, glm::vec3 initialWorldUp, GLfloat initialYaw, GLfloat initialPitch, GLfloat initialFov)
:position(initialPosition), worldUp(initialWorldUp), yaw(initialYaw), pitch(initialPitch), fov(initialFov)
{
    // Initialize yaw value between 0 and 360
    yaw = glm::mod(initialYaw, 360.0f);

    // Initialize yaw value between -89 and 89
    if (initialPitch > 89.0f)
    {
        pitch = 89.0f;
    }
    else if (initialPitch < -89.0f)
    {
        pitch = -89.0f;
    }
    else
    {
        pitch = initialPitch;
    }

    // Initialize yaw value between 44 and 47
    if (initialFov > 47.0f)
    {
        fov = 47.0f;
    }
    else if (initialFov < 44.0f)
    {
        fov = 44.0f;
    }
    else
    {
        fov = initialFov;
    }

    // Update the camera's 3-axis coordinate system
    updateCameraVectors();
}

/* --- Get FOV --- */

GLfloat Camera::getFov()
{
    return fov;
}

/* --- Get view matrix function --- */

glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(position, position + front, up);
}

/* --- Keyboard handle function --- */

void Camera::processKeyboard(CameraMovement direction, GLfloat deltaTime)
{
    // Generating velocity with camera speed and elapsed time between 2 frames
    GLfloat velocity = movementSpeed * deltaTime;

    // Add to position vector the movement vector made with velocity and right or front vector
    if (direction == CameraMovement::FORWARD)
    {
        position += front * velocity;
    }
    if (direction == CameraMovement::BACKWARD)
    {
        position -= front * velocity;
    }
    if (direction == CameraMovement::LEFT)
    {
        position -= right * velocity;
    }
    if (direction == CameraMovement::RIGHT)
    {
        position += right * velocity;
    }
}

/* --- Mouse handle function --- */

void Camera::processMouseMovement(GLfloat xOffset, GLfloat yOffset, GLfloat deltaTime)
{
    // Scaling offset with mouse sensitivity and elapsed time between 2 frames
    xOffset *= mouseSensitivity * deltaTime;
    yOffset *= mouseSensitivity * deltaTime;

    // Update view angles with offsets
    yaw = glm::mod(yaw + xOffset, 360.0f);
    pitch += yOffset;

    // Block the camera if it looks completely up or completely down
    if (pitch > 89.0f)
    {
        pitch = 89.0f;
    }
    else if (pitch < -89.0f)
    {
        pitch = -89.0f;
    }

    // Update the camera's 3-axis coordinate system
    updateCameraVectors();
}

/* --- Mouse scroll handle function --- */

void Camera::processMouseScroll(GLfloat yOffset, GLfloat deltaTime)
{
    // Scaling offset with mouse scroll sensitivity and elapsed time between 2 frames
    yOffset *= mouseScrollSensitivity * deltaTime;

    // Update field of view with offset
    fov -= yOffset;

    // Block FOV if it's not between 44 and 47
    if (fov < 44.0f)
    {
        fov = 44.0f;
    }
    else if (fov > 47.0f)
    {
        fov = 47.0f;
    }
}
