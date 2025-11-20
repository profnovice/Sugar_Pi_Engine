#include <SFML/Graphics.hpp>
#include <memory>
#include "Components.h"
#pragma once
class SimpleEntity
{
	
public:
	const size_t m_id;
	const std::string& m_tag;
	bool m_alive;

	std::shared_ptr<CTransform> cTransform;
	std::shared_ptr<std::string>cName;
	std::shared_ptr<sf::RectangleShape> cShape;
	std::shared_ptr<CDisplayTag> cDisplayTag;

	SimpleEntity(size_t, const std::string &);


};