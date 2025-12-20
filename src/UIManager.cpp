#include "UIManager.h"


int UIManager::removeInactiveElements(UIElementVec& vec)
{
	int removedCount = 0;
	const auto deadEnd = std::remove_if(vec.begin(), vec.end(),
		[](const UIElementPtr& e) { return !e->m_isActive; });
	removedCount = std::distance(deadEnd, vec.end());
	vec.erase(deadEnd, vec.end());
	return removedCount;
}


UIManager::UIManager()
	:m_uiElements(), m_uiElementsToAdd(), m_uiElementMap()
{
}
UIElementVec& UIManager::getUIElements()
{
	return m_uiElements;
}
UIElementVec& UIManager::getUIElements(const std::string& tag)
{
	return m_uiElementMap[tag];
}

template<typename T>
T& UIManager::addUIElement(const std::string & tag)
{

	auto element = std::make_shared<T>(m_uniqueIdIndex,tag);
	++m_uniqueIdIndex;
	T& ref = *element;
	m_uiElementsToAdd.push_back(element);
	return ref;
}
bool UIManager::handleAction(const Action& action)
{
	bool handled = false;
	for (auto& element : m_uiElements)
	{
		if (element->isPointInside(action.mouseX, action.mouseY))
		{
			handled = element->handleAction(action);
			if (handled)
			{
				break;
			}
		}
	}
	return handled;
}

void UIManager::update(float deltaTime)
{
	for (auto& element : m_uiElements)
	{
		if (element->m_isActive)
		{
			element->update(deltaTime);
		}
	}
	//Add queued elements
	for (auto& element : m_uiElementsToAdd)
	{
		m_uiElements.push_back(element);
		m_uiElementMap[element->m_tag].push_back(element);
		++m_totalUIElements;
	}
	m_uiElementsToAdd.clear();
	int checkVec = 0;
	int checkMap = 0;
	//Remove inactive elements from map vecs
	for (auto& key : m_uiElementMap)
	{
		checkMap += removeInactiveElements(key.second);
	}
	//Remove inactive elements from main vec
	checkVec += removeInactiveElements(m_uiElements);
	
	if (checkMap != checkVec) {
		//std::cout << "UIManager::update() - Mismatch in removed UI element count between main vec and map vecs!" << std::endl;
	}
	m_totalUIElements -= checkVec;
	
}

void UIManager::render(sf::RenderWindow& window)
{
}

