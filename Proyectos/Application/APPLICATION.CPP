#include "Application.h"
#include "ShaderFuncs.h"
#include <GLFW/glfw3.h>

void Application::setup()
{
	SetUpGeometria();
	SetUpProgamaShaders();
	
}

void Application::update()
{
	time += 0.001f;
}

void Application::draw()
{
	//selecciona programa de shaders
	glUseProgram(ids["program"]);
	//Pasa los parametros del programa. Los Asocia del cpu al gpu
	glUniform1f(ids["time"], time);
	//selecciona geometria (triangulo)
	glBindVertexArray(ids["triangle"]);

	//gl_draw
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void Application::SetUpGeometria()
{
	std::vector<float> geometry{
		//x      y     z     w
		-1.0f, -1.0f, 0.0f, 1.0f, //vertice 1
		-1.0f , 1.0f ,0.0f, 1.0f, //vertice 2
		1.0f, -1.0, 0.0f, 1.0f, //vertice 3
		1.0f, 1.0f, 0.0f, 1.0f, //vertice 4
		1.0f , 0.0f ,0.0f, 1.0f, // v1 Rojo
		0.0f , 1.0f ,0.0f, 1.0f,  // v2 verde
		0.0f , 0.0f ,1.0f, 1.0f,  // v3 azul
		1.0f , 1.0f ,1.0f, 1.0f,  // v4 blanco
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
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)(15 * sizeof(float)));
	glEnableVertexAttribArray(1);

	std::cout << "setup" << std::endl;
}

void Application::SetUpProgamaShaders()
{
	std::string strVertexShader = leer_archivo_a_string("C:/Users/Estudiante/Estebo-17744/ComputoGrafico2025-4/Proyectos/Application/Shaders/VertexShader.glsl");
	std::string strFragmentShader = leer_archivo_a_string("C:/Users/Estudiante/Estebo-17744/ComputoGrafico2025-4/Proyectos/Application/Shaders/FragmentShader.glsl");
	ids["program"] = ShaderFuncs::InitializeProgram(strVertexShader, strFragmentShader);
	ids["time"] = glGetUniformLocation(ids["program"], "time");
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