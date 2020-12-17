#include <glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<cubie.h>
#include<tgmath.h>
#include<list>
#include <GLFW/glfw3.h>
#include <shader.h>

#ifndef CUBE
#define CUBE

class Cube {

private:
	const float clockTurn = glm::radians(90.0f);
	const float antiClockTurn = glm::radians(90.0f);
	std::list<Cubie> cubieList;
	double lastCommandTime;
	double commandDelay;
	int cubeDimension;

	glm::mat4 generalRotation(glm::vec3 rotationDirection, float angle);
	glm::vec2 getNewCords(float x, float y, float rotationDir);

public:
	Cube(int dimension) {
		lastCommandTime = glfwGetTime();
		commandDelay = 0.3f;
		cubeDimension = dimension;
	}

	//setup/drawing methods
	void generateCubies();
	void drawCubies(Shader* ourShader);
	void reset();

	//Input Handling commands
	bool checkValidCommand();

	//Face Rotations
	void rotateZClockwise(bool automated);
	void rotateZantiClockwise(bool automated);
	void rotateXClockwise(bool automated);
	void rotateXantiClockwise(bool automated);
	void rotateYClockwise(bool automated);
	void rotateYantiClockwise(bool automated);
};
#endif