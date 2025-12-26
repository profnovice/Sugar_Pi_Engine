#pragma once
#include "Scene.h"

class Scene_Play : public Scene {

private:
	void spawnPlayer();

protected:
	void assignActions();
	void sMovement();
	void sAABBCollision();
	Vec2 overlapAABB(const Vec2& aPos, const CBoundingBox& aBox, const Vec2& bPos, const CBoundingBox& bBox);
public:
	using Scene::Scene;
	void init();
	void update();
	void sDoAction(const Action& action);
	void sRender(sf::RenderWindow& window);
};