#include"Vector2D.h"
#include<math.h>


Vector2D::Vector2D() {
	x = 0;
	y = 0;
}

Vector2D::Vector2D(float x, float y) {
	this->x = x ;
	this->y = y;
}


Vector2D& Vector2D::add(const Vector2D& vec) {
	this->x += vec.x;
	this->y += vec.y;
	
	return *this;
}

Vector2D& Vector2D::substract(const Vector2D& vec) {
	this->x -= vec.x;
	this->y -= vec.y;

	return *this;
}

Vector2D& Vector2D::multiply(const Vector2D& vec) {
	this->x *= vec.x;
	this->y *= vec.y;

	return *this;
}

Vector2D& Vector2D::divide(const Vector2D& vec) {
	this->x /= vec.x;
	this->y /= vec.y;

	return *this;
}

float Vector2D::get_distance(const Vector2D& v1, const Vector2D& v2)
{
	Vector2D sub = { v1.x - v2.x , v1.y - v2.y };

	float distance = sqrt(sub.x * sub.x + sub.y * sub.y);

	return distance;

}




Vector2D& Vector2D::set_vlength(const Vector2D& v1, const Vector2D& v2, float length)
{

	
	*this = { (v1.x - v2.x)/get_distance(v1,v2) *length , (v1.y - v2.y)/ get_distance(v1,v2) * length };

	

	return *this;
}

float Vector2D::get_vlength()
{

	float length = sqrt(this->x * this->x + this->y * this->y);
	return length;
}








Vector2D& operator+(Vector2D& v1, Vector2D& v2)
{
	return v1.add(v2);
};


Vector2D& operator-(Vector2D& v1, Vector2D& v2)
{
	return v1.substract(v2);
};

Vector2D& operator*(Vector2D& v1, Vector2D& v2)
{
	return v1.multiply(v2);
};

Vector2D& operator/(Vector2D& v1, Vector2D& v2)
{
	return v1.divide(v2);
};








Vector2D& Vector2D::operator+=(const Vector2D& vec) 
{
	return this->add(vec);
}

Vector2D& Vector2D::operator-=(const Vector2D& vec)
{
	return this->substract(vec);
}

Vector2D& Vector2D::operator*=(const Vector2D& vec)
{
	return this->multiply(vec);
}

Vector2D& Vector2D::operator/=(const Vector2D& vec)
{
	return this->divide(vec);
}


Vector2D& Vector2D::operator*(const int& i) {
	this->x *= i;
	this->y *= i;

	return *this;
}






Vector2D& Vector2D::zero() {
	this->x = 0;
	this->y = 0;
	return *this;
}


std::ostream& operator <<(std::ostream& stream, const Vector2D& vec)
{
	stream << " Vector(" << vec.x << "," << vec.y << ")";
	return stream;
};