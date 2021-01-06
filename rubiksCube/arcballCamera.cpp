#include "arcballCamera.h"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include <iostream>

arcballCamera::arcballCamera(int windowWidth, int windowHeight, float rollSpeed, bool useXAxis, bool useYAxis) {
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;

    this->isMouseActive = false;
    this->rollSpeed = rollSpeed;
    this->angle = 0.0f;
    this->rotationAxis = glm::vec3(0.0f, 1.0f, 0.0f);

    this->useXAxis = useXAxis;
    this->useYAxis = useYAxis;

    currentPosition = glm::vec3(0, 0, 0);
    startPosition = glm::vec3(0, 0, 0);
}

glm::vec3 arcballCamera::toScreenBounds(double x, double y) {
    glm::vec3 coord(0.0f);
    //converts x,y cord from (0,0) -> (windowWidth, windowHeight) TO (-1, -1) -> (1, 1)
    if (useXAxis)
        coord.x = (float) (2 * x - windowWidth) / windowWidth;

    if (useYAxis)
        coord.y = (float) -(2 * y - windowHeight) / windowHeight;

    coord.x = glm::clamp(coord.x, -1.0f, 1.0f);
    coord.y = glm::clamp(coord.y, -1.0f, 1.0f);

    float lengthSquared = coord.x * coord.x + coord.y * coord.y;
    if (lengthSquared <= 1.0)
        coord.z = (float) sqrt(1.0 - lengthSquared);
    else
        coord = glm::normalize(coord);

    return coord;
}

void arcballCamera::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    isMouseActive = (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_LEFT);
    if (isMouseActive) {
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        startPosition = toScreenBounds(x, y);
    }
}

void arcballCamera::cursorCallback(GLFWwindow* window, double x, double y) {
    if (isMouseActive) {//mouse is being held while moving
        std::cout << "tracking loation" << std::endl;
        currentPosition = toScreenBounds(x, y);
        angle = acos(std::min(1.0f, glm::dot(startPosition, currentPosition)));
        rotationAxis = glm::cross(startPosition, currentPosition);
    }
    else {
        return;
    }
}

glm::mat4 arcballCamera::createViewRotationMatrix(glm::mat4 viewMatrix) {
    return glm::rotate(viewMatrix, glm::degrees(angle) * rollSpeed, rotationAxis);
}