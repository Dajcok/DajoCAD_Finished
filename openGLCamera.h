#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtx/transform.hpp>
#include <glfw3.h>
#include <SFML/Window.hpp>

class openGLCamera
{
	public:
		glm::mat4 getViewMatrix();
		glm::mat4 getProjectionMatrix();

		glm::vec3 getCameraPosition();

		void computeMatricesFromInputs();
};

