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
	std::list<Cubie> cubieList;
	double lastCommandTime;
	double commandDelay;
	int cubeDimension;


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

	//Commands
	bool checkValidCommand();

	//Z Face Rotations
	void rotateZClockwise(bool automated);
	void rotateZCounterwise(bool automated);


};
#endif