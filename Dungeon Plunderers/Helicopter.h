#pragma once
#include "Player.h"
#include "WeaponOfHelicopter.h"


class Helicopter :
	public Player
{
public:
	Helicopter(const sf::Vector2f& Position, const Keybinds& keybinds,
		const Resources& resources, const PlayerData& PlayerData);
	virtual ~Helicopter();
	virtual void matchHitboxesToAnimation() override;
	virtual void handleGettingBonus(BonusesTypes name) override;

private:
	virtual void setCurrentVelocityX(const float deltaTime) override;
	virtual void setCurrentVelocityY(const float deltaTime) override;
	virtual void animate(const float deltaTime) override;
	virtual void setPositionOfArm() override;
	virtual void setCurrentWeapon() override;
	virtual void handleDrinkingPotions() override;
	virtual void setRotationOfArm(const sf::Vector2f& MousePosition);
	virtual void setScaleOfPlayer(const sf::Vector2f& MousePosition);
}; 


