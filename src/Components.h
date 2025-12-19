#pragma once
#include <iostream>
#include "Vec2.h"
#include <SFML/Graphics.hpp>


class Component {
public:
	virtual std::string toString() const = 0;
};

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
	std::string toString() const;
};

class CDisplayTag : public  Component
{
public:
	sf::Text text;
	CDisplayTag(const sf::Font &);
	std::string toString() const;
};

class CShape : public Component
{
public:
	sf::CircleShape circle;
	CShape(float radius);
	CShape(float radius, const sf::Color& fill);
	CShape(float radius, int edges, const sf::Color& fill, const sf::Color& outline, float thickness);
	std::string toString() const;
};

class CCollision : public Component
{
public:
	float radius = 0;
	CCollision(float r);
	std::string toString() const;
};

class CSprite : public Component
{
public:
	sf::Sprite sprite;
	CSprite(const sf::Texture& texture);
	std::string toString() const;
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
	std::string toString() const;

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
	std::string toString() const;
};

class CBoundingBox : public Component
{
public:
	Vec2 size;
	Vec2 halfSize;
	sf::RectangleShape debugRec;
	CBoundingBox(const Vec2& s);
	std::string toString() const;
};

class CHealth : public Component
{
public:
	int currentHealth = 100;
	int maxHealth = 100;
	CHealth(int maxH);
	std::string toString() const;
};

class CAI : public Component
{
public:
	bool isSeeking = false;
	int cooldown = 0;
	int cooldownMax = 60;
	CAI();
	CAI(int cdMax);
	std::string toString() const;
};

class CButton : public Component
{
	public:
	sf::RectangleShape shape;
	sf::Text text;
	CButton(const sf::Font& font);
	CButton(const sf::Vector2f& size, const sf::Font& font, const std::string& str);
	std::string toString() const;
};
class CUIElement : public Component
{
public:
	Vec2 anchorPoint;
	Vec2 offset;
	Vec2 scale;
	CUIElement();
	std::string toString() const;
};