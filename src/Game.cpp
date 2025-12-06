#include "Game.h"

template <typename T>
T custom_lerp(T a, T b, T t) {
	return a + t * (b - a);
}

Game::Game(const std::string& config)
	:m_font("assets/8bitOperatorPlus8-Regular.ttf"), m_text(m_font)
{
	init(config);
}

void Game::init(const std::string& config)
{
	m_font.openFromFile("assets/8bitOperatorPlus8-Regular.ttf");
	m_text.setFont(m_font);
	
	ghostTexture = sf::Texture("assets/ghost_01.png"); 
	ghostTexture.setSmooth(false);
	playerTexture = sf::Texture("assets/SimplePlayer.png");
	playerTexture.setSmooth(false);	
	updateWindow();
	spawnPlayer();
	//sf::Sprite ghostSprite(ghostTexture);
	m_showColliders = false;




}

void Game::run()
{
	sf::Clock framesPerSecondClock;
	size_t framesSinceClockTick = 0;
	//sEnemySpawner();
	sTestAABB();
	while (m_running)
	{
		m_manager.update();
		if (!m_paused)
		{
			
			sMovement();
			//sCollision();
			sAABBCollision();
			
		}
		//sUpdatePreviousPositions();
		sUserInput();
		sRender();
		m_currentFrame++;//could be affected by pause
		framesSinceClockTick++;
		float elapsedSeconds = framesPerSecondClock.getElapsedTime().asSeconds();
		if (elapsedSeconds >= 1.0f)
		{
			//std::cout << std::to_string((int)(framesSinceClockTick / elapsedSeconds)) << std::endl;
			framesPerSecondClock.restart();
			framesSinceClockTick = 0;

		}
	}
}

void Game::setPaused(bool paused)
{
	m_paused = paused;
}


void Game::updateWindow()
{
	m_window.create(sf::VideoMode({ (unsigned int)m_windowSize.x, (unsigned int)m_windowSize.y }), "SimEngine", sf::Style::Default);
	m_window.setMouseCursorVisible(false);
	m_window.setFramerateLimit(m_frameLimit);
	sf::Image iconImage("assets/SFMLPracticeIcon.png");
	m_window.setIcon(iconImage);

}

