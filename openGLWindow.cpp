#include "openGLWindow.h"
#include "GL/glew.h"
#include <glfw3.h>
#include <gtc/matrix_transform.hpp>
#include <gtx/transform.hpp>

#include "openGLshaders.h"
#include "Coors2DTo3D.h"
#include "openGLCamera.h"
#include "assets_gl.h"
#include "exportOBJ.h"

#include <iostream>
#include <vector>
#include <windows.h>
#include <shlobj.h>
#include <stdlib.h>

#include "imgui.h"
#include "imgui-SFML.h"

#define PI 3.14159265359

struct bufferData
{
	bool firstFillBuffer = true;
	bool init = true;

	Coors2DTo3D* coorsConverter = new Coors2DTo3D();

	GLfloat* initializeVertices(bool initialization)
	{

		static GLfloat g_vertex_buffer_data[10000];
		int n = 0;

		const static float wHeight = .10f;
		const static float wWidth = .010f;


		for (int i = 0; i < coorsConverter->vertexSize / 2; i++)
		{
			int num = i * 90;
			float sinAngle;
			float cosAngle;
			float degAngle = coorsConverter->getVertexEdgeAngle(0 + n) * 180 / PI;

			if (degAngle < 90)
			{
				cosAngle = std::cos(coorsConverter->getVertexEdgeAngle(0 + n)) * wWidth - wWidth;
				sinAngle = std::sin(coorsConverter->getVertexEdgeAngle(0 + n)) * wWidth;
			}

			if (degAngle == 90)
			{
				sinAngle = wWidth * -1;
				cosAngle = wWidth * -1;
			}

			if (coorsConverter->vertexBuffer[0 + n].x > coorsConverter->vertexBuffer[1 + n].x)
			{
				cosAngle = std::cos(coorsConverter->getVertexEdgeAngle(0 + n)) * wWidth + wWidth * -1;
				sinAngle = std::sin(coorsConverter->getVertexEdgeAngle(0 + n)) * wWidth * -1;
			}

			g_vertex_buffer_data[0 + num] = coorsConverter->vertexBuffer[0 + n].x; g_vertex_buffer_data[1 + num] = coorsConverter->vertexBuffer[0 + n].y; g_vertex_buffer_data[2 + num] = coorsConverter->vertexBuffer[0 + n].z;
			g_vertex_buffer_data[3 + num] = coorsConverter->vertexBuffer[1 + n].x; g_vertex_buffer_data[4 + num] = coorsConverter->vertexBuffer[1 + n].y; g_vertex_buffer_data[5 + num] = coorsConverter->vertexBuffer[1 + n].z;
			g_vertex_buffer_data[6 + num] = coorsConverter->vertexBuffer[1 + n].x; g_vertex_buffer_data[7 + num] = coorsConverter->vertexBuffer[0 + n].y + wHeight; g_vertex_buffer_data[8 + num] = coorsConverter->vertexBuffer[1 + n].z;

			g_vertex_buffer_data[9 + num] = coorsConverter->vertexBuffer[0 + n].x; g_vertex_buffer_data[10 + num] = coorsConverter->vertexBuffer[0 + n].y; g_vertex_buffer_data[11 + num] = coorsConverter->vertexBuffer[0 + n].z;
			g_vertex_buffer_data[12 + num] = coorsConverter->vertexBuffer[0 + n].x; g_vertex_buffer_data[13 + num] = coorsConverter->vertexBuffer[0 + n].y + wHeight; g_vertex_buffer_data[14 + num] = coorsConverter->vertexBuffer[0 + n].z;
			g_vertex_buffer_data[15 + num] = coorsConverter->vertexBuffer[1 + n].x; g_vertex_buffer_data[16 + num] = coorsConverter->vertexBuffer[0 + n].y + wHeight; g_vertex_buffer_data[17 + num] = coorsConverter->vertexBuffer[1 + n].z;


			g_vertex_buffer_data[18 + num] = coorsConverter->vertexBuffer[0 + n].x + sinAngle; g_vertex_buffer_data[19 + num] = coorsConverter->vertexBuffer[0 + n].y; g_vertex_buffer_data[20 + num] = (coorsConverter->vertexBuffer[0 + n].z + wWidth) + cosAngle;
			g_vertex_buffer_data[21 + num] = coorsConverter->vertexBuffer[1 + n].x + sinAngle; g_vertex_buffer_data[22 + num] = coorsConverter->vertexBuffer[1 + n].y; g_vertex_buffer_data[23 + num] = (coorsConverter->vertexBuffer[1 + n].z + wWidth) + cosAngle;
			g_vertex_buffer_data[24 + num] = coorsConverter->vertexBuffer[1 + n].x + sinAngle; g_vertex_buffer_data[25 + num] = coorsConverter->vertexBuffer[0 + n].y + wHeight; g_vertex_buffer_data[26 + num] = (coorsConverter->vertexBuffer[1 + n].z + wWidth) + cosAngle;

			g_vertex_buffer_data[27 + num] = coorsConverter->vertexBuffer[0 + n].x + sinAngle; g_vertex_buffer_data[28 + num] = coorsConverter->vertexBuffer[0 + n].y; g_vertex_buffer_data[29 + num] = (coorsConverter->vertexBuffer[0 + n].z + wWidth) + cosAngle;
			g_vertex_buffer_data[30 + num] = coorsConverter->vertexBuffer[0 + n].x + sinAngle; g_vertex_buffer_data[31 + num] = coorsConverter->vertexBuffer[0 + n].y + wHeight; g_vertex_buffer_data[32 + num] = (coorsConverter->vertexBuffer[0 + n].z + wWidth) + cosAngle;
			g_vertex_buffer_data[33 + num] = coorsConverter->vertexBuffer[1 + n].x + sinAngle; g_vertex_buffer_data[34 + num] = coorsConverter->vertexBuffer[0 + n].y + wHeight; g_vertex_buffer_data[35 + num] = (coorsConverter->vertexBuffer[1 + n].z + wWidth) + cosAngle;


			g_vertex_buffer_data[36 + num] = coorsConverter->vertexBuffer[1 + n].x; g_vertex_buffer_data[37 + num] = coorsConverter->vertexBuffer[1 + n].y; g_vertex_buffer_data[38 + num] = coorsConverter->vertexBuffer[1 + n].z;
			g_vertex_buffer_data[39 + num] = coorsConverter->vertexBuffer[1 + n].x + sinAngle; g_vertex_buffer_data[40 + num] = coorsConverter->vertexBuffer[1 + n].y; g_vertex_buffer_data[41 + num] = (coorsConverter->vertexBuffer[1 + n].z + wWidth) + cosAngle;
			g_vertex_buffer_data[42 + num] = coorsConverter->vertexBuffer[1 + n].x + sinAngle; g_vertex_buffer_data[43 + num] = coorsConverter->vertexBuffer[0 + n].y + wHeight; g_vertex_buffer_data[44 + num] = (coorsConverter->vertexBuffer[1 + n].z + wWidth) + cosAngle;

			g_vertex_buffer_data[45 + num] = coorsConverter->vertexBuffer[1 + n].x; g_vertex_buffer_data[46 + num] = coorsConverter->vertexBuffer[1 + n].y; g_vertex_buffer_data[47 + num] = coorsConverter->vertexBuffer[1 + n].z;
			g_vertex_buffer_data[48 + num] = coorsConverter->vertexBuffer[1 + n].x; g_vertex_buffer_data[49 + num] = coorsConverter->vertexBuffer[0 + n].y + wHeight; g_vertex_buffer_data[50 + num] = coorsConverter->vertexBuffer[1 + n].z;
			g_vertex_buffer_data[51 + num] = coorsConverter->vertexBuffer[1 + n].x + sinAngle; g_vertex_buffer_data[52 + num] = coorsConverter->vertexBuffer[0 + n].y + wHeight; g_vertex_buffer_data[53 + num] = (coorsConverter->vertexBuffer[1 + n].z + wWidth) + cosAngle;


			g_vertex_buffer_data[54 + num] = coorsConverter->vertexBuffer[1 + n].x; g_vertex_buffer_data[55 + num] = coorsConverter->vertexBuffer[0 + n].y + wHeight; g_vertex_buffer_data[56 + num] = coorsConverter->vertexBuffer[1 + n].z;
			g_vertex_buffer_data[57 + num] = coorsConverter->vertexBuffer[0 + n].x; g_vertex_buffer_data[58 + num] = coorsConverter->vertexBuffer[0 + n].y + wHeight; g_vertex_buffer_data[59 + num] = coorsConverter->vertexBuffer[0 + n].z;
			g_vertex_buffer_data[60 + num] = coorsConverter->vertexBuffer[0 + n].x + sinAngle; g_vertex_buffer_data[61 + num] = coorsConverter->vertexBuffer[0 + n].y + wHeight; g_vertex_buffer_data[62 + num] = (coorsConverter->vertexBuffer[0 + n].z + wWidth) + cosAngle;

			g_vertex_buffer_data[63 + num] = coorsConverter->vertexBuffer[1 + n].x; g_vertex_buffer_data[64 + num] = coorsConverter->vertexBuffer[0 + n].y + wHeight; g_vertex_buffer_data[65 + num] = coorsConverter->vertexBuffer[1 + n].z;
			g_vertex_buffer_data[66 + num] = coorsConverter->vertexBuffer[1 + n].x + sinAngle; g_vertex_buffer_data[67 + num] = coorsConverter->vertexBuffer[0 + n].y + wHeight; g_vertex_buffer_data[68 + num] = (coorsConverter->vertexBuffer[1 + n].z + wWidth) + cosAngle;
			g_vertex_buffer_data[69 + num] = coorsConverter->vertexBuffer[0 + n].x + sinAngle; g_vertex_buffer_data[70 + num] = coorsConverter->vertexBuffer[0 + n].y + wHeight; g_vertex_buffer_data[71 + num] = (coorsConverter->vertexBuffer[0 + n].z + wWidth) + cosAngle;

			g_vertex_buffer_data[72 + num] = coorsConverter->vertexBuffer[0 + n].x; g_vertex_buffer_data[73 + num] = coorsConverter->vertexBuffer[0 + n].y; g_vertex_buffer_data[74 + num] = coorsConverter->vertexBuffer[0 + n].z;
			g_vertex_buffer_data[75 + num] = coorsConverter->vertexBuffer[0 + n].x + sinAngle; g_vertex_buffer_data[76 + num] = coorsConverter->vertexBuffer[0 + n].y; g_vertex_buffer_data[77 + num] = (coorsConverter->vertexBuffer[0 + n].z + wWidth) + cosAngle;
			g_vertex_buffer_data[78 + num] = coorsConverter->vertexBuffer[0 + n].x + sinAngle; g_vertex_buffer_data[79 + num] = coorsConverter->vertexBuffer[0 + n].y + wHeight; g_vertex_buffer_data[80 + num] = (coorsConverter->vertexBuffer[0 + n].z + wWidth) + cosAngle;

			g_vertex_buffer_data[81 + num] = coorsConverter->vertexBuffer[0 + n].x; g_vertex_buffer_data[82 + num] = coorsConverter->vertexBuffer[0 + n].y; g_vertex_buffer_data[83 + num] = coorsConverter->vertexBuffer[0 + n].z;
			g_vertex_buffer_data[84 + num] = coorsConverter->vertexBuffer[0 + n].x; g_vertex_buffer_data[85 + num] = coorsConverter->vertexBuffer[0 + n].y + wHeight; g_vertex_buffer_data[86 + num] = coorsConverter->vertexBuffer[0 + n].z;
			g_vertex_buffer_data[87 + num] = coorsConverter->vertexBuffer[0 + n].x + sinAngle; g_vertex_buffer_data[88 + num] = coorsConverter->vertexBuffer[0 + n].y + wHeight; g_vertex_buffer_data[89 + num] = (coorsConverter->vertexBuffer[0 + n].z + wWidth) + cosAngle;

			n += 2;
		}

		return g_vertex_buffer_data;
	}

