#include <string>
#include <iostream>
#include <cmath>  
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
	Vec2 operator*(const Vec2& rhs) const;
	void operator += (const Vec2 & rhs);
	void operator -= (const Vec2& rhs);
	Vec2& add(const Vec2& v);
	Vec2& scale(const float s);
	static Vec2 const getVelocityFromSpeedAndAngle(const float, const float);
	static Vec2 const normalize(const Vec2 &);
	void normalize();
	static bool circleCollision(const Vec2&, const Vec2&, float, float);
	static Vec2 circleOverlap(const Vec2&, const Vec2&, float, float);

	std::string toString() const;


};