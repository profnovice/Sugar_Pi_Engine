#include "Scene_Play.h"

void Scene_Play::spawnPlayer()
{
	SimpEntPtr background = m_entityManager.addEntity("Background");

	background->cSprite = std::make_shared<CSprite>(m_assetManager.getTexture("tile01"));
	background->cSprite->sprite.setTextureRect(sf::IntRect({ 0,0 }, { 4096, 4096 }));
	background->cTransform = std::make_shared<CTransform>(Vec2(32, 32));

	SimpEntPtr player = m_entityManager.addEntity("Player");
	player->cTransform = std::make_shared<CTransform>(Vec2(500, 500));
	player->cSprite = std::make_shared<CSprite>(m_assetManager.getTexture("ghost"));
	player->cShape = std::make_shared<CShape>(32,6,sf::Color::Blue,sf::Color::Red,2.0f);
	player->cBoundingBox = std::make_shared<CBoundingBox>(Vec2(64, 64));
	player->cInput = std::make_shared<CInput>();

	SimpEntPtr entityA = m_entityManager.addEntity("Test");
	entityA->cShape = std::make_shared<CShape>(32, 6, sf::Color::Red, sf::Color::Blue, 2.0f);
	entityA->cTransform = std::make_shared<CTransform>(Vec2(200,200));
	entityA->cTransform->velocity = Vec2(1, 1);
	entityA->cBoundingBox = std::make_shared<CBoundingBox>(Vec2(64, 64));


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
	SimpEntPtr player = m_entityManager.getEntities("Player").front();
	if (action.getType() == ActionType::Pressed)
	{
		if (action.getName() == "MOVE_UP")
		{
			player->cInput->up = true;
			std::cout << "Play Action: MOVE_UP" << std::endl;
		}
		else if (action.getName() == "MOVE_LEFT")
		{
			player->cInput->left = true;
			std::cout << "Play Action: MOVE_LEFT" << std::endl;
		}
		else if (action.getName() == "MOVE_DOWN")
		{
			player->cInput->down = true;
			std::cout << "Play Action: MOVE_DOWN" << std::endl;
		}
		else if (action.getName() == "MOVE_RIGHT")
		{
			player->cInput->right = true;
			std::cout << "Play Action: MOVE_RIGHT" << std::endl;
		}
	}
	else if (action.getType() == ActionType::Released)
	{
		if (action.getName() == "MOVE_UP")
		{
			player->cInput->up = false;
			std::cout << "Play Action Released: MOVE_UP" << std::endl;
		}
		else if (action.getName() == "MOVE_LEFT")
		{
			player->cInput->left = false;
			std::cout << "Play Action Released: MOVE_LEFT" << std::endl;
		}
		else if (action.getName() == "MOVE_DOWN")
		{
			player->cInput->down = false;
			std::cout << "Play Action Released: MOVE_DOWN" << std::endl;
		}
		else if (action.getName() == "MOVE_RIGHT")
		{
			player->cInput->right = false;
			std::cout << "Play Action Released: MOVE_RIGHT" << std::endl;
		}
	}
}
void Scene_Play::update()
{
	m_entityManager.update();
	sMovement();
	sAABBCollision();
}

