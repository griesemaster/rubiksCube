#include "GLcube.h"
#include <glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include<cubie.h>
#include<ctgmath>
#include<math.h>
#include <shader.h>
#include<list>
#include <GLFW/glfw3.h>


//creates the list of cubies. The bounds are set so that the center of the cube is on 0,0,0. 
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


//draws each cubie
void Cube::drawCubies(Shader* ourShader) {
	for (Cubie& currentCubie : cubieList) {
		currentCubie.draw(ourShader);
	}
}


void Cube::triggerBreakpoint() {
	;//place breakpoint here to trigger within the cube and view the cube list and internal vars
}

//resets each cubie to their starting orientation and position.
void Cube::reset() {
	if (checkValidCommand()) {
		for (Cubie& currentCubie : cubieList) {
			currentCubie.reset();
		}
		std::cout << "Reset Cubies" << std::endl;
		lastCommandTime = glfwGetTime();
	}
}

//checks if the cube is ready for a command yet. This should be called before any transformation that is user inputed to prevent rapid inputs. Controlled by "commandDelay" variable
bool Cube::checkValidCommand() {
	if (lastCommandTime + commandDelay < glfwGetTime()) {
		return true;
	}
	else {
		return false;
	}
}


//------------------- General methods that the other rotation methods rely on ---------------------


