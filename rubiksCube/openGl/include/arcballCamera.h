#ifndef ARCBALL_CAMERA
#define ARCBALL_CAMERA

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

class arcballCamera
{
private:
	int windowWidth;
	int windowHeight;
	bool isMouseActive;

	float rollSpeed;
    float angle;

    glm::vec3 cursorStart;
    glm::vec3 cursorCurrent;
    glm::vec3 rotationAxis;


    glm::quat currentOrientation = glm::quat(1, 0, 0, 0);
    glm::mat4 currentLocation = glm::mat4(1);

public:
    arcballCamera(int window_width, int window_height, float roll_speed = 1.0f);
    glm::vec3 toBall(double x, double y);

    void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    void cursorCallback(GLFWwindow* window, double x, double y);

    void updateViewMatrix();
    glm::mat4 getViewMatrix();

};

#endif // !ARCBALL_CAMERA
