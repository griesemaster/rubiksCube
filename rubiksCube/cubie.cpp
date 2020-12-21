#include "cubie.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <iostream>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>
#include <shader.h>
#include <GLFW/glfw3.h>
#include <shader.h>
#include <list>


void Cubie::draw(Shader* shader) {
	
	if (!rotationList.empty()) {//if there is a rotation to apply, then apply one before drawing
		rotate(glm::toMat4(rotationList.front()));
		rotationList.pop_front();	//rotate then remove one 
	}
	
	glm::mat4 modelMatrix = translationMatrix * rotationMatrix;
	(*shader).setMat4("model", modelMatrix);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDrawArrays(GL_LINES, 36, 24);
	// 36 draws faces 24 draws outlines 
}


void Cubie::rotate(glm::mat4 nextRotation) {
	rotationMatrix = nextRotation * rotationMatrix;
}


void Cubie::reset() {
	rotationMatrix = glm::mat4(1.0f);
	translationMatrix = glm::translate(glm::mat4(1.0f), startPosition);
	x = (int) startPosition[0];
	y = (int) startPosition[1];
	z = (int) startPosition[2];
}