	GLfloat g_vertex_buffer_data_floor[10000];
	int i = 0;

	GLfloat* initializeVertices_floor()
	{
		for (auto iterator : coorsConverter->computePolygons(false, coorsConverter->nFloor))
		{
			g_vertex_buffer_data_floor[i] = iterator;
			i++;
		}

		return g_vertex_buffer_data_floor;
	}


	GLfloat g_vertex_bufffer_data_window[10000];
	int j = 0;

	GLfloat* initializeVertices_window()
	{
		assets_gl* assetObject = new assets_gl;

		if (assetObject != nullptr)
		{
			for (auto it : *assetObject->computePolygonsWindow())
			{
				g_vertex_bufffer_data_window[j] = it.x;
				j++;
				g_vertex_bufffer_data_window[j] = it.y * .10f;
				j++;
				g_vertex_bufffer_data_window[j] = it.z;
				j++;
			}
			int a = 0;

			return g_vertex_bufffer_data_window;
		}
		else
			return nullptr;
	}
};

static const GLfloat lightCube[] =
{
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,

		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,

		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
};

static int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{

	if (uMsg == BFFM_INITIALIZED)
	{
		std::string tmp = (const char*)lpData;
		std::cout << "path: " << tmp << std::endl;
		SendMessage(hwnd, BFFM_SETSELECTION, TRUE, lpData);
	}

	return 0;
}

