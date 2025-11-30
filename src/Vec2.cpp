#include "Vec2.h"
#include <cmath>

 // Construction
Vec2::Vec2()
    :x(0), y(0)
{
}

Vec2::Vec2(float x_in, float y_in)
    :x(x_in), y(y_in)
{
}

 // Queries / helpers
Vec2 Vec2::length() const
{
    return Vec2();
}

std::string Vec2::toString() const
{
    return "x: " + std::to_string(x) + " y: " + std::to_string(y);
}

 // Comparison
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

 // Binary arithmetic
Vec2 Vec2::operator+(const Vec2& rhs) const
{
    return Vec2(x + rhs.x, y + rhs.y);
}

Vec2 Vec2::operator-(const Vec2& rhs) const
{
    return Vec2(x - rhs.x, y - rhs.y);
}

Vec2 Vec2::operator*(const float val) const
{
    return Vec2(x * val, y * val);
}

Vec2 Vec2::operator/(const float val) const
{
    return Vec2(x / val, y / val);
}

 // Compound assignment
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

void Vec2::operator*=(const float val)
{
    x = x * val;
    y = y * val;
}

void Vec2::operator/=(const float val)
{
    x = x / val;
    y = y / val;
}

Vec2::operator sf::Vector2f const()
{
    return { x,y };
}


 // Mutating helpers
void Vec2::normalize()
{
    float magnitude = std::sqrt(x * x + y * y);
    x = x / magnitude;
    y = y / magnitude;
}

float Vec2::dist(const Vec2& rhs) const
{
    float xdist = x - rhs.x;
    float ydist = y - rhs.y;
    return std::sqrt(xdist * xdist + ydist * ydist);
}

Vec2& Vec2::add(const Vec2& rhs)
{
    x = x + rhs.x;
    y = y + rhs.y;
    return *this;
}

Vec2& Vec2::scale(const float val)
{
    x = x * val;
    y = y * val;
    return *this;
}

 // Static utilities
Vec2 const Vec2::getVelocityFromSpeedAndAngle(const float speed, const float angle)
{
    return Vec2(speed * std::cos(angle), speed * std::sin(angle));
}

Vec2 const Vec2::polarToCartesian(const float angle, const float magnitude)
{
    return Vec2(magnitude * std::cos(angle), magnitude * std::sin(angle));
}


Vec2 const Vec2::normalize(const Vec2& in)
{
    float magnitude = std::sqrt(in.x * in.x + in.y * in.y);
    return Vec2(in.x / magnitude, in.y / magnitude);
}

float Vec2::dist(const Vec2& lhs, const Vec2& rhs)
{
    float xdist = lhs.x - rhs.x;
    float ydist = lhs.y - rhs.y;
    return std::sqrt(xdist * xdist + ydist * ydist);
}

bool Vec2::circleCollision(const Vec2& cp1, const Vec2& cp2, float r1, float r2)
{
    Vec2 distance = cp1 - cp2;
    float DisSq = distance.x * distance.x + distance.y * distance.y;

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
    float dist = std::sqrt(distSq);
    if (dist == 0.0f)
    {
        return Vec2(radii, 0);
    }

    float overlap = radii - dist;
    return delta * (overlap / dist);
}