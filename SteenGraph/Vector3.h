#ifndef VECTOR3_H
#define VECTOR3_H
#include <iostream>
class Vector3
{

	public:
	Vector3();
	Vector3(float x, float y, float z);
	Vector3(const Vector3& v);
    

	Vector3 operator+ (const Vector3& v);

    Vector3 operator* (const Vector3& v);
    Vector3 operator- (const Vector3& v);

    Vector3 operator* (const float &d);
    Vector3 operator/ (const float &d);
    Vector3 operator- (const float &d);
	bool operator== (Vector3& d);

	const void operator= (const Vector3& v);

	friend std::ostream& operator<<(std::ostream& o,Vector3& v);

	void setX(float x);
	void setY(float y);
	void setZ(float z);

	float length(void);
	float sum(void);

	float getX(void);
	float getY(void);
	float getZ(void);

	private:
	float x,y,z;

};
#endif