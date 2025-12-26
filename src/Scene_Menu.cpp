#include "Scene_Menu.h"

void Scene_Menu::init()
{
	assignActions();
	createMenuItems();
}

void Scene_Menu::createMenuItems()
{
	auto& test = m_uiManager.addUIElement<TestUIElement>("Test");
	test.shape.setSize({ 200.0f,100.0f });
	test.shape.setFillColor(sf::Color::Green);
	test.shape.setPosition({ 300.0f,250.0f });
	

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
	if(action.getType() == ActionType::Pressed)
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
	else if(action.getType() == ActionType::Released)
	{


	}
}

void Scene_Menu::update()
{
	m_uiManager.update(1.0f / 60.0f);//Assuming 60 FPS for deltaTime
	m_entityManager.update();
}

void Scene_Menu::sRender(sf::RenderWindow& window)
{
	m_uiManager.render(window);
}