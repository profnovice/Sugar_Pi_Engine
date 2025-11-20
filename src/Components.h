#include <ioStream>
#include "Vec2.h"
#include <SFML/Graphics.hpp>

#pragma once
class Component {};

class CTransform : public  Component
{
public:
	Vec2 pos;
	Vec2 velocity;
	CTransform();
	CTransform(const Vec2, const Vec2);
	~CTransform();
	void print();
};

class CDisplayTag : public  Component
{
	const sf::Font & m_font;
public:

	sf::Text text;

	CDisplayTag(const sf::Font &);
	
};