void Game::sMovement()
{
	m_player->cTransform->velocity = Vec2::polarToCartesian(
		m_player->cInput->inputAngle,
		m_player->cInput->inputMagnitude * 10
	);
	


	//std::cout << m_player->cTransform->pos.toString() << std::endl;
	for (auto& entity : m_manager.getEntities())
	{
		if (!entity->cTransform){continue;}
		
		entity->cTransform->previousPos = entity->cTransform->pos;
		entity->cTransform->pos += entity->cTransform->velocity;
		
		

		if (!entity->cBoundingBox){continue;}

		//bounce off walls
		if(entity->cTransform->pos.x - entity->cBoundingBox->halfSize.x < 0.0f || 
			entity->cTransform->pos.x + entity->cBoundingBox->halfSize.x > m_windowSize.x)
		{
			entity->cTransform->velocity.x = -entity->cTransform->velocity.x;
		}
		if (entity->cTransform->pos.y - entity->cBoundingBox->halfSize.y < 0.0f ||
			entity->cTransform->pos.y + entity->cBoundingBox->halfSize.y > m_windowSize.y)
		{
			entity->cTransform->velocity.y = -entity->cTransform->velocity.y;
		}

		
	}


	if (m_player->cTransform->pos.x < 0.0f + m_player->cBoundingBox->halfSize.x)
	{
		m_player->cTransform->pos.x = 0.0f + m_player->cBoundingBox->halfSize.x;
	}
	if (m_player->cTransform->pos.x > m_windowSize.x - m_player->cBoundingBox->halfSize.x)
	{
		m_player->cTransform->pos.x = m_windowSize.x - m_player->cBoundingBox->halfSize.x;
	}
	if (m_player->cTransform->pos.y < 0.0f + m_player->cBoundingBox->halfSize.y)
	{
		m_player->cTransform->pos.y = 0.0f + m_player->cBoundingBox->halfSize.y;
	}
	if (m_player->cTransform->pos.y > m_windowSize.y - m_player->cBoundingBox->halfSize.y)
	{
		m_player->cTransform->pos.y = m_windowSize.y - m_player->cBoundingBox->halfSize.y;
	}
	
}
void Game::sUserInput()
{
	while (const std::optional event = m_window.pollEvent())
	{
		if (event->is<sf::Event::Closed>())
		{
			m_window.close();
			m_running = false;
		}

		if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
		{
			switch (keyPressed->scancode)
			{
			case sf::Keyboard::Scancode::W:
				m_player->cInput->up = true;
				break;
			case sf::Keyboard::Scancode::S:
				m_player->cInput->down = true;
				break;
			case sf::Keyboard::Scancode::A:
				m_player->cInput->left = true;
				break;
			case sf::Keyboard::Scancode::D:
				m_player->cInput->right = true;
				break;
			case sf::Keyboard::Scancode::Escape:
				m_paused = !m_paused;
				break;
			}
		}
		if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>())
		{
			switch (keyReleased->scancode)
			{
			case sf::Keyboard::Scancode::W:
				m_player->cInput->up = false;
				break;
			case sf::Keyboard::Scancode::S:
				m_player->cInput->down = false;
				break;
			case sf::Keyboard::Scancode::A:
				m_player->cInput->left = false;
				break;
			case sf::Keyboard::Scancode::D:
				m_player->cInput->right = false;
				break;
			}
		}
		

		
		if(m_player->cInput->up || m_player->cInput->down || m_player->cInput->left || m_player->cInput->right)
		{
			Vec2 inputDir = { 0.0f,0.0f };
			if (m_player->cInput->up)
				inputDir.y -= 1.0f;
			if (m_player->cInput->down)
				inputDir.y += 1.0f;
			if (m_player->cInput->left)
				inputDir.x -= 1.0f;
			if (m_player->cInput->right)
				inputDir.x += 1.0f;
			inputDir.normalize();

			m_player->cInput->inputAngle = std::atan2(inputDir.y, inputDir.x);
			
			m_player->cInput->inputMagnitude = 1.0f;
			if ((inputDir.x == 0 && inputDir.y == 0))
			{
				m_player->cInput->inputMagnitude = 0.0f;
			}
		}
		else
		{
			m_player->cInput->inputMagnitude = 0.0f;
		}


		if (const auto* mouseClick = event->getIf<sf::Event::MouseButtonPressed>())
		{
			if (mouseClick->button == sf::Mouse::Button::Left)
			{
				m_player->cInput->primaryAction = true;
			}

		}
		if (const auto* mouseRelease = event->getIf<sf::Event::MouseButtonReleased>())
		{
			if (mouseRelease->button == sf::Mouse::Button::Left)
			{
				m_player->cInput->primaryAction = false;
			}

		}

		if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>())
		{
			m_player->cInput->mousePosition = Vec2((float)mouseMoved->position.x, (float)mouseMoved->position.y);
		}

		if (const auto* resized = event->getIf<sf::Event::Resized>())
		{
			m_windowSize = Vec2((float)resized->size.x, (float)resized->size.y);
			updateWindow();
		}


	}
	
}

void Game::sRender()
{
	m_window.clear();
	for (auto& entity : m_manager.getEntities())
	{
		if (entity->cShape && entity->cTransform)
		{
			entity->cShape->circle.setPosition((sf::Vector2f)(entity->cTransform->pos));
			m_window.draw(entity->cShape->circle);
		}
		if (entity->cSprite&& entity->cTransform)
		{
			entity->cSprite->sprite.setPosition((entity->cTransform->pos));
			
			Vec2 rotator = Vec2(entity->cTransform->velocity);

			rotator.normalize();
			Vec2 flippedRotator = rotator;
			flippedRotator *= -1;
			float angle = rotator.angle();
			float flippedAngle = flippedRotator.angle();
			if(angle <90 || angle >270)
			{
				entity->cSprite->sprite.setScale(Vec2(1.0f, 1.0f));
				entity->cSprite->sprite.setRotation(sf::degrees(angle));
			}
			else
			{
				entity->cSprite->sprite.setScale(Vec2( - 1.0f, 1.0f));
				entity->cSprite->sprite.setRotation(sf::degrees(flippedAngle));
			}
			m_window.draw(entity->cSprite->sprite);
		}
		if (entity->cBoundingBox && entity->cTransform && m_showColliders)
		{
			entity->cBoundingBox->debugRec.setPosition((sf::Vector2f)(entity->cTransform->pos));

			m_window.draw(entity->cBoundingBox->debugRec);
		}
	}
	m_window.display();
}

