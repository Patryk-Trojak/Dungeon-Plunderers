#pragma once
#include "Effect.h"

class Blood4
	: public Effect
{
public:
	Blood4(const sf::Vector2f& Position, const sf::Texture& Texture, const float ScaleX);
	virtual ~Blood4();
};

