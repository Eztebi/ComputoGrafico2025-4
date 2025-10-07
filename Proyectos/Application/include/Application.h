#pragma once
#include "glad.h"
#include <vector>
#include <map>

class Application {
public:
	void setup();
	void update();
	void draw();
private:
	std::vector<float> geometry{
	    //x      y     z     w
		(-1.f , 1.0f ,0.0f, 1.0f), //vertice 1
		(-1.0f, -1.0f, 0.0f, 1.0f), //vertice 2
		(1.0f, -1.0, 0.0f, 1.0f) //vertice 3
	};
	std::map<std::string, GLuint> ids;
};