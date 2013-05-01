#ifndef TRIANGLE_H
#define TRIANGLE_H

class Triangle
{
public:
	int p1,p2,p3;
	Vector3 normal;
	Triangle();
	Triangle(int p1, int p2, int p3);

};
#endif