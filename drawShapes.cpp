#include "drawShapes.h"

#define PI 3.14159265
#define POFFSETX -5
#define POFFSETY -20

extern targetWindow cadWin;

void drawShapes::circleShape()
{
	int radius;

	if (clickRelease)
	{
		if (firstClick && !secondClick)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				m_circles.resize(arraylengthCircles);
				m_circles.push_back(sf::CircleShape());

				lastStackShapeWrite->resize(arrayLengthShapeStack);
				lastStackShapeWrite->push_back(1);

				m_circles[arraylengthCircles].setOrigin(m_circles[arraylengthCircles].getRadius(), m_circles[arraylengthCircles].getRadius());
				m_circles[arraylengthCircles].setPosition(sf::Vector2f(cadWin.convertCoordinates(sf::Mouse::getPosition()).x + POFFSETX,
					cadWin.convertCoordinates(sf::Mouse::getPosition()).y + POFFSETY));
				m_circles[arraylengthCircles].setOutlineThickness(1);
				m_circles[arraylengthCircles].setOutlineColor(sf::Color(255, 255, 255));
				m_circles[arraylengthCircles].setFillColor(sf::Color(255, 255, 255, 0));

				m_dimLines.resize(arraylengthDimLine);
				m_dimLines.push_back(dcad::dimensioningLine({ 0 }));
				m_dimLines[arraylengthDimLine].setPosition(m_circles[arraylengthCircles].getPosition());
				m_dimLines[arraylengthDimLine].setColor(sf::Color(62, 33, 64, 255));

				firstMousePos.x = sf::Mouse::getPosition().x;
				firstMousePos.y = sf::Mouse::getPosition().y;

				clickRelease = false;
				firstClick = false;

				try
				{
					if (&cadWin == nullptr)
						throw 100;

					update();
				}
				catch (int err)//Error 100: objekt je nullptr
				{
					exit(1);
				}
				
			}
		}


		else if (!firstClick && secondClick)
		{
			arraylengthCircles++;
			arraylengthDimLine++;
			arraylengthText++;
			arrayLengthShapeStack++;

			firstClick = true;
			clickRelease = false;
			secondClick = false;
		}

	}


	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (!clickRelease)
		{
			bool pointCountChange = false;
			int old_radius;
			std::size_t newPointCount = 30;

			while (!firstClick && !secondClick)
			{
				radius = firstMousePos.x - sf::Mouse::getPosition().x;
				m_circles[arraylengthCircles].setOrigin(m_circles[arraylengthCircles].getRadius(), m_circles[arraylengthCircles].getRadius());

				lineLength = radius / 40.f;

				if (lineLength < 0)
					lineLength = lineLength * -1;

				if (!pointCountChange)
				{
					old_radius = m_circles[arraylengthCircles].getRadius();

					pointCountChange = true;
				}

				m_circles[arraylengthCircles].setRadius(radius);

				if (pointCountChange)
				{
					if (radius - old_radius < -10 && radius < 0)
					{
						newPointCount = newPointCount + 2;

						m_circles[arraylengthCircles].setPointCount(newPointCount);

						pointCountChange = false;
					}

					else if (radius - old_radius > 10 && radius > 0)
					{
						newPointCount = newPointCount + 2;

						m_circles[arraylengthCircles].setPointCount(newPointCount);

						pointCountChange = false;
					}

					else if (old_radius - radius > 10 && radius > 0)
					{
						newPointCount = newPointCount - 2;

						m_circles[arraylengthCircles].setPointCount(newPointCount);

						pointCountChange = false;
					}

					else if (old_radius - radius < -10 && radius < 0)
					{
						newPointCount = newPointCount - 2;

						m_circles[arraylengthCircles].setPointCount(newPointCount);

						pointCountChange = false;
					}
				}

				m_dimLines[arraylengthDimLine].setSize(radius);
				m_dimLines[arraylengthDimLine].setPosition({ m_circles[arraylengthCircles].getPosition().x - radius, m_circles[arraylengthCircles].getPosition().y});

				if(radius < 0)
					m_dimLines[arraylengthDimLine].setPosition({ m_circles[arraylengthCircles].getPosition().x + radius, m_circles[arraylengthCircles].getPosition().y });

				std::stringstream textStream;
				textStream << std::fixed << std::setprecision(2) << lineLength;
				std::string text = textStream.str() + " m";

				m_text.resize(arraylengthText);
				m_text.push_back(sf::Text());
				m_text[arraylengthText].setString(text);
				m_text[arraylengthText].setFont(cadWin.font);
				m_text[arraylengthText].setFillColor(sf::Color(93, 50, 96, 255));
				m_text[arraylengthText].setPosition({ m_dimLines[arraylengthDimLine].getPosition().x + m_dimLines[arraylengthDimLine].getSize() / 2,  m_dimLines[arraylengthDimLine].getPosition().y });
				m_text[arraylengthText].setCharacterSize(15);
				m_text[arraylengthText].setOrigin(26, 35);

				try
				{
					if (&cadWin == nullptr)
						throw 100;

					update();
				}
				catch (int err)//Error 100: objekt je nullptr
				{
					exit(1);
				}

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					clickRelease = true;
					secondClick = true;

				}
			}

			if (firstClick && !secondClick && !clickRelease)
				clickRelease = true;
		}
	}
}