void Game::sEnemySpawner()
{

	SimpEntPtr collisionTestA = m_manager.addEntity("Points");
	collisionTestA->cTransform = std::make_shared<CTransform>(Vec2(400.0f, 300.0f));
	collisionTestA->cShape = std::make_shared<CShape>(50.0f, 12, sf::Color::Green, sf::Color::Red, 3.0f);
	collisionTestA->cCollision = std::make_shared<CCollision>(50.0f);
	SimpEntPtr collisionTestB = m_manager.addEntity("Points");
	collisionTestB->cTransform = std::make_shared<CTransform>(Vec2(600.0f, 300.0f));
	collisionTestB->cShape = std::make_shared<CShape>(50.0f, 12, sf::Color::Blue, sf::Color::Red, 3.0f);
	collisionTestB->cCollision = std::make_shared<CCollision>(50.0f);

	int iMax = 40;
	int jMax = 10;
	int gravIn = 1;
	bool grav = true;

	for (int i = 0; i < iMax; i++)
	{
		for (int j = 0; j < jMax; j++)
		{


			int radius = 16;
			SimpEntPtr physicsEntity = m_manager.addEntity("Physics");
			physicsEntity->cTransform = std::make_shared<CTransform>(Vec2(m_windowSize.x / iMax * i + 20, m_windowSize.x / iMax * j + 100));
			physicsEntity->cTransform->previousPos = physicsEntity->cTransform->pos;
			sf::Color specialColor
			(
				custom_lerp(0.0f, 255.0f, (float)i / (float)iMax),
				255 - custom_lerp(0.0f, 255.0f, (float)j / (float)jMax),
				255 - (custom_lerp(0.0f, 255.0f, (float)i / (float)iMax) + (255 - custom_lerp(0.0f, 255.0f, (float)j / (float)jMax))) / 2
			);
			physicsEntity->cShape = std::make_shared<CShape>(radius, 12, specialColor, sf::Color::Red, 3.0f);
			physicsEntity->cCollision = std::make_shared<CCollision>(radius);
			//physicsEntity->cBoundingBox = std::make_shared<CBoundingBox>(Vec2(radius * 2.0f, radius * 2.0f));
			physicsEntity->cRidgedBody = std::make_shared<CRidgedBody>();
			physicsEntity->cRidgedBody->mass = .25;
			physicsEntity->cRidgedBody->useGravity = grav;
		}

	}
}

