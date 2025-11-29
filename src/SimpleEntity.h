#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Components.h"

class SimpleEntity
{
	friend class EntityManager;

	SimpleEntity(size_t, const std::string);
	
	const size_t m_id = 0;
	const std::string m_tag = "default";
	bool m_alive = true;
	
public:
	
	std::shared_ptr<CTransform> cTransform;
	std::shared_ptr<std::string>cName;
	std::shared_ptr<sf::RectangleShape> cRectShape;
	std::shared_ptr<CShape> cShape;
	std::shared_ptr<CDisplayTag> cDisplayTag;
	std::shared_ptr<CCollision> cCollision;
	std::shared_ptr<cSprite> cSprite;
	std::shared_ptr<cRidgedBody> cRidgedBody;

	bool isAlive() const;
	const std::string& getTag() const;
	const size_t getId() const;
	void destroy();
	

};