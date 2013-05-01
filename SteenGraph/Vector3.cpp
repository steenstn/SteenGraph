#include "Vector3.h"


Vector3::Vector3()
{
	setX(0.0f);
	setY(0.0f);
	setZ(0.0f);
}

Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3::Vector3(const Vector3& v)
{
    x=v.x;
    y=v.y;
    z=v.z;
}

float Vector3::length(void)
{
    return sqrtf(x*x+y*y+z*z);

}

float Vector3::sum(void)
{
    return x+y+z;
}

void Vector3::setX(float x)
{
	this->x = x;
}

void Vector3::setY(float y)
{
	this->y = y;
}

void Vector3::setZ(float z)
{
	this->z = z;
}

float Vector3::getX(void)
{
	return x;
}

float Vector3::getY(void)
{
	return y;
}

float Vector3::getZ(void)
{
	return z;
}

Vector3 Vector3::operator+ (const Vector3& v)
{
    Vector3 temp((*this).x,(*this).y,(*this).z);
    temp.x+=v.x;
    temp.y+=v.y;
    temp.z+=v.z;
    return temp;
}

Vector3 Vector3::operator* (const Vector3& v)
{
    Vector3 temp((*this).x,(*this).y,(*this).z);
    temp.x*=v.x;
    temp.y*=v.y;
    temp.z*=v.z;
    return temp;
}

Vector3 Vector3::operator- (const Vector3& v)
{
    Vector3 temp((*this).x,(*this).y,(*this).z);
    temp.x-=v.x;
    temp.y-=v.y;
    temp.z-=v.z;
    return temp;
}



Vector3 Vector3::operator* (const float &d)
{
    Vector3 temp((*this).x,(*this).y,(*this).z);
    temp.x*=d;
    temp.y*=d;
    temp.z*=d;
    return temp;
}
Vector3 Vector3::operator/ (const float &d)
{
    Vector3 temp((*this).x,(*this).y,(*this).z);
    temp.x/=d;
    temp.y/=d;
    temp.z/=d;
    return temp;
}
Vector3 Vector3::operator- (const float &d)
{
    Vector3 temp((*this).x,(*this).y,(*this).z);
    temp.x-=d;
    temp.y-=d;
    temp.z-=d;
    return temp;
}

bool Vector3::operator== (Vector3& d)
{
    if(x==d.x && y==d.y && z==d.z)
		return true;
	return false;
}


const void Vector3::operator= (const Vector3& v)
{
    (*this).x=v.x;
    (*this).y=v.y;
    (*this).z=v.z;

	
}

std::ostream& operator<<(std::ostream& o,Vector3& v)
{
    o<<"["<< v.x << " " << v.y << " " << v.z << "]";
    return o;
}