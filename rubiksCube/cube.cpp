#include "cube.h"
#include <glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
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

//Z Face Rotations
void Cube::rotateZClockwise(bool automated) {
	if (checkValidCommand()) {
		for (Cubie& currentCubie : cubieList) {
			if (currentCubie.getZ() == cubeDimension / 2) {
				//calculate the desired final location in terms of x/y/z (Z) will be static for this test
				constexpr float angle = glm::radians(-90.0f);
				float newX = currentCubie.getX() * cos(angle) - currentCubie.getY() * sin(angle);
				float newY = currentCubie.getX() * sin(angle) - currentCubie.getY() * cos(angle);

				currentCubie.translate(glm::vec3(-currentCubie.getX(), -currentCubie.getY(), -currentCubie.getZ()));
				currentCubie.rotate(90.0f, glm::vec3(0, 0, 1));
				currentCubie.translate(glm::vec3(newX, newY, cubeDimension / 2));
			}
		}
		lastCommandTime = glfwGetTime();
	}
}

void Cube::rotateZCounterwise(bool automated) {
	if (checkValidCommand()) {
		for (Cubie& currentCubie : cubieList) {
			if (currentCubie.getZ() == cubeDimension / 2) {
				//calculate the desired final location in terms of x/y/z (Z) will be static for this test
				constexpr float angle = glm::radians(90.0f);
				float newX = currentCubie.getX() * cos(angle) - currentCubie.getY() * sin(angle);
				float newY = currentCubie.getX() * sin(angle) - currentCubie.getY() * cos(angle);

				currentCubie.translate(glm::vec3(-currentCubie.getX(), -currentCubie.getY(), -currentCubie.getZ()));
				currentCubie.rotate(90.0f, glm::vec3(0, 0, 1));
				currentCubie.translate(glm::vec3(newX, newY, cubeDimension / 2));
			}
		}
		lastCommandTime = glfwGetTime();
	}
}

void Cube::rotateXClockwise(bool automated) {
	if (checkValidCommand()) {
		for (Cubie& currentCubie : cubieList) {
			if (currentCubie.getX() == cubeDimension / 2) {
				//calculate the desired final location in terms of x/y/z (Z) will be static for this test
				constexpr float angle = glm::radians(-90.0f);
				float newY = currentCubie.getY() * cos(angle) - currentCubie.getZ() * sin(angle);
				float newZ = currentCubie.getY() * sin(angle) - currentCubie.getZ() * cos(angle);

				currentCubie.translate(glm::vec3(-currentCubie.getX(), -currentCubie.getY(), -currentCubie.getZ()));
				currentCubie.rotate(90.0f, glm::vec3(1, 0, 0));
				currentCubie.translate(glm::vec3(cubeDimension/2, newY, newZ));
			}
		}
		lastCommandTime = glfwGetTime();
	}
};

void Cube::rotateXCounterwise(bool automated) {
	if (checkValidCommand()) {
		for (Cubie& currentCubie : cubieList) {
			if (currentCubie.getX() == cubeDimension / 2) {
				//calculate the desired final location in terms of x/y/z (Z) will be static for this test
				constexpr float angle = glm::radians(90.0f);
				float newY = currentCubie.getY() * cos(angle) - currentCubie.getZ() * sin(angle);
				float newZ = currentCubie.getY() * sin(angle) - currentCubie.getZ() * cos(angle);

				currentCubie.translate(glm::vec3(-currentCubie.getX(), -currentCubie.getY(), -currentCubie.getZ()));
				currentCubie.rotate(90.0f, glm::vec3(1, 0, 0));
				currentCubie.translate(glm::vec3(cubeDimension / 2, newY, newZ));
			}
		}
		lastCommandTime = glfwGetTime();
	}
};
