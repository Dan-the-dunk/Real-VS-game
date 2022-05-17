#pragma once
#include<iostream>

class Vector2D
{
public:

	float x;
	float y;

	Vector2D() ;
	Vector2D(float x, float y);

	Vector2D& add(const Vector2D& vec);
	Vector2D& substract(const Vector2D& vec);
	Vector2D& multiply(const Vector2D& vec);
	Vector2D& divide(const Vector2D& vec);




	float get_distance(const Vector2D& v1, const Vector2D& v2);
	Vector2D& set_vlength(const Vector2D& v1, const Vector2D& v2, float length);

	float get_vlength();

	friend Vector2D& operator+(Vector2D& v1, Vector2D& v2);
	friend Vector2D& operator-(Vector2D& v1, Vector2D& v2);
	friend Vector2D& operator*(Vector2D& v1, Vector2D& v2);
	friend Vector2D& operator/(Vector2D& v1, Vector2D& v2);

	Vector2D& operator+=(const Vector2D& vec);
	Vector2D& operator-=(const Vector2D& vec);
	Vector2D& operator*=(const Vector2D& vec);
	Vector2D& operator/=(const Vector2D& vec);

	Vector2D& operator*(const int& i);
	Vector2D& zero();
	friend std::ostream& operator <<(std::ostream& stream, const Vector2D& vec);
};