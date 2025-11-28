#include <SFML/Graphics.hpp>
#include "SimpleEntity.h"
#include "EntityManager.h"
#include "Vec2.h"
#include <string>

#pragma once

class Game
{
	sf::RenderWindow m_window;
	EntityManager m_entities;
	SimpEntPtr Player;
	bool m_paused;
	bool m_running;
	bool m_showColliders;
	Vec2 m_windowOffset;

	template <typename T>
	void drawWrapper(T);

public:
	Game(std::string);
	~Game();
	void run();
	void init();
	void update();
	void sMovement();
	void sUserInput();
	void sRender();
	void sEnemySpawner();
	void sCollision();
};
