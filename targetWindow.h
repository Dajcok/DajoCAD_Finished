#pragma once
#ifndef TARGETWINDOW_H
#define TARGETWINDOW_H

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "drawShapes.h"
#include "backgroundGrid.h"
#include "targetCamera.h"
#include "ellipseShape.h"
#include "dimensioningLine.h"
#include "assets.h"
#include "shapeManagment.h"
#include "dGui.h"
#include "cursor.h"
#include "openGLWindow.h"
#include "Coors2DTo3D.h"

class targetWindow : protected dG::dGui
{
public:
	explicit targetWindow(sf::VideoMode winResolution = sf::VideoMode(800, 600), sf::Color bgColor = sf::Color::White, int clockVar = 10);
	~targetWindow();

private:
	void minimap();
	void worldCamera(bool event);

	sf::VideoMode winResolution;
	sf::Color bgColor;
	sf::Sprite mMapBckg;
	sf::RectangleShape mMapPosition;

	targetCamera camera;
	targetCamera minimapView;
	targetCamera cursorView;
	backgroundGrid backgroundObj;

	int clockVar;
	bool setup = true;
	bool mSetup = true;
	bool stepBack = true;
	bool cSetup = true;
	bool renderFloorDimLines = false;

	sf::Event event;


	///////OPENGL
	float clock = 1;
	bool floorBufferWrite = false;


protected:
	friend class drawShapes;
	friend class shapeManagment;
	friend class Coors2DTo3D;
	friend class openGLWindow;
	friend class bufferData;
	friend class assets_gl;

	dcad::cursor cursor;

	void update(std::vector<sf::RectangleShape> *lines, std::vector<sf::CircleShape> *circles, std::vector<dcad::ellipseShape> *ellipses,
		std::vector<dcad::dimensioningLine> *dimLines, std::vector<sf::Text> *text, dcad::cursor *crsr, std::vector<dcad::dimensioningLine> *dimLinesFloor,
		std::vector<sf::Text> *textFloor, std::vector<dcad::assets> *assets);

	sf::RenderWindow window;

	sf::Vector2f convertCoordinates(sf::Vector2i mousePos) const;

	drawShapes *shapes;

	sf::Font font;

	sf::Vector2i mouseOffset;
};

#endif !TARGETWINDOW_H