void drawShapes::lineShape(int bufferIndex)
{
	std::string text;

	if (firstInit)
	{
		memoryOfFI.resize(memSize);
		memoryOfFI.at(0) = 0;
		firstInit = false;
	}

	if (clickRelease)
	{
		if (firstClick && !secondClick) 
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))//prvy klik
			{
				m_lineShape.resize(arraylengthLines);

				m_lineShape.push_back(sf::RectangleShape(sf::Vector2f(0, 1)));

				lastStackShapeWrite->resize(arrayLengthShapeStack);
				lastStackShapeWrite->push_back(2);

				m_lineShape[arraylengthLines].setOrigin(sf::Vector2f(0, m_lineShape[arraylengthLines].getSize().y / 2));
				m_lineShape[arraylengthLines].setPosition(getLinePos());	

				if (bufferIndex == 0)
				{
					m_lineShape[arraylengthLines].setFillColor(sf::Color::White);
					m_lineShape[arraylengthLines].setOutlineColor(sf::Color::White);

					lineCoorsBuffer.resize(arraylengthLineCoors);
					lineCoorsBuffer.push_back({ getLinePos().x, floorNumber, getLinePos().y });

					m_dimLines.resize(arraylengthDimLine);
					m_dimLines.push_back(dcad::dimensioningLine({ 0 }));
					m_dimLines[arraylengthDimLine].setPosition(m_lineShape[arraylengthLines].getPosition());
					m_dimLines[arraylengthDimLine].setColor(sf::Color(62, 33, 64, 255));

					nOfLines++;
				}

				else if (bufferIndex == 1)
				{
					m_lineShape[arraylengthLines].setFillColor(sf::Color::Blue);
					m_lineShape[arraylengthLines].setOutlineColor(sf::Color::Blue);

					lineCoorsBuffer_floor.resize(arraylengthLineCoors_floor);
					lineCoorsBuffer_floor.push_back({ getLinePos().x, floorNumber, getLinePos().y });

					m_dimLines_floor.resize(arraylengthDimLineFloor);
					m_dimLines_floor.push_back(dcad::dimensioningLine({ 0 }));
					m_dimLines_floor[arraylengthDimLineFloor].setPosition(m_lineShape[arraylengthLines].getPosition());
					m_dimLines_floor[arraylengthDimLineFloor].setColor(sf::Color(62, 33, 64, 255));

					nOfLines_floor++;
				}

				firstMousePos = cadWin.convertCoordinates(sf::Mouse::getPosition());
				
				try
				{
					if (&cadWin == nullptr)
						throw 100;

					update();
				}
				catch (int err)//Error 100: objekt je nullptr
				{
					exit(1);
				}

				clickRelease = false;
				firstClick = false;
			}
		}

		else if (!firstClick && secondClick)//2. uvolnenie
		{
			firstClick = true;
			clickRelease = false;
			secondClick = false;
		}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			floorNumber++;

			std::cout << floorNumber << std::endl;

			memSize++;
			memoryOfFI.resize(memSize);
			memoryOfFI.at(memSize - 1) = nOfLines_floor;

			if(nOfLines_floor != 0)
				firstCoorPosition_floor = (nOfLines_floor * 2);

			if (nOfLines != 0)
				firstCoorPosition = (nOfLines * 2);

			std::cout << firstCoorPosition_floor << std::endl;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				while (1)
				{
					if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
						break;
				}
		}

		if (floorNumber != 0)//<-------------------------------- dorobit!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				floorNumber--;
				std::cout << "Floor: " << floorNumber << ". " << std::endl;

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
					while (1)
					{
						if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
							break;
					}
			}
	}

	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (!clickRelease)
		{
			while (!firstClick && !secondClick)//prve uvolnenie
			{
				sf::Vector2f mousePosDif;
				mousePosDif.x = cadWin.convertCoordinates(sf::Mouse::getPosition()).x - firstMousePos.x;
				mousePosDif.y = cadWin.convertCoordinates(sf::Mouse::getPosition()).y - firstMousePos.y;

				float sizeX = pow(mousePosDif.x, 2) + pow(mousePosDif.y, 2);
				sizeX = sqrt(sizeX);

				float alpha = mousePosDif.y / mousePosDif.x;
				alpha = atan(alpha);

				float positionY = m_lineShape[arraylengthLines].getPosition().y;

				if (mousePosDif.x < 0)
					alpha = alpha + PI;

				alpha = alpha * 180 / PI;

				m_lineShape[arraylengthLines].setSize(sf::Vector2f(sizeX, 2));
				m_lineShape[arraylengthLines].setRotation(alpha);


				lineLength = sizeX / 40.f;
				
				std::stringstream textStream;
				textStream << std::fixed << std::setprecision(2) << lineLength;
				std::string text = textStream.str() + " m";

				try
				{
					if (&cadWin == nullptr)
						throw 100;

					update();
				}
				catch (int err)//Error 100: objekt je nullptr
				{
					exit(1);
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
				{
					if (bufferIndex == 0)
					{
						mousePosDif.x = lineCoorsBuffer[firstCoorPosition].x - firstMousePos.x - POFFSETX;
						mousePosDif.y = lineCoorsBuffer[firstCoorPosition].z - firstMousePos.y - POFFSETY;

						float sizeX = pow(mousePosDif.x, 2) + pow(mousePosDif.y, 2);
						sizeX = sqrt(sizeX);

						float alpha = mousePosDif.y / mousePosDif.x;
						alpha = atan(alpha);

						float positionY = m_lineShape[arraylengthLines].getPosition().y;

						if (mousePosDif.x < 0)
							alpha = alpha + PI;

						alpha = alpha * 180 / PI;

						m_lineShape[arraylengthLines].setSize(sf::Vector2f(sizeX, 2));
						m_lineShape[arraylengthLines].setRotation(alpha);

						lineLength = sizeX / 40.f;

						std::stringstream textStream;
						textStream << std::fixed << std::setprecision(2) << lineLength;
						std::string text = textStream.str() + " m";

						m_text.resize(arraylengthText);
						m_text.push_back(sf::Text());
						m_text[arraylengthText].setString(text);
						m_text[arraylengthText].setFont(cadWin.font);
						m_text[arraylengthText].setFillColor(sf::Color(93, 50, 96, 255));
						m_text[arraylengthText].setPosition({ m_lineShape[arraylengthLines].getPosition().x + mousePosDif.x / 2, m_lineShape[arraylengthLines].getPosition().y + mousePosDif.y / 2 });
						m_text[arraylengthText].setRotation(alpha);
						m_text[arraylengthText].setCharacterSize(15);
						m_text[arraylengthText].setOrigin(26, 35);

						m_dimLines[arraylengthDimLine].setSize(sizeX);
						m_dimLines[arraylengthDimLine].setRotation(alpha);

						arraylengthLineCoors++;
						lineCoorsBuffer.resize(arraylengthLineCoors);
						lineCoorsBuffer.push_back(lineCoorsBuffer[firstCoorPosition]);
					}

					else if (bufferIndex == 1)
					{
						mousePosDif.x = lineCoorsBuffer_floor[firstCoorPosition_floor].x - firstMousePos.x - POFFSETX;
						mousePosDif.y = lineCoorsBuffer_floor[firstCoorPosition_floor].z - firstMousePos.y - POFFSETY;

						float sizeX = pow(mousePosDif.x, 2) + pow(mousePosDif.y, 2);
						sizeX = sqrt(sizeX);

						float alpha = mousePosDif.y / mousePosDif.x;
						alpha = atan(alpha);

						float positionY = m_lineShape[arraylengthLines].getPosition().y;

						if (mousePosDif.x < 0)
							alpha = alpha + PI;

						alpha = alpha * 180 / PI;

						m_lineShape[arraylengthLines].setSize(sf::Vector2f(sizeX, 2));
						m_lineShape[arraylengthLines].setRotation(alpha);

						lineLength = sizeX / 40.f;

						std::stringstream textStream;
						textStream << std::fixed << std::setprecision(2) << lineLength;
						std::string text = textStream.str() + " m";

						m_textFloor.resize(arraylengthText);
						m_textFloor.push_back(sf::Text());
						m_textFloor[arraylengthText].setString(text);
						m_textFloor[arraylengthText].setFont(cadWin.font);
						m_textFloor[arraylengthText].setFillColor(sf::Color(93, 50, 96, 255));
						m_textFloor[arraylengthText].setPosition({ m_lineShape[arraylengthLines].getPosition().x + mousePosDif.x / 2, m_lineShape[arraylengthLines].getPosition().y + mousePosDif.y / 2 });
						m_textFloor[arraylengthText].setRotation(alpha);
						m_textFloor[arraylengthText].setCharacterSize(15);
						m_textFloor[arraylengthText].setOrigin(26, 35);

						m_dimLines_floor[arraylengthDimLineFloor].setSize(sizeX);
						m_dimLines_floor[arraylengthDimLineFloor].setRotation(alpha);

						arraylengthLineCoors_floor++;
						lineCoorsBuffer_floor.resize(arraylengthLineCoors_floor);
						lineCoorsBuffer_floor.push_back(lineCoorsBuffer_floor[firstCoorPosition_floor]);

						lineWriteCheck++;
					}

					goto A;
				}

				if (bufferIndex == 0)
				{
					m_text.resize(arraylengthText);
					m_text.push_back(sf::Text());
					m_text[arraylengthText].setString(text);
					m_text[arraylengthText].setFont(cadWin.font);
					m_text[arraylengthText].setFillColor(sf::Color(93, 50, 96, 255));
					m_text[arraylengthText].setPosition({ m_lineShape[arraylengthLines].getPosition().x + mousePosDif.x / 2, m_lineShape[arraylengthLines].getPosition().y + mousePosDif.y / 2 });
					m_text[arraylengthText].setRotation(alpha);
					m_text[arraylengthText].setCharacterSize(15);
					m_text[arraylengthText].setOrigin(26, 35);

					m_dimLines[arraylengthDimLine].setSize(sizeX);
					m_dimLines[arraylengthDimLine].setRotation(alpha);
				}

				else if (bufferIndex == 1)
				{
					m_textFloor.resize(arraylengthText);
					m_textFloor.push_back(sf::Text());
					m_textFloor[arraylengthText].setString(text);
					m_textFloor[arraylengthText].setFont(cadWin.font);
					m_textFloor[arraylengthText].setFillColor(sf::Color(93, 50, 96, 255));
					m_textFloor[arraylengthText].setPosition({ m_lineShape[arraylengthLines].getPosition().x + mousePosDif.x / 2, m_lineShape[arraylengthLines].getPosition().y + mousePosDif.y / 2 });
					m_textFloor[arraylengthText].setRotation(alpha);
					m_textFloor[arraylengthText].setCharacterSize(15);
					m_textFloor[arraylengthText].setOrigin(26, 35);

					m_dimLines_floor[arraylengthDimLineFloor].setSize(sizeX);
					m_dimLines_floor[arraylengthDimLineFloor].setRotation(alpha);
				}


				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))//2. klik
				{
					clickRelease = true;
					secondClick = true;

					if (bufferIndex == 0)
					{
						arraylengthLineCoors++;
						lineCoorsBuffer.resize(arraylengthLineCoors);
						lineCoorsBuffer.push_back({ getLinePos().x, floorNumber, getLinePos().y });
					}

					else if (bufferIndex == 1)
					{
						arraylengthLineCoors_floor++;
						lineCoorsBuffer_floor.resize(arraylengthLineCoors_floor);
						lineCoorsBuffer_floor.push_back({ getLinePos().x, floorNumber, getLinePos().y });

						lineWriteCheck++;
					}
				}
			}

			if (firstClick && !secondClick && !clickRelease)
			{
			A:

				firstClick = true;
				clickRelease = true;
				secondClick = false;

				arraylengthLines++;

				if (bufferIndex == 0)
				{
					arraylengthLineCoors++;
					arraylengthDimLine++;
				}

				else if (bufferIndex == 1)
				{
					arraylengthLineCoors_floor++;
					arraylengthDimLineFloor++;
				}

				arraylengthText++;
				arrayLengthShapeStack++;
			}
		}
	}
}

