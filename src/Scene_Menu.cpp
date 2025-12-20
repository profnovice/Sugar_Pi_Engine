#include "Scene.h"

void Scene_Menu::init()
{
	assignActions();
	spawnMenuItems();
}

void Scene_Menu::spawnMenuItems()
{
	SimpEntPtr playButton = m_entityManager.addEntity("Button");
	playButton->cButton = std::make_shared<CButton>(m_assetManager.getFont("mainFont"));
	playButton->cButton->shape.setSize(sf::Vector2f(200.0f, 50.0f));
	playButton->cButton->shape.setFillColor(sf::Color::Green);
	playButton->cButton->text.setString("Play");
	playButton->cUIElement = std::make_shared<CUIElement>();
	playButton->cUIElement->anchorPoint = Vec2(0.5f, 0.5f);
	playButton->cUIElement->offset = Vec2(0.0f, 0.0f);
	playButton->cUIElement->scale = Vec2(1.0f, 1.0f);

}

void Scene_Menu::assignActions()
{
	registerAction(sf::Keyboard::Scancode::Space, "SELECT");
	registerAction(sf::Keyboard::Scancode::Escape, "BACK");
	registerAction(sf::Keyboard::Scancode::W, "UP");
	registerAction(sf::Keyboard::Scancode::S, "DOWN");
}

void Scene_Menu::sDoAction(const Action& action) 
{
	if(action.getType() == "PRESSED")
	{
		if (action.getName() == "SELECT")
		{
			std::cout << "Menu Action: SELECT" << std::endl;
		}
		else if (action.getName() == "BACK")
		{
			std::cout << "Menu Action: BACK" << std::endl;
		}
		else if (action.getName() == "UP")
		{
			std::cout << "Menu Action: UP" << std::endl;
		}
		else if (action.getName() == "DOWN")
		{
			std::cout << "Menu Action: DOWN" << std::endl;
		}
	}
	else if(action.getType() == "RELEASED")
	{


	}
}

void Scene_Menu::update()
{
	m_entityManager.update();
}

void Scene_Menu::sRender(sf::RenderWindow& window)
{
	for (auto& button : m_entityManager.getEntities("Button"))
	{
	
		if (button->cButton && button->cUIElement)
		{
			// Update button position based on anchor point and offset
			sf::Vector2f windowSize = static_cast<sf::Vector2f>(window.getSize());
			sf::Vector2f anchorPos = sf::Vector2f(button->cUIElement->anchorPoint.x * windowSize.x,
				button->cUIElement->anchorPoint.y * windowSize.y);
			sf::Vector2f finalPos = anchorPos + sf::Vector2f(button->cUIElement->offset.x, button->cUIElement->offset.y);
			button->cButton->shape.setPosition(finalPos);
			button->cButton->text.setPosition({ finalPos.x + 10.0f, finalPos.y + 10.0f }); // Slight offset for text
			window.draw(button->cButton->shape);
			window.draw(button->cButton->text);
		}


	}
}