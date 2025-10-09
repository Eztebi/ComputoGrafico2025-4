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
	std::vector<float> geometry{
	    //x      y     z     w
		(-1.f , 1.0f ,0.0f, 1.0f), //vertice 1
		(-1.0f, -1.0f, 0.0f, 1.0f), //vertice 2
		(1.0f, -1.0, 0.0f, 1.0f) //vertice 3
	};
	std::map<std::string, GLuint> ids;          
};