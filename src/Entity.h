#include "Vec2.h"
#include <SFML/Graphics.hpp>

#pragma once
class Entity 
{
	const int m_entityID;
	sf::CircleShape & m_shape;
	Vec2 m_position;


public:


	Entity(int,sf::CircleShape&);

	//mutators
	void setShape(sf::CircleShape&);

	void setVecPosition(Vec2);



	const Vec2 getVecPosition();
	
	sf::CircleShape& getShape();


};