void Scene_Play::sRender(sf::RenderWindow& window)
{
	SimpEntPtr player = m_entityManager.getEntities("Player").front();
	sf::View newView(
	sf::Vector2f(player->cTransform->pos.x, player->cTransform->pos.y),
	sf::Vector2f(window.getSize().x, window.getSize().y)
	);
	window.setView(newView);
		
	for(auto& e : m_entityManager.getEntities())
	{
		if (e->cTransform && e->cShape)
		{
			e->cShape->circle.setPosition(e->cTransform->pos);
			window.draw(e->cShape->circle);
		}
		if (e->cBoundingBox && e->cTransform) {
			e->cBoundingBox->debugRec.setPosition(e->cTransform->pos);
			window.draw(e->cBoundingBox->debugRec);
		}
		if (e->cTransform && e->cSprite) {
			e->cSprite->sprite.setPosition(e->cTransform->pos);
			window.draw(e->cSprite->sprite);
		}
		
	}
	
	m_uiManager.render(window);
}
void Scene_Play::sMovement()
{
	for (auto& player : m_entityManager.getEntities("Player"))
	{
		if (!player->cTransform || !player->cInput) { continue; }

		if (player->cInput->up || player->cInput->down || player->cInput->left || player->cInput->right)
		{
			Vec2 inputDir = { 0.0f,0.0f };
			if (player->cInput->up)
				inputDir.y -= 1.0f;
			if (player->cInput->down)
				inputDir.y += 1.0f;
			if (player->cInput->left)
				inputDir.x -= 1.0f;
			if (player->cInput->right)
				inputDir.x += 1.0f;
			inputDir.normalize();

			player->cInput->inputAngle = std::atan2(inputDir.y, inputDir.x);

			player->cInput->inputMagnitude = 1.0f;
			if ((inputDir.x == 0 && inputDir.y == 0))
			{
				player->cInput->inputMagnitude = 0.0f;
			}
		}
		else
		{
			player->cInput->inputMagnitude = 0.0f;
		}

		player->cTransform->velocity = Vec2::polarToCartesian(
			player->cInput->inputAngle,
			player->cInput->inputMagnitude * 10.0f
		);
	}
	for (auto& entity : m_entityManager.getEntities())
	{
		if (!entity->cTransform) { continue; }

		entity->cTransform->previousPos = entity->cTransform->pos;
		entity->cTransform->pos += entity->cTransform->velocity;
	}
}
void Scene_Play::sAABBCollision()
{
	for (auto& entityA : m_entityManager.getEntities())
	{
		if (!entityA->cBoundingBox || !entityA->cTransform) { continue; }
		for (auto& entityB : m_entityManager.getEntities())
		{
			if (entityA == entityB) { continue; }
			if (!entityB->cBoundingBox || !entityB->cTransform) { continue; }
			Vec2 currentOverlap = overlapAABB(
				entityA->cTransform->pos,
				*entityA->cBoundingBox,
				entityB->cTransform->pos,
				*entityB->cBoundingBox
			);
			Vec2 previousOverlap = overlapAABB(
				entityA->cTransform->previousPos,
				*entityA->cBoundingBox,
				entityB->cTransform->previousPos,
				*entityB->cBoundingBox
			);
			if (currentOverlap.x > 0.0f && currentOverlap.y > 0.0f)
			{

				if (previousOverlap.x > 0.0f && previousOverlap.y > 0.0f)
				{
					entityA->cTransform->pos.y -= .1 + (currentOverlap.y / 2);
					entityB->cTransform->pos.y += .1 + (currentOverlap.y / 2);
					continue;
				}

				else if (previousOverlap.y > 0.0f)//movement came left or right
				{
					entityA->cTransform->pos.x -= .1 + (currentOverlap.x / 2);
					entityB->cTransform->pos.x += .1 + (currentOverlap.x / 2);
					continue;
				}
				else if (previousOverlap.x > 0.0f)//movement came from top or bottom
				{
					entityA->cTransform->pos.y -= .1 + (currentOverlap.y / 2);
					entityB->cTransform->pos.y += .1 + (currentOverlap.y / 2);
					continue;
				}

			}

		}
	}
}
Vec2 Scene_Play::overlapAABB(const Vec2& aPos, const CBoundingBox& aBox, const Vec2& bPos, const CBoundingBox& bBox)
{
	Vec2 overlap(0.0f, 0.0f);
	float deltaX = bPos.x - aPos.x;
	float deltaY = bPos.y - aPos.y;
	overlap.x = (aBox.halfSize.x + bBox.halfSize.x) - std::abs(deltaX);
	overlap.y = (aBox.halfSize.y + bBox.halfSize.y) - std::abs(deltaY);
	return overlap;
}