std::string ws2s(const std::wstring& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = WideCharToMultiByte(CP_ACP, 0, s.c_str(), slength, 0, 0, 0, 0);
	char* buf = new char[len];
	WideCharToMultiByte(CP_ACP, 0, s.c_str(), slength, buf, len, 0, 0);
	std::string r(buf);
	delete[] buf;
	return r;
}


std::string saveAs()
{
	std::wstring src;
	const std::wstring title = L"Save As";

	wchar_t filename[MAX_PATH];

	OPENFILENAMEW ofn;
	ZeroMemory(&filename, sizeof(filename));
	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = L"3D Object (.obj)\0*.obj\0All\0*.*\0";
	ofn.lpstrFile = LPWSTR(filename);
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrTitle = title.c_str();
	ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

	if (GetSaveFileNameW(&ofn))
	{
		src = filename;
		return ws2s(src);
	}
	return "";
}


openGLWindow::openGLWindow()
{
	windowInit();
	glewInit();
	glfwInit();

	bufferData* dataObject = new bufferData;

	if (dataObject->coorsConverter != nullptr)
		bufferSize = dataObject->coorsConverter->vertexSize / 2;
	else
		exit(0);

	//delete coorsConverter;

	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, 360 * bufferSize, dataObject->initializeVertices(false), GL_STATIC_DRAW);

	GLuint vertexBufferFloor;
	glGenBuffers(1, &vertexBufferFloor);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferFloor);
	glBufferData(GL_ARRAY_BUFFER, 10000, dataObject->initializeVertices_floor(), GL_STATIC_DRAW);
	size_t bufferSize_floor = dataObject->i;

	GLuint vertexBufferWindow;
	glGenBuffers(1, &vertexBufferWindow);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferWindow);
	glBufferData(GL_ARRAY_BUFFER, 10000, dataObject->initializeVertices_window(), GL_STATIC_DRAW);

	GLuint lightBuffer;
	glGenBuffers(1, &lightBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, lightBuffer);
	glBufferData(GL_ARRAY_BUFFER, 360 * bufferSize, lightCube, GL_STATIC_DRAW);

	openGLshaders* shaders = new openGLshaders();
	GLuint programID = shaders->loadShaders("shaders/vertexShaders.vshader", "shaders/fragmentShaders.fshader");
	GLuint programID1 = shaders->loadShaders("shaders/nCubeVShader.vshader", "shaders/nCubeFShader.fshader");
	GLuint programID2 = shaders->loadShaders("shaders/vertexShaderFloor.vshader", "shaders/fragmentShaderFloor.fshader");
	GLuint programID3 = shaders->loadShaders("shaders/vertexShaderWindow.vshader", "shaders/fragmentShaderWindow.fshader");

	//Steny
	GLuint ModelID = glGetUniformLocation(programID, "model");
	GLuint ViewID = glGetUniformLocation(programID, "view");
	GLuint ProjectionID = glGetUniformLocation(programID, "projection");
	GLuint LightColorID = glGetUniformLocation(programID, "lightColor");
	GLuint LightPosID = glGetUniformLocation(programID, "lightPos");
	GLuint ColorID = glGetUniformLocation(programID, "color");
	GLuint ViewPosID = glGetUniformLocation(programID, "viewPos");

	//Zdroj svetla (kocka)
	GLuint ModelID1 = glGetUniformLocation(programID1, "model");
	GLuint ViewID1 = glGetUniformLocation(programID1, "view");
	GLuint ProjectionID1 = glGetUniformLocation(programID1, "projection");

	//Podlaha
	GLuint ModelID2 = glGetUniformLocation(programID2, "model");
	GLuint ViewID2 = glGetUniformLocation(programID2, "view");
	GLuint ProjectionID2 = glGetUniformLocation(programID2, "projection");
	GLuint LightColorID2 = glGetUniformLocation(programID2, "lightColor");
	GLuint LightPosID2 = glGetUniformLocation(programID2, "lightPos");
	GLuint ColorID2 = glGetUniformLocation(programID2, "color");
	GLuint ViewPosID2 = glGetUniformLocation(programID2, "viewPos");

	//Oknna
	GLuint ModelID3 = glGetUniformLocation(programID3, "model");
	GLuint ViewID3 = glGetUniformLocation(programID3, "view");
	GLuint ProjectionID3 = glGetUniformLocation(programID3, "projection");
	GLuint LightColorID3 = glGetUniformLocation(programID3, "lightColor");
	GLuint LightPosID3 = glGetUniformLocation(programID3, "lightPos");
	GLuint ColorID3 = glGetUniformLocation(programID3, "color");
	GLuint ViewPosID3 = glGetUniformLocation(programID3, "viewPos");

	//LIGHTING
	float RGB[3] = {1.f, 1.f, 1.f};
	float RGB_floor[3] = { 1.f, 1.f, 1.f };
	bool fEdit = false;
	glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos(1.0f, 1.0f, 1.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	float x = 1.0;

	openGLCamera camera;
	this->cameraPosition = camera.getCameraPosition();

	sf::Clock deltaClock;

	glBindVertexArray(0);

	bool popup = false;
	bool canDrawCursor = true;

	ImGuiIO& io = ImGui::GetIO();
	io.MouseDrawCursor = true;
	


	int frame = 0;

	while (programRuns)
	{

		sf::Event event;

		while (glR_Window->pollEvent(event))
		{
			ImGui::SFML::ProcessEvent(event);

			if (event.type == sf::Event::Closed)
			{
				glR_Window->setActive(false);
				glR_Window->close();
				programRuns = false;

				delete dataObject;
			}

			else if (event.type == sf::Event::Resized)
			{
				glViewport(0, 0, event.size.width, event.size.height);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				glR_Window->setActive(false);
				glR_Window->close();
				programRuns = false;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			{
				Coors2DTo3D* coorsConverter = new Coors2DTo3D();
				std::cout << coorsConverter->getVertexEdgeAngle(0) << std::endl;
				delete coorsConverter;
			}

			if (!this->renderGui)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
				{
					this->keyPressed = true;
				}

			}
			else
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
					this->keyPressed = true;

			if (this->keyPressed)
			{
				if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Tab) && !this->renderGui)
				{
					this->renderGui = true;
					this->keyPressed = false;
				}
				else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Tab) && this->renderGui)
				{
					sf::Mouse::setPosition(this->oldMousePos);
					this->renderGui = false;
					this->keyPressed = false;
				}
			}
		}
		if (!this->renderGui)
		{
			camera.computeMatricesFromInputs();
			this->project = camera.getProjectionMatrix();
			this->view = camera.getViewMatrix();
			this->oldMousePos = sf::Mouse::getPosition(*this->glR_Window);
		}

		glm::mat4 ProjectionMatrix = this->project;
		glm::mat4 ViewMatrix = this->view;
		glm::mat4 ModelMatrix = glm::mat4(1.0);
		glm::vec3 matColor(RGB[0], RGB[1], RGB[2]);
		glm::vec3 matColorFloor(RGB_floor[0], RGB_floor[1], RGB_floor[2]);

		glm::mat4 ModelMatrix1 = glm::mat4(1.0);
		ModelMatrix1 = glm::translate(ModelMatrix1, lightPos);
		ModelMatrix1 = glm::scale(ModelMatrix1, glm::vec3(0.2f));

		ImGui::SFML::Update(*this->glR_Window, deltaClock.restart());

		ImGui::Begin("OpenGL Config");
		if (ImGui::Button("Edit Vertex Shader")) 
		{
			fEdit = false;
		}
		if (ImGui::Button("Edit Fragment Shader"))
		{
			fEdit = true;
		}
		if (ImGui::Button("Export Obj"))
		{
			fEdit = false;
			ShowCursor(true);
			ShowCursor(true);

			std::string path = saveAs();
			std::cout << path << std::endl;

			ShowCursor(false);
			ShowCursor(false);
			exportOBJ::exportObj(dataObject->initializeVertices(false), 90 * bufferSize, 1, path);
			exportOBJ::exportObj(dataObject->initializeVertices_floor(), bufferSize_floor, 90 * bufferSize / 3 + 1, path);
			popup = true;
		}

		if (popup)
		{
			fEdit = false;
			ImGui::Begin("INFO", &popup);
			ImGui::Text("Data successfully exported to an obj file format!!");
			ImGui::End();
		}

		if (fEdit)
		{
			ImGui::SliderFloat3("RGB Values(Walls)", RGB, 0.f, 1.f);
			ImGui::SliderFloat3("RGB Values(Floor)", RGB_floor, 0.f, 1.f);
			std::cout << RGB[0] << std::endl;
		}
		
		ImGui::End(); 

		glClearColor(0.11f, 0.11f, 0.11f, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glVertexAttribPointer
		(
			0,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
		);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferFloor);
		glVertexAttribPointer
		(
			1,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
		);

		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, lightBuffer);
		glVertexAttribPointer(
			2,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
		);

		glEnableVertexAttribArray(3);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferWindow);
		glVertexAttribPointer(
			3,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
		);

		glUseProgram(programID);
		
		glUniformMatrix4fv(ModelID, 1, GL_FALSE, &ModelMatrix[0][0]);
		glUniformMatrix4fv(ViewID, 1, GL_FALSE, &ViewMatrix[0][0]);
		glUniformMatrix4fv(ProjectionID, 1, GL_FALSE, &ProjectionMatrix[0][0]);
		glUniform3fv(LightColorID, 1, &lightColor[0]);
		glUniform3fv(LightPosID, 1, &lightPos[0]);
		glUniform3fv(ColorID, 1, &matColor[0]);
		glUniform3fv(ViewPosID, 1, &cameraPosition[0]);
		
		glBindVertexArray(vertexBuffer);
		glDrawArrays(GL_TRIANGLES, 0, 10 * 3 * bufferSize);


		glUseProgram(programID1);
		glUniformMatrix4fv(ModelID1, 1, GL_FALSE, &ModelMatrix1[0][0]);
		glUniformMatrix4fv(ViewID1, 1, GL_FALSE, &ViewMatrix[0][0]);
		glUniformMatrix4fv(ProjectionID1, 1, GL_FALSE, &ProjectionMatrix[0][0]);

		glBindVertexArray(lightBuffer);
		glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

		glUseProgram(programID2);
		glUniformMatrix4fv(ModelID2, 1, GL_FALSE, &ModelMatrix[0][0]);
		glUniformMatrix4fv(ViewID2, 1, GL_FALSE, &ViewMatrix[0][0]);
		glUniformMatrix4fv(ProjectionID2, 1, GL_FALSE, &ProjectionMatrix[0][0]);
		glUniform3fv(LightColorID2, 1, &lightColor[0]);
		glUniform3fv(LightPosID2, 1, &lightPos[0]);
		glUniform3fv(ColorID2, 1, &matColorFloor[0]);
		glUniform3fv(ViewPosID2, 1, &cameraPosition[0]);

		glBindVertexArray(vertexBufferFloor);
		glDrawArrays(GL_TRIANGLES, 0, 10000);//dorobit velkost buffera nech zbytocne nezere pamat

		glUseProgram(programID3);
		glUniformMatrix4fv(ModelID3, 1, GL_FALSE, &ModelMatrix[0][0]);
		glUniformMatrix4fv(ViewID3, 1, GL_FALSE, &ViewMatrix[0][0]);
		glUniformMatrix4fv(ProjectionID3, 1, GL_FALSE, &ProjectionMatrix[0][0]);
		glUniform3fv(LightColorID3, 1, &lightColor[0]);
		glUniform3fv(LightPosID3, 1, &lightPos[0]);
		glUniform3fv(ColorID3, 1, &matColor[0]);
		glUniform3fv(ViewPosID3, 1, &cameraPosition[0]);

		glBindVertexArray(vertexBufferWindow);
		glDrawArrays(GL_TRIANGLES, 0, 10000);//dorobit velkost buffera nech zbytocne nezere pamat*/

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(3);

		if (this->renderGui)
		{
			this->glR_Window->pushGLStates();
			ImGui::SFML::Render(*this->glR_Window);
			this->glR_Window->popGLStates();
		}
		
		glR_Window->display();
	}
}

