/*
Class containing a Vertex buffer object
*/
#ifndef VERTEXBUFFEROBJECT_H
#define VERTEXBUFFEROBJECT_H

#include <GL\glew.h>
class VertexBufferObject
{
	public:

		VertexBufferObject(GLfloat* vertexArray,GLsizeiptr size);
		~VertexBufferObject();

		GLuint GetAdress();
	private:

		GLuint adress;
};
#endif