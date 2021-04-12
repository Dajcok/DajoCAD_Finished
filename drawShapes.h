#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <math.h>
#include <string>
#include <vector> 
#include <iostream>
#include <iomanip>
#include <sstream>

#include "ellipseShape.h"
#include "targetWindow.h"
#include "dimensioningLine.h"
#include "assets.h"

class drawShapes
{
public:
	void lineShape(int bufferIndex);
	void circleShape();
	void ellipseShape();
	void assetShape(std::size_t index);
	std::vector<float> getAnglesWindow();

	std::vector<sf::RectangleShape> m_lineShape;
	std::vector<sf::CircleShape> m_circles;
	std::vector<dcad::ellipseShape> m_ellipses;
	std::vector<dcad::assets> m_doors;//v skutoènosti buffer assetov nie len dveri. Nazov buffera by mal byt m_assets

	std::vector<dcad::dimensioningLine> m_dimLines;
	std::vector<dcad::dimensioningLine> m_dimLines_floor;

	std::vector<sf::Text> m_text;
	std::vector<sf::Text> m_textFloor;

	std::vector<sf::Vector3f> lineCoorsBuffer;
	std::vector<sf::Vector3f> lineCoorsBuffer_floor;

	std::vector<sf::Vector3f> doorCoorsBuffer;
	std::vector<sf::Vector3f> windowCoorsBuffer;

	std::size_t arraylengthEllipses = 0;
	std::size_t arraylengthCircles = 0;
	std::size_t arraylengthLines = 0;
	std::size_t arraylengthLineCoors = 0;
	std::size_t arraylengthDimLine = 0;
	std::size_t arraylengthText = 0;
	std::size_t arraylengthDimLineFloor = 0;
	std::size_t arraylengthLineCoors_floor = 0;

	//Assety
	std::size_t arraylengthDoors = 0;
	std::size_t arraylengthDoorsCoors = 0;
	std::size_t arraylengthWindowCoors = 0;

	float floorNumber = 0;
	std::vector<int> memoryOfFI; //floor index vektor

private:
	void update();
	void updateAngle();


	sf::Vector2f getLinePos();

	sf::Vector2f firstMousePos;

	float lineLength;

	bool clickRelease = true;
	bool firstClick = true;
	bool secondClick = false;

	int pytRadius;
	int old_pytRadius;

	int lineWriteCheck = 0;

	sf::Vector2f mousePosStorage_line;

	std::size_t nOfLines_floor = 0; //podlaha
	std::size_t nOfLines = 0; //steny

	std::size_t memSize = 1;

	std::size_t firstCoorPosition_floor = 0;
	std::size_t firstCoorPosition = 0;

	bool firstInit = true;

	float alpha;
	std::vector<float> angles;
	short index = 0;

protected:
	friend class shapeManagment;
	friend class targetWindow;

	std::vector<int> *lastStackShapeWrite = new std::vector<int>;  //1 - circles, 2 - lines, 3 - ellipses     invalid vector <T> subscript vyriesit zatial davam 1000 velkost
	std::size_t arrayLengthShapeStack = 0;
};

