#pragma once
#include "Scene.h"

class Scene_Menu : public Scene {

protected:
	void assignActions();

public:
	void init();
	void update();
	void sDoAction(const Action& action);
	void sRender(sf::RenderWindow& window);
};