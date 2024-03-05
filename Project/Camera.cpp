#include "Camera.hpp"

namespace gps {

    //Camera constructor
    Camera::Camera(glm::vec3 cameraPosition, glm::vec3 cameraTarget, glm::vec3 cameraUp) {
        //TODO
        this->cameraPosition = cameraPosition;
        this->cameraTarget = cameraTarget;
        this->cameraUpDirection = cameraUp;

    }

    //return the view matrix, using the glm::lookAt() function
    glm::mat4 Camera::getViewMatrix() {
        //TODO

        //return glm::mat4(1.0f);
        return glm::lookAt(cameraPosition, cameraTarget, this->cameraUpDirection);
    }

    //update the camera internal parameters following a camera move event
    void Camera::move(MOVE_DIRECTION direction, float speed) {
        // Calculate the camera's forward, right, and up directions
        glm::vec3 cameraFront = glm::normalize(cameraTarget - cameraPosition);
        glm::vec3 cameraRight = glm::normalize(glm::cross(cameraFront, cameraUpDirection));
        glm::vec3 cameraUp = glm::cross(cameraRight, cameraFront);

        // Move the camera based on the specified direction and speed
        switch (direction) {
        case MOVE_FORWARD:
            cameraPosition += cameraFront * speed;
            break;
        case MOVE_BACKWARD:
            cameraPosition -= cameraFront * speed;
            break;
        case MOVE_RIGHT:
            cameraPosition += cameraRight * speed;
            break;
        case MOVE_LEFT:
            cameraPosition -= cameraRight * speed;
            break;
        case MOVE_UP: // Move the camera upward
            cameraPosition += cameraUp * speed;
            break;
        case MOVE_DOWN: // Move the camera downward
            cameraPosition -= cameraUp * speed;
            break;
        }

        // Update the camera target based on the new position
        cameraTarget = cameraPosition + cameraFront;
    }

    //update the camera internal parameters following a camera rotate event
    //yaw - camera rotation around the y-axis
    //pitch - camera rotation around the x-axis
    void Camera::rotate(float pitch, float yaw) {
        glm::vec3 direction = glm::normalize(cameraTarget - cameraPosition);
        glm::vec3 right = glm::normalize(glm::cross(direction, cameraUpDirection));
        glm::vec3 up = glm::normalize(glm::cross(right, direction));
        glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(pitch), right) * glm::rotate(glm::mat4(1.0f), glm::radians(yaw), up);
        glm::vec4 newTarget = rotationMatrix * glm::vec4(direction, 1.0f);
        cameraTarget = cameraPosition + glm::vec3(newTarget);
        cameraUpDirection = glm::vec3(rotationMatrix * glm::vec4(cameraUpDirection, 1.0f));
    }



}