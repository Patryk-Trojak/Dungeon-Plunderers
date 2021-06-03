#pragma once
#include "Effect.h"
class Blood1
	: public Effect
{
public:
	Blood1(const sf::Vector2f& Position, const sf::Texture& Texture, const float ScaleX);
	virtual ~Blood1();
};

