#include "Vector3.h"
#include "math.h"

float dot(Vector3 v1, Vector3 v2)
{
	return v1.getX()*v2.getX() + v1.getY()*v2.getY() + v1.getZ()*v2.getZ();
}

Vector3 cross(Vector3 v1, Vector3 v2)
{
	// TO-DO: Calculate cross product
	return Vector3();
}

Vector3 normalize(Vector3 v)
{
	float norm = sqrtf(v.getX()*v.getX() + v.getY()*v.getY() + v.getZ()*v.getZ());

	return Vector3(v.getX()/norm, v.getY()/norm, v.getZ()/norm);
}