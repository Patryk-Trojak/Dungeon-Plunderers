#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "HitboxComponent.h"


enum class BlocksTypes {
	brick,
	dirt,
	concrete,
	granite
};

class Block
{
public:
	Block(const sf::Vector2f& Position, const sf::Vector2f& Size, const BlocksTypes name);
	Block(const sf::Vector2f& Position, const sf::Vector2f& Size, const BlocksTypes name, const sf::Vector2f& Velocity, const sf::Vector2f& MaxDistanceOfMoving);

	virtual ~Block();
	void move(float deltaTime);
	void setColor(const sf::Color& Color);
	sf::Color getColor() const;
	HitboxComponent hitboxComponent;
	sf::Vector2f getPosition() const;
	sf::Vector2f getSize() const;
	sf::Vector2f getVelocity() const;
	BlocksTypes getType() const;

	float right() const;
	float left() const;
	float top() const;
	float bottom() const;

	void drawHb(sf::RenderTarget& target);

protected:
	BlocksTypes name;
	sf::Vector2f position;
	sf::Vector2f size;
	sf::Vector2f velocity;
	sf::Vector2f changeDirectionDistance;
	sf::Vector2f distanceMoved;
	sf::Color color;
	void move(const sf::Vector2f& offset);
};
