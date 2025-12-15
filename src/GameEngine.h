#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "AssetManager.h"
#include <fstream>
#include "Scene_Menu.h"

class GameEngine {
	std::unordered_map<std::string, std::unique_ptr<Scene>> m_scenes;
	sf::RenderWindow m_window;
	AssetManager m_assetManager;
	std::string m_currentScene;
	bool m_running = true;
	void init(const std::string& config);
	void sUserInput();
	Scene& getCurrentScene();
	void updateWindow();
	void createScenes();
	void loadAssets(const std::string& config);

public:

	GameEngine(const std::string& config);
	void run();

	AssetManager& getAssetManager();
	sf::RenderWindow& getWindow();

};