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
	(*shader).setMat4("model", modelMatrix);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDrawArrays(GL_LINES, 36, 24);
	// 36 draws faces 24 draws outlines 
}


void Cubie::rotate(float angle, glm::vec3 rotationAxis) {
	modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), rotationAxis);
}

void Cubie::translate(glm::vec3 direction) {
	modelMatrix = glm::translate(modelMatrix, direction);
}

void Cubie::reset() {
	modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, startPosition);
}