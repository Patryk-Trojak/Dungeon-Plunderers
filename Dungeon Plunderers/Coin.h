#pragma once
#include<SFML/Graphics.hpp>
#include "HitboxComponent.h"
#include "AnimationComponent.h"
#include "Block.h"


class Coin
	: public sf::Drawable
{
public:
	Coin(const sf::Vector2f& Position, const sf::Texture& Texture);
	virtual ~Coin();
	HitboxComponent hitboxComponent;
	HitboxComponent base;
	sf::Vector2f getPosition() const;
	void setPosition(const sf::Vector2f& Position);
	void animate(const float deltaTime);
	sf::FloatRect getGlobalBoundsOfSprite() const;
	std::unique_ptr<Coin> clone() const;
	void setBlockWhichItsStandingOn(std::vector<Block>::const_iterator& block);
	virtual void moveWithBlock(float deltaTime);

private:
	sf::Sprite coin;
	Animation animation;
	std::vector<Block>::const_iterator blockItsStandingOn;
	bool isStandingOnBlock{ false };

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

