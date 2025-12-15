#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>
#include "EntityManager.h"
#include "Action.h"

typedef std::unordered_map<sf::Keyboard::Scancode, std::string> InputMap;

class Scene {
	size_t m_currentFrame = 0;
	InputMap m_inputMap;
	bool m_paused = false;
	bool m_hasEnded = false;

protected:
	EntityManager m_entityManager;
	void registerAction(sf::Keyboard::Scancode code, std::string name);
	virtual void assignActions() = 0;

public:
	Scene();
	virtual void init() = 0;
	virtual void update() = 0;
	virtual void sDoAction(const Action& action) = 0;
	virtual void sRender(sf::RenderWindow& window) = 0;
	
	const InputMap& getInputMap() const;

};