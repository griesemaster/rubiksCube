#include<glm/gtc/matrix_transform.hpp>
#include<cubie.h>
#include<tgmath.h>
#include<list>

#ifndef CUBE
#define CUBE

class Cube {

private:
	std::list<Cubie> cubieList;
	float rotateTime = 0;
	float lastCommandTime;
	float commandDelay;
	glm::mat2 clockwiseRotationMat;
	glm::mat2 counterwiseRotationMat;
	int cubeDimension;


public:
	Cube(int dimension) {
		lastCommandTime = glfwGetTime();
		commandDelay = 0.3f;

		cubeDimension = dimension;

		//create clockwise 2D rotation matrix
		float x = glm::radians(90.0f);
		clockwiseRotationMat[0] = glm::vec2(glm::cos(x), -1 * glm::sin(x));
		clockwiseRotationMat[1] = glm::vec2(glm::sin(x), glm::cos(x));

		//create counterclockwise 2D rotation matrix
		x = glm::radians(-90.0f);
		counterwiseRotationMat[0] = glm::vec2(glm::cos(x), -1 * glm::sin(x));
		counterwiseRotationMat[1] = glm::vec2(glm::sin(x), glm::cos(x));
	}

	void generateCubies() {
		for (float x = 0; x < cubeDimension; x++) {
			for (float y = 0; y < cubeDimension; y++) {
				for (float z = 0; z < cubeDimension; z++) {
					cubieList.emplace_back(Cubie(glm::vec3(x, y, z), x, y, z));
				}
			}
		}
		std::cout << "made cubies" << std::endl;
	}

	void draw(Shader ourShader) {
		for (Cubie currentCubie : cubieList) {
			currentCubie.draw(ourShader);
		}
	}

	void reset() {

	}


	//Z Face Rotations
	void rotateZPositiveClockwise(bool automated) {

	}

	void rotateZPositiveCounterwise(bool automated) {

	}

	void rotateZNegativeClockwise(bool automated) {
		;
	}

	void rotateZNegativeCounterwise(bool automated) {
		;
	}

	//Y Face Rotations
	void rotateYPositiveClockwise(bool automated) {
		;
	}

	void rotateYPositiveCounterwise(bool automated) {
		;
	}

	void rotateYNegativeClockwise(bool automated) {
		;
	}

	void rotateYNegativeCounterwise(bool automated) {
		;
	}


	//X Face Rotations
	void rotateXPositiveClockwise(bool automated) {
		;
	}

	void rotateXPositiveCounterwise(bool automated) {
		;
	}

	void rotateXNegativeClockwise(bool automated) {
		;
	}

	void rotateXNegativeCounterwise(bool automated) {
		;
	}

};
#endif