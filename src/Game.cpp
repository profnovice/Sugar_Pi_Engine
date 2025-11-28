#include "Game.h"

void Game::run()
{
	while (m_running)
	{
		m_entities.update();

		if (!m_paused)
		{
			sEnemySpawner();
			sMovement();
			sCollision();
		}
		sUserInput();
		sRender();

		m_currentFrame++;//could be affected by pause

	}
}

void Game::sMovement()
{
}

void Game::sUserInput()
{
}

void Game::sRender()
{
}

void Game::sEnemySpawner()
{
}

void Game::sCollision()
{
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
