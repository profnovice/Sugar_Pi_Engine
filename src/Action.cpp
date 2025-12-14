#include "Action.h"

Action::Action(const std::string& name, const std::string& type)
	: name(name), type(type) {
}
Action::Action()
	: name("NONE"), type("NONE") {
}

const std::string& Action::getName() const
{
	return name;
}
const std::string& Action::getType() const {
	return type;
}
std::string Action::toString() const {
	return "Action(Name: " + name + ", Type: " + type + ")";
}
