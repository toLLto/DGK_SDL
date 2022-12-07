#include "Vector.h"

Vector::Vector()
{
	this->x = 0;
	this->y = 0;
}

Vector::Vector(const float _x, const float _y)
{
	this->x = _x;
	this->y = _y;
}

Vector::Vector(const Vector v1, const Vector v2)
{
	this->x = v2.x - v1.x;
	this->y = v2.y - v1.y;
}

Vector::Vector(const Vector& v)
{
	this->x = v.x;
	this->y = v.y;
}

float Vector::length()
{
	return (float)(sqrt(
		(this->x * this->x) +
		(this->y * this->y)
	));
}

void Vector::normalize()
{
	const float length = this->length();
	if (length != 0.0f)
	{
		this->divide(length);
	}
	else
	{
		std::cout << "Can't divide by 0 [normalize]" << std::endl;
	}
}

float Vector::angle(Vector v)
{
	return acos(this->dotProduct(v) / (this->length() * v.length()));
}

void Vector::add(const float& f)
{
	this->x += f;
	this->y += f;
}

void Vector::operator+=(const float& f)
{
	add(f);
}

Vector Vector::operator+(const Vector& v) const
{
	Vector res(this->x + v.x, this->y + v.y);
	return res;
}

void Vector::subtract(const float& f)
{
	this->x -= f;
	this->y -= f;
}

void Vector::operator-=(const float& f)
{
	subtract(f);
}

Vector Vector::operator-(const Vector& v) const
{
	Vector res(this->x - v.x, this->y - v.y);
	return res;
}

void Vector::divide(const float& f)
{
	if (f != 0) {
		this->x /= f;
		this->y /= f;
	}
	else 
	{
		std::cout << "Can't divide by 0 [div]" << std::endl;
	}
}

void Vector::operator/=(const float& f)
{
	divide(f);
}

Vector Vector::operator/(const float& f) const
{
	if (f != 0) 
	{
		Vector res(this->x / f, this->y / f);
		return res;
	}
	else
	{
		std::cout << "Can't divide by 0 [div]" << std::endl;
	}
}

void Vector::multiply(const float& f)
{
	this->x *= f;
	this->y *= f;
}

void Vector::operator*=(const float& f)
{
	multiply(f);
}

Vector Vector::operator*(const float& f) const
{
	Vector res(this->x * f, this->y * f);
	return res;
}

Vector Vector::dot(const Vector& v)
{
	return {
		this->x * v.x,
		this->y * v.y
	};
}

float Vector::dotProduct(const Vector& v)
{
	Vector result;
	result.x = this->x * v.x;
	result.y = this->y * v.y;
	return result.x + result.y;
}

void Vector::add(const Vector& v)
{
	this->x += v.x;
	this->y += v.y;
}

void Vector::operator+=(const Vector& v)
{
	add(v);
}

void Vector::subtract(const Vector& v)
{
	this->x -= v.x;
	this->y -= v.y;
}

void Vector::operator-=(const Vector& v)
{
	subtract(v);
}

bool Vector::isEqual(const Vector& v)
{
	if (this->x == v.x && this->y == v.y)
		return true;

	return false;
}

void Vector::operator==(const Vector& v)
{
	isEqual(v);
}