void Game::sTestAABB()
{
	int radius = 36;
	int points = 6;
	// = std::sqrt(radius * radius + radius * radius);
	float boxSize = 60; 
	
	//from the side of the screen, moving towards each other
	SimpEntPtr entityA = m_manager.addEntity("AABBTest");
	entityA->cTransform = std::make_shared<CTransform>(Vec2(500, 500));
	entityA->cTransform->velocity = Vec2(0.5f, .1);
	//entityA->cShape = std::make_shared<CShape>(radius, points, sf::Color::Yellow, sf::Color::Red, 3.0f);
	//entityA->cShape->circle.setRotation(sf::degrees(45.0f));
	entityA->cSprite = std::make_shared<CSprite>(ghostTexture);
	entityA->cSprite->sprite.setColor(sf::Color::Yellow);
	entityA->cBoundingBox = std::make_shared<CBoundingBox>(Vec2(boxSize, boxSize));

	SimpEntPtr entityB = m_manager.addEntity("AABBTest");
	entityB->cTransform = std::make_shared<CTransform>(Vec2(700, 500));
	entityB->cTransform->velocity = Vec2(-0.5f, 0);
	//entityB->cShape = std::make_shared<CShape>(radius, points, sf::Color::Cyan, sf::Color::Red, 3.0f);
	//entityB->cShape->circle.setRotation(sf::degrees(45.0f));
	entityB->cSprite = std::make_shared<CSprite>(ghostTexture);
	entityB->cSprite->sprite.setColor(sf::Color::Cyan);
	entityB->cBoundingBox = std::make_shared<CBoundingBox>(Vec2(boxSize, boxSize));

		
	//from top and bottom, moving towards each other
	SimpEntPtr entityC = m_manager.addEntity("AABBTest");
	entityC->cTransform = std::make_shared<CTransform>(Vec2(900, 300));
	entityC->cTransform->velocity = Vec2(.1, 0.5f);
	//entityC->cShape = std::make_shared<CShape>(radius, points, sf::Color::Magenta, sf::Color::Red, 3.0f);
	//entityC->cShape->circle.setRotation(sf::degrees(45.0f));
	entityC->cSprite = std::make_shared<CSprite>(ghostTexture);
	entityC->cSprite->sprite.setColor(sf::Color::Magenta);
	entityC->cBoundingBox = std::make_shared<CBoundingBox>(Vec2(boxSize, boxSize));

	SimpEntPtr entityD = m_manager.addEntity("AABBTest");
	entityD->cTransform = std::make_shared<CTransform>(Vec2(900, 500));
	entityD->cTransform->velocity = Vec2(0, -0.5f);
	//entityD->cShape = std::make_shared<CShape>(radius, points, sf::Color::Green, sf::Color::Red, 3.0f);
	//entityD->cShape->circle.setRotation(sf::degrees(45.0f));
	entityD->cSprite = std::make_shared<CSprite>(ghostTexture);
	entityD->cSprite->sprite.setColor(sf::Color::Green);
	entityD->cBoundingBox = std::make_shared<CBoundingBox>(Vec2(boxSize, boxSize));

	//diagonal collision
	SimpEntPtr entityE = m_manager.addEntity("AABBTest");
	entityE->cTransform = std::make_shared<CTransform>(Vec2(1100, 300));
	entityE->cTransform->velocity = Vec2(0.5f, 0.5f);
	//entityE->cShape = std::make_shared<CShape>(radius, points, sf::Color::White, sf::Color::Red, 3.0f);
	//entityE->cShape->circle.setRotation(sf::degrees(45.0f));
	entityE->cSprite = std::make_shared<CSprite>(ghostTexture);
	entityE->cSprite->sprite.setColor(sf::Color::White);
	entityE->cBoundingBox = std::make_shared<CBoundingBox>(Vec2(boxSize, boxSize));
	
	SimpEntPtr entityF = m_manager.addEntity("AABBTest");
	entityF->cTransform = std::make_shared<CTransform>(Vec2(1300, 500));
	entityF->cTransform->velocity = Vec2(-0.5f, -0.5f);
	//entityF->cShape = std::make_shared<CShape>(radius, points, sf::Color::Black, sf::Color::Red, 3.0f);
	//entityF->cShape->circle.setRotation(sf::degrees(45.0f));
	entityF->cSprite = std::make_shared<CSprite>(ghostTexture);
	entityF->cSprite->sprite.setColor(sf::Color::Red);
	entityF->cBoundingBox = std::make_shared<CBoundingBox>(Vec2(boxSize, boxSize));

	
}

void Game::sCollision()
{
	for (auto& entityA : m_manager.getEntities())
	{
		if (!entityA->cCollision || !entityA->cTransform) { continue; }

		for (auto& entityB : m_manager.getEntities())
		{
			if (entityA == entityB) { continue; }
			if (!entityB->cCollision || !entityB->cTransform) { continue; }
			if (!Vec2::circleCollision(entityA->cTransform->pos, entityB->cTransform->pos, entityA->cCollision->radius, entityB->cCollision->radius)) { continue; }
			//std::cout << "Collision detected between Entity " << entityA->getId() << " and Entity " << entityB->getId() << std::endl;
			
			Vec2 overlap = Vec2::circleOverlap(
				entityA->cTransform->pos,
				entityB->cTransform->pos,
				entityA->cCollision->radius,
				entityB->cCollision->radius
			);
			entityA->cTransform->pos -= overlap / 2.0f;
			entityB->cTransform->pos += overlap / 2.0f;

			if(entityA->getTag() == "Player" && entityB->getTag() == "Points")
			{
				std::cout << "Player collected a point!" << std::endl;
				entityB->destroy();
			}
			
			
		}
		
	}
}

