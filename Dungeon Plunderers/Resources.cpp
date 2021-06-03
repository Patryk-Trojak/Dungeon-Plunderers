#include "pch.h"
#include "Resources.h"

const sf::Texture& Resources::operator[](TextureID textureID) const
{
	return textures.getResource(textureID);
}

const sf::SoundBuffer& Resources::operator[](SoundBufferID soundBuffer) const
{
	return soundBuffers.getResource(soundBuffer);
}
