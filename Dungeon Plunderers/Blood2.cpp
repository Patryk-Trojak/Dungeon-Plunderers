#include "pch.h"
#include "Blood2.h"

Blood2::Blood2(const sf::Vector2f& Position, const sf::Texture& Texture, const float ScaleX)
	:Effect(Position, Texture, 1, 1, sf::Vector2i(86, 124), 12, 0.07, ScaleX)
{
	effect.setOrigin(86, 59);
}

Blood2::~Blood2()
{
}
