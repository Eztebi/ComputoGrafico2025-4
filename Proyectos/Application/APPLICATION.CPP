#include "Application.h"
#include "ShaderFuncs.h"
#include <GLFW/glfw3.h>

void Application::setup()
{
	SetUpGeometria();
	SetUpProgamaShaders();
	SetUpProgamaCamera();
	projection = glm::perspective(45.0f, 1024.0f / 768.0f, 0.1f, 100.0f);
	glEnable(GL_DEPTH_TEST);
}

void Application::update()
{
	//time += 0.1f;
	eye = glm::vec3(0.0f, 0.0f, 5.0f);
	center = glm::vec3(0.0f, 0.0f, 0.0f);
	camera = glm::lookAt(eye, center, glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, (float)zOffset));
	glm::mat4 rotateX = glm::rotate(glm::mat4(1.0f),glm::radians(xRot),glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 rotateY = glm::rotate(glm::mat4(1.0f),glm::radians(yRot),glm::vec3(0.0f, 1.0f, 0.0f));

	model = rotateX * rotateY * translate * scale;
}

void Application::draw()
{
	//selecciona programa de shaders
	//glUseProgram(ids["program1"]);
	glUseProgram(ids["program2"]);
	//Pasa los parametros del programa. Los Asocia del cpu al gpu
	glUniform1f(ids["time2"], time);
	glUniformMatrix4fv(ids["model"], 1,GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(ids["camera"], 1,GL_FALSE, &camera[0][0]);
	glUniformMatrix4fv(ids["projection"], 1,GL_FALSE, &projection[0][0]);
	
	glUniform1f(ids["xPos"], xPos);
	glUniform1f(ids["yPos"], yPos);
	glUniform1f(ids["xRot"], xRot);
	glUniform1f(ids["yRot"], yRot);
	//selecciona geometria (triangulo)
	glBindVertexArray(ids["triangle"]);

	//gl_draw
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Application::SetUpGeometria()
{
	std::vector<float> geometry{
		//x      y     z     w
		// vertices
		//v1 Frente T1
		-1.0f,  1.0f,  1.0f, 1.0f,
		-1.0f, -1.0f,  1.0f, 1.0f,
		1.0f, -1.0f,  1.0f, 1.0f,
		//v1 frente T2
		-1.0f,  1.0f,  1.0f, 1.0f,
		1.0f, -1.0f,  1.0f, 1.0f,
		1.0f, 1.0f,  1.0f, 1.0f,

		//v2 atras T1
		-1.0f,  1.0f,  -1.0f, 1.0f,
		-1.0f, -1.0f,  -1.0f, 1.0f,
		1.0f, -1.0f,  -1.0f, 1.0f,
		//v2 atras T2
		-1.0f,  1.0f,  -1.0f, 1.0f,
		1.0f, -1.0f,  -1.0f, 1.0f,
		1.0f, 1.0f,  -1.0f, 1.0f,

		//v3 Derecha T1
	    1.0f, 1.0f, 1.0f, 1.0f,
	    1.0f,  -1.0f, 1.0f, 1.0f,
	    1.0f, -1.0f,  -1.0f, 1.0f,
		//v3 DERECHA T2
	    1.0f, 1.0f, 1.0f, 1.0f,
	    1.0f, -1.0f,  -1.0f, 1.0f,
	    1.0f, 1.0f,  -1.0f, 1.0f,
		
	    //v4 Izquierda t1
		-1.0f, 1.0f, 1.0f, 1.0f,
		-1.0f,  -1.0f, 1.0f, 1.0f,
		-1.0f, -1.0f,  -1.0f, 1.0f,
		//v4 Izquierda T2
		-1.0f, 1.0f, 1.0f, 1.0f,
		-1.0f, -1.0f,  -1.0f, 1.0f,
		-1.0f, 1.0f,  -1.0f, 1.0f,

	    //v5 Arriba t1
	    -1.0f,  1.0f, 1.0f, 1.0f,
	    1.0f,  1.0f,  1.0f, 1.0f,
		 1.0f,  1.0f, -1.0f, 1.0f,
		 //v5 arriba t2
	    -1.0f,  1.0f, 1.0f, 1.0f,
		 1.0f,  1.0f, -1.0f, 1.0f,
		 -1.0f,  1.0f, -1.0f, 1.0f,


	   	 //v6 Abajo t1
		-1.0f,  -1.0f, 1.0f, 1.0f,
		1.0f,  -1.0f,  1.0f, 1.0f,
		 1.0f,  -1.0f, -1.0f, 1.0f,
		 //v6 abajo t2
		-1.0f,  -1.0f, 1.0f, 1.0f,
		 1.0f,  -1.0f, -1.0f, 1.0f,
		 -1.0f,  -1.0f, -1.0f, 1.0f,
		
		//colores
		//V1 rojo
		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,

		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,

		//v2blanco
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,

		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,

	    //v3 verde
	    0.0f, 1.0f, 0.0f, 1.0f,
	    0.0f, 1.0f, 0.0f, 1.0f,
	    0.0f, 1.0f, 0.0f, 1.0f,
		
	    0.0f, 1.0f, 0.0f, 1.0f,
	    0.0f, 1.0f, 0.0f, 1.0f,
	    0.0f, 1.0f, 0.0f, 1.0f,
	    
		//v4 azul
	    0.0f, 0.0f, 1.0f, 1.0f,
	    0.0f, 0.0f, 1.0f, 1.0f,
	    0.0f, 0.0f, 1.0f, 1.0f,
	    
		0.0f, 0.0f, 1.0f, 1.0f,
	    0.0f, 0.0f, 1.0f, 1.0f,
	    0.0f, 0.0f, 1.0f, 1.0f,
		
		//v5 naranja
		 1.0f, 0.5f, 0.0f, 1.0f,
		 1.0f, 0.5f, 0.0f, 1.0f,
		 1.0f, 0.5f, 0.0f, 1.0f,
		
		 1.0f, 0.5f, 0.0f, 1.0f,
		 1.0f, 0.5f, 0.0f, 1.0f,
		 1.0f, 0.5f, 0.0f, 1.0f,
		 
		//v6 amarillo
		  1.0f, 1.0f, 0.0f, 1.0f,
		  1.0f, 1.0f, 0.0f, 1.0f,
		  1.0f, 1.0f, 0.0f, 1.0f,
		  
		  1.0f, 1.0f, 0.0f, 1.0f,
		  1.0f, 1.0f, 0.0f, 1.0f,
		  1.0f, 1.0f, 0.0f, 1.0f
	};
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
		sizeof(GLfloat) * geometry.size(), //calculo de tamaño en bytes
		&geometry[0],
		GL_STATIC_DRAW); //Manda la geometria al buffer

	//glVertexAtrubvPointer sirve para decirle como va a leer la geometria
	//para vertices
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	//para color
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)(144 * sizeof(float)));
	glEnableVertexAttribArray(1);

	std::cout << "setup" << std::endl;
}

