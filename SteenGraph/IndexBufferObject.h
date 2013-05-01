#ifndef INDEXBUFFEROBJECT_H
#define INDEXBUFFEROBJECT_H
#include <GL\glew.h>

class IndexBufferObject
{
	public:

		IndexBufferObject(GLushort* elementArray, GLsizeiptr size);
		~IndexBufferObject();

		GLushort GetAdress();

	private:

		GLuint adress;

};

#endif