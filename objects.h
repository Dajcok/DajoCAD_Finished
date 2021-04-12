#pragma once
#include "glm.hpp"
#include "glfw3.h"

class objects
{
public:
	objects(int type);

	void setPosition(glm::vec3 &position);
	void setSize(glm::vec3 &size);
	void setActive(bool active);

	glm::vec3 getPosition();
	glm::vec3 getSize();
	bool isActive();

private:
	void resolveType();

private:
	glm::vec3 position;
	glm::vec3 size;

	int objectType;
	bool active;
};

