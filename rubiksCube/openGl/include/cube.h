#include <glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<cubie.h>
#include<tgmath.h>
#include<list>
#include <GLFW/glfw3.h>

#ifndef CUBE
#define CUBE

class Cube {

private:
	std::list<Cubie> cubieList;
	float lastCommandTime;
	float commandDelay;
	int cubeDimension;


public:
	Cube(int dimension) {
		lastCommandTime = glfwGetTime();
		commandDelay = 0.3f;
		cubeDimension = dimension;
	}

	//setup/drawing methods
	void generateCubies();
	void draw(Shader ourShader);
	void reset();

	//Commands
	bool checkValidCommand();

	//Z Face Rotations
	void rotateZzeroClockwise(bool automated);
	void rotateZzeroCounterwise(bool automated);


};
#endif