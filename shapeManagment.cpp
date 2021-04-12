#include "shapeManagment.h"
#include <iostream>

extern targetWindow cadWin;

void shapeManagment::deleteAll()
{
	drawShapes *shapesPtr = cadWin.shapes;

	if (shapesPtr != nullptr)
	{
		shapesPtr->arraylengthLines = 0;
		shapesPtr->arraylengthCircles = 0;
		shapesPtr->arraylengthEllipses = 0;
		shapesPtr->arraylengthDimLine = 0;
		shapesPtr->arraylengthText = 0;
		shapesPtr->arrayLengthShapeStack = 0;

		shapesPtr->m_lineShape.clear();
		shapesPtr->m_circles.clear();
		shapesPtr->m_ellipses.clear();
		shapesPtr->m_dimLines.clear();
		shapesPtr->m_text.clear();
		shapesPtr->lastStackShapeWrite->clear();

		shapesPtr->m_lineShape.resize(shapesPtr->arraylengthLines);
		shapesPtr->m_circles.resize(shapesPtr->arraylengthCircles);
		shapesPtr->m_ellipses.resize(shapesPtr->arraylengthEllipses);
		shapesPtr->m_dimLines.resize(shapesPtr->arraylengthDimLine);
		shapesPtr->m_text.resize(shapesPtr->arraylengthText);
		shapesPtr->lastStackShapeWrite->resize(shapesPtr->arrayLengthShapeStack);
	}
}

void shapeManagment::stepBack()
{
	drawShapes *shapesPtr = cadWin.shapes;


		std::cout << shapesPtr->lastStackShapeWrite->back() << std::endl;

		if (shapesPtr->lastStackShapeWrite->back() == 1 && !shapesPtr->m_circles.empty() && canStepBack)
		{
			canStepBack = false;

			shapesPtr->m_circles.pop_back();
			shapesPtr->arraylengthCircles--;
			shapesPtr->lastStackShapeWrite->pop_back();
			shapesPtr->arrayLengthShapeStack--;

			shapesPtr->m_dimLines.pop_back();
			shapesPtr->arraylengthDimLine--;
			shapesPtr->m_text.pop_back();
			shapesPtr->arraylengthText--;

			shapesPtr->m_circles.resize(shapesPtr->arraylengthCircles);
			shapesPtr->lastStackShapeWrite->resize(shapesPtr->arrayLengthShapeStack);
			shapesPtr->m_dimLines.resize(shapesPtr->arraylengthDimLine);
			shapesPtr->m_text.resize(shapesPtr->arraylengthText);
		}

		if (shapesPtr->lastStackShapeWrite->back() == 2 && !shapesPtr->m_lineShape.empty() && canStepBack)
		{
			canStepBack = false;

			shapesPtr->m_lineShape.pop_back();
			shapesPtr->arraylengthLines--;
			shapesPtr->lastStackShapeWrite->pop_back();
			shapesPtr->arrayLengthShapeStack--;

			shapesPtr->m_dimLines.pop_back();
			shapesPtr->arraylengthDimLine--;
			shapesPtr->m_text.pop_back();
			shapesPtr->arraylengthText--;

			shapesPtr->m_lineShape.resize(shapesPtr->arraylengthLines);
			shapesPtr->lastStackShapeWrite->resize(shapesPtr->arrayLengthShapeStack);
			shapesPtr->m_dimLines.resize(shapesPtr->arraylengthDimLine);
			shapesPtr->m_text.resize(shapesPtr->arraylengthText);


			//OpenGL
			for(int i = 0; i < 2; i++)
				cadWin.shapes->lineCoorsBuffer.pop_back();

		}

		if (shapesPtr->lastStackShapeWrite->back() == 3 && !shapesPtr->m_ellipses.empty() && canStepBack)
		{
			canStepBack = false;

			shapesPtr->m_ellipses.pop_back();
			shapesPtr->arraylengthEllipses--;
			shapesPtr->lastStackShapeWrite->pop_back();
			shapesPtr->arrayLengthShapeStack--;

			//shapesPtr->m_dimLines.pop_back();
			//shapesPtr->arraylengthDimLine--;
			//shapesPtr->m_text.pop_back();
			//shapesPtr->arraylengthText--;

			shapesPtr->m_ellipses.resize(shapesPtr->arraylengthEllipses);
			//shapesPtr->lastStackShapeWrite->resize(shapesPtr->arrayLengthShapeStack);
			//shapesPtr->m_dimLines.resize(shapesPtr->arraylengthDimLine);
			//shapesPtr->m_text.resize(shapesPtr->arraylengthText);
		}
	
}

void shapeManagment::eraseTool()
{

}
