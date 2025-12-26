#pragma once
#include "Scene.h"

class Scene_Menu : public Scene {

private:
	void createMenuItems();

protected:
	void assignActions();

public:
	using Scene::Scene;
	void init();
	void update();
	void sDoAction(const Action& action);
	void sRender(sf::RenderWindow& window);
};