#include "TestUIElement.h"
bool TestUIElement::handleAction(const Action& action)
{
	return true;
}
void TestUIElement::update(float deltaTime)
{
	shape.rotate(sf::degrees(90.0f * deltaTime));
}
void TestUIElement::render(sf::RenderWindow& window)
{
	window.draw(shape);
}