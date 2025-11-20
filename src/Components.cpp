#include "Components.h"

CTransform::CTransform()
{
	pos = Vec2(0, 0);
	velocity = Vec2(0, 0);
}

CTransform::CTransform(const Vec2 inPos, const Vec2 inVelocity)
	:pos(inPos), velocity(inVelocity)
{
}

CTransform::~CTransform()
{
}

void CTransform::print()
{
	std::cout << "Pos: " << pos.x << ", " << pos.y << " Vel: " << velocity.x << ", " << velocity.y << std::endl;
}

CDisplayTag::CDisplayTag(const sf::Font& font)
	:m_font(font), text(sf::Text(m_font))
{
		
}
