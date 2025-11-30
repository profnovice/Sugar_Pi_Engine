#include "Game.h"

Game::Game(const std::string& config)
	:m_font("assets/8bitOperatorPlus8-Regular.ttf"), m_text(m_font)
{
	init(config);
}

void Game::init(const std::string& config)
{
	m_font.openFromFile("assets/8bitOperatorPlus8-Regular.ttf");
	m_text.setFont(m_font);
	m_player = m_manager.addEntity();
	m_player->cTransform = std::make_shared<CTransform>(Vec2());
	m_player->cInput = std::make_shared<CInput>();
	m_player->cShape = std::make_shared<CShape>(64);
	m_player->cCollision = std::make_shared<CCollision>(64);
	updateWindow();

	SimpEntPtr collisionTestA = m_manager.addEntity("CollisionEntity");
	collisionTestA->cTransform = std::make_shared<CTransform>(Vec2(400.0f, 300.0f));
	collisionTestA->cShape = std::make_shared<CShape>(50.0f, 12, sf::Color::Green, sf::Color::Red, 3.0f);
	collisionTestA->cCollision = std::make_shared<CCollision>(50.0f);
	SimpEntPtr collisionTestB = m_manager.addEntity("CollisionEntity");
	collisionTestB->cTransform = std::make_shared<CTransform>(Vec2(600.0f, 300.0f));
	collisionTestB->cShape = std::make_shared<CShape>(50.0f, 12, sf::Color::Blue, sf::Color::Red, 3.0f);
	collisionTestB->cCollision = std::make_shared<CCollision>(50.0f);



}

void Game::run()
{
	sf::Clock framesPerSecondClock;
	size_t framesSinceClockTick = 0;

	while (m_running)
	{
		m_manager.update();
		if (!m_paused)
		{
			sEnemySpawner();
			sMovement();
			sCollision();
		}
		sUserInput();
		sRender();
		m_currentFrame++;//could be affected by pause
		framesSinceClockTick++;
		float elapsedSeconds = framesPerSecondClock.getElapsedTime().asSeconds();
		if (elapsedSeconds >= 1.0f)
		{
			std::cout << std::to_string((int)(framesSinceClockTick / elapsedSeconds)) << std::endl;
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
	for (auto& entity : m_manager.getAllEntities())
	{
		if (entity->cTransform)
		{
			entity->cTransform->previousPos = entity->cTransform->pos;
			entity->cTransform->pos += entity->cTransform->velocity;
			
		}
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
	for (auto& entity : m_manager.getAllEntities())
	{
		if (entity->cShape && entity->cTransform)
		{
			entity->cShape->circle.setPosition((sf::Vector2f)(entity->cTransform->pos));
			m_window.draw(entity->cShape->circle);
		}
	}
	m_window.display();
}

void Game::sEnemySpawner()
{
}

void Game::sCollision()
{
	for (auto& entityA : m_manager.getAllEntities())
	{
		if (!entityA->cCollision || !entityA->cTransform){ continue; }

		for (auto& entityB : m_manager.getAllEntities())
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
			entityA->cTransform->pos += overlap / 2.0f;
			entityB->cTransform->pos -= overlap / 2.0f;
			
		}
		
	}
}

void Game::spawnPlayer()
{
}

void Game::spawnEnemy(SimpEntPtr entity)
{
}

void Game::spawnProjectile(SimpEntPtr entity)
{
}
