#ifndef CUBIE
#define CUBIE

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>
#include <shader.h>

class Cubie {

private:
	glm::vec3 localPosition;
	glm::vec3 startPosition;
	float x, y, z;
	glm::mat4 modelMatrix = glm::mat4(1.0f);

public:
	//Constructor
	Cubie(glm::vec3 localMatrix, float x, float y, float z) {
		localPosition = glm::vec3(x, y, z);
		startPosition = glm::vec3(x, y, z);
		this->x = x;
		this->y = y;
		this->z = z;
		modelMatrix = glm::translate(modelMatrix, localPosition);
	}

	void draw(Shader* drawShader);

	float getX() { return x; }

	float getY() { return y; }

	float getZ() { return z; }

	void rotate(float angle, glm::vec3 rotationAxis);

	void translate(glm::vec3 direction);

	void reset();

	void setPos(glm::vec3 newPos) {
		this->x = newPos[0];
		this->y = newPos[1];
		this->z = newPos[2];
		localPosition = newPos;
	}

	void setModel(glm::mat4 newModel) { modelMatrix = newModel; }

	glm::mat4 getModel() { return modelMatrix; }
};

#endif