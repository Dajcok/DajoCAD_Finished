#pragma once

#include "targetWindow.h"
#include "OpenGLWindow.h"

class shapeManagment
{
public:
	void deleteAll();
	void stepBack();
	void eraseTool();

	bool canStepBack = true;
};

