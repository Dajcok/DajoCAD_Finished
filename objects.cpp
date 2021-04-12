#include "objects.h"

objects::objects(int type)
{
	this->objectType = type;

	this->active = false;
}

void objects::setPosition(glm::vec3 &position)
{
	this->position = position;
}

void objects::setSize(glm::vec3 &size)
{
	this->size = size;
}

void objects::setActive(bool active)
{
	this->active = active;
}

glm::vec3 objects::getPosition()
{
	return this->position;
}

glm::vec3 objects::getSize()
{
	return this->size;
}

bool objects::isActive()
{
	return this->active;
}

void objects::resolveType()
{
	
}
