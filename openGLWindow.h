#pragma once
#ifndef OPENGL_WINOW_H
#define OPENGL_WINOW_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <glm.hpp>
#include "cursor.h"

class openGLWindow
{

public:
	openGLWindow();
	~openGLWindow();

private:
	void windowInit();
	void bufferHandler(int index);

	sf::RenderWindow *glR_Window = nullptr;
	bool programRuns;
	size_t bufferSize;
	
	glm::vec3 cameraPosition;
	glm::mat4 project;
	glm::mat4 view;
	sf::Vector2i oldMousePos;

	bool renderGui = false;
	bool keyPressed = false;

	//FPS counter
	float fpsCounter();
	bool firstRun = true;
	int nbFrames;
	double lastTime;
	float FPS;
};

#endif !OPENGL_WINOW_H