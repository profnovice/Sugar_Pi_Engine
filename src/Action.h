#pragma once
#include <string>

class Action {
	std::string name;
	std::string type;

public:
	Action(const std::string& name, const std::string& type);
	Action();
	const std::string& getName() const;
	const std::string& getType() const;
	std::string toString() const;
};