void Application::SetUpProgamaShaders()
{
	std::string strVertexShader = leer_archivo_a_string("Shaders/VertexShader.glsl");
	std::string strFragmentShader = leer_archivo_a_string("Shaders/FragmentShader.glsl");
	ids["program1"] = ShaderFuncs::InitializeProgram(strVertexShader, strFragmentShader);
	ids["time1"] = glGetUniformLocation(ids["program1"], "time");
	ids["xPos"] = glGetUniformLocation(ids["program1"], "xPos");
	ids["yPos"] = glGetUniformLocation(ids["program1"], "yPos");
	ids["xRot"] = glGetUniformLocation(ids["program1"], "xRot");
	ids["yRot"] = glGetUniformLocation(ids["program1"], "yRot");
}
void Application::SetUpProgamaCamera() {
	std::string strVertexShader = leer_archivo_a_string("Shaders/VertexCamera.glsl");
	std::string strFragmentShader = leer_archivo_a_string("Shaders/FragmentCamera.glsl");
	ids["program2"] = ShaderFuncs::InitializeProgram(strVertexShader, strFragmentShader);
	ids["time2"] = glGetUniformLocation(ids["program2"], "time");
	ids["model"] = glGetUniformLocation(ids["program2"], "model");
	ids["projection"] = glGetUniformLocation(ids["program2"], "projection");
	ids["camera"] = glGetUniformLocation(ids["program2"], "camera");
	ids["xPos"] = glGetUniformLocation(ids["program1"], "xPos");
	ids["yPos"] = glGetUniformLocation(ids["program1"], "yPos");
	ids["xRot"] = glGetUniformLocation(ids["program1"], "xRot");
	ids["yRot"] = glGetUniformLocation(ids["program1"], "yRot");
}
void Application::SetUpCube()
{
}
std::string Application::leer_archivo_a_string(const std::string& ruta_archivo) {
	// 1. Abrir el archivo
	// std::ios::in es para modo de entrada (lectura)
	std::ifstream archivo_entrada(ruta_archivo, std::ios::in);

	// 2. Verificar si el archivo se abrió correctamente
	if (!archivo_entrada.is_open()) {
		// Podrías añadir un mensaje de error si lo deseas
		std::cerr << "Error: No se pudo abrir el archivo en la ruta: " << ruta_archivo << std::endl;
		return ""; // Devuelve un string vacío en caso de error
	}

	// 3. Crear un stream de salida de string para construir el resultado
	std::ostringstream ss;

	// 4. Leer el contenido del archivo al stream de string
	// El operador << sobrecarga para 'std::ifstream' y 'std::ostringstream' 
	// permite una lectura y escritura muy eficiente.
	ss << archivo_entrada.rdbuf();

	// 5. Devolver el string resultante
	return ss.str();
}

void Application::keyCallback(int key, int scancode, int action, int nods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	//Traslacion
	//A
	if (key == GLFW_KEY_A && action == GLFW_REPEAT)
		xPos -= 0.01f;
	//D
	if (key == GLFW_KEY_D && action == GLFW_REPEAT)
		xPos += 0.01f;
	//W
	if (key == GLFW_KEY_W && action == GLFW_REPEAT)
		yPos += 0.01f;
	//S
	if (key == GLFW_KEY_S && action == GLFW_REPEAT)
		yPos -= 0.01f;

	//Rotacion
	//UP
	if (key == GLFW_KEY_UP && action == GLFW_REPEAT)
		yRot += 0.01f;
	//DOWN
	if (key == GLFW_KEY_DOWN && action == GLFW_REPEAT)
		yRot -= 0.01f;
	//LEFT
	if (key == GLFW_KEY_LEFT && action == GLFW_REPEAT)
		xRot -= 0.01f;
	//RIGHT
	if (key == GLFW_KEY_RIGHT && action == GLFW_REPEAT)
		xRot += 0.01f;
}
double deltaX;
double deltaY;
void Application::cursorCallback(double xpos, double ypos)
{
	static double lastX = xpos;
	static double lastY = ypos;

	float sensitivity = 0.1f;

	float deltaX = xpos - lastX;
	float deltaY = ypos - lastY;

	yRot += deltaX * sensitivity;
	xRot += deltaY * sensitivity;

	lastX = xpos;
	lastY = ypos;
}
void Application::scrollCallback(double yoffset)
{
	zOffset += yoffset * 0.5f; 
}