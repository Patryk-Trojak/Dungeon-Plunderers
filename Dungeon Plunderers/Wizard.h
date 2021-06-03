#pragma once
#include "Player.h"
#include "Handgun.h"
#include "Resources.h"
#include "PlayerData.h"
#include "Wand.h"


class Wizard :
	public Player
{
public:
	Wizard(const sf::Vector2f& Position, const Keybinds& keybinds,
		 const Resources& resources, const PlayerData& PlayerData);
	virtual ~Wizard();
	virtual void matchHitboxesToAnimation() override;
	virtual void handleGettingBonus(BonusesTypes name) override;
	int getCurrentNumberOfHealthPotions() const;
	void addNumberOfHealthPotions(int value = 1);	
	int getCurrentNumberOfManaPotions() const;
	void addNumberOfManaPotions(int value = 1);
	int getMana() const;
	int getInitialMana() const;
private:
	std::shared_ptr<Wand> basicWand;
	std::shared_ptr<Wand> fireWand;
	std::shared_ptr<Wand> iceWand;
	virtual void setCurrentVelocityX(const float deltaTime) override;
	virtual void setCurrentVelocityY(const float deltaTime) override;
	virtual void animate(const float deltaTime) override;
	virtual void setPositionOfArm() override;
	virtual void setCurrentWeapon() override;
	virtual void handleDrinkingPotions() override;
	virtual void setScaleOfPlayer(const sf::Vector2f& MousePosition) override;
	virtual void setRotationOfArm(const sf::Vector2f& MousePosition) override;

	int mana;
	int initialMana;
	float lastTimeOfJump{ 0 };
	int numberOfHealthPotions;
	bool isKeyDrinkHealhtPotionReleased;
	int numberOfManaPotions;
	bool isKeyDrinkManaPotionReleased;
};