//generates a rotation matrix based on a given rotation axis and angle (passed in radians). Used to generate the next roation for a given cubie.
glm::mat4 Cube::generateQuatRotation(glm::vec3 rotationAxis, float angle) {
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

glm::quat Cube::genQuat(glm::vec3 rotationAxis, float angle) {
	//create w,x,y,z to define a quaterion
	float w = cos(angle / 2);
	float x = rotationAxis[0] * sin(angle / 2);
	float y = rotationAxis[1] * sin(angle / 2);
	float z = rotationAxis[2] * sin(angle / 2);
	//construct the quat
	glm::quat rotationQuat = glm::quat(w, x, y, z);
	return rotationQuat;
}


//translates the cords passed around the cube. This is used to find the new location of a cubie after a rotation.
glm::vec2 Cube::getNewCords(float x, float y, float rotationDir) {
	return glm::vec2(round(x * cos(rotationDir) - y * sin(rotationDir)), round(x * sin(rotationDir) + y * cos(rotationDir)));
}



//------------------------ Z Face Moves -------------------------------------
/// hotkey 1
void Cube::rotateZClockwiseFrontQUATSTACK(bool automated) {
	if (checkValidCommand() || automated) {
		for (Cubie& currentCubie : cubieList) {
			if (currentCubie.getZ() == (cubeDimension / 2)) {
				glm::quat nextRotation = genQuat(glm::vec3(0, 0, 1), clockTurn);
				glm::quat currentRotation = currentCubie.getRawRotation();
		
				
		
				for (float i = 1; i <= 15; i++) {
					glm::quat intermediateFrame = glm::slerp(currentRotation, nextRotation, 0.0666f * i);
					currentCubie.addIntermdiateFrame(intermediateFrame);
				}
				

				currentCubie.addRawRotation(nextRotation);
				glm::vec2 rotatedPoints = getNewCords(currentCubie.getX(), currentCubie.getY(), clockTurn);
				glm::vec3 newLocation = glm::vec3(rotatedPoints[0], rotatedPoints[1], currentCubie.getZ());
				currentCubie.setPos(newLocation);
			}
		}
		std::cout << "Z SLERP clockwise 90" << std::endl;
		lastCommandTime = glfwGetTime();
	}
}

void Cube::rotateZClockwiseFront(bool automated) {
	if (checkValidCommand() || automated) {
		for (Cubie& currentCubie : cubieList) {
			if (currentCubie.getZ() == (cubeDimension / 2)) {
				glm::mat4 nextRotation = generateQuatRotation(glm::vec3(0, 0, 1), clockTurn);
				currentCubie.rotate(nextRotation);
				glm::vec2 rotatedPoints = getNewCords(currentCubie.getX(), currentCubie.getY(), clockTurn);
				glm::vec3 newLocation = glm::vec3(rotatedPoints[0], rotatedPoints[1], currentCubie.getZ());
				currentCubie.setPos(newLocation);
			}
		}
		std::cout << "Z antiClockwise 90" << std::endl;
		lastCommandTime = glfwGetTime();
	}
}

/// hotkey 2
void Cube::rotateZantiClockwiseFront(bool automated) {
	if (checkValidCommand() || automated) {
		for (Cubie& currentCubie : cubieList) {
			if (currentCubie.getZ() == (cubeDimension / 2)) {
				glm::mat4 nextRotation = generateQuatRotation(glm::vec3(0, 0, 1), antiClockTurn);
				currentCubie.rotate(nextRotation);
				glm::vec2 rotatedPoints = getNewCords(currentCubie.getX(), currentCubie.getY(), antiClockTurn);
				glm::vec3 newLocation = glm::vec3(rotatedPoints[0], rotatedPoints[1], currentCubie.getZ());
				currentCubie.setPos(newLocation);
			}
		}
		std::cout << "Z antiClockwise 90" << std::endl;
		lastCommandTime = glfwGetTime();
	}
}

void Cube::rotateZClockwiseBack(bool automated) {
	if (checkValidCommand() || automated) {
		for (Cubie& currentCubie : cubieList) {
			if (currentCubie.getZ() == (-cubeDimension / 2)) {
				glm::mat4 nextRotation = generateQuatRotation(glm::vec3(0, 0, 1), clockTurn);
				currentCubie.rotate(nextRotation);
				glm::vec2 rotatedPoints = getNewCords(currentCubie.getX(), currentCubie.getY(), clockTurn);
				glm::vec3 newLocation = glm::vec3(rotatedPoints[0], rotatedPoints[1], currentCubie.getZ());
				currentCubie.setPos(newLocation);
			}
		}
		std::cout << "Z clockwise 90" << std::endl;
		lastCommandTime = glfwGetTime();
	}
}

void Cube::rotateZantiClockwiseBack(bool automated) {
	if (checkValidCommand() || automated) {
		for (Cubie& currentCubie : cubieList) {
			if (currentCubie.getZ() == (-cubeDimension / 2)) {
				glm::mat4 nextRotation = generateQuatRotation(glm::vec3(0, 0, 1), antiClockTurn);
				currentCubie.rotate(nextRotation);
				glm::vec2 rotatedPoints = getNewCords(currentCubie.getX(), currentCubie.getY(), antiClockTurn);
				glm::vec3 newLocation = glm::vec3(rotatedPoints[0], rotatedPoints[1], currentCubie.getZ());
				currentCubie.setPos(newLocation);
			}
		}
		std::cout << "Z antiClockwise 90" << std::endl;
		lastCommandTime = glfwGetTime();
	}
}

//------------------------- X Face moves -----------------------------------
/// hotkey 3
void Cube::rotateXClockwiseFront(bool automated) {
	if (checkValidCommand() || automated) {
		for (Cubie& currentCubie : cubieList) {
			if (currentCubie.getX() == (cubeDimension / 2)) {
				glm::mat4 nextRotation = generateQuatRotation(glm::vec3(1, 0, 0), clockTurn);
				currentCubie.rotate(nextRotation);
				glm::vec2 rotatedPoints = getNewCords(currentCubie.getY(), currentCubie.getZ(), clockTurn);
				glm::vec3 newLocation = glm::vec3(currentCubie.getX(), rotatedPoints[0], rotatedPoints[1]);
				currentCubie.setPos(newLocation);
			}
		}
		std::cout << "X clockwise 90" << std::endl;
		lastCommandTime = glfwGetTime();
	}
}

/// hotkey 4
void Cube::rotateXantiClockwiseFront(bool automated) {
	if (checkValidCommand() || automated) {
		for (Cubie& currentCubie : cubieList) {
			if (currentCubie.getX() == (cubeDimension / 2)) {
				glm::mat4 nextRotation = generateQuatRotation(glm::vec3(1, 0, 0), antiClockTurn);
				currentCubie.rotate(nextRotation);
				glm::vec2 rotatedPoints = getNewCords(currentCubie.getY(), currentCubie.getZ(), antiClockTurn);
				glm::vec3 newLocation = glm::vec3(currentCubie.getX(), rotatedPoints[0], rotatedPoints[1]);
				currentCubie.setPos(newLocation);
			}
		}
		std::cout << "X antiClockwise 90" << std::endl;
		lastCommandTime = glfwGetTime();
	}
}

void Cube::rotateXClockwiseBack(bool automated) {
	if (checkValidCommand() || automated) {
		for (Cubie& currentCubie : cubieList) {
			if (currentCubie.getX() == (-cubeDimension / 2)) {
				glm::mat4 nextRotation = generateQuatRotation(glm::vec3(1, 0, 0), clockTurn);
				currentCubie.rotate(nextRotation);
				glm::vec2 rotatedPoints = getNewCords(currentCubie.getY(), currentCubie.getZ(), clockTurn);
				glm::vec3 newLocation = glm::vec3(currentCubie.getX(), rotatedPoints[0], rotatedPoints[1]);
				currentCubie.setPos(newLocation);
			}
		}
		std::cout << "X clockwise 90" << std::endl;
		lastCommandTime = glfwGetTime();
	}
}

void Cube::rotateXantiClockwiseBack(bool automated) {
	if (checkValidCommand() || automated) {
		for (Cubie& currentCubie : cubieList) {
			if (currentCubie.getX() == (-cubeDimension / 2)) {
				glm::mat4 nextRotation = generateQuatRotation(glm::vec3(1, 0, 0), antiClockTurn);
				currentCubie.rotate(nextRotation);
				glm::vec2 rotatedPoints = getNewCords(currentCubie.getY(), currentCubie.getZ(), antiClockTurn);
				glm::vec3 newLocation = glm::vec3(currentCubie.getX(), rotatedPoints[0], rotatedPoints[1]);
				currentCubie.setPos(newLocation);
			}
		}
		std::cout << "X antiClockwise 90" << std::endl;
		lastCommandTime = glfwGetTime();
	}
}


//--------------------- Y Face moves --------------------------------------
/// hotkey 5
void Cube::rotateYClockwiseFront(bool automated) {
	if (checkValidCommand() || automated) {
		for (Cubie& currentCubie : cubieList) {
			if (currentCubie.getY() == (cubeDimension / 2)) {
				glm::mat4 nextRotation = generateQuatRotation(glm::vec3(0, 1, 0), antiClockTurn);
				currentCubie.rotate(nextRotation);
				glm::vec2 rotatedPoints = getNewCords(currentCubie.getX(), currentCubie.getZ(), clockTurn);
				glm::vec3 newLocation = glm::vec3(rotatedPoints[0], currentCubie.getY(), rotatedPoints[1]);
				currentCubie.setPos(newLocation);
			}
		}
		std::cout << "Y clockwise 90" << std::endl;
		lastCommandTime = glfwGetTime();
	}
}

/// hotkey 6
void Cube::rotateYantiClockwiseFront(bool automated) {
	if (checkValidCommand() || automated) {
		for (Cubie& currentCubie : cubieList) {
			if (currentCubie.getY() == (cubeDimension / 2)) {
				glm::mat4 nextRotation = generateQuatRotation(glm::vec3(0, 1, 0), clockTurn);
				currentCubie.rotate(nextRotation);
				glm::vec2 rotatedPoints = getNewCords(currentCubie.getX(), currentCubie.getZ(), antiClockTurn);
				glm::vec3 newLocation = glm::vec3(rotatedPoints[0], currentCubie.getY(), rotatedPoints[1]);
				currentCubie.setPos(newLocation);
			}
		}
		std::cout << "Y antiClockwise 90" << std::endl;
		lastCommandTime = glfwGetTime();
	}
}

void Cube::rotateYClockwiseBack(bool automated) {
	if (checkValidCommand() || automated) {
		for (Cubie& currentCubie : cubieList) {
			if (currentCubie.getY() == (-cubeDimension / 2)) {
				glm::mat4 nextRotation = generateQuatRotation(glm::vec3(0, 1, 0), antiClockTurn);
				currentCubie.rotate(nextRotation);
				glm::vec2 rotatedPoints = getNewCords(currentCubie.getX(), currentCubie.getZ(), clockTurn);
				glm::vec3 newLocation = glm::vec3(rotatedPoints[0], currentCubie.getY(), rotatedPoints[1]);
				currentCubie.setPos(newLocation);
			}
		}
		std::cout << "Y clockwise 90" << std::endl;
		lastCommandTime = glfwGetTime();
	}
}

void Cube::rotateYantiClockwiseBack(bool automated) {
	if (checkValidCommand() || automated) {
		for (Cubie& currentCubie : cubieList) {
			if (currentCubie.getY() == (-cubeDimension / 2)) {
				glm::mat4 nextRotation = generateQuatRotation(glm::vec3(0, 1, 0), clockTurn);
				currentCubie.rotate(nextRotation);
				glm::vec2 rotatedPoints = getNewCords(currentCubie.getX(), currentCubie.getZ(), antiClockTurn);
				glm::vec3 newLocation = glm::vec3(rotatedPoints[0], currentCubie.getY(), rotatedPoints[1]);
				currentCubie.setPos(newLocation);
			}
		}
		std::cout << "Y antiClockwise 90" << std::endl;
		lastCommandTime = glfwGetTime();
	}
}
