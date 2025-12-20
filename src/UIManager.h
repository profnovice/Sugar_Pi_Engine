#pragma once

#include "UIElement.h"
#include <memory>
#include <vector>
#include <algorithm>

typedef std::shared_ptr<UIElement> UIElementPtr;
typedef std::vector<UIElementPtr> UIElementVec;
typedef std::unordered_map<std::string, UIElementVec> UIElementMap;

class UIManager {
	size_t m_uniqueIdIndex = 0;
	size_t m_totalUIElements = 0;
	UIElementVec m_uiElements;
	UIElementVec m_uiElementsToAdd;
	UIElementMap m_uiElementMap;
	int removeInactiveElements(UIElementVec &);
public:

	UIManager();
	UIElementVec& getUIElements();
	UIElementVec& getUIElements(const std::string& tag);
	template <typename T>
	T& addUIElement(const std::string &);
	bool handleAction(const Action& action);
	void update(float deltaTime);
	void render(sf::RenderWindow& window);
	
};


