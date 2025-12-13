#include "AssetManager.h"

void AssetManager::addTexture(const std::string name, const std::string path)
{
	sf::Texture texture(path);
	m_textures[name] = texture;
}

void AssetManager::addFont(const std::string name, const std::string path)
{
	sf::Font font(path);
	m_fonts[name] = font;
}

const sf::Texture& AssetManager::getTexture(const std::string name) const
{
	return m_textures.at(name);
}

const sf::Font& AssetManager::getFont(const std::string name) const
{
	return m_fonts.at(name);
}

AssetManager::AssetManager()
{
}
