#include "Entity.h"

	
Entity::Entity(int entityID)
	:m_entityID(entityID)
{
	m_shape = sf::CircleShape(64);
	m_shape.setFillColor(sf::Color(255, 255, 255));
}

Entity::Entity(int entityID, sf::CircleShape & shape)
	:m_entityID(entityID), m_shape(shape)
{
	m_position = Vec2(shape.getPosition().x, shape.getPosition().y);
}



void Entity::setShape(sf::CircleShape& shape)
{
	m_shape = shape;

}

void Entity::setVecPosition(const Vec2 position)
{
	m_position = position;
	m_shape.setPosition({ m_position.x, m_position.y });
}

const Vec2 Entity::getVecPosition()
{
	return m_position;
}

sf::CircleShape & Entity::getShape()
{
	return m_shape;
}
