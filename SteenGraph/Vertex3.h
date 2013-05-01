#ifndef VERTEX3_H
#define VERTEX3_H

class Vertex3
{

public:
	Vertex3();
	Vertex3(float x, float y, float z);
	

	float operator[](int index) const;

private:
	float x,y,z;
};

#endif