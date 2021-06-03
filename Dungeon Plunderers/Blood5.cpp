#include "pch.h"
#include "Blood5.h"

Blood5::Blood5(const sf::Vector2f& Position, const sf::Texture& Texture, const float ScaleX)
	: Effect(Position, Texture, 1, 1, sf::Vector2i(110, 78), 10, 0.07, ScaleX)
{
	effect.setOrigin(81, 20);
}

Blood5::~Blood5()
{
}
