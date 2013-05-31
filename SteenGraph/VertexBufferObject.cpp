#include "VertexBufferObject.hpp"

VertexBufferObject::VertexBufferObject()
{}

VertexBufferObject::VertexBufferObject(GLfloat* vertexArray, GLsizeiptr size)
{
	glGenBuffers(1, &adress);
	glBindBuffer(GL_ARRAY_BUFFER, adress);
	glBufferData(GL_ARRAY_BUFFER, size, vertexArray, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

GLuint VertexBufferObject::GetAdress()
{
	return adress;
}