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
	const float clockTurn = glm::radians(-90.0f); //idk bro seems right when you do the math
	const float antiClockTurn = glm::radians(90.0f);
	std::list<Cubie> cubieList;
	double lastCommandTime;
	double commandDelay;
	int cubeDimension;

	glm::mat4 generateQuatRotation(glm::vec3 rotationDirection, float angle);
	glm::quat genQuat(glm::vec3 rotationDirection, float angle);
	glm::vec2 getNewCords(float x, float y, float rotationDir);

public:
	Cube(int dimension) {
		lastCommandTime = glfwGetTime();
		commandDelay = 0.2f;
		cubeDimension = dimension;
	}

	//setup/drawing methods
	void generateCubies();
	void drawCubies(Shader* ourShader);
	void reset();
	void triggerBreakpoint();

	//Input Handling commands
	bool checkValidCommand();

	//Z Face Rotations
	void rotateZClockwiseFront(bool automated);
	void rotateZantiClockwiseFront(bool automated);
	void rotateZClockwiseBack(bool automated);
	void rotateZantiClockwiseBack(bool automated);

	//X Face Rotations
	void rotateXClockwiseFront(bool automated);
	void rotateXantiClockwiseFront(bool automated);
	void rotateXClockwiseBack(bool automated);
	void rotateXantiClockwiseBack(bool automated);

	//Y Face Rotations
	void rotateYClockwiseFront(bool automated);
	void rotateYantiClockwiseFront(bool automated);
	void rotateYClockwiseBack(bool automated);
	void rotateYantiClockwiseBack(bool automated);
};
#endif