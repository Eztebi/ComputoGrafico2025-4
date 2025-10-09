#version 460 core

layout (location = 0) in vec4 vPosition;

void main()
{
	gl_Position = vPosition; //equivale a hacer return gl_Position
}