#pragma once
#include "Player.h"
#include "TextureHolder.h"
#include "PlayerData.h"
#include "Wand.h"

class WizardOnCloud :
	public Player
{
public:
	WizardOnCloud(const sf::Vector2f& Position, const Keybinds& keybinds,
		const Resources& resources, const PlayerData& PlayerData);
	virtual ~WizardOnCloud();
	virtual void matchHitboxesToAnimation() override;
	virtual void handleGettingBonus(BonusesTypes name) override;
	HitboxComponent shieldHitboxes;
	HitboxComponent cloudHitboxes;
	void addShieldHp(const int value);
	void addCloudHp(const int value);
	int getShieldHp() const;
	int getCloudHp() const;	
	int getInitialShieldHp() const;
	int getInitialCloudHp() const;
	bool hasShield() const;
	virtual void setPosition(const sf::Vector2f& Position);
	virtual void setPositionRelativeToHitbox(const sf::Vector2f& Position);
private:
	void move(const float deltaTime) override;
	sf::Sprite cloud;
	sf::Sprite shield;
	Animation shieldAnimation;

	std::shared_ptr<Wand> shadowWand;
	int mana{100000};

	int shieldHp;
	int cloudHp;

	int initialShieldHp;
	int initialCloudHp;

	bool HasShield;

	virtual void setCurrentVelocityX(const float deltaTime) override;
	virtual void setCurrentVelocityY(const float deltaTime) override;
	virtual void animate(const float deltaTime) override;
	virtual void setPositionOfArm() override;
	virtual void setCurrentWeapon() override;
	virtual void handleDrinkingPotions() override;
	virtual void setPositionOfHitboxes() override;
	virtual void setScaleOfPlayer(const sf::Vector2f& MousePosition) override;
	virtual void setRotationOfArm(const sf::Vector2f& MousePosition) override;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

