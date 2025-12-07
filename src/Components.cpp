#include "Components.h"

CTransform::CTransform()
	:pos({ 0.0f,0.0f }), velocity({ 0.0f,0.0f }), angle(0.0f), previousPos({ 0.0f,0.0f }){}

CTransform::CTransform(const Vec2 inPos)
	:pos(inPos), velocity({ 0.0f,0.0f }), angle(0.0f), previousPos({ 0.0f,0.0f }) {}

CTransform::CTransform(const Vec2 inPos, const Vec2 inVelocity)
	:pos(inPos), velocity(inVelocity), angle(0.0f), previousPos({ 0.0f,0.0f }){}

CTransform::CTransform(const Vec2 inPos, const Vec2 inVelocity, float a)
	:pos(inPos), velocity(inVelocity), angle(a), previousPos({ 0.0f,0.0f }){}

CTransform::~CTransform(){}

void CTransform::print()
{
	std::cout << "Pos: " << pos.x << ", " << pos.y << " Vel: " << velocity.x << ", " << velocity.y << std::endl;
}

CDisplayTag::CDisplayTag(const sf::Font& font)
	:text(sf::Text(font)){}

CShape::CShape(float radius)
	:circle(radius)
{
	circle.setOrigin({ radius, radius });
	circle.setFillColor(sf::Color::White);
	circle.setOutlineColor(sf::Color::Black);
	circle.setOutlineThickness(1.0f);
}

CShape::CShape(float radius, const sf::Color& fill)
	:circle(radius)
{
	circle.setFillColor(fill);
	circle.setOutlineColor(sf::Color::Black);
	circle.setOutlineThickness(1.0f);
	circle.setOrigin({ radius, radius });
}


CShape::CShape(float radius, int edges, const sf::Color& fill, const sf::Color& outline, float thickness)
		:circle(radius, edges)
	{
		circle.setFillColor(fill);
		circle.setOutlineColor(outline);
		circle.setOutlineThickness(thickness);
		circle.setOrigin({ radius, radius });
	}

CCollision::CCollision(float r)
	:radius(r) {}

CSprite::CSprite(const sf::Texture& texture)
	:sprite(sf::Sprite(texture))
{
	sprite.setOrigin(sf::Vector2f(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f));
}

CRidgedBody::CRidgedBody()
{
}

CInput::CInput()
{
}

CBoundingBox::CBoundingBox(const Vec2& s)
	:size(s), halfSize(s.x / 2.0f, s.y / 2.0f), debugRec(sf::RectangleShape(sf::Vector2f(s.x, s.y)))
{
	debugRec.setOrigin(sf::Vector2f(halfSize.x, halfSize.x));
	debugRec.setFillColor(sf::Color(255,0,0,64));
	debugRec.setOutlineColor(sf::Color::Red);
	debugRec.setOutlineThickness(1.0f);
}

CHealth::CHealth(int maxH)
	:maxHealth(maxH), currentHealth(maxH)
{
}

CAI::CAI()
	: isSeeking(false), cooldown(0), cooldownMax(60)
{
}

CAI::CAI(int cdMax)
	: isSeeking(false), cooldown(0), cooldownMax(cdMax)
{
}