openGLWindow::~openGLWindow()
{
	ImGui::SFML::Shutdown();
	delete glR_Window;
	delete this;
}

void openGLWindow::windowInit()
{
	sf::ContextSettings glSettings;
	glSettings.depthBits = 24;
	glSettings.stencilBits = 8;
	glSettings.antialiasingLevel = 8;
	glSettings.sRgbCapable = true;

	glR_Window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Renderer", sf::Style::Default, glSettings);

	glR_Window->setVerticalSyncEnabled(true);
	glR_Window->setActive(true);
	glR_Window->setFramerateLimit(144);

	sf::ContextSettings Settings = glR_Window->getSettings();
	std::cout << "OpenGL version:" << Settings.majorVersion << "." << Settings.minorVersion << std::endl;

	ImGui::SFML::Init(*this->glR_Window);
	programRuns = true;
}

void openGLWindow::bufferHandler(int index)
{
	/*bufferData *dataObject = new bufferData();
	Coors2DTo3D *coorsConverter = new Coors2DTo3D();
	switch (index)
	{
	case 0:
			bufferSize = coorsConverter->vertexSize / 2;
			delete coorsConverter;
			GLuint vertexbuffer;
			glGenBuffers(1, &vertexbuffer);
			glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
			glBufferData(GL_ARRAY_BUFFER, 288 * bufferSize, dataObject->initializeVertices(), GL_STATIC_DRAW);
			GLuint colorbuffer;
			glGenBuffers(1, &colorbuffer);
			glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
			glBufferData(GL_ARRAY_BUFFER, 288 * bufferSize, dataObject->initializeFragments(), GL_STATIC_DRAW);
			GLuint VertexArrayID;
			glGenVertexArrays(1, &VertexArrayID);
			glBindVertexArray(VertexArrayID);
			delete dataObject;

			break;
		case 1:
			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
			glVertexAttribPointer
			(
				0,
				3,
				GL_FLOAT,
				GL_FALSE,
				0,
				(void*)0
			);
			glEnableVertexAttribArray(1);
			glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
			glVertexAttribPointer
			(
				1,
				3,
				GL_FLOAT,
				GL_FALSE,
				0,
				(void*)0
			);
			break;
		case 2:
			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);
			break;
	}*///doriesit koooood
}

float openGLWindow::fpsCounter()
{
	if (firstRun)
	{
		lastTime = glfwGetTime();
		nbFrames = 0;

		firstRun = false;
	}

	double currentTime = glfwGetTime();
	nbFrames++;
	if (currentTime - lastTime >= 1.0) {

		float frameTime = 1000.0 / double(nbFrames);
		FPS = 1000 / frameTime;
		nbFrames = 0;
		lastTime += 1.0;
	}

	return FPS;
}