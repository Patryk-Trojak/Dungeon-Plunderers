#pragma once
#include<SFML/Graphics.hpp>
#include "Movable.h"
#include "HitboxComponent.h"

enum class BonusesTypes {
	healthPotion,
	manaPotion,
	rifleAmmoBox,
	shotgunAmmoBox
};

class Bonus
	:public sf::Drawable,
	public Movable
{
public:
	Bonus(const sf::Vector2f& Position, const sf::Texture& Texture, const BonusesTypes name);
	virtual ~Bonus();
	HitboxComponent hitboxComponent;
	virtual void move(const float deltaTime) override;
	void setIsAbleToFall(const bool isAbleToFall);
	void setPositionY(const float PositionY);
	sf::Vector2f getSize() const;
	void move(const sf::Vector2f& offset);
	void setPosition(const sf::Vector2f& position);
	sf::Vector2f getPosition() const;
	sf::FloatRect getGlobalBoundsOfSprite() const;
	BonusesTypes getType() const;
private:
	sf::Sprite bonus;
	BonusesTypes name;
	bool isAbleToFall;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
