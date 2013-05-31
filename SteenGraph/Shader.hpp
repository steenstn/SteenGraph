#ifndef SHADER_HPP
#define SHADER_HPP
#include <GL\glew.h>
#include <GL\glfw.h>
#include <stdlib.h>
#include <cstdio>
//#include "ShaderFunctions.h"
class Shader
{
	public:
		Shader();
		Shader(char* vertexFile, char* fragmentFile);

		GLuint* GetProgram();

	private:
		// The vertex shader file
		GLuint VertexShader;
		// The fragment shader file
		GLuint FragmentShader;
		// The resulting shader program
		GLuint Program;

		void print_log(GLuint object);
		char* file_read(const char* filename);
		GLuint create_shader(const char* filename, GLenum type);
};
#endif