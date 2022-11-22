#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

class Vector
{
public:
	float x, y;

	Vector();
	Vector(const float _x, const float _y);
	Vector(const Vector v1, const Vector v2);

	float length();
	void normalize();
	float angle(Vector v);

	void add(const float& f);
	void operator+=(const float& f);
	void subtract(const float& f);
	void operator-=(const float& f);
	void divide(const float& f);
	void operator/=(const float& f);
	void multiply(const float& f);
	void operator*=(const float& f);
	Vector dot(const Vector& v);
	float dotProduct(const Vector& v);

	void add(const Vector& v);
	void operator+=(const Vector& v);
	void subtract(const Vector& v);
	void operator-=(const Vector& v);
};
#endif