void Game::sAABBCollision()
{
	for (auto& entityA : m_manager.getEntities())
	{
		if (!entityA->cBoundingBox || !entityA->cTransform) { continue; }
		for (auto& entityB : m_manager.getEntities())
		{
			if (entityA == entityB) { continue; }
			if (!entityB->cBoundingBox || !entityB->cTransform) { continue; }
			Vec2 currentOverlap = overlapAABB(
				*entityA->cTransform,
				*entityA->cBoundingBox,
				*entityB->cTransform,
				*entityB->cBoundingBox
			);
			Vec2 previousOverlap = overlapAABB(
				CTransform{ entityA->cTransform->previousPos },
				*entityA->cBoundingBox,
				CTransform{ entityB->cTransform->previousPos },
				*entityB->cBoundingBox
			);
			//std::cout << "Current Overlap: " << currentOverlap.toString() << " Previous Overlap: " << previousOverlap.toString() << std::endl;
			if(currentOverlap.x > 0.0f && currentOverlap.y > 0.0f)
			{
				/*
				if(previousOverlap.x <= 0.0f && previousOverlap.y <= 0.0f)
				{
					//no previous overlap info, just separate in both axes equally
					entityA->cTransform->pos.x -= currentOverlap.x / 2.0f;
					entityB->cTransform->pos.x += currentOverlap.x / 2.0f;
					entityA->cTransform->pos.y -= currentOverlap.y / 2.0f;
					entityB->cTransform->pos.y += currentOverlap.y / 2.0f;
				}
				*/
	
				if(previousOverlap.x > 0.0f && previousOverlap.y > 0.0f)
				{
					//no movement info, by default place on top/bottom
					entityA->cTransform->pos.y -= .1 + (currentOverlap.y / 2);
					entityB->cTransform->pos.y += .1 + (currentOverlap.y / 2);
					//entityA->cTransform->pos.y = entityA->cTransform->previousPos.y;
					//entityB->cTransform->pos.y = entityB->cTransform->previousPos.y;
					continue;
				}

				else if (previousOverlap.y > 0.0f)//movement came left or right
				{
					entityA->cTransform->pos.x -= .1 + (currentOverlap.x / 2);
					entityB->cTransform->pos.x += .1 + (currentOverlap.x / 2);
					//entityA->cTransform->pos.x = entityA->cTransform->previousPos.x;
					//entityB->cTransform->pos.x = entityB->cTransform->previousPos.x;
					continue;
				}
				else if (previousOverlap.x > 0.0f)//movement came from top or bottom
				{
					entityA->cTransform->pos.y -= .1 + (currentOverlap.y / 2);
					entityB->cTransform->pos.y += .1 + (currentOverlap.y / 2);
					//entityA->cTransform->pos.y = entityA->cTransform->previousPos.y;
					//entityB->cTransform->pos.y = entityB->cTransform->previousPos.y;
					continue;
				}
				

				std::cout << "AABB Collision detected between Entity " << entityA->getId() << " and Entity " << entityB->getId() << std::endl;
				
			}
			//entityA->cTransform->pos += resolution;
			//entityB->cTransform->pos -= resolution;
		}
	}
}


void Game::spawnPlayer()
{
	int radius = 32;
	m_player = m_manager.addEntity("Player");
	m_player->cTransform = std::make_shared<CTransform>(Vec2(50,50));
	m_player->cInput = std::make_shared<CInput>();
	//m_player->cShape = std::make_shared<CShape>(64);
	//m_player->cShape = std::make_shared<CShape>(std::sqrt(radius * radius + radius * radius), 4, sf::Color::Blue, sf::Color::Red, 3.0f);
	//m_player->cShape->circle.setRotation(sf::degrees(45.0f));
	m_player->cSprite = std::make_shared<CSprite>(playerTexture);

	//m_player->cSprite->sprite.setColor(sf::Color(255,255,255));
	m_player->cBoundingBox = std::make_shared<CBoundingBox>(Vec2(radius*2, radius*2));
	//m_player->cCollision = std::make_shared<CCollision>(64);
}

void Game::spawnEnemy(SimpEntPtr entity)
{
}

void Game::spawnProjectile(SimpEntPtr entity)
{
}


Vec2 Game::overlapAABB(const CTransform& aTrans, const CBoundingBox& aBox, const CTransform& bTrans, const CBoundingBox& bBox)
{
	Vec2 overlap(0.0f, 0.0f);
	float deltaX = bTrans.pos.x - aTrans.pos.x;
	float deltaY = bTrans.pos.y - aTrans.pos.y;
	overlap.x = (aBox.halfSize.x + bBox.halfSize.x) - std::abs(deltaX);
	overlap.y = (aBox.halfSize.y + bBox.halfSize.y) - std::abs(deltaY);
	return overlap;
}
