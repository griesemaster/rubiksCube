#include "arcballCamera.h"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include <iostream>

arcballCamera::arcballCamera(int windowWidth, int windowHeight, float rollSpeed) {
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;

    this->isMouseActive = false;
    this->rollSpeed = rollSpeed;
    this->angle = 0.0f;
    this->rotationAxis = glm::vec3(0.0f, 1.0f, 0.0f);

    cursorCurrent = glm::vec3(0, 0, 0);
    cursorStart = glm::vec3(0, 0, 0);
}

glm::vec3 arcballCamera::toBall(double screenX, double screenY) {
    glm::vec3 coord(0.0f);
   
    float radius = glm::min(windowHeight / 2.0f, windowWidth / 2.0f); //diameter of the circle is whichever side is shorter
    
    coord.x = (screenX - (windowWidth / 2.0f)) / radius;
    coord.y = (screenY - (windowHeight / 2.0f)) / radius;

    float lengthSquared = coord.x * coord.x + coord.y * coord.y;
    if (lengthSquared <= 1.0)
        coord.z = (float)sqrt(1.0 - lengthSquared);
    else {
        float s = 1.0f / sqrt(lengthSquared);
        coord.x = s * coord.x;
        coord.y = s * coord.y;
        coord.z = 0.0f;
    }

    return coord;
}

void arcballCamera::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    isMouseActive = (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_LEFT);
    if (isMouseActive) {
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        cursorStart = toBall(x, y);
    }
}

void arcballCamera::cursorCallback(GLFWwindow* window, double x, double y) {
    if (isMouseActive) {//mouse is being held while moving
        cursorCurrent = toBall(x, y);
        angle = acos(std::min(1.0f, glm::dot(cursorStart, cursorCurrent)));
        rotationAxis = glm::cross(cursorStart, cursorCurrent);
    }
    else {
        return;
    }
}

void arcballCamera::updateViewMatrix() {
    float w = angle / 2.0f;
    float x = rotationAxis.x * sin(angle / 2.0f);
    float y = rotationAxis.y * sin(angle / 2.0f);
    float z = rotationAxis.z * sin(angle / 2.0f);
    glm::quat newRotation = glm::quat(w, x, y, z);
    currentOrientation = newRotation * currentOrientation;
}

glm::mat4 arcballCamera::getViewMatrix() {
    updateViewMatrix();
    return (currentLocation * glm::toMat4(currentOrientation)); //return location * orientation for the composed view matrix
}
