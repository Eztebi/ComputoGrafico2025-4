#include "Application.h"
#include "ShaderFuncs.h"

void Application::setup()
{
	SetUpGeometria();
	SetUpProgamaShaders();
	
}

void Application::update()
{
	std::cout << "update" << std::endl;
}

void Application::draw()
{
	//selecciona programa de shaders
	glUseProgram(ids["program"]);

	//selecciona geometria (triangulo)
	glBindVertexArray(ids["triangle"]);

	//gl_draw
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Application::SetUpGeometria()
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

void Application::SetUpProgamaShaders()
{
	std::string strVertexShader = leer_archivo_a_string("C:/Users/Estudiante/Estebo-17744/ComputoGrafico2025-4/Proyectos/Application/Shaders/VertexShader.glsl");
	std::string strFragmentShader = leer_archivo_a_string("C:/Users/Estudiante/Estebo-17744/ComputoGrafico2025-4/Proyectos/Application/Shaders/FragmentShader.glsl");
	ids["program"] = ShaderFuncs::InitializeProgram(strVertexShader, strFragmentShader);
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