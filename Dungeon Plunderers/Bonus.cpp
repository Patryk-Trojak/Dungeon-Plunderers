#include "pch.h"
#include "Bonus.h"


Bonus::Bonus(const sf::Vector2f& Position, const sf::Texture& Texture, const BonusesTypes name)
	:Movable(sf::Vector2f(0, 400.f)),
	isAbleToFall(true),
	name(name)
{
	bonus.setPosition(Position);
	bonus.setTexture(Texture);
	bonus.setOrigin(Texture.getSize().x / 2, 0);
	hitboxComponent.addHitbox(Hitbox(Position - bonus.getOrigin(), sf::Vector2f(Texture.getSize().x, Texture.getSize().y)));
	if (name == BonusesTypes::shotgunAmmoBox)
		bonus.setColor(sf::Color::Red);
}

Bonus::~Bonus()
{
}

void Bonus::move(const float deltaTime)
{
	if (isAbleToFall)
	{
		if (currentVelocity.y < maxVelocity.y)
		{
			currentVelocity.y += 700 * deltaTime;
		}
		move(currentVelocity * deltaTime);
	}
}

void Bonus::setIsAbleToFall(const bool isAbleToFall)
{
	this->isAbleToFall = isAbleToFall;
}

void Bonus::setPositionY(const float PositionY)
{
	bonus.setPosition(bonus.getPosition().x, PositionY);
	hitboxComponent.setPositionOfHitbox(0, bonus.getPosition() + hitboxComponent[0].getOffset());
}

sf::Vector2f Bonus::getSize() const
{
	return sf::Vector2f(bonus.getTexture()->getSize().x, bonus.getTexture()->getSize().y);
}

void Bonus::move(const sf::Vector2f& offset)
{
	bonus.move(offset);
	hitboxComponent.moveAllHitboxes(offset);
}

void Bonus::setPosition(const sf::Vector2f& position)
{
	bonus.setPosition(position);
	hitboxComponent.setPositionOfHitbox(0, position - bonus.getOrigin());
}

sf::Vector2f Bonus::getPosition() const
{
	return bonus.getPosition();
}

sf::FloatRect Bonus::getGlobalBoundsOfSprite() const
{
	return bonus.getGlobalBounds();
}

BonusesTypes Bonus::getType() const
{
	return name;
}

void Bonus::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(bonus, states);
}

