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
	sf::Font m_font;
	sf::Text m_text;
	SimpEntPtr Player;
	int m_score = 0;
	int m_currentFrame = 0;
	bool m_paused;
	bool m_running;
	bool m_showColliders;
	Vec2 m_windowOffset;

	template <typename T>
	void drawWrapper(T); //Not sure I'll need this just preemptive
	~Game();
	void setPaused(bool paused);
	
	void init();//read in config, create window with settings, call spawn player
	//std::ifstream fin(path);

	void sMovement();
	void sUserInput();
	void sRender();
	void sEnemySpawner();
	void sCollision();

	void spawnPlayer();
	void spawnEnemy(SimpEntPtr entity);
	void spawnProjectile(SimpEntPtr entity);

	public:
	Game(const std::string & config);
	void run();

};

