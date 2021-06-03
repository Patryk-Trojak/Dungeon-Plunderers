#include "pch.h"
#include "Blood1.h"

Blood1::Blood1(const sf::Vector2f& Position, const sf::Texture& Texture, const float ScaleX)
	:Effect(Position, Texture, 1, 1, sf::Vector2i(62, 72), 11, 0.07f, ScaleX)
{
	effect.setOrigin(62, 34);
}

Blood1::~Blood1()
{
}
