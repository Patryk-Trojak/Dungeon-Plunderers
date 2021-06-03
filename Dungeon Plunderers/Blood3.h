#pragma once
#include "Effect.h"

class Blood3
	: public Effect
{
public:
	Blood3(const sf::Vector2f& Position, const sf::Texture& Texture, const float ScaleX);
	virtual ~Blood3();
};

