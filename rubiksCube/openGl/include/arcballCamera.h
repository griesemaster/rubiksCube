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

    glm::vec3 startPosition;
    glm::vec3 currentPosition;
    glm::vec3 rotationAxis;

    bool useXAxis;
    bool useYAxis;


public:
    arcballCamera(int window_width, int window_height, float roll_speed = 1.0f, bool x_axis = true, bool y_axis = true);
    glm::vec3 toScreenBounds(double x, double y);

    void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    void cursorCallback(GLFWwindow* window, double x, double y);

    glm::mat4 createViewRotationMatrix(glm::mat4 viewMatrix);

};

#endif // !ARCBALL_CAMERA
