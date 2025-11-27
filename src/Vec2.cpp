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

Vec2 Vec2::operator*(const Vec2& rhs) const
{
	return Vec2(x * rhs.x, y * rhs.y);
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

Vec2 const Vec2::getVelocityFromSpeedAndAngle(const float speed, const float angle)
{
	return Vec2(speed * std::cos(angle), speed * std::sin(angle));
}

void Vec2::normalize()
{
	float magnitude = std::sqrtf(x * x + y * y);
	x = x / magnitude;
	y = y / magnitude;
	
}

bool Vec2::circleCollision(const Vec2& cp1, const Vec2& cp2, float r1, float r2)
{
	//rewrite sqrt(distance.x ^2 distance.y ^2) < r1 + r2
	Vec2 distance = cp1 - cp2;
	float DisSq = distance.x * distance.x + distance.y * distance.y; // D.x *D.x + D.y * D.y

	if (DisSq < (r1 + r2) * (r1 + r2))
	{
		return true;
	}
	return false;
}

Vec2 Vec2::circleOverlap(const Vec2& cp1, const Vec2& cp2, float r1, float r2)
{
	Vec2 delta = cp2 - cp1;
	float distSq = delta.x * delta.x + delta.y * delta.y;
	float radii = r1 + r2;
	float radiiSq = radii * radii;
	if (distSq >= radiiSq)
	{
		return Vec2(0, 0);
	}
	float dist = std::sqrtf(distSq);
	if (dist == 0.0f)
	{
		return Vec2(radii, 0);
	}

	float overlap = radii - dist;
	return delta * (overlap / dist);
}

Vec2 const Vec2::normalize(const Vec2& in) 
{
	float magnitude = std::sqrtf(in.x * in.x + in.y * in.y);
	return Vec2(in.x/magnitude,in.y/magnitude);
}



std::string Vec2::toString() const
{
	return "x: " + std::to_string(x) + " y: " + std::to_string(y);

}