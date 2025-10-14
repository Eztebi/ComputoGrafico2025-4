#pragma once
#include "glad.h"
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

class Application {
public:
	void setup();
	void update();
	void draw();
	void SetUpGeometria();
	void SetUpProgamaShaders();
	static std::string leer_archivo_a_string(const std::string& ruta_archivo);
	
private:
	float time{ 0.0f };
	std::map<std::string, GLuint> ids;          
};