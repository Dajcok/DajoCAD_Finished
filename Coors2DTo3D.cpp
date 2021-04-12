#include "Coors2DTo3D.h"
#include <cmath> 

#include "earcut.hpp-master/earcut.hpp-master/include/mapbox/earcut.hpp"
#include <array>

#define PI 3.14159265

extern targetWindow cadWin;

Coors2DTo3D::Coors2DTo3D()
{
	int i = 0;
	int j = 0;

	if (cadWin.shapes != nullptr)
	{	
		vertexBuffer.resize(cadWin.shapes->arraylengthLineCoors);

		if (&cadWin.shapes->lineCoorsBuffer != nullptr)
			for (auto it : cadWin.shapes->lineCoorsBuffer)
			{
				vertexBuffer[i].x = ((it.x * 2) / 1920) - 1;
				vertexBuffer[i].y = it.y * wHeight;
				vertexBuffer[i].z = ((it.z * 2) / 1080) - 1;

				i++;
				vertexSize++;
			}

		vertexBuffer_floor.resize(cadWin.shapes->arraylengthLineCoors_floor);

		if(&cadWin.shapes->lineCoorsBuffer_floor != nullptr)
			for (auto it : cadWin.shapes->lineCoorsBuffer_floor)
			{
				vertexBuffer_floor[j].x = ((it.x * 2) / 1920) - 1;
				vertexBuffer_floor[j].y = it.y;
				vertexBuffer_floor[j].z = ((it.z * 2) / 1080) - 1;

				j++;
				vertexSize_floor++;
			}
	}
}



float Coors2DTo3D::getVertexEdgeAngle(int index)
{
	float angle;
	int i = 0;

	if (&vertexBuffer != nullptr)
	{
		float difference_x = vertexBuffer[index].x - vertexBuffer[1 + index].x;
		float difference_y = vertexBuffer[index].z - vertexBuffer[1 + index].z; //y-ova os je v openGL suradnicovom systeme z-ova os

		float pytC = std::sqrt(std::pow(difference_x, 2) + std::pow(difference_y, 2));

		angle = difference_y / pytC;
	}

	return std::asin(angle);
}


