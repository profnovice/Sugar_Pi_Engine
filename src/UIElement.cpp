#include "UIElement.h"

UIElement::UIElement(size_t id, std::string tag)
	: m_id(id), m_tag(tag)
{
}

bool UIElement::isPointInside(int x, int y) const
{
	return false;
}
