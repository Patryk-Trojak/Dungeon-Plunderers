#include "pch.h"
#include "FireExplosion.h"

FireExplosion::FireExplosion(const sf::Vector2f& Position, const sf::Texture& Texture)
	: Effect(Position, Texture, 1, 1, sf::Vector2i(80, 80), 8, 0.08f, 1)
{

}

FireExplosion::~FireExplosion()
{
}
