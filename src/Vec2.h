#pragma once
class Vec2 {
public:
	float x;
	float y;

	Vec2();
	Vec2(float, float);
	bool operator == (const Vec2& rhs) const;
	Vec2 operator + (const Vec2& rhs) const;
	Vec2 operator - (const Vec2& rhs) const;
	Vec2 operator * (const float& val) const;
	void operator +=(const Vec2 & rhs);
	void operator -=(const Vec2& rhs);


};