#include "GameEngine.h"

GameEngine::GameEngine(const std::string& config) {
	init(config);
}

void GameEngine::init(const std::string& config) {
	updateWindow();
	loadAssets(config);
	createScenes();
}

void GameEngine::updateWindow()
{
	m_window.create(sf::VideoMode({ 800, 600 }), "Game Engine", sf::Style::Default);
	m_window.setFramerateLimit(60);
	m_window.setKeyRepeatEnabled(false);
	sf::Image iconImage("assets/SFMLPracticeIcon.png");
	m_window.setIcon(iconImage);
}

void GameEngine::createScenes()
{
	m_scenes["menu"] = std::make_unique<Scene_Menu>(m_assetManager);
	m_scenes["menu"]->init();
	m_scenes["play"] = std::make_unique<Scene_Play>(m_assetManager);
	m_scenes["play"]->init();
}

void GameEngine::loadAssets(const std::string& config)
{
	auto& backgroundTexture = m_assetManager.addTexture("Castle_Wall", "assets/Castle_Wall_sdvtcgja_1K_BaseColor.jpg");
	backgroundTexture.setRepeated(true);

	m_assetManager.addFont("mainFont", "assets/8bitOperatorPlus8-Regular.ttf");
	m_assetManager.addTexture("ghost", "assets/ghost_01.png").setSmooth(false);
	m_assetManager.addTexture("player", "assets/SimplePlayer.png");
	m_assetManager.addTexture("cursor", "assets/crosshair.png");

}

void GameEngine::run() {
	m_currentScene = "menu";
	std::cout << "Game Engine Running..." << std::endl;
	while (m_running) {
		sUserInput();
		//update current scene
		//render current scene
		getCurrentScene().update();
		m_window.clear();
		getCurrentScene().sRender(m_window);
		m_window.display();

	}
}

void GameEngine::sUserInput()
{
	while (const std::optional event = m_window.pollEvent())
	{
		//ImGui::SFML::ProcessEvent(m_window, *event);
		if (event->is<sf::Event::Closed>())
		{
			std::cout << "Closing window..." << std::endl;
			m_window.close();
			m_running = false;
		}
		if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
		{
			if(getCurrentScene().getInputMap().find(keyPressed->scancode) == getCurrentScene().getInputMap().end())
			{
				continue;
			}
			getCurrentScene().sDoAction(Action(getCurrentScene().getInputMap().at(keyPressed->scancode), "PRESSED"));
		}
		else if( const auto* keyReleased = event->getIf<sf::Event::KeyReleased>())
		{
			if(getCurrentScene().getInputMap().find(keyReleased->scancode) == getCurrentScene().getInputMap().end())
			{
				continue;
			}
			getCurrentScene().sDoAction(Action(getCurrentScene().getInputMap().at(keyReleased->scancode), "RELEASED"));
		}


	}

}

AssetManager& GameEngine::getAssetManager() {
	return m_assetManager;
}
sf::RenderWindow& GameEngine::getWindow() {
	return m_window;
}

Scene& GameEngine::getCurrentScene() {
	return *m_scenes.at(m_currentScene);
}