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
	Vector(const Vector& v);

	float length();
	void normalize();
	float angle(Vector v);

	void add(const float& f);
	void operator+=(const float& f);
	Vector operator+(const Vector& v) const;
	void subtract(const float& f);
	void operator-=(const float& f);
	Vector operator-(const Vector& v) const;
	void divide(const float& f);
	void operator/=(const float& f);
	Vector operator/(const float& f) const;
	void multiply(const float& f);
	void operator*=(const float& f);
	Vector operator*(const float& f) const;
	Vector dot(const Vector& v);
	float dotProduct(const Vector& v);

	void add(const Vector& v);
	void operator+=(const Vector& v);
	void subtract(const Vector& v);
	void operator-=(const Vector& v);

	bool isEqual(const Vector& v);
	void operator==(const Vector& v);
};
#endif