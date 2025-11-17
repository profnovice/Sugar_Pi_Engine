#include "EntityManager.h"

/*
	EntityVec m_entities;
	EntityMap m_entityMap;
	size_t m_totalEntities = 0;
	size_t m_uniqueIdIndex = 0;

*/

EntityManager::EntityManager()
{
}

SimpEntPtr EntityManager::addEntity(const std::string & tag)
{
	//create a new entity obj
	SimpEntPtr e = std::make_shared<SimpleEntity>(m_uniqueIdIndex++, tag); m_totalEntities++;
	
	m_queueToAdd.push_back(e);
	//return shared ptr of new entity

	return e;
}

void EntityManager::update()
{
	for (auto & e : m_queueToAdd)
	{//store in all entities vec
		m_entities.push_back(e);
		//store in map of tag->entityvector
		m_entityMap[e->m_tag].push_back(e);

	}
	m_queueToAdd.clear();
	
}
