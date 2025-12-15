#include "GameEngine.h"

GameEngine::GameEngine(const std::string& config) {
	init(config);
}

void GameEngine::init(const std::string& config) {
	//create window
	m_window.create(sf::VideoMode({ 800, 600 }), "Game Engine", sf::Style::Default);
	m_window.setFramerateLimit(60);
	m_window.setKeyRepeatEnabled(false);
	//load assets
	//load scenes
	m_scenes["menu"] = std::make_unique<Scene_Menu>();
	m_scenes["menu"]->init();
	
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