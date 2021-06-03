#pragma once
#include "Effect.h"

class FireExplosion
	: public Effect
{
public:
	FireExplosion(const sf::Vector2f& Position, const sf::Texture& Texture);
	virtual ~FireExplosion();
};

