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
	glm::mat4 rotationMatrix = glm::mat4(1.0f);
	glm::mat4 translationMatrix = glm::mat4(1.0f);

public:
	//Constructor
	Cubie(glm::vec3 localMatrix, float x, float y, float z) {
		localPosition = glm::vec3(x, y, z);
		startPosition = glm::vec3(x, y, z);
		this->x = x;
		this->y = y;
		this->z = z;
		translationMatrix = glm::translate(translationMatrix, localPosition);
	}

	void draw(Shader* drawShader);

	float getX() { return x; }

	float getY() { return y; }

	float getZ() { return z; }

	void rotate(glm::mat4 nextRotation);

	void translate(glm::vec3 direction);

	void reset();

	void setPos(glm::vec3 newPos) {
		this->x = newPos[0];
		this->y = newPos[1];
		this->z = newPos[2];
		localPosition = newPos;
	}


	glm::mat4 getRotation() { return rotationMatrix; }
	glm::mat4 getTranslation() { return translationMatrix; }
};

#endif