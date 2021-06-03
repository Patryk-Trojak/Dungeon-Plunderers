#pragma once
#include "Player.h"
#include "Handgun.h"
#include "Rifle.h"
#include "Shotgun.h"
#include "PlayerData.h"

enum class WeaponsOfStormtrooper
{
	handgun = 1,
	rifle,
	shotgun
};

class Stormtrooper :
	public Player
{
public:
	Stormtrooper(const sf::Vector2f& Position, const Keybinds& keybinds,
		const Resources& resources, const PlayerData& PlayerData);
	virtual ~Stormtrooper();
	std::string getAmmo() const;
	int getCurrentNumberOfHealthPotions() const;
	void addNumberOfHealthPotions(int value = 1);
	virtual void matchHitboxesToAnimation();
	virtual void handleGettingBonus(BonusesTypes name) override;
	void addCurrentRifleAmmo(int value);
	void addCurrentShotgunAmmo(int value);
private:
	std::shared_ptr<Handgun> handgun;
	std::shared_ptr<Rifle> rifle;
	std::shared_ptr<Shotgun> shotgun;
	WeaponsOfStormtrooper nameOfCurrentWeapon;
	virtual void setCurrentVelocityX(const float deltaTime) override;
	virtual void setCurrentVelocityY(const float deltaTime) override;
	virtual void animate(const float deltaTime) override;
	virtual void setPositionOfArm() override;
	virtual void setCurrentWeapon() override;
	virtual void handleDrinkingPotions() override;

	int numberOfHealthPotions;
	bool isKeyDrinkHealhtPotionReleased;
	float lastTimeOfJump{ 0 };

};


