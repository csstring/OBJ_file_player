#include "math/Vec2.h"
#include "math/Vec4.h"
#include "Common.h"
namespace math
{
Vec2::Vec2(float x, float y) : x(x), y(y)
{}
Vec2::Vec2(float scalar) : x(scalar), y(scalar)
{}
Vec2::Vec2(const Vec2& v) : x(v.x), y(v.y)
{}
Vec2::Vec2():x(0), y(0)
{}


float& Vec2::operator[](int i)
{
	assert(i >= 0 && i < 2);
		switch(i)
		{
		default:
		case 0:
			return x;
		case 1:
			return y;
		}
}

const float& Vec2::operator[](int i) const
{
	assert(i >= 0 && i < 2);
		switch(i)
		{
		default:
		case 0:
			return x;
		case 1:
			return y;
		}
}

Vec2& Vec2::operator=(Vec2 const& v)
{
	this->x = static_cast<float>(v.x);
	this->y = static_cast<float>(v.y);
	return *this;
}

Vec2& Vec2::operator+=(float scalar)
{
	this->x += static_cast<float>(scalar);
	this->y += static_cast<float>(scalar);
	return *this;
}

Vec2& Vec2::operator+=(Vec2 const& v)
{
	this->x += static_cast<float>(v.x);
	this->y += static_cast<float>(v.y);
	return *this;
}

Vec2& Vec2::operator-=(float scalar)
{
	this->x -= static_cast<float>(scalar);
	this->y -= static_cast<float>(scalar);
	return *this;
}

Vec2& Vec2::operator-=(Vec2 const& v)
{
	this->x -= static_cast<float>(v.x);
	this->y -= static_cast<float>(v.y);
	return *this;
}

Vec2& Vec2::operator*=(float scalar)
{
	this->x *= static_cast<float>(scalar);
	this->y *= static_cast<float>(scalar);
	return *this;
}

Vec2& Vec2::operator*=(Vec2 const& v)
{
	this->x *= static_cast<float>(v.x);
	this->y *= static_cast<float>(v.y);
	return *this;
}

Vec2& Vec2::operator/=(float v)
{
	this->x /= static_cast<float>(v);
	this->y /= static_cast<float>(v);
	return *this;
}

Vec2& Vec2::operator/=(Vec2 const& v)
{
	this->x /= static_cast<float>(v.x);
	this->y /= static_cast<float>(v.y);
	return *this;
}


Vec2 operator+(Vec2 const& v)
{
	return v;
}

Vec2 operator-(Vec2 const& v)
{
	return Vec2( -v.x, -v.y);
}

Vec2 operator+(Vec2 const& v, float scalar)
{
	return Vec2(v.x + scalar,v.y + scalar);
}

Vec2 operator+(float scalar, Vec2 const& v)
{
		return Vec2(scalar + v.x,scalar + v.y);
}

Vec2 operator+(Vec2 const& v1, Vec2 const& v2)
{
		return Vec2(v1) += v2;
}

Vec2 operator-(Vec2 const& v, float scalar)
{
		return Vec2(v.x - scalar, v.y - scalar);
}

Vec2 operator-(float scalar, Vec2 const& v)
{
		return Vec2( scalar - v.x, scalar - v.y);
}

Vec2 operator-(Vec2 const& v1, Vec2 const& v2)
{
		return Vec2(v1) -= v2;
}

Vec2 operator*(Vec2 const& v, float scalar)
{
		return Vec2( v.x * scalar, v.y * scalar);
}

Vec2 operator*(float scalar, Vec2 const& v)
{
		return Vec2( scalar * v.x, scalar * v.y);
}

Vec2 operator*(Vec2 const& v1, Vec2 const& v2)
{
	return Vec2(v1) *= v2;
}

Vec2 operator/(Vec2 const& v, float scalar)
{
		return Vec2( v.x / scalar, v.y / scalar);
}

Vec2 operator/(float scalar, Vec2 const& v)
{
		return Vec2( scalar / v.x, scalar / v.y);
}

Vec2 operator/(Vec2 const& v1, Vec2 const& v2)
{
	return Vec2(v1) /= v2;
}

bool operator==(Vec2 const& v1, Vec2 const& v2)
{
	return (v1.x == v2.x) && (v1.y == v2.y);
}

bool operator!=(Vec2 const& v1, Vec2 const& v2)
{
	return !(v1 == v2);
}
}