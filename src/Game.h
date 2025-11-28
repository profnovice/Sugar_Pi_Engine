#include <SFML/Graphics.hpp>
#include "SimpleEntity.h"
#include "EntityManager.h"

#pragma once

class Game
{
	sf::RenderWindow m_window;
	EntityManager m_entities;
	SimpEntPtr Player;
	bool m_paused;
	bool m_running;

public:
	Game();
	~Game();
	void init();
	void update();
	void sMovement();
	void sUserInput();
	void sRender();
	void sEnemySpawner();
	void sCollision();
};
