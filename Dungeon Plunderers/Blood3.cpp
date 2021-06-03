#include "pch.h"
#include "Blood3.h"

Blood3::Blood3(const sf::Vector2f& Position, const sf::Texture& Texture, const float ScaleX)
	:Effect(Position, Texture, 1, 1, sf::Vector2i(62, 80), 10, 0.07, ScaleX)
{
	effect.setOrigin(62, 32);

}

Blood3::~Blood3()
{
}
