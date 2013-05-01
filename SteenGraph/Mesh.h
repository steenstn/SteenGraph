#include <GL\glew.h>
class Mesh {

	public:
	
		Mesh();
		~Mesh();
		GLfloat *vertices;
		GLushort *triangles;
		GLfloat *normals;
};