#pragma once
#include <SFML/Audio.hpp>
#include"ResourceHolder.h"
#include "TextureID.h"



enum class SoundBufferID {
	
};


struct Resources {

	const sf::Texture& operator[](TextureID textureID) const;
	const sf::SoundBuffer& operator[](SoundBufferID soundBuffer) const;

	ResourceHolder<TextureID, sf::Texture> textures;
	ResourceHolder<SoundBufferID, sf::SoundBuffer> soundBuffers;
	sf::Font font;
};
