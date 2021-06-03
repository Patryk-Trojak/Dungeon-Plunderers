#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <iostream>


class TextureHolder
{
public:
	TextureHolder();
	~TextureHolder();
	void loadTexture(const std::string& id, const std::string& filepath, const bool repeated = false , const sf::IntRect& area = sf::IntRect());
	sf::Texture* getPointerToTexture(const std::string& id) const;
	sf::Texture& getTexture(const std::string& id) const;
private:
	std::map< std::string,
		std::unique_ptr< sf::Texture> > textureMap;
};

