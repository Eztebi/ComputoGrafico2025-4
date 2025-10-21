#version 460 core

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec4 vColor;

out vec4 vertexColor;
uniform float time;
uniform float xPos;
uniform float yPos;
uniform float xRot;
uniform float yRot;

void main()
{
	vertexColor = vColor;

	vec4 newPosition = vPosition;

	newPosition.x = newPosition.x + xPos;
	newPosition.x = newPosition.x * cos(xRot);

	newPosition.y = newPosition.y + yPos;
	newPosition.y = newPosition.y * cos(yRot);
	
	gl_Position = newPosition; //equivale a hacer return gl_Position
}