#include "Vec2.h"

Vec2::Vec2()
	:x(0), y(0)
{
}

Vec2::Vec2(float x_in, float y_in)
	:x(x_in),y(y_in)
{
	
}

Vec2 Vec2::length() const
{
	return Vec2();

}


bool Vec2::operator==(const Vec2& rhs) const
{
	if (x == rhs.x && y == rhs.y)
	{
		return true;
	}
	return false;
}

bool Vec2::operator!=(const Vec2& rhs) const
{
	if (x == rhs.x && y == rhs.y)
	{
		return false;
	}
	return true;
}

Vec2 Vec2::operator+(const Vec2& rhs) const
{
	return Vec2(x+rhs.x,y + rhs.y);
}

Vec2 Vec2::operator-(const Vec2& rhs) const
{
	return Vec2(x - rhs.x, y - rhs.y);
}

Vec2 Vec2::operator*(const float& val) const
{
	return Vec2(x * val, y * val);
}

void Vec2::operator+=(const Vec2& rhs)
{
	x = x + rhs.x;
	y = y + rhs.y;
}

void Vec2::operator-=(const Vec2& rhs)
{
	x = x - rhs.x;
	y = y - rhs.y;
}

Vec2& Vec2::add(const Vec2& v)
{
	x = x + v.x;
	y = y + v.y;
	return *this;
}

Vec2& Vec2::scale(const float s)
{
	x = x * s;
	y = y * s;
	return *this;
}



std::string Vec2::toString() const
{
	return "x: " + std::to_string(x) + " y: " + std::to_string(y);

}