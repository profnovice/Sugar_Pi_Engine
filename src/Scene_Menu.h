#pragma once
#include "Scene.h"

class Scene_Menu : public Scene {

	void init();
	void update();
	void sDoAction(Action& action);
	void sRender(sf::RenderWindow& window);
	
};