#include "pch.h"
#include "SnowDust.h"

SnowDust::SnowDust(const sf::Vector2f& Position, const sf::Texture& Texture)
	: Effect(Position, Texture, 1, 1, sf::Vector2i(66, 54), 5, 0.1f, 1)
{

}


SnowDust::~SnowDust()
{
}
