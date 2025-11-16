#include "Vec2.h"

Vec2::Vec2()
{
	x = 0;
	y = 0;
}

Vec2::Vec2(float x_in, float y_in)
	:x(x_in),y(y_in)
{
	
}

bool Vec2::operator==(const Vec2& rhs) const
{
	if (x == rhs.x && y == rhs.y)
	{
		return true;
	}
	return false;
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

