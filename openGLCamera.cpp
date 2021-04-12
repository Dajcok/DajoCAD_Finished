#include "openGLCamera.h"
#include <iostream>
#include <cmath>

glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;

glm::mat4 openGLCamera::getViewMatrix() 
{
	return ViewMatrix;
}
glm::mat4 openGLCamera::getProjectionMatrix() 
{
	return ProjectionMatrix;
}



glm::vec3 position = glm::vec3(0, 0, 5);

float horizontalAngle = 3.14f;

float verticalAngle = 0.0f;

float initialFoV = 90.0f;

float speed = 1.0f;
float mouseSpeed = 0.002f;



void openGLCamera::computeMatricesFromInputs() 
{
	static double lastTime = glfwGetTime();

	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	double xpos, ypos;
	xpos = sf::Mouse::getPosition().x;
	ypos = sf::Mouse::getPosition().y;

	sf::Mouse::setPosition({ 1024 / 2, 768 / 2 });

	horizontalAngle += mouseSpeed * float(1024 / 2 - xpos);
	verticalAngle += mouseSpeed * float(768 / 2 - ypos);

	glm::vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);

	glm::vec3 right = glm::vec3(
		sin(horizontalAngle - 3.14f / 2.0f),
		0,
		cos(horizontalAngle - 3.14f / 2.0f)
	);

	glm::vec3 up = glm::cross(right, direction);


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		position += direction * deltaTime * speed;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		position -= direction * deltaTime * speed;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		position += right * deltaTime * speed;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		position -= right * deltaTime * speed;
	}

	float FoV = initialFoV;


	ProjectionMatrix = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.01f, 100.0f);

	ViewMatrix = glm::lookAt(
		position,          
		position + direction,
		up                 
	);

	lastTime = currentTime;
}

glm::vec3 openGLCamera::getCameraPosition()
{
	return position;
}