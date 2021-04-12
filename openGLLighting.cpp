/*#include "openGLLighting.h"

#include "GL/glew.h"
#include <glfw3.h>
#include <gtc/matrix_transform.hpp>
#include <gtx/transform.hpp>

openGLLighting::openGLLighting(bool loop)
{

	if (!loop)
	{
		int normalVecBuffSize = 12;

		GLuint *normalbuffer;
		pointerToNBuffer = normalbuffer;
		glGenBuffers(1, normalbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, *normalbuffer);
		glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(glm::vec3), &initializeNormals()[0], GL_STATIC_DRAW);
	}

	else
		bufferLoop(pointerToNBuffer);
}


std::vector<glm::vec3> openGLLighting::initializeNormals()
{
	std::vector<glm::vec3> normals;

	return normals;
}

void openGLLighting::bufferLoop(GLuint *normalbuffer)
{
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, *normalbuffer);
	glVertexAttribPointer(
		2,                                
		3,                               
		GL_FLOAT,                         
		GL_FALSE,                         
		0,                                
		(void*)0                          
	);
}*/
