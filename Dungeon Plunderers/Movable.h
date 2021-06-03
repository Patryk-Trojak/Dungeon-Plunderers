#pragma once
#include <SFML/Graphics.hpp>
class Movable
{
public:
	Movable(const sf::Vector2f& maxVelocity);
	~Movable();
	virtual void move(const float deltaTime) = 0;
	const sf::Vector2f& getInitialVelocity() const;
protected:
	sf::Vector2f currentVelocity;
	sf::Vector2f maxVelocity;
	sf::Vector2f initialVelocity;
};

