#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <unordered_map>
#include <iostream>
#include <string>

class AssetManager {
	std::unordered_map<std::string, sf::Texture> m_textures;
	std::unordered_map<std::string, sf::Font> m_fonts;
	//std::unordered_map<std::string, sf::Sound> m_sounds;

public:
	void addTexture(const std::string name, const std::string path);
	void addFont(const std::string name, const std::string path);

	const sf::Texture& getTexture(const std::string name) const;
	const sf::Font& getFont(const std::string name) const;

	AssetManager();

};