void drawShapes::ellipseShape(void)
{
	if (clickRelease)
	{
		if (firstClick && !secondClick)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				m_ellipses.resize(arraylengthEllipses);
				m_ellipses.push_back(dcad::ellipseShape(sf::Vector2f(0.f, 0.f)));

				lastStackShapeWrite->resize(arrayLengthShapeStack);
				lastStackShapeWrite->push_back(3);

				m_ellipses[arraylengthEllipses].setPosition(sf::Vector2f(cadWin.convertCoordinates(sf::Mouse::getPosition()).x + POFFSETX,
					cadWin.convertCoordinates(sf::Mouse::getPosition()).y + POFFSETY));
				m_ellipses[arraylengthEllipses].setOutlineThickness(1);
				m_ellipses[arraylengthEllipses].setOutlineColor(sf::Color(255, 255, 255));
				m_ellipses[arraylengthEllipses].setFillColor(sf::Color(255, 255, 255, 0));
				m_ellipses[arraylengthEllipses].setRadius(sf::Vector2f(0.f, 0.f));

				firstMousePos.x = cadWin.convertCoordinates(sf::Mouse::getPosition()).x;
				firstMousePos.y = cadWin.convertCoordinates(sf::Mouse::getPosition()).y;

				try
				{
					if (&cadWin == nullptr)
						throw 100;

					update();
				}
				catch (int err)//Error 100: objekt je nullptr
				{
					exit(1);
				}

				clickRelease = false;
				firstClick = false;
			}
		}


		else if (!firstClick && secondClick)
		{
			arraylengthEllipses++;
			arrayLengthShapeStack++;

			firstClick = true;
			clickRelease = false;
			secondClick = false;
		}
	}


	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (!clickRelease)
		{
			bool pointCountChange = false;

			sf::Vector2f old_radius;

			std::size_t newPointCount = 30;

			while (!firstClick && !secondClick)
			{		
				sf::Vector2f radius(firstMousePos.x - cadWin.convertCoordinates(sf::Mouse::getPosition()).x, firstMousePos.y - cadWin.convertCoordinates(sf::Mouse::getPosition()).y);

				if (!pointCountChange)
				{
					old_pytRadius = pow(radius.x, 2) + pow(radius.y, 2);
					old_pytRadius = sqrt(old_pytRadius);

					pointCountChange = true;
				}

				m_ellipses[arraylengthEllipses].setRadius(radius);

				pytRadius = pow(radius.x, 2) + pow(radius.y, 2);
				pytRadius = sqrt(pytRadius);

				if (pointCountChange)
				{
					if (pytRadius - old_pytRadius < -10)
					{
						newPointCount = newPointCount - 2;

						m_ellipses[arraylengthEllipses].setPointCount(newPointCount);

						pointCountChange = false;
					}

					else if (pytRadius - old_pytRadius > 10)
					{
						newPointCount = newPointCount + 2;

						m_ellipses[arraylengthEllipses].setPointCount(newPointCount);

						pointCountChange = false;
					}
				}

				m_ellipses[arraylengthEllipses].setOrigin(radius.x, radius.y);

				try
				{
					if (&cadWin == nullptr)
						throw 100;

					update();
				}
				catch (int err)//Error 100: objekt je nullptr
				{
					exit(1);
				}

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					clickRelease = true;
					secondClick = true;
				}
			}

			if (firstClick && !secondClick && !clickRelease)
				clickRelease = true;
		}
	}
}

