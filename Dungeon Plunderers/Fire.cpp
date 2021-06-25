#include "pch.h"
#include "Fire.h"

Fire::Fire(const sf::Vector2f& Position, const sf::Texture& Texture)
	: Effect(Position, Texture, 1, 1, sf::Vector2i(27, 53), 3, 0.1f, 1)
{

}

Fire::~Fire()
{
}
