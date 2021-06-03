#include "pch.h"
#include "Blood4.h"

Blood4::Blood4(const sf::Vector2f& Position, const sf::Texture& Texture, const float ScaleX)
	:Effect(Position, Texture, 1, 1, sf::Vector2i(64, 36), 8, 0.07, ScaleX)
{
	effect.setOrigin(64, 14);

}

Blood4::~Blood4()
{
}
