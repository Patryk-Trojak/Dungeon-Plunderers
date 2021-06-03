#pragma once
#include "Effect.h"

class SnowDust
	: public Effect
{
public:
	SnowDust(const sf::Vector2f& Position, const sf::Texture& Texture);
	virtual ~SnowDust();
};

