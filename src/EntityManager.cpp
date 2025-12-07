#include "EntityManager.h"

/*
	EntityVec m_entities;
	EntityMap m_entityMap;
	size_t m_totalEntities = 0;
	size_t m_uniqueIdIndex = 0;

*/

bool is_Dead(const SimpEntPtr e)
{
	return !e->isAlive();
}


int EntityManager::removeDeadEntities(EntityVec & vec)
{ 
	int removedCount = 0;
	const auto deadEnd = std::remove_if(vec.begin(), vec.end(), is_Dead);
	removedCount = std::distance(deadEnd, vec.end());
	vec.erase(deadEnd, vec.end());
	return removedCount;
}

EntityManager::EntityManager()
	:m_queueToAdd(), m_entities(), m_entityMap()
	//:m_entities(std::make_shared<std::vector<SimpleEntity>>())
{
}
SimpEntPtr EntityManager::addEntity()
{
	SimpEntPtr e = std::shared_ptr<SimpleEntity>(new SimpleEntity(m_uniqueIdIndex++, "Default")); m_totalEntities++;
	m_queueToAdd.push_back(e);
	return e;
}
SimpEntPtr EntityManager::addEntity(const std::string & tag)
{
	//create a new entity obj
	//SimpEntPtr e = std::make_shared<SimpleEntity>(m_uniqueIdIndex++, tag); m_totalEntities++;
	SimpEntPtr e = std::shared_ptr<SimpleEntity>(new SimpleEntity(m_uniqueIdIndex++, tag)); m_totalEntities++;
	
	m_queueToAdd.push_back(e);
	//return shared ptr of new entity

	return e;
}

SimpEntPtr EntityManager::addRec()
{
	SimpEntPtr e = std::shared_ptr<SimpleEntity>(new SimpleEntity(m_uniqueIdIndex++, "Rectangle")); m_totalEntities++;
	e->cRectShape = std::make_shared<sf::RectangleShape>();
	e->cRectShape->setSize({ 64,64 });
	e->cRectShape->setPosition({ 64.0f * (recPlacement % 20),64 });
	e->cRectShape->setFillColor(sf::Color::Red);
	m_queueToAdd.push_back(e);
	recPlacement++;
	return e;
}

const EntityVec & EntityManager::getEntities()
{
	return m_entities;
}

const EntityVec & EntityManager::getEntities(std::string tag)
{
	return m_entityMap[tag];
}

std::string const EntityManager::catMap()
{
	std::string outputString;
	for (auto key : m_entityMap)
	{
		outputString += key.first + ": " + catEntVec(key.second) + "\n";

	}
	return outputString;
}

std::string const EntityManager::catEntVec(const EntityVec entities)
{
	std::string outputString;
	for (auto e : entities)
	{
		//std::cout << e->m_id << ", ";
		outputString += std::to_string(e->m_id) + ", ";
	}
	return outputString;
}

void EntityManager::update()
{
	
	for (auto & e : m_queueToAdd)
	{//store in all entities vec
		m_entities.push_back(e);
		m_entityMap[e->m_tag].push_back(e);
	}
	int checkVec = 0;
	int checkMap = 0;
	checkVec += removeDeadEntities(m_entities);
	
	for (auto & key : m_entityMap)
	{
		checkMap += removeDeadEntities(key.second);
	}
	if(checkMap != checkVec){
		std::cout << "EntityManager::update() - Mismatch in removed entity count between main vec and map vecs!" << std::endl;
	}
	m_totalEntities -= checkVec;
	m_queueToAdd.clear();
	//std::cout << m_totalEntities << ": Entities" << std::endl;
	for (auto& e : m_entities)
	{
		if (e->m_ttl > 1) {
			e->m_ttl -= 1;
		}
		else if (e->m_ttl == 1) {
			e->destroy();
		}
	}
	
}


