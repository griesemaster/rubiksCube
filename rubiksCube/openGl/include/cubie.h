#ifndef CUBIE
#define CUBIE

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>
#include <shader.h>
#include <list>

class Cubie {

private:

	glm::vec3 localPosition;
	glm::vec3 startPosition;
	float  x, y, z;

	glm::mat4 rotationMatrix = glm::mat4(1.0f);
	glm::quat rawRotation = glm::quat(1.0, 0.0, 0.0, 0.0);
	glm::mat4 translationMatrix = glm::mat4(1.0f);

	std::list<glm::quat> rotationList;



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

	void reset();

	void setPos(glm::vec3 newPos) {
		x = newPos[0];
		y = newPos[1];
		z = newPos[2];
		localPosition = newPos;
		translationMatrix = glm::translate(glm::mat4(1), newPos);
	}


	glm::mat4 getRotation() { return rotationMatrix; }

	glm::quat getRawRotation() { return rawRotation; }

	void addRawRotation(glm::quat newRotation) { rawRotation = newRotation * rawRotation; }

	void addIntermdiateFrame(glm::quat newRotation) { rotationList.emplace_back(newRotation); }

	glm::mat4 getTranslation() { return translationMatrix; }
};

#endif