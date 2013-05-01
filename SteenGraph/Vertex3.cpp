#include "Vertex3.h"

Vertex3::Vertex3()
{
	x=y=z=0.0f;
}
Vertex3::Vertex3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}
float Vertex3::operator[](int index) const
{
	if(index==0)
		return x;
	else if(index==1)
		return y;
	else if(index==2)
		return z;
	else
		return 0.0f;
}