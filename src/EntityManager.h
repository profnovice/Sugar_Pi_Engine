#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "SimpleEntity.h"

typedef std::shared_ptr<SimpleEntity> SimpEntPtr;
typedef std::vector<std::shared_ptr<SimpleEntity>> EntityVec;
typedef std::unordered_map <std::string, EntityVec> EntityMap;
#pragma once
class EntityManager {
	EntityVec m_entities;
	EntityVec m_queueToAdd;
	EntityMap m_entityMap;
	size_t m_totalEntities = 0;
	size_t m_uniqueIdIndex = 0;
	

public:
	EntityManager();
	void update();
	SimpEntPtr addEntity(const std::string &);


};