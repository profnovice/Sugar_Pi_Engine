#include "Components.h"

CTransform::CTransform()
	:pos({ 0.0f,0.0f }), velocity({ 0.0f,0.0f }), angle(0.0f) {}

CTransform::CTransform(const Vec2 inPos)
	:pos(inPos), velocity({ 0.0f,0.0f }), angle(0.0f) {}

CTransform::CTransform(const Vec2 inPos, const Vec2 inVelocity)
	:pos(inPos), velocity(inVelocity), angle(0.0f){}

CTransform::CTransform(const Vec2 inPos, const Vec2 inVelocity, float a)
	:pos(inPos), velocity(inVelocity), angle(a){}

CTransform::~CTransform(){}

void CTransform::print()
{
	std::cout << "Pos: " << pos.x << ", " << pos.y << " Vel: " << velocity.x << ", " << velocity.y << std::endl;
}

CDisplayTag::CDisplayTag(const sf::Font& font)
	:text(sf::Text(font)){}

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