void drawShapes::assetShape(std::size_t index)
{
	if (clickRelease)
	{
		if (firstClick && !secondClick)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				m_doors.resize(arraylengthDoors);
				m_doors.push_back(dcad::assets(index, sf::Vector2f(100,100)));

				//lastStackShapeWrite->resize(arrayLengthShapeStack);
				//lastStackShapeWrite->push_back(3);

				m_doors[arraylengthDoors].setPosition(sf::Vector2f(cadWin.convertCoordinates(sf::Mouse::getPosition()).x + POFFSETX,
					cadWin.convertCoordinates(sf::Mouse::getPosition()).y + POFFSETY));
				m_doors[arraylengthDoors].setOutlineThickness(1);
				m_doors[arraylengthDoors].setOutlineColor(sf::Color(255, 255, 255));
				m_doors[arraylengthDoors].setFillColor(sf::Color(255, 255, 255, 0));

				firstMousePos.x = cadWin.convertCoordinates(sf::Mouse::getPosition()).x;
				firstMousePos.y = cadWin.convertCoordinates(sf::Mouse::getPosition()).y;

				if (index == 1)
				{
					doorCoorsBuffer.resize(arraylengthDoorsCoors);
					doorCoorsBuffer.push_back({ getLinePos().x, floorNumber, getLinePos().y });
					arraylengthDoorsCoors++;
				}

				else if (index == 2)
				{
					windowCoorsBuffer.resize(arraylengthWindowCoors);
					windowCoorsBuffer.push_back({ getLinePos().x, floorNumber, getLinePos().y });

					std::cout << "W posX: " << windowCoorsBuffer.at(arraylengthWindowCoors).x << "\t W posY: " << windowCoorsBuffer.at(arraylengthWindowCoors).z << "\t floor: " << windowCoorsBuffer.at(arraylengthWindowCoors).y << std::endl;

					arraylengthWindowCoors++;
				}

				else
					std::cout << "Err: Invalid Index !" << std::endl;

				try
				{
					if (&cadWin == nullptr)
						throw 100;

					update();
				}
				catch (int err)//Error 100: objekt je nullptr
				{
					exit(1);
				}

				clickRelease = false;
				firstClick = false;
			}
		}


		else if (!firstClick && secondClick)
		{
			arraylengthDoors++;
			//arrayLengthShapeStack++;

			firstClick = true;
			clickRelease = false;
			secondClick = false;
		}
	}


	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (!clickRelease)
		{
			while (!firstClick && !secondClick)
			{
				sf::Vector2f mousePosDif;
				mousePosDif.x = cadWin.convertCoordinates(sf::Mouse::getPosition()).x - firstMousePos.x;
				mousePosDif.y = cadWin.convertCoordinates(sf::Mouse::getPosition()).y - firstMousePos.y;

				float sizeX = pow(mousePosDif.x, 2) + pow(mousePosDif.y, 2);
				sizeX = sqrt(sizeX);

				alpha = mousePosDif.y / mousePosDif.x;
				alpha = atan(alpha);

				float positionY = m_doors[arraylengthDoors].getPosition().y;

				if (mousePosDif.x < 0)
					alpha = alpha + PI;

				m_doors[arraylengthDoors].setSize(sizeX);
				m_doors[arraylengthDoors].setRotation(alpha);

				alpha = alpha * 180 / PI;

				try
				{
					if (&cadWin == nullptr)
						throw 100;

					update();
				}
				catch (int err)//Error 100: objekt je nullptr
				{
					exit(1);
				}

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					clickRelease = true;
					secondClick = true;

					if (index == 1)
					{
						doorCoorsBuffer.resize(arraylengthDoorsCoors);
						doorCoorsBuffer.push_back({ getLinePos().x, floorNumber, getLinePos().y });
						arraylengthDoorsCoors++;
					}

					else if (index == 2)
					{
						windowCoorsBuffer.resize(arraylengthWindowCoors);
						windowCoorsBuffer.push_back({ getLinePos().x, floorNumber, getLinePos().y });

						updateAngle();

						arraylengthWindowCoors++;
					}
				}
			}

			if (firstClick && !secondClick && !clickRelease)
				clickRelease = true;
		}
	}
}

std::vector<float> drawShapes::getAnglesWindow()
{
	return angles;
}


void drawShapes::update()
{
	cadWin.update(&m_lineShape, &m_circles, &m_ellipses, &m_dimLines, &m_text, &cadWin.cursor, &m_dimLines_floor, &m_textFloor, &m_doors);

	cadWin.cursor.setPosition({ sf::Mouse::getPosition().x - 960 + cadWin.mouseOffset.x, sf::Mouse::getPosition().y - 540 + cadWin.mouseOffset.y});
}

void drawShapes::updateAngle()
{
	angles.resize(index);
	angles.push_back(alpha);
	index++;
}

sf::Vector2f drawShapes::getLinePos()
{
	mousePosStorage_line = sf::Vector2f(cadWin.convertCoordinates(sf::Mouse::getPosition()).x + POFFSETX, cadWin.convertCoordinates(sf::Mouse::getPosition()).y + POFFSETY);

	return mousePosStorage_line;
}



