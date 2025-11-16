#include <string>
#pragma once
class Vec2 {
public:
	float x;
	float y;

	Vec2();
	Vec2(float, float);
	Vec2 length() const;
	bool operator == (const Vec2& rhs) const;
	bool operator != (const Vec2& rhs) const;
	Vec2 operator + (const Vec2& rhs) const;
	Vec2 operator - (const Vec2& rhs) const;
	Vec2 operator * (const float& val) const;
	void operator += (const Vec2 & rhs);
	void operator -= (const Vec2& rhs);
	Vec2& add(const Vec2& v);
	Vec2& scale(const float s);
	std::string toString() const;


};