#include "Game.h"

template <typename T>
T custom_lerp(T a, T b, T t) {
	return a + t * (b - a);
}

Game::Game(const std::string& config)
	:m_font("assets/8bitOperatorPlus8-Regular.ttf"), m_text(m_font), m_livesText(m_font)
{
	init(config);
}

void Game::init(const std::string& config)
{
	m_font.openFromFile("assets/8bitOperatorPlus8-Regular.ttf");
	m_text.setFont(m_font);
	m_text.setOutlineColor(sf::Color::Black);
	m_livesText.setFont(m_font);
	m_livesText.setOutlineColor(sf::Color::Black);
	
	ghostTexture = sf::Texture("assets/ghost_01.png"); 
	ghostTexture.setSmooth(false);
	playerTexture = sf::Texture("assets/SimplePlayer.png");
	playerTexture.setSmooth(false);	
	backgroundTexture = sf::Texture("assets/Castle_Wall_sdvtcgja_1K_BaseColor.jpg");
	backgroundTexture.setRepeated(true);
	cursorTexture = sf::Texture("assets/crosshair.png");
	
	updateWindow();
	m_clock.restart();
	ImGui::SFML::Init(m_window);
	spawnPlayer();
	//sf::Sprite ghostSprite(ghostTexture);
	m_showColliders = false;
	m_showImGui = false;

}

