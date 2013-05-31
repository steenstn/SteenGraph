#include <GL\glew.h>
#include "Shader.hpp"
class Mesh {

	public:
	
		Mesh();
		~Mesh();

	private:
		Shader shader;
		GLfloat *vertices;
		GLushort *triangles;
		GLfloat *normals;
};