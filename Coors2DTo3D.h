#pragma once
#include "targetWindow.h"
#include <glm.hpp>
#include <vec3.hpp>

class Coors2DTo3D
{
public:
	Coors2DTo3D();
	float getVertexEdgeAngle(int index);

	std::size_t vertexSize = 0;
	std::size_t vertexSize_floor = 0;

	std::vector <glm::vec3> vertexBuffer; // steny

	std::vector<float> computePolygons(bool holesEnabled, std::size_t nFloor);

private:
	std::vector <glm::vec3> vertexBuffer_floor; // podlažie

	std::vector<float> returnVector_final;
	std::size_t final_size = 0;
	int s;

	const float wHeight = .10f;

protected:
	friend class bufferData;
	friend class assets_gl;

	static std::vector<glm::vec3> convertCoors_assets();
	static std::vector<float> getWindowAngle();
	
	std::size_t nFloor;


};