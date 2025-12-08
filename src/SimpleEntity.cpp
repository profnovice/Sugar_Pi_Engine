#include "SimpleEntity.h"

SimpleEntity::SimpleEntity(size_t id, std::string tag)
	: m_id(id), m_tag(tag), m_alive(true), m_ttl(0), m_ttlMax(0)
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
	m_ttlMax = time;
}

const unsigned int SimpleEntity::getTTL() const
{
	return m_ttl;
}

const unsigned int SimpleEntity::getTTLMax() const
{
	return m_ttlMax;
}
