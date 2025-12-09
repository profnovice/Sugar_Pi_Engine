#pragma once
#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include "SimpleEntity.h"
#include "EntityManager.h"
#include "Vec2.h"
#include <string>



class Game
{
	sf::RenderWindow m_window;
	EntityManager m_manager;
	sf::Font m_font;
	sf::Text m_text;
	sf::Text m_livesText;
	SimpEntPtr m_player;
	int m_score = 0;
	int m_currentFrame = 0;
	bool m_paused = false;
	bool m_running = true;
	bool m_showColliders = false;
	bool m_showImGui = false;
	Vec2 m_windowOffset;
	Vec2 m_windowSize = Vec2(1920, 1080);
	int m_frameLimit = 120;
	int m_pointsPerEnemy = 100;
	int m_Score = 0;
	int m_lives = 3;
	bool m_invincible = false;

	sf::Clock m_clock;

	sf::Texture ghostTexture;
	sf::Texture playerTexture;
	sf::Texture backgroundTexture;
	sf::Texture cursorTexture;

	template <typename T>
	void drawWrapper(T); //Not sure I'll need this just preemptive
	void setPaused(bool paused);
	
	void init(const std::string& config);//read in config, create window with settings, call spawn player
	//std::ifstream fin(path);
	void updateWindow();

	void sMovement();
	void sUserInput();
	void sRender();
	void sEnemySpawner();
	void sPointSpawner();
	void sTestCCollision();
	void sTestAABB();
	void sCollision();
	void sAABBCollision();
	void sUpdateImGui();

	void spawnPlayer();
	void spawnEnemy(Vec2 pos, Vec2 vel, sf::Color color);
	void spawnPoints(Vec2 pos, int amount);
	void spawnProjectile(SimpEntPtr entity);
	void spawnExplosion(SimpEntPtr entity);

	Vec2 overlapAABB(const CTransform& aTrans, const CBoundingBox& aBox, const CTransform& bTrans, const CBoundingBox& bBox);
	Vec2 resolveAABB(const Vec2& currentOverlap, const Vec2& previousOverlap);

	public:
	Game(const std::string & config);
	void run();

};

