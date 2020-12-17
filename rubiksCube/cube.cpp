#include "cube.h"
#include <glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include<cubie.h>
#include<tgmath.h>
#include<math.h>
#include <shader.h>
#include<list>
#include <GLFW/glfw3.h>


void Cube::generateCubies() {
	for (float x = -cubeDimension/2; x <= cubeDimension/2; x++) {
		for (float y = -cubeDimension / 2; y <= cubeDimension / 2; y++) {
			for (float z = -cubeDimension / 2; z <= cubeDimension / 2; z++) {
				cubieList.emplace_back(Cubie(glm::vec3(x, y, z), x, y, z));
			}
		}
	}
	std::cout << "made cubies" << std::endl;
}

void Cube::drawCubies(Shader* ourShader) {
	for (Cubie& currentCubie : cubieList) {
		currentCubie.draw(ourShader);
	}
}


void Cube::reset() {
	if (checkValidCommand()) {
		for (Cubie& currentCubie : cubieList) {
			currentCubie.reset();
		}
		std::cout << "Reset Cubies" << std::endl;
		lastCommandTime = glfwGetTime();
	}
}

bool Cube::checkValidCommand() {
	if (lastCommandTime + commandDelay < glfwGetTime()) {
		return true;
	}
	else {
		return false;
	}
}




glm::mat4 Cube::generalRotation(glm::vec3 rotationAxis, float angle) {
	//create w,x,y,z to define a quaterion
	float w = cos(angle / 2);
	float x = rotationAxis[0] * sin(angle / 2);
	float y = rotationAxis[1] * sin(angle / 2);
	float z = rotationAxis[2] * sin(angle / 2);
	//construct the quat
	glm::quat rotationQuat = glm::quat(w, x, y, z);
	glm::mat4 newRotation = glm::toMat4(rotationQuat);
	return newRotation;
}


//------------------------ Z Face Moves -------------------------------------
void Cube::rotateZClockwise(bool automated) {
	if (checkValidCommand()) {
		for (Cubie& currentCubie : cubieList) {
			if (currentCubie.getZ() == cubeDimension / 2) {
				glm::mat4 nextRotation = generalRotation(glm::vec3(0, 0, 1), clockTurn);
				currentCubie.rotate(nextRotation);
			}
		}
		std::cout << "Z clockwise 90" << std::endl;
		lastCommandTime = glfwGetTime();
	}
}

void Cube::rotateZantiClockwise(bool automated) {
	if (checkValidCommand()) {
		for (Cubie& currentCubie : cubieList) {
			if (currentCubie.getZ() == cubeDimension / 2) {
				glm::mat4 nextRotation = generalRotation(glm::vec3(0, 0, 1), antiClockTurn);
				currentCubie.rotate(nextRotation);
			}
		}
		std::cout << "Z Cclockwise 90" << std::endl;
		lastCommandTime = glfwGetTime();
	}
}

//------------------------- X Face moves -----------------------------------
void Cube::rotateXClockwise(bool automated) {
	if (checkValidCommand()) {
		for (Cubie& currentCubie : cubieList) {
			if (currentCubie.getX() == cubeDimension / 2) {
				glm::mat4 nextRotation = generalRotation(glm::vec3(1, 0, 0), clockTurn);
				currentCubie.rotate(nextRotation);
			}
		}
		std::cout << "X clockwise 90" << std::endl;
		lastCommandTime = glfwGetTime();
	}
}

void Cube::rotateXantiClockwise(bool automated) {
	if (checkValidCommand()) {
		for (Cubie& currentCubie : cubieList) {
			if (currentCubie.getX() == cubeDimension / 2) {
				glm::mat4 nextRotation = generalRotation(glm::vec3(1, 0, 0), antiClockTurn);
				currentCubie.rotate(nextRotation);

			}
		}
		std::cout << "X Cclockwise 90" << std::endl;
		lastCommandTime = glfwGetTime();
	}
}

//--------------------- Y Face moves --------------------------------------
void Cube::rotateYClockwise(bool automated) {
	if (checkValidCommand()) {
		for (Cubie& currentCubie : cubieList) {
			if (currentCubie.getY() == cubeDimension / 2) {
				glm::mat4 nextRotation = generalRotation(glm::vec3(0, 1, 0), clockTurn);
				currentCubie.rotate(nextRotation);
			}
		}
		std::cout << "Y clockwise 90" << std::endl;
		lastCommandTime = glfwGetTime();
	}
}

void Cube::rotateYantiClockwise(bool automated) {
	if (checkValidCommand()) {
		for (Cubie& currentCubie : cubieList) {
			if (currentCubie.getY() == cubeDimension / 2) {
				glm::mat4 nextRotation = generalRotation(glm::vec3(0, 1, 0), antiClockTurn);
				currentCubie.rotate(nextRotation);

			}
		}
		std::cout << "Y Cclockwise 90" << std::endl;
		lastCommandTime = glfwGetTime();
	}
};
