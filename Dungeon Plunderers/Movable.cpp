#include "pch.h"
#include "Movable.h"

Movable::Movable(const sf::Vector2f& maxVelocity)
	:maxVelocity(maxVelocity),
	currentVelocity(sf::Vector2f(0, 0))
{
	
}

Movable::~Movable()
{
}

const sf::Vector2f& Movable::getInitialVelocity() const
{
	return initialVelocity;
}
