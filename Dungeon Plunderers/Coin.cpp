#include "pch.h"
#include "Coin.h"

Coin::Coin(const sf::Vector2f& Position, const sf::Texture& Texture)
	: //coins(Texture, sf::IntRect(0, 0, 67, 67)),
	  animation(1, 1, sf::Vector2i(50, 50), 6, 0.1f)
{
	coin.setPosition(Position);
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(50, 50)));
	coin.setTexture(Texture);
	coin.setTextureRect(sf::IntRect(0, 0, 67, 67));
	coin.setOrigin(25.f, 25.f);
	base.addHitbox(Hitbox(Position, sf::Vector2f(20, 2), sf::Vector2f(0.f - 25.f, 50.f / 2 + 2.f)));
	base.addHitbox(Hitbox(Position, sf::Vector2f(20, 2), sf::Vector2f(15.f - 25.f, 50.f / 2 + 2.f)));
	base.addHitbox(Hitbox(Position, sf::Vector2f(20, 2), sf::Vector2f(30.f - 25.f, 50.f / 2 + 2.f)));
	animation.setFrame(coin, 1);
}

Coin::~Coin()
{
}

sf::Vector2f Coin::getPosition() const
{
	return coin.getPosition();
}

void Coin::setPosition(const sf::Vector2f& Position)
{
	coin.setPosition(Position);
	hitboxComponent.setPositionOfHitbox(0, Position);
}

void Coin::animate(const float deltaTime)
{
	animation.play(coin, deltaTime);
}

sf::FloatRect Coin::getGlobalBoundsOfSprite() const
{
	return coin.getGlobalBounds();
}

std::unique_ptr<Coin> Coin::clone() const
{
	return std::make_unique<Coin>(*this);
}

void Coin::setBlockWhichItsStandingOn(std::vector<Block>::const_iterator& block)
{
	isStandingOnBlock = true;
	blockItsStandingOn = block;
}

void Coin::moveWithBlock(float deltaTime)
{
	if (isStandingOnBlock)
	{
		coin.move(blockItsStandingOn->getVelocity() * deltaTime);
	}
}

void Coin::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(coin, states);
	target.draw(base.getHitboxes()[0]);
}
