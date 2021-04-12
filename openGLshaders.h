#pragma once
#ifndef SHADERS_H
#define SHADERS_H

#include <GL/glew.h>
#include <glm.hpp>

class openGLshaders
{
public:
	unsigned int ID;

	GLuint loadShaders(const char * vertex_file_path, const char * fragment_file_path);

};

#endif !SHADERS_H