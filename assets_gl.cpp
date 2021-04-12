#include "assets_gl.h"

#include "earcut.hpp-master/earcut.hpp-master/include/mapbox/earcut.hpp"


extern targetWindow cadWin;

std::vector<glm::vec3> *assets_gl::computePolygonsWindow()
{
	if (init)
	{
		std::vector<glm::vec3> coordinates;
		short adressIndex = 0;
		int g = 0;

		coordinates = Coors2DTo3D::convertCoors_assets();

		for (int j = 0; j < coordinates.size() / 2; j++)
		{
			std::vector<float> zCoor;
			std::vector<float> zCoorHole;

			using coorsType = double;
			using indexType = uint16_t;
			using vertexCoors = std::array<coorsType, 2>;

			std::vector<std::vector<vertexCoors>> polygon;

			std::vector<vertexCoors> vertexCoordinates;
			std::vector<vertexCoors> holeVertexCoordinates;

			int vCoorsIndex = 0;
			int bufferIndex = 0;

			int i = 0;
			int wIndex = 0;
			int zIndex = 0;
			short length = 0;
			bool execTesselation = false;
			short loopIndex = 0;

			for (auto it : coordinates)
			{
				if (loopIndex >= adressIndex && loopIndex < adressIndex + 2)
				{
					vertexCoordinates.resize(i + 1);
					holeVertexCoordinates.resize(i + 1);

					if (wIndex % 2 == 0)
					{
						vertexCoordinates[i][0] = it.x;
						vertexCoordinates[i][1] = it.y;

						holeVertexCoordinates[i][0] = it.x + 0.025;
						holeVertexCoordinates[i][1] = it.y + 0.025;

						i++;
						vertexCoordinates.resize(i + 1);
						holeVertexCoordinates.resize(i + 1);

						zCoorHole.resize(zIndex);
						zCoorHole.push_back(it.z);

						zCoor.resize(zIndex);
						zCoor.push_back(it.z);
						zIndex++;

						vertexCoordinates[i][0] = it.x;
						vertexCoordinates[i][1] = this->wHeight * it.y + 1;

						holeVertexCoordinates[i][0] = it.x + 0.025;
						holeVertexCoordinates[i][1] = (this->wHeight * it.y + 1) - 0.025;

						i++;

						zCoorHole.resize(zIndex);
						zCoorHole.push_back(it.z);

						zCoor.resize(zIndex);
						zCoor.push_back(it.z);
						zIndex++;
					}

					else
					{
						vertexCoordinates[i][0] = it.x;
						vertexCoordinates[i][1] = this->wHeight * it.y + 1;

						holeVertexCoordinates[i][0] = it.x - 0.025;
						holeVertexCoordinates[i][1] = (this->wHeight * it.y + 1) - 0.025;

						i++;
						vertexCoordinates.resize(i + 1);
						holeVertexCoordinates.resize(i + 1);

						zCoorHole.resize(zIndex);
						zCoorHole.push_back(it.z);

						zCoor.resize(zIndex);
						zCoor.push_back(it.z);
						zIndex++;

						vertexCoordinates[i][0] = it.x;
						vertexCoordinates[i][1] = it.y;

						holeVertexCoordinates[i][0] = it.x - 0.025;
						holeVertexCoordinates[i][1] = it.y + 0.025;

						i++;

						zCoorHole.resize(zIndex);
						zCoorHole.push_back(it.z);

						zCoor.resize(zIndex);
						zCoor.push_back(it.z);
						zIndex++;
					}

					wIndex++;

					execTesselation = true;
				}
				loopIndex++;
			}

			if (execTesselation)
			{
				vertexCoordinates.resize(i + 1);
				vertexCoordinates[i][0] = vertexCoordinates[0][0];
				vertexCoordinates[i][1] = vertexCoordinates[0][1];

				holeVertexCoordinates.resize(i + 1);
				holeVertexCoordinates[i][0] = holeVertexCoordinates[0][0];
				holeVertexCoordinates[i][1] = holeVertexCoordinates[0][1];

				zCoorHole.resize(zIndex);
				zCoorHole.push_back(zCoorHole[0]);

				zCoor.resize(zIndex);
				zCoor.push_back(zCoor[0]);
				zIndex++;

				polygon.push_back(vertexCoordinates);
				polygon.push_back(holeVertexCoordinates);

				std::vector<indexType> indices = mapbox::earcut<indexType>(polygon);

				/*for (auto it : Coors2DTo3D::getWindowAngle())
					std::cout << "uhol " << it << std::endl;*/

				for (auto it : indices)
				{
					returnVector.resize(g);

					if (it <= 4)
					{
						returnVector.push_back({ vertexCoordinates[it][0], vertexCoordinates[it][1], 0 });
					}

					else if (it > 4)
					{
						returnVector.push_back({ holeVertexCoordinates[it - 5][0], holeVertexCoordinates[it - 5][1], 0 });
					}

					g++;
				}
			}
			adressIndex += 2;
		}
		return &returnVector;
		init = false;
	}
	else
		return &returnVector;
}
