#pragma once
#include "Action.h"
#include <string>
#include <memory>
#include <SFML/Graphics.hpp>

class UIElement
{
protected:
	friend class UIManager;
	bool m_isActive = true;
	bool m_isVisible = true;
	std::string m_tag = "Default";
	size_t m_id = 0;
	UIElement(size_t , std::string);
	

public:
	

	virtual bool handleAction(const Action& action) = 0;
	virtual void update(float deltaTime) = 0;
	virtual void render(sf::RenderWindow& window) = 0;
	virtual bool isPointInside(int x, int y) const;

};
