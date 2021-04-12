#pragma once

#include <vector>
#include <array>


#include <glm.hpp>

#include "targetWindow.h"

class assets_gl
{
public:
	std::vector<glm::vec3>* computePolygonsWindow();

private:
	const float wHeight = 0.1f;
	bool init = true;
	std::vector<glm::vec3> returnVector;
};

