#pragma once
#include "Effect.h"

class Fire
	: public Effect
{
public:
	Fire(const sf::Vector2f& Position, const sf::Texture& Texture);
	virtual ~Fire();
};
