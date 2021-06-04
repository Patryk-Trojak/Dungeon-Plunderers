#include "pch.h"
#include "FireExplosion.h"

FireExplosion::FireExplosion(const sf::Vector2f& Position, const sf::Texture& Texture)
	: Effect(Position, Texture, 1, 1, sf::Vector2i(80, 80), 7, 0.07f, 1)
{

}

FireExplosion::~FireExplosion()
{
}
