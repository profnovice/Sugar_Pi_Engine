#pragma once
#include "UIElement.h"
class TestUIElement : public UIElement
{
protected:
	using UIElement::UIElement;
public:
	sf::RectangleShape shape;
	
	bool handleAction(const Action& action) override;
	void update(float deltaTime) override;
	void render(sf::RenderWindow& window) override;
};