std::vector<float> Coors2DTo3D::computePolygons(bool holesEnabled, std::size_t nFloor)
{
	for (int g = 0; g <= cadWin.shapes->floorNumber; g++)
	{
		std::vector<float> returnVector;

		using coorsType = double;
		using indexType = uint16_t;
		using vertexCoors = std::array<coorsType, 2>;

		std::vector<std::vector<vertexCoors>> polygon;

		std::vector<vertexCoors> vertexCoordinates;
		std::vector<vertexCoors> holeVertexCoordinates;

		vertexCoordinates.resize(1);

		if (cadWin.shapes->floorNumber != 0)
		{
			int vCoorsIndex = 0;

			for (int i = cadWin.shapes->memoryOfFI[g] * 2; i < cadWin.shapes->memoryOfFI[1 + g] * 2; i++)
			{
				vertexCoordinates.resize(1 + vCoorsIndex);

				vertexCoordinates[vCoorsIndex][0] = vertexBuffer_floor[i].x;
				vertexCoordinates[vCoorsIndex][1] = vertexBuffer_floor[i].z;

				vCoorsIndex++;
			}

			for (auto it : vertexCoordinates)
				std::cout << it[0] << "       " << it[1] << std::endl;
		}

		else
		{
			int i = 0;

			for (auto it : vertexBuffer_floor)
			{
				vertexCoordinates[i][0] = it.x;
				vertexCoordinates[i][1] = it.z;

				i++;
				vertexCoordinates.resize(1 + i);
			}

		}

		polygon.push_back(vertexCoordinates);

		if (holesEnabled)
			polygon.push_back(holeVertexCoordinates);

		std::vector<indexType> indices = mapbox::earcut<indexType>(polygon);

		int returnVecSize = 0;

		for (auto it : indices)
		{
			returnVector.resize(returnVecSize);
			returnVector.push_back(vertexCoordinates[it][0]);
			returnVecSize++;

			returnVector.resize(returnVecSize);
			returnVector.push_back(g * wHeight);
			returnVecSize++;

			returnVector.resize(returnVecSize);
			returnVector.push_back(vertexCoordinates[it][1]);
			returnVecSize++;
			
		}

		for (auto it : indices)
		{
			returnVector.push_back(vertexCoordinates[it][0]);
			returnVecSize++;
			returnVector.resize(returnVecSize);

			returnVector.push_back((g * wHeight) - .020f);//hrubka podlahy
			returnVecSize++;
			returnVector.resize(returnVecSize);

			returnVector.push_back(vertexCoordinates[it][1]);
			returnVecSize++;
			returnVector.resize(returnVecSize);
		}

		for (int i = cadWin.shapes->memoryOfFI[g] * 2; i < cadWin.shapes->memoryOfFI[1 + g] * 2; i += 2)
		{
			returnVector.push_back(vertexBuffer_floor[i].x);
			returnVecSize++;
			returnVector.resize(returnVecSize);

			returnVector.push_back(g * wHeight);
			returnVecSize++;
			returnVector.resize(returnVecSize);

			returnVector.push_back(vertexBuffer_floor[i].z);
			returnVecSize++;
			returnVector.resize(returnVecSize);



			returnVector.push_back(vertexBuffer_floor[1 + i].x);
			returnVecSize++;
			returnVector.resize(returnVecSize);

			returnVector.push_back(g * wHeight);
			returnVecSize++;
			returnVector.resize(returnVecSize);

			returnVector.push_back(vertexBuffer_floor[1 + i].z);
			returnVecSize++;
			returnVector.resize(returnVecSize);



			returnVector.push_back(vertexBuffer_floor[i].x);
			returnVecSize++;
			returnVector.resize(returnVecSize);

			returnVector.push_back((g * wHeight) - .020f);
			returnVecSize++;
			returnVector.resize(returnVecSize);

			returnVector.push_back(vertexBuffer_floor[i].z);
			returnVecSize++;
			returnVector.resize(returnVecSize);



			returnVector.push_back(vertexBuffer_floor[i].x);
			returnVecSize++;
			returnVector.resize(returnVecSize);

			returnVector.push_back((vertexBuffer_floor[i].y * wHeight) - .020f);
			returnVecSize++;
			returnVector.resize(returnVecSize);

			returnVector.push_back(vertexBuffer_floor[i].z);
			returnVecSize++;
			returnVector.resize(returnVecSize);



			returnVector.push_back(vertexBuffer_floor[1 + i].x);
			returnVecSize++;
			returnVector.resize(returnVecSize);

			returnVector.push_back((g * wHeight) - .020f);
			returnVecSize++;
			returnVector.resize(returnVecSize);

			returnVector.push_back(vertexBuffer_floor[1 + i].z);
			returnVecSize++;
			returnVector.resize(returnVecSize);



			returnVector.push_back(vertexBuffer_floor[1 + i].x);
			returnVecSize++;
			returnVector.resize(returnVecSize);

			returnVector.push_back((vertexBuffer_floor[1 + i].y * wHeight));
			returnVecSize++;
			returnVector.resize(returnVecSize);

			returnVector.push_back(vertexBuffer_floor[1 + i].z);
			returnVecSize++;
			returnVector.resize(returnVecSize);

		}

		s = final_size;

		final_size += returnVector.size();

		returnVector_final.resize(final_size);

		for (auto it : returnVector)
		{
			returnVector_final[s] = it;
			s++;
		}

		//std::cout << g << std::endl;

		returnVector.clear();
		vertexCoordinates.clear();

	}

	return returnVector_final;
}

std::vector<glm::vec3> Coors2DTo3D::convertCoors_assets()
{
	const float assets_wHeight = .10f;
	std::vector<glm::vec3> vertexBuffer_window;

	if (&cadWin.shapes->windowCoorsBuffer != nullptr)
	{
		int i = 0;
		for (auto it : cadWin.shapes->windowCoorsBuffer)
		{
			vertexBuffer_window.resize(i + 1);
			vertexBuffer_window[i].x = ((it.x * 2) / 1920) - 1;
			vertexBuffer_window[i].y = it.y * assets_wHeight;
			vertexBuffer_window[i].z = ((it.z * 2) / 1080) - 1;

			i++;
		}
	}
	return vertexBuffer_window;
}

std::vector<float> Coors2DTo3D::getWindowAngle()
{
	return cadWin.shapes->getAnglesWindow();
}
