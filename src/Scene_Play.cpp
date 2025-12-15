#include "Scene_Play.h"

void Scene_Play::init()
{
	assignActions();
}
void Scene_Play::assignActions()
{
	registerAction(sf::Keyboard::Scancode::W, "MOVE_UP");
	registerAction(sf::Keyboard::Scancode::A, "MOVE_LEFT");
	registerAction(sf::Keyboard::Scancode::S, "MOVE_DOWN");
	registerAction(sf::Keyboard::Scancode::D, "MOVE_RIGHT");
}
void Scene_Play::sDoAction(const Action& action)
{
	if (action.getType() == "PRESSED")
	{
		if (action.getName() == "MOVE_UP")
		{
			std::cout << "Play Action: MOVE_UP" << std::endl;
		}
		else if (action.getName() == "MOVE_LEFT")
		{
			std::cout << "Play Action: MOVE_LEFT" << std::endl;
		}
		else if (action.getName() == "MOVE_DOWN")
		{
			std::cout << "Play Action: MOVE_DOWN" << std::endl;
		}
		else if (action.getName() == "MOVE_RIGHT")
		{
			std::cout << "Play Action: MOVE_RIGHT" << std::endl;
		}
	}
	else if (action.getType() == "RELEASED")
	{
		if (action.getName() == "MOVE_UP")
		{
			std::cout << "Play Action Released: MOVE_UP" << std::endl;
		}
		else if (action.getName() == "MOVE_LEFT")
		{
			std::cout << "Play Action Released: MOVE_LEFT" << std::endl;
		}
		else if (action.getName() == "MOVE_DOWN")
		{
			std::cout << "Play Action Released: MOVE_DOWN" << std::endl;
		}
		else if (action.getName() == "MOVE_RIGHT")
		{
			std::cout << "Play Action Released: MOVE_RIGHT" << std::endl;
		}
	}
}
void Scene_Play::update()
{

}

void Scene_Play::sRender(sf::RenderWindow& window)
{
}