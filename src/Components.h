#include <iostream>
#include "Vec2.h"
#include <SFML/Graphics.hpp>

#pragma once
class Component {};

class CTransform : public  Component
{
public:
	Vec2 pos = {0.0,0.0};
	Vec2 velocity = { 0.0,0.0 };
	float angle = 0.0f;
	CTransform();
	CTransform(const Vec2 inPos);
	CTransform(const Vec2 inPos, const Vec2 inVelocity);
	CTransform(const Vec2 inPos, const Vec2 inVelocity, float a);
	~CTransform();
	void print();
};

class CDisplayTag : public  Component
{
public:
	sf::Text text;
	CDisplayTag(const sf::Font &);
};

class CShape : public Component
{
public:
	sf::CircleShape circle;
	CShape(float radius, int edges, const sf::Color& fill, const sf::Color& outline, float thickness);
};

class CCollision : public Component
{
public:
	float radius = 0;
	CCollision(float r);
};