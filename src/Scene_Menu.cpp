#include "Scene_Menu.h"

void Scene_Menu::init()
{
	registerAction(sf::Keyboard::Scancode::Space, "SELECT");
	registerAction(sf::Keyboard::Scancode::Escape, "BACK");
	registerAction(sf::Keyboard::Scancode::W, "UP");
	registerAction(sf::Keyboard::Scancode::S, "DOWN");

}

void Scene_Menu::sDoAction(Action& action) 
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

}

void Scene_Menu::sRender(sf::RenderWindow& window)
{

}