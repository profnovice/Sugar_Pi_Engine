#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <cmath>

class Vec2 {
public:
    // Data
    float x;
    float y;

    // Construction
    Vec2();
    Vec2(float, float);

    // Queries / helpers
    Vec2 length() const;
    std::string toString() const;

    // Comparison
    bool operator == (const Vec2& rhs) const;
    bool operator != (const Vec2& rhs) const;
	bool operator == (const float val) const;
	bool operator < (const float val) const;
	bool operator > (const float val) const;

    // Binary arithmetic
    Vec2 operator + (const Vec2& rhs) const;
    Vec2 operator - (const Vec2& rhs) const;
    Vec2 operator * (const float val) const;
    Vec2 operator / (const float val) const;

    // Compound assignment
    void operator += (const Vec2 & rhs);
    void operator -= (const Vec2 & rhs);
    void operator *= (const float rhs);
    void operator /= (const float val);

    // User-defined conversion
    operator sf::Vector2f const();

    // Mutating helpers
    void normalize();
    float dist(const Vec2& rhs) const;
    Vec2& add(const Vec2& v);
    Vec2& scale(const float s);

    // Static utilities
    static Vec2 const getVelocityFromSpeedAndAngle(const float speed, const float angle);
    static Vec2 const polarToCartesian(const float angle, const float magnitude);
    static Vec2 const normalize(const Vec2& in);
    static float dist(const Vec2& lhs, const Vec2& rhs);
    static bool circleCollision(const Vec2& cp1, const Vec2& cp2, float r1, float r2);
    static Vec2 circleOverlap(const Vec2& cp1, const Vec2& cp2, float r1, float r2);
};