#pragma once
#include "glad.h"
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "GLFW/glfw3.h";
#include "glm/glm.hpp";
#include "glm/gtc/matrix_transform.hpp";

class Application {
public:
	void setup();
	void update();
	void draw();
	void SetUpGeometria();
	void SetUpProgamaShaders();
	void SetUpProgamaCamera();
	void SetUpCube();
	glm::mat4 camera;
	glm::mat4 projection;
	glm::vec3 eye{ 0.0f,0.f,2.0f };
	glm::vec3 center{ 0.0f,0.0f,0.0f };
	static std::string leer_archivo_a_string(const std::string& ruta_archivo);
	GLFWwindow* window;
	void keyCallbalck(int key, int scancode, int action, int nods);
private:
	float time{ 0.0f };
	float xPos{ 0.0f };
	float yPos{ 0.0f };
	float xRot{ 0.0f };
	float yRot{ 0.0f };
	std::map<std::string, GLuint> ids;          
};