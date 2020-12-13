#include "cubie.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>
#include <shader.h>
#include <GLFW/glfw3.h>
#include <shader.h>


void Cubie::draw(Shader* shader) {
	//Sample rotation line: if enabled the cubies will all be rotated. However, if this line is used in rotate() method the cubies do not rotate even after the method is confirmed to run.
	//modelMatrix = glm::rotate(modelMatrix, glm::radians(90.0f), glm::vec3(0.5f, 1.0f, 0.0f));
	(*shader).setMat4("model", modelMatrix);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}


void Cubie::rotate(float angle, glm::vec3 rotationAxis) {
	modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), rotationAxis);
	// example which works in the draw method, why does it not change anything here?
	//modelMatrix = glm::rotate(debugMatrix, glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

}

void Cubie::reset() {
	modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, startPosition);
}