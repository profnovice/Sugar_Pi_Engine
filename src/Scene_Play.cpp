#include "Scene.h"

void Scene_Play::spawnPlayer()
{
	SimpEntPtr player = m_entityManager.addEntity("Player");
	player->cTransform = std::make_shared<CTransform>(Vec2(500, 500));
	player->cSprite = std::make_shared<CSprite>(m_assetManager.getTexture("ghost"));
	player->cShape = std::make_shared<CShape>(32,6,sf::Color::Blue,sf::Color::Red,2.0f);
	player->cBoundingBox = std::make_shared<CBoundingBox>(Vec2(64, 64));

}
void Scene_Play::init()
{
	assignActions();
	spawnPlayer();
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
	m_entityManager.update();
}

void Scene_Play::sRender(sf::RenderWindow& window)
{
	for(auto& e : m_entityManager.getEntities())
	{
		if (!e->cTransform) { continue; }
		if (!e->cShape) { continue; }
		
		e->cShape->circle.setPosition(e->cTransform->pos);
		window.draw(e->cShape->circle);
		if (!e->cSprite) { continue; }
		e->cSprite->sprite.setPosition(e->cTransform->pos);
		window.draw(e->cSprite->sprite);
		
	}
}