void Game::run()
{
	sf::Clock framesPerSecondClock;
	size_t framesSinceClockTick = 0;
	//sTestCCollision();
	//sTestAABB();
	while (m_running)
	{
		if (!m_paused)
		{
			m_manager.update();
			if(m_player->cInput->primaryAction)
			{
				m_player->cInput->primaryAction = false;
				spawnProjectile(m_player);
			}
			sMovement();
			//sCollision();
			sAABBCollision();
			sEnemySpawner();
			sPointSpawner();
			
		}
		//sUpdatePreviousPositions();
		sUserInput();
		sUpdateImGui();
		
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
		if(m_lives <= 0)
		{
			m_running = false;
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
	m_text.setPosition({ m_windowSize.x / 2.0f - 50.0f, 10.0f });
	m_livesText.setPosition({ 10.0f, 10.0f });

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
		if (!entity->cTransform->velocity.x == 0 || !entity->cTransform->velocity.y == 0)
		{
			entity->cTransform->storedVelocity = entity->cTransform->velocity;
		}
		
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


		if (entity->cTransform->pos.x < 0.0f + entity->cBoundingBox->halfSize.x)
		{
			entity->cTransform->pos.x = 0.0f + entity->cBoundingBox->halfSize.x;
		}
		if (entity->cTransform->pos.x > m_windowSize.x - entity->cBoundingBox->halfSize.x)
		{
			entity->cTransform->pos.x = m_windowSize.x - entity->cBoundingBox->halfSize.x;
		}
		if (entity->cTransform->pos.y < 0.0f + entity->cBoundingBox->halfSize.y)
		{
			entity->cTransform->pos.y = 0.0f + entity->cBoundingBox->halfSize.y;
		}
		if (entity->cTransform->pos.y > m_windowSize.y - entity->cBoundingBox->halfSize.y)
		{
			entity->cTransform->pos.y = m_windowSize.y - entity->cBoundingBox->halfSize.y;
		}
		
	}

	for(auto & ghost : m_manager.getEntities("Ghost"))
	{
		if(!ghost->cTransform){continue;}
		if (!ghost->cAI) { continue; }
		if (ghost->cAI->isSeeking) {
			//follow player
			Vec2 toPlayer = m_player->cTransform->pos - ghost->cTransform->pos;
			toPlayer.normalize();
			ghost->cTransform->velocity = toPlayer * Vec2::dist(Vec2(), ghost->cTransform->velocity);
		}
		else if (ghost->cAI->cooldown <= 0)
		{
			
			ghost->cAI->isSeeking = true;
		}
		else
		{
			--ghost->cAI->cooldown;
		}
		//if (!ghost->cHealth) { continue; }
		//ghost->cTransform->velocity = ghost->cTransform->storedVelocity * (ghost->cHealth->currentHealth/ghost->cHealth->maxHealth);

	}
}
void Game::sUserInput()
{
	while (const std::optional event = m_window.pollEvent())
	{
		ImGui::SFML::ProcessEvent(m_window, *event);
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
	sf::Sprite background = sf::Sprite(backgroundTexture);
	background.scale({ .5f, .5f });
	background.setTextureRect(sf::IntRect({0,0}, { 4096, 4096 }));
	
	m_window.draw(background);

	for (auto& entity : m_manager.getEntities())
	{
		if (entity->cShape && entity->cTransform)
		{
			entity->cShape->circle.setPosition((sf::Vector2f)(entity->cTransform->pos));
			if (entity->getTag() == "Points")
			{
				float pulseValue = (float)(m_currentFrame % 30) / 30;
				sf::Color updatedColor(pulseValue * 255, 255 - pulseValue * 255, 0);
				entity->cShape->circle.setFillColor(updatedColor);
			}
			m_window.draw(entity->cShape->circle);
		}
		if (entity->cSprite&& entity->cTransform)
		{
			entity->cSprite->sprite.setPosition((entity->cTransform->pos));

			if (entity->getTag() == "Ghost" && entity->cHealth) {
				sf::Color correctedColor = sf::Color(
					entity->cSprite->sprite.getColor().r, 
					entity->cSprite->sprite.getColor().g, 
					entity->cSprite->sprite.getColor().b, 
					155 *entity->cHealth->currentHealth/ entity->cHealth->maxHealth +100);
				entity->cSprite->sprite.setColor(correctedColor);
			}
			
			Vec2 rotator = Vec2(entity->cTransform->storedVelocity);

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
	m_text.setString("SCORE: " + std::to_string(m_score));
	m_livesText.setString("LIVES: " + std::to_string(m_lives));
	m_window.draw(m_text);
	m_window.draw(m_livesText);

	sf::Sprite cursorSprite(cursorTexture);
	cursorSprite.setOrigin({ cursorTexture.getSize().x / 2.0f, cursorTexture.getSize().y / 2.0f });
	cursorSprite.setScale({ 0.5f,0.5f });
	cursorSprite.setPosition((sf::Vector2f)(m_player->cInput->mousePosition));
	m_window.draw(cursorSprite);

	ImGui::SFML::Render(m_window);
	
	m_window.display();
}

void Game::sEnemySpawner()
{
	if (m_currentFrame % 240 == 0)
	{
		int posx = (float)(rand() % (int)m_windowSize.x);
		int posy = (float)(rand() % (int)m_windowSize.y);

		if(m_player->cTransform)
		{
			int attempts = 20;
			while (attempts > 0 && Vec2::dist(Vec2(posx, posy), m_player->cTransform->pos) < 500.0f)
			{
				posx = (float)(rand() % (int)m_windowSize.x);
				posy = (float)(rand() % (int)m_windowSize.y);
				attempts--;
			}
			if(attempts == 0)
			{
				//couldn't find a good spawn point away from player
				return;
			}
		}

		int signx = (rand() % 2) * 2 - 1;
		int signy = (rand() % 2) * 2 - 1;
		spawnEnemy(
			Vec2(posx,posy),
			Vec2(signx * (float)(rand() % 3 +2), signy *(float)(rand() % 3 +2)),
			sf::Color(rand() % 255, rand() % 255, rand() % 255)
		);
	}
}

void Game::sPointSpawner()
{
	if (m_currentFrame % 600 == 0)
	{
		int posx = std::clamp((float)(rand() % (int)m_windowSize.x), 10.0f, m_windowSize.x - 10);
		int posy = std::clamp((float)(rand() % (int)m_windowSize.y), 10.0f, m_windowSize.y - 10);
		if (m_player->cTransform)
		{
			int attempts = 20;
			while (attempts > 0 && Vec2::dist(Vec2(posx, posy), m_player->cTransform->pos) < 500.0f)
			{
				posx = std::clamp((float)(rand() % (int)m_windowSize.x), 10.0f, m_windowSize.x - 10);
				posy = std::clamp((float)(rand() % (int)m_windowSize.y), 10.0f, m_windowSize.y - 10);
				attempts--;
			}
			if (attempts == 0)
			{
				//couldn't find a good spawn point away from player
				return;
			}
		}
		spawnPoints(Vec2(posx, posy), rand() % 5 + 1);
	}

}

void Game::sTestCCollision()
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
	SimpEntPtr entityA = m_manager.addEntity("Ghost");
	entityA->cTransform = std::make_shared<CTransform>(Vec2(500, 500));
	entityA->cTransform->velocity = Vec2(0.5f, .1);
	//entityA->cShape = std::make_shared<CShape>(radius, points, sf::Color::Yellow, sf::Color::Red, 3.0f);
	//entityA->cShape->circle.setRotation(sf::degrees(45.0f));
	entityA->cSprite = std::make_shared<CSprite>(ghostTexture);
	entityA->cSprite->sprite.setColor(sf::Color::Yellow);
	entityA->cBoundingBox = std::make_shared<CBoundingBox>(Vec2(boxSize, boxSize));
	entityA->cHealth = std::make_shared<CHealth>(100);


	SimpEntPtr entityB = m_manager.addEntity("Ghost");
	entityB->cTransform = std::make_shared<CTransform>(Vec2(700, 500));
	entityB->cTransform->velocity = Vec2(-0.5f, 0);
	//entityB->cShape = std::make_shared<CShape>(radius, points, sf::Color::Cyan, sf::Color::Red, 3.0f);
	//entityB->cShape->circle.setRotation(sf::degrees(45.0f));
	entityB->cSprite = std::make_shared<CSprite>(ghostTexture);
	entityB->cSprite->sprite.setColor(sf::Color::Cyan);
	entityB->cBoundingBox = std::make_shared<CBoundingBox>(Vec2(boxSize, boxSize));
	entityB->cHealth = std::make_shared<CHealth>(100);

		
	//from top and bottom, moving towards each other
	SimpEntPtr entityC = m_manager.addEntity("Ghost");
	entityC->cTransform = std::make_shared<CTransform>(Vec2(900, 300));
	entityC->cTransform->velocity = Vec2(.1, 0.5f);
	//entityC->cShape = std::make_shared<CShape>(radius, points, sf::Color::Magenta, sf::Color::Red, 3.0f);
	//entityC->cShape->circle.setRotation(sf::degrees(45.0f));
	entityC->cSprite = std::make_shared<CSprite>(ghostTexture);
	entityC->cSprite->sprite.setColor(sf::Color::Magenta);
	entityC->cBoundingBox = std::make_shared<CBoundingBox>(Vec2(boxSize, boxSize));
	entityC->cHealth = std::make_shared<CHealth>(100);

	SimpEntPtr entityD = m_manager.addEntity("Ghost");
	entityD->cTransform = std::make_shared<CTransform>(Vec2(900, 500));
	entityD->cTransform->velocity = Vec2(0, -0.5f);
	//entityD->cShape = std::make_shared<CShape>(radius, points, sf::Color::Green, sf::Color::Red, 3.0f);
	//entityD->cShape->circle.setRotation(sf::degrees(45.0f));
	entityD->cSprite = std::make_shared<CSprite>(ghostTexture);
	entityD->cSprite->sprite.setColor(sf::Color::Green);
	entityD->cBoundingBox = std::make_shared<CBoundingBox>(Vec2(boxSize, boxSize));
	entityD->cHealth = std::make_shared<CHealth>(100);

	//diagonal collision
	SimpEntPtr entityE = m_manager.addEntity("Ghost");
	entityE->cTransform = std::make_shared<CTransform>(Vec2(1100, 300));
	entityE->cTransform->velocity = Vec2(0.5f, 0.5f);
	//entityE->cShape = std::make_shared<CShape>(radius, points, sf::Color::White, sf::Color::Red, 3.0f);
	//entityE->cShape->circle.setRotation(sf::degrees(45.0f));
	entityE->cSprite = std::make_shared<CSprite>(ghostTexture);
	entityE->cSprite->sprite.setColor(sf::Color::White);
	entityE->cBoundingBox = std::make_shared<CBoundingBox>(Vec2(boxSize, boxSize));
	entityE->cHealth = std::make_shared<CHealth>(100);
	
	SimpEntPtr entityF = m_manager.addEntity("Ghost");
	entityF->cTransform = std::make_shared<CTransform>(Vec2(1300, 500));
	entityF->cTransform->velocity = Vec2(-0.5f, -0.5f);
	//entityF->cShape = std::make_shared<CShape>(radius, points, sf::Color::Black, sf::Color::Red, 3.0f);
	//entityF->cShape->circle.setRotation(sf::degrees(45.0f));
	entityF->cSprite = std::make_shared<CSprite>(ghostTexture);
	entityF->cSprite->sprite.setColor(sf::Color::Red);
	entityF->cBoundingBox = std::make_shared<CBoundingBox>(Vec2(boxSize, boxSize));
	entityF->cHealth = std::make_shared<CHealth>(100);

	
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
	for(auto& projectile : m_manager.getEntities("Projectile"))
	{
		if(!projectile->cTransform || !projectile->cBoundingBox){continue;}

		/* // use if you want projectiles to despawn offscreen
		if(projectile->cTransform->pos.x < -50.0f || projectile->cTransform->pos.x > m_windowSize.x + 50.0f ||
		   projectile->cTransform->pos.y < -50.0f || projectile->cTransform->pos.y > m_windowSize.y + 50.0f)
		{
			projectile->destroy();
		}
		*/
		for(auto& ghost : m_manager.getEntities("Ghost"))
		{
			if(projectile == ghost){continue;}
			if(!ghost->cTransform || !ghost->cBoundingBox){continue;}
			Vec2 currentOverlap = overlapAABB(
				projectile->cTransform->pos,
				*projectile->cBoundingBox,
				ghost->cTransform->pos,
				*ghost->cBoundingBox
			);
			if(currentOverlap.x > 0.0f && currentOverlap.y > 0.0f)
			{
				//std::cout << "Projectile hit Ghost!" << std::endl;
				projectile->destroy();
				if(ghost->cHealth)
				{
					ghost->cHealth->currentHealth -= 25;
					ghost->cTransform->velocity = ghost->cTransform->velocity * ((float)ghost->cHealth->currentHealth / (float)ghost->cHealth->maxHealth);
					if (ghost->cAI)
					{
						if (ghost->cAI->isSeeking == true)
						{
							ghost->cTransform->velocity *= -1;
						}
						ghost->cAI->isSeeking = false;
						ghost->cAI->cooldown = ghost->cAI->cooldownMax;
						
						
					}
					if(ghost->cHealth->currentHealth <=0)
					{
						spawnExplosion(ghost);
						ghost->destroy();
						m_score += m_pointsPerEnemy;
					}
				}
			}
		}

	}
	bool playerHit = false;
	for(auto & ghost : m_manager.getEntities("Ghost"))
	{
		if(!ghost->cTransform || !ghost->cBoundingBox){continue;}
		Vec2 currentOverlap = overlapAABB(
			m_player->cTransform->pos,
			*m_player->cBoundingBox,
			ghost->cTransform->pos,
			*ghost->cBoundingBox
		);
		if (!playerHit && currentOverlap.x > 0.0f && currentOverlap.y > 0.0f)
		{
			if (!m_invincible)
			{
				--m_lives;
			}
			playerHit = true;
			for(auto & g: m_manager.getEntities("Ghost"))
			{
				g->destroy();
			}
		}
		
	}
	for(auto & points : m_manager.getEntities("Points"))
	{
		if(!points->cTransform || !points->cBoundingBox){continue;}
		Vec2 currentOverlap = overlapAABB(
			m_player->cTransform->pos,
			*m_player->cBoundingBox,
			points->cTransform->pos,
			*points->cBoundingBox
		);
		if (currentOverlap.x > 0.0f && currentOverlap.y > 0.0f)
		{
			m_score += m_pointsPerEnemy * 5;
			points->destroy();
			spawnExplosion(points);
		}
		
	}

	for (auto& entityA : m_manager.getEntities())
	{
		if (!entityA->cBoundingBox || !entityA->cTransform) { continue; }
		for (auto& entityB : m_manager.getEntities())
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
				

				//std::cout << "AABB Collision detected between Entity " << entityA->getId() << " and Entity " << entityB->getId() << std::endl;
				
			}
			//entityA->cTransform->pos += resolution;
			//entityB->cTransform->pos -= resolution;
		}
	}
}
void Game::sUpdateImGui()
{
	ImGui::SFML::Update(m_window, m_clock.restart());

	//ImGui::SetNextWindowSize(ImVec2(80, 60), ImGuiCond_Once);
	
	//ImGui::SetNextWindowPos();
	
	
	ImGui::Begin("SHOW", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoDecoration);
	ImGui::Checkbox("GUI", &m_showImGui);
	//ImGui::SetWindowPos(ImVec2(m_windowSize.x - ImGui::GetWindowSize().x, m_windowSize.y - ImGui::GetWindowSize().y), ImGuiCond_FirstUseEver);
	ImGui::SetWindowPos(ImVec2(m_windowSize.x - ImGui::GetWindowSize().x, m_windowSize.y - ImGui::GetWindowSize().y));
	ImGui::End();

	if (!m_showImGui) { return; }

	ImGui::SetNextWindowSize(ImVec2(200, 500), ImGuiCond_Once);
	ImGui::Begin("Settings",nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Checkbox("Show Colliders", &m_showColliders);
	ImGui::Checkbox("Invincible", &m_invincible);
	ImGui::Separator();
	ImGui::End();
	
	//ImGui::ShowDemoWindow();
}


void Game::spawnPlayer()
{
	int radius = 32;
	m_player = m_manager.addEntity("Player");
	m_player->cTransform = std::make_shared<CTransform>(Vec2(m_windowSize.x/2,m_windowSize.y/2));
	m_player->cInput = std::make_shared<CInput>();
	//m_player->cShape = std::make_shared<CShape>(64);
	//m_player->cShape = std::make_shared<CShape>(std::sqrt(radius * radius + radius * radius), 4, sf::Color::Blue, sf::Color::Red, 3.0f);
	//m_player->cShape->circle.setRotation(sf::degrees(45.0f));
	m_player->cSprite = std::make_shared<CSprite>(playerTexture);

	//m_player->cSprite->sprite.setColor(sf::Color(255,255,255));
	m_player->cBoundingBox = std::make_shared<CBoundingBox>(Vec2(radius*2, radius*2));
	//m_player->cCollision = std::make_shared<CCollision>(64);
}

void Game::spawnEnemy(Vec2 pos, Vec2 vel, sf::Color color)
{
	int radius = 36;
	int points = 6;
	float boxSize = 60;
	SimpEntPtr enemy = m_manager.addEntity("Ghost");
	//enemy->setTTL(2400);
	enemy->cTransform = std::make_shared<CTransform>(pos);
	enemy->cTransform->velocity = vel;
	enemy->cSprite = std::make_shared<CSprite>(ghostTexture);
	enemy->cSprite->sprite.setColor(color);
	enemy->cBoundingBox = std::make_shared<CBoundingBox>(Vec2(boxSize, boxSize));
	enemy->cHealth = std::make_shared<CHealth>(100);
	enemy->cAI = std::make_shared<CAI>(120);
}

void Game::spawnPoints(Vec2 pos, int amount)
{
	SimpEntPtr points = m_manager.addEntity("Points");
	points->setTTL(300);
	points->cTransform = std::make_shared<CTransform>(pos);
	points->cShape = std::make_shared<CShape>(16.0f, 12, sf::Color::Green, sf::Color::Yellow, 2.0f);
	points->cBoundingBox = std::make_shared<CBoundingBox>(Vec2(32, 32));
}

void Game::spawnProjectile(SimpEntPtr entity)
{
	SimpEntPtr projectile = m_manager.addEntity("Projectile");
	Vec2 mouseAngleVec = entity->cInput->mousePosition - entity->cTransform->pos;
	Vec2 spawnPos = entity->cTransform->pos + Vec2::normalize(mouseAngleVec) * 40.0f;
	projectile->setTTL(120); //lasts 2 seconds at 60fps
	projectile->cTransform = std::make_shared<CTransform>(spawnPos);
	projectile->cTransform->velocity = Vec2::normalize(mouseAngleVec) * 15.0f;
	projectile->cShape = std::make_shared<CShape>(8.0f, 12, sf::Color::Red, sf::Color::Yellow, 2.0f);
	projectile->cBoundingBox = std::make_shared<CBoundingBox>(Vec2(16,16));
}

void Game::spawnExplosion(SimpEntPtr entity)
{
	for(int i =0; i <10; i++)
	{
		SimpEntPtr particle = m_manager.addEntity("ExplosionParticle");
		particle->setTTL(30 + (rand() % 30)); //lasts between 0.5 and 1 seconds at 60fps
		particle->cTransform = std::make_shared<CTransform>(entity->cTransform->pos);
		float angle = (float)(rand() % 360);
		particle->cTransform->velocity = Vec2::polarToCartesian(angle * (3.14159f / 180.0f), (float)(2 + (rand() % 4)));
		sf::Color fillColor;
		sf::Color lineColor;
		if (entity->cSprite)
		{
			fillColor = entity->cSprite->sprite.getColor();
			fillColor = sf::Color(fillColor.r, fillColor.g, fillColor.b);
			lineColor = sf::Color(fillColor.r/2, fillColor.g/2, fillColor.b/2);
		}
		else if (entity->cShape)
		{
			fillColor = entity->cShape->circle.getFillColor();
			lineColor = entity->cShape->circle.getOutlineColor();
			fillColor = sf::Color(fillColor.r, fillColor.g, fillColor.b);
			lineColor = sf::Color(lineColor.r / 2, lineColor.g / 2, lineColor.b / 2);

		}
		else
		{
			fillColor = sf::Color::Yellow;
			lineColor = sf::Color::Red;
		}
		particle->cShape = std::make_shared<CShape>(4.0f, 6, fillColor, lineColor, 1.0f);
	}
}


Vec2 Game::overlapAABB(const Vec2& aPos, const CBoundingBox& aBox, const Vec2& bPos, const CBoundingBox& bBox)
{
	Vec2 overlap(0.0f, 0.0f);
	float deltaX = bPos.x - aPos.x;
	float deltaY = bPos.y - aPos.y;
	overlap.x = (aBox.halfSize.x + bBox.halfSize.x) - std::abs(deltaX);
	overlap.y = (aBox.halfSize.y + bBox.halfSize.y) - std::abs(deltaY);
	return overlap;
}
