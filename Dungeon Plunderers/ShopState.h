#pragma once
#include "PlayerUpgradeState.h"
#include "MoneyHUD.h"
#include "WeaponOfHelicopter.h"

class ShopState :
	public PlayerUpgradeState
{
public:
	ShopState(StateData& stateData);
	virtual ~ShopState();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
	void update(const float deltaTime) override;
private:
	MoneyHUD moneyHUD;

	virtual void savePlayerData() override;

	virtual void tryBoostUpgrade(UpgradeName upgradeName);
	virtual void tryDecreaseUpgrade(UpgradeName upgradeName);
	virtual void makeFeedbackWhyIsNotAbleToBoostUpgrade(UpgradeName upgradeName);
	virtual void resetAllUpgrade();

	bool isAbleToBoostUpgrade(UpgradeName upgradeName) const override;

	
	WeaponOfHelicopter weaponOfHelicopter;

	void handleShooting(float deltaTime);
	void updateRotationWeapon();

	std::vector<std::unique_ptr<PlayerProjectile>> projectiles;
	void eraseProjectiles();

	bool hasEnoughMoneyToBuyUpgrade(UpgradeName upgradeName) const;
	int makePriceOfUpgrade(int numberOfUpgrade);
};

