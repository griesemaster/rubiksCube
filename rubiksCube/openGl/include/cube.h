#include<glm/gtc/matrix_transform.hpp>
#include<cubie.h>

#ifndef CUBE
#define CUBE

class Cube {

private:
	Cubie cubieList[27];
	float rotateTime = 0;
	float lastCommandTime;
	float commandDelay;
	glm::mat2 clockwiseRotationMat;
	glm::mat2 counterwiseRotationMat;

public:
	Cube() {
		lastCommandTime = glfwGetTime();
		commandDelay = 0.3f;

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
		int index = 0;
		for (float x = -1; x < 2; x++) {
			for (float y = -1; y < 2; y++) {
				for (float z = -1; z < 2; z++) {
					cubieList[index] = Cubie(glm::vec3(x, y, z), x, y, z);
					index++;
				}
			}
		}
		std::cout << "made cubies" << std::endl;
	}

	void draw(Shader ourShader) {
		for (int index = 0; index < 27; index++) {
			cubieList[index].draw(ourShader);
		}
	}

	void reset() {
		for (int index = 0; index < sizeof(cubieList) / sizeof(Cubie); index++) {
			cubieList[index].reset();
		}
	}


	//Z Face Rotations
	void rotateZPositiveClockwise(bool automated) {
		float currentCommandTime = glfwGetTime();
		if ((currentCommandTime - lastCommandTime > commandDelay) || (automated)) {
			for (int index = 0; index < sizeof(cubieList) / sizeof(Cubie); index++) {
				if (cubieList[index].getZ() == 1) {
					Cubie qb = cubieList[index];
					qb.rotate(90.0f, glm::vec3(0, 0, 1));
				}
			}
			lastCommandTime = currentCommandTime;
		}
	}

	void rotateZPositiveCounterwise(bool automated) {
		float currentCommandTime = glfwGetTime();
		if ((currentCommandTime - lastCommandTime > commandDelay) || (automated)) {
			for (int index = 0; index < sizeof(cubieList) / sizeof(Cubie); index++) {
				if (cubieList[index].getZ() == 1) {
					Cubie qb = cubieList[index];
					qb.rotate(-90.0f, glm::vec3(0, 0, 1));
					//glm::vec2 slicePos = glm::vec2(qb.getX(), qb.getY());
					//glm::vec2 finalPos = counterwiseRotationMat * slicePos;
					//qb.setPos(glm::vec3(finalPos, qb.getZ()));
				}
			}
			lastCommandTime = currentCommandTime;
		}
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