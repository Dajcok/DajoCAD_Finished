/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////       C O N T R O L S        ////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////	C + LB     - HOLD FOR DRAWING CIRCLE                                                   //////////////
////////	L + LB     - HOLD FOR DRAWING LINE                                                     //////////////
////////	L || R  + LB + Q - WHEN DRAWING LINE (NOT FIRST ONE) PRESS TO RETURN TO STARTING POINT //////////////
////////	F + LB     - HOLD FOR DRAWING FLOOR LINE											   //////////////
////////	E + LB     - HOLD FOR DRAWING ELLIPSE												   //////////////
////////	D + LB     - HOLD FOR DRAWING DOORLINES												   //////////////
////////	W + LB     - HOLD FOR DRAWING WINDOW LINES      									   //////////////
////////	UP         - PESS FOR NEXT FLOOR													   //////////////
/// --------------------------------------SHAPE-MANAGMENT---------------------------------------------------- ///
////////	DEL        - PRESS TO EREASE CAD EDITOR                                                //////////////
////////	CTRL + Y   - PRESS TO STEP BACK                                                        //////////////
/// --------------------------------------IN-3D-RENDERING-WINDOW--------------------------------------------- ///
////////	ESC		   - PRESS TO RETURN BACK TO CAD EDITOR                                        //////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////       T O          D O       ////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////	Urobiù podporu pre assety                                                              //////////////
////////	Urobiù podporu pre dvÌhanie 1 strany podlahy (do y osi v OpenGL)                       //////////////
////////	Urobiù podporu pre kreslenie viacer˝ch podl·ch na 1 poschodÌ                           //////////////
////////	Urobiù podporu pre okn·, diery v podlahe                                               //////////////
////////	Aktiv·cia / deaktiv·cia poschodÌ                                                       //////////////
////////	pomocou setOrgin urobiù Ëiary so öÌrkou                                                //////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "targetWindow.h"

#include <iostream>

using std::cout; using std::endl;



targetWindow::targetWindow(sf::VideoMode winResolution, sf::Color bgColor, int clockVar):
	clockVar(clockVar),
	bgColor(bgColor),//zmenit aby bolo kompatibilne s glClear()
	winResolution(winResolution)
{
	ShowCursor(false);

	cursorView.setCenter({ 0, 0 });
	cursorView.setSize({ 1920, 1080 });
	cursorView.camera.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));

	sf::Event event;

	dG::dGui m_gui(&window);

	shapeManagment *shapeTools = new shapeManagment;

	shapes = new drawShapes;

	if (!font.loadFromFile("OpenSans-Light.ttf"))
	{
		cout << "Couldn¥t load font" << endl;
	}

	worldCamera(false);
	minimap();

	window.create(this->winResolution, "DCAD");

	mouseOffset = sf::Vector2i(-7, -30);

	window.setActive(true);

	while (window.isOpen())
	{
		sf::Vector2f worldPos = window.mapPixelToCoords(sf::Mouse::getPosition());

		camera.setMousePosition(sf::Mouse::getPosition());
		camera.setWorldPosition(worldPos);
		
		cursor.setPosition({ sf::Mouse::getPosition().x - 960 + mouseOffset.x, sf::Mouse::getPosition().y - 540 + mouseOffset.y });

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			
			if (event.type == sf::Event::MouseWheelMoved)
			{
				camera.setWheelState(event.mouseWheel.delta);
				worldCamera(true);
			}
		}

		//doËastnÈ gui
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
		{
			shapes->circleShape();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			shapes->assetShape(1);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			shapes->assetShape(2);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
		{
			shapes->lineShape(0);

			renderFloorDimLines = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
		{
			shapes->lineShape(1);

			renderFloorDimLines = true;
			floorBufferWrite = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			shapes->ellipseShape();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Delete))
		{
			shapeTools->deleteAll();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && stepBack)
		{
			shapeTools->stepBack();
			stepBack = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
		{
			shapes->memSize++;
			shapes->memoryOfFI.resize(shapes->memSize);
			shapes->memoryOfFI.at(shapes->memSize - 1) = shapes->nOfLines_floor;

			openGLWindow *glWindow = new openGLWindow();
		}


		else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && !stepBack)
		{
			shapeTools->canStepBack = true;
			stepBack = true;
		}
		//////////////////////////////////////////////////


		if (freeLook && !guiActive(sf::Mouse::getPosition()))
		{
			if (camera.getBoundaries_X().y > 1920)
				camera.cameraMove(1);

			else if (camera.getBoundaries_X().x < -1920)
				camera.cameraMove(2);
			
			else if (camera.getBoundaries_Y().y > 1080)
				camera.cameraMove(3);

			else if (camera.getBoundaries_Y().x < -1080)
				camera.cameraMove(4);

			else
				camera.cameraMove(0);
		}

		update(&shapes->m_lineShape, &shapes->m_circles, &shapes->m_ellipses, &shapes->m_dimLines, &shapes->m_text, &cursor, &shapes->m_dimLines_floor, &shapes->m_textFloor, &shapes->m_doors);
	}
}

