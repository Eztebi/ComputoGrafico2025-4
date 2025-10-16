#version 460 core

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec4 vColor;

out vec4 vertexColor;
uniform float time;
uniform float xPos;
uniform mat4 camera;
uniform mat4 projection;
uniform mat4 model;

void main()
{
	vertexColor = vColor;
	vec4 newPosition = projection * camera * model * vPosition ;

	gl_Position = newPosition; //equivale a hacer return gl_Position
}