#include "Application.h"
#include <iostream>

void Application::setup()
{
	//crear vertex array object
	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	ids["triangle"] = VAO;

	glBindVertexArray(VAO);

	//crear vertex buffer object de vertices
	glGenBuffers(1, &VBO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO); 

	//PASA arreglo de vertices
	glBufferData(GL_ARRAY_BUFFER, 
		sizeof(GLfloat) * geometry.size(),
		&geometry[0],
		GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	std::cout << "setup" << std::endl;
}

void Application::update()
{
	std::cout << "update" << std::endl;
}

void Application::draw()
{
	std::cout << "Draw" << std::endl;
}