targetWindow::~targetWindow()
{
	exit(1);
}

void targetWindow::update(std::vector<sf::RectangleShape> *lines, std::vector<sf::CircleShape> *circles, std::vector<dcad::ellipseShape> *ellipses,
	std::vector<dcad::dimensioningLine> *dimLines, std::vector<sf::Text> *text, dcad::cursor *crsr, std::vector<dcad::dimensioningLine> *dimLinesFloor,
	std::vector<sf::Text> *textFloor, std::vector<dcad::assets> *assets)
{
	hoverChange(sf::Mouse::getPosition());

	if (mMap)
		minimap();

	glClearColor(0.11f, 0.11f, 0.11f, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	if (mMap)
	{
		window.draw(mMapPosition);
		window.draw(backgroundObj);
	}

	worldCamera(false);

	if (drawGrid)
		window.draw(backgroundObj);

	if (circles != nullptr)
		for (auto iterator : *circles)
			window.draw(iterator);
	if (lines != nullptr)
		for (auto iterator : *lines)
			window.draw(iterator);
	if (ellipses != nullptr)
		for (auto iterator : *ellipses)
			window.draw(iterator);
	if (assets != nullptr)
		for (auto iterator : *assets)
			window.draw(iterator);

	if (!renderFloorDimLines)
	{
		if (dimLines != nullptr)
			for (auto iterator : *dimLines)
				window.draw(iterator);
		if (text != nullptr)
			for (auto iterator : *text)
				window.draw(iterator);
	}

	else if (renderFloorDimLines)
	{
		if (dimLinesFloor != nullptr)
			for (auto iterator : *dimLinesFloor)
				window.draw(iterator);

		if (textFloor != nullptr)
			for (auto iterator : *textFloor)
				window.draw(iterator);
	}

	window.setView(dGuiView);

	if(finalLeftPanel != nullptr)
		window.draw(*finalLeftPanel);

	window.setView(cursorView.camera);

	if (crsr != nullptr)
		window.draw(*crsr);
		
	window.display();

	if (!guiActive(sf::Mouse::getPosition()))
		worldCamera(false);

	else if(guiActive(sf::Mouse::getPosition()))
		window.setView(dGuiView);

	backgroundObj.drawMBackg(0);

	sf::sleep(sf::milliseconds(clockVar));
}

sf::Vector2f targetWindow::convertCoordinates(sf::Vector2i mousePos) const
{
	return window.mapPixelToCoords(mousePos);
}



void targetWindow::minimap()
{
	if (mSetup)
	{
		minimapView.setCenter({ 0, 0 });
		minimapView.setSize({ 3842, 2162 });
		minimapView.camera.setViewport(sf::FloatRect(0.75f, 0.f, 0.25f, 0.25f));

		mMapPosition.setFillColor(sf::Color(133, 180, 255));

		mSetup = false;
	}

	mMapPosition.setOrigin({ mMapPosition.getSize().x / 2, mMapPosition.getSize().y / 2 });
	mMapPosition.setSize(camera.camera.getSize());
	mMapPosition.setPosition(camera.camera.getCenter());
	minimapView.setView(window);
	
}

void targetWindow::worldCamera(bool event)
{
	if (!event)
	{
		if (setup)
		{
			camera.setCenter({ 1920/2, 1080/2 });
			camera.setSize({ 1280, 720 });
			setup = false;
		}
		camera.setView(window);

		if (camera.getSize().x < 300 && camera.getSize().y < 180)
			backgroundObj.drawMBackg(1);
		else
			backgroundObj.drawMBackg(0);
	}

	if (event)
	{
		if (camera.getSize().x > 1920 && camera.getSize().y > 1080)
			camera.cameraZoom(1);


		else if (camera.getSize().x < 100 && camera.getSize().y < 60)
			camera.cameraZoom(2);

		else
			camera.cameraZoom(0);
	}
}