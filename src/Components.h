#pragma once
#include <iostream>
#include "Vec2.h"
#include <SFML/Graphics.hpp>


class Component {};

class CTransform : public  Component
{
public:
	Vec2 pos = {0.0,0.0};
	Vec2 velocity = { 0.0,0.0 };
	Vec2 storedVelocity = { 0.0,0.0 };
	Vec2 previousPos = { 0.0,0.0 };
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
	CShape(float radius);
	CShape(float radius, const sf::Color& fill);
	CShape(float radius, int edges, const sf::Color& fill, const sf::Color& outline, float thickness);
};

class CCollision : public Component
{
public:
	float radius = 0;
	CCollision(float r);
};

class CSprite : public Component
{
public:
	sf::Sprite sprite;
	CSprite(const sf::Texture& texture);
};
class CRidgedBody : public Component
{
public:
	float mass = 1.0f;
	float drag = 0.0f;
	float angularDrag = 0.0f;
	bool useGravity = true;
	Vec2 velocity = { 0.0f,0.0f };
	Vec2 angularVelocity = { 0.0f,0.0f };
	CRidgedBody();

};

class CInput : public Component
{
public:
	bool primaryAction = false;
	bool secondaryAction = false;
	Vec2 mousePosition = { 0.0f,0.0f };
	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;
	float inputAngle = 0.0f;
	float inputMagnitude = 0.0f;
	CInput();
};

class CBoundingBox : public Component
{
public:
	Vec2 size;
	Vec2 halfSize;
	sf::RectangleShape debugRec;
	CBoundingBox(const Vec2& s);
	
};

class CHealth : public Component
{
public:
	int currentHealth = 100;
	int maxHealth = 100;
	CHealth(int maxH);
};

class CAI : public Component
{
public:
	bool isSeeking = false;
	int cooldown = 0;
	int cooldownMax = 60;
	CAI();
	CAI(int cdMax);
};