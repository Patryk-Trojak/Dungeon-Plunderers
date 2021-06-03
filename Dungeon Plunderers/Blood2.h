#pragma once
#include "Effect.h"

class Blood2
	: public Effect
{
public:
	Blood2(const sf::Vector2f& Position, const sf::Texture& Texture, const float ScaleX);
	virtual ~Blood2();
};

