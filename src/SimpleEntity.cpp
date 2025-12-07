#include "SimpleEntity.h"

SimpleEntity::SimpleEntity(size_t id, std::string tag)
	: m_id(id), m_tag(tag), m_alive(true)
{
}

bool SimpleEntity::isAlive() const
{
	return m_alive;
}

const std::string& SimpleEntity::getTag() const
{
	return m_tag;
}

const size_t SimpleEntity::getId() const
{
	return m_id;
}

void SimpleEntity::destroy()
{
	m_alive = false;
}

void SimpleEntity::setTTL(unsigned int time)
{
	m_ttl = time;
}