#include "IndexBufferObject.hpp"

IndexBufferObject::IndexBufferObject()
{}
IndexBufferObject::IndexBufferObject(GLushort* elementArray, GLsizeiptr size)
{

	glGenBuffers(1, &adress);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, adress);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, elementArray, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

GLushort IndexBufferObject::GetAdress()
{
	return adress;
}