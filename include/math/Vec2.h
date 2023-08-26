#pragma once

namespace math
{
class Vec2
{
	public:
		float x;
		float y;

  public:
    explicit Vec2(float x, float y);
    explicit Vec2(float scalar);
    Vec2(const Vec2& v);
		Vec2();
    ~Vec2(){};
		float& operator[](int i);
		const float& operator[](int i) const;
		Vec2& operator=(Vec2 const& v);
		Vec2& operator+=(float scalar);
		Vec2& operator+=(Vec2 const& v);
		Vec2& operator-=(float scalar);
		Vec2& operator-=(Vec2 const& v);
		Vec2& operator*=(float scalar);
		Vec2& operator*=(Vec2 const& v);
		Vec2& operator/=(float scalar);
		Vec2& operator/=(Vec2 const& v);

};

Vec2 operator+(Vec2 const& v);
Vec2 operator-(Vec2 const& v);
Vec2 operator+(Vec2 const& v, float scalar);
Vec2 operator+(float scalar, Vec2 const& v);
Vec2 operator+(Vec2 const& v1, Vec2 const& v2);
Vec2 operator-(Vec2 const& v, float scalar);
Vec2 operator-(float scalar, Vec2 const& v);
Vec2 operator-(Vec2 const& v1, Vec2 const& v2);
Vec2 operator*(Vec2 const& v, float scalar);
Vec2 operator*(float scalar, Vec2 const& v);
Vec2 operator*(Vec2 const& v1, Vec2 const& v2);
Vec2 operator/(Vec2 const& v, float scalar);
Vec2 operator/(float scalar, Vec2 const& v);
Vec2 operator/(Vec2 const& v1, Vec2 const& v2);
bool operator==(Vec2 const& v1, Vec2 const& v2);
bool operator!=(Vec2 const& v1, Vec2 const& v2);
}