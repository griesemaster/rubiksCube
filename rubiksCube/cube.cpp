#include "cube.h"
#include <glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<cubie.h>
#include<tgmath.h>
#include <shader.h>
#include<list>
#include <GLFW/glfw3.h>


void Cube::generateCubies() {
	for (float x = 0; x < cubeDimension; x++) {
		for (float y = 0; y < cubeDimension; y++) {
			for (float z = 0; z < cubeDimension; z++) {
				cubieList.emplace_back(Cubie(glm::vec3(x, y, z), x, y, z));
			}
		}
	}
	std::cout << "made cubies" << std::endl;
}

void Cube::draw(Shader* ourShader) {
	for (Cubie currentCubie : cubieList) {
		currentCubie.draw(ourShader);
	}
}

void Cube::reset() {

}

bool Cube::checkValidCommand() {
	if (lastCommandTime + commandDelay < glfwGetTime()) {
		return true;
	}
	else {
		return false;
	}
}

//Z Face Rotations
void Cube::rotateZClockwise(bool automated) {
	if (checkValidCommand()) {
		for (Cubie& currentCubie : cubieList) {
			if (currentCubie.getZ() == 0) {
				currentCubie.rotate(-90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			}
		}
		std::cout << "Rotated Cubies -90Z" << std::endl;
		lastCommandTime = glfwGetTime();
	}
}

void Cube::rotateZCounterwise(bool automated) {
	if (checkValidCommand()) {
		for (Cubie& currentCubie : cubieList) {
			if (currentCubie.getZ() == 0) {
				currentCubie.rotate(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			}
		}
		std::cout << "Rotated Cubies +90Z" << std::endl;
		lastCommandTime = glfwGetTime();
	}
}