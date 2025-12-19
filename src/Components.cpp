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

std::string CTransform::toString() const
{
	return std::string("Pos: " + pos.toString() + " Vel: " + velocity.toString() + " Angle: " + std::to_string(angle));
}

CDisplayTag::CDisplayTag(const sf::Font& font)
	:text(sf::Text(font)){}

std::string CDisplayTag::toString() const
{
	return std::string("");
}

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

std::string CShape::toString() const
{
	return std::string(
		"radius: " + std::to_string(circle.getRadius()) +
		"edges: " + std::to_string(circle.getPointCount()) +
		"rgb fill: " + std::to_string(circle.getFillColor().r) + "," +
		std::to_string(circle.getFillColor().g) + "," +
		std::to_string(circle.getFillColor().b) +
		"rgb outline: " + std::to_string(circle.getOutlineColor().r)
		+ "," + std::to_string(circle.getOutlineColor().g) + "," +
		std::to_string(circle.getOutlineColor().b) +
		"thickness: " + std::to_string(circle.getOutlineThickness())
	);	
}

CCollision::CCollision(float r)
	:radius(r) {}

std::string CCollision::toString() const
{
	return std::string("Radius: " + std::to_string(radius));
}

CSprite::CSprite(const sf::Texture& texture)
	:sprite(sf::Sprite(texture))
{
	sprite.setOrigin(sf::Vector2f(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f));
}
std::string CSprite::toString() const
{
	return std::string(
		"Texture Size: x:"  + std::to_string(sprite.getTextureRect().size.x) +
		"y: " + std::to_string(sprite.getTextureRect().size.y)
	);
}

CRidgedBody::CRidgedBody()
{
}
std::string CRidgedBody::toString() const
{
	return std::string(
		"Mass: " + std::to_string(mass) +
		" Drag: " + std::to_string(drag) +
		" Angular Drag: " + std::to_string(angularDrag) +
		" Use Gravity: " + (useGravity ? "true" : "false") +
		" Velocity: " + velocity.toString() +
		" Angular Velocity: " + angularVelocity.toString()
	);
}

CInput::CInput()
{
}
std::string CInput::toString() const
{
	return std::string(
		"Primary Action: " + std::string(primaryAction ? "true" : "false") +
		" Secondary Action: " + std::string(secondaryAction ? "true" : "false") +
		" Mouse Position: " + mousePosition.toString() +
		" Up: " + std::string(up ? "true" : "false") +
		" Down: " + std::string(down ? "true" : "false") +
		" Left: " + std::string(left ? "true" : "false") +
		" Right: " + std::string(right ? "true" : "false") +
		" Input Angle: " + std::to_string(inputAngle) +
		" Input Magnitude: " + std::to_string(inputMagnitude)
	);
}

CBoundingBox::CBoundingBox(const Vec2& s)
	:size(s), halfSize(s.x / 2.0f, s.y / 2.0f), debugRec(sf::RectangleShape(sf::Vector2f(s.x, s.y)))
{
	debugRec.setOrigin(sf::Vector2f(halfSize.x, halfSize.x));
	debugRec.setFillColor(sf::Color(255,0,0,64));
	debugRec.setOutlineColor(sf::Color::Red);
	debugRec.setOutlineThickness(1.0f);
}
std::string CBoundingBox::toString() const
{
	return std::string(
		"Size: " + size.toString() +
		" Half Size: " + halfSize.toString()
	);
}

CHealth::CHealth(int maxH)
	:maxHealth(maxH), currentHealth(maxH)
{
}
std::string CHealth::toString() const
{
	return std::string(
		"Current Health: " + std::to_string(currentHealth) +
		" Max Health: " + std::to_string(maxHealth)
	);
}

CAI::CAI()
	: isSeeking(false), cooldown(0), cooldownMax(60)
{
}

CAI::CAI(int cdMax)
	: isSeeking(false), cooldown(0), cooldownMax(cdMax)
{
}
std::string CAI::toString() const
{
	return std::string(
		"Is Seeking: " + std::string(isSeeking ? "true" : "false") +
		" Cooldown: " + std::to_string(cooldown) +
		" Cooldown Max: " + std::to_string(cooldownMax)
	);
}

CUIElement::CUIElement()
	:anchorPoint({ 0.0f,0.0f }), offset({ 0.0f,0.0f }), scale({ 1.0f,1.0f })
{
}
std::string CUIElement::toString() const
{
	return std::string(
		"Anchor Point: " + anchorPoint.toString() +
		" Offset: " + offset.toString() +
		" Scale: " + scale.toString()
	);
}

CButton::CButton(const sf::Font& font)
	:shape(sf::RectangleShape()), text(sf::Text(font))
{
}

CButton::CButton(const sf::Vector2f& size, const sf::Font& font, const std::string& str)
	:shape(sf::RectangleShape(size)), text(sf::Text(font))
{
	text.setString(str);
	shape.setFillColor(sf::Color::White);
	shape.setOutlineColor(sf::Color::Black);
	shape.setOutlineThickness(1.0f);
	text.setFillColor(sf::Color::Black);
}

std::string CButton::toString() const
{
	return std::string(
		"Shape Size: " + std::to_string(shape.getSize().x) + "," + std::to_string(shape.getSize().y) +
		" Text: " + text.getString().toAnsiString()
	);
}


