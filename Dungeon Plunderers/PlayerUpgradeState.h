#pragma once
#include <vector>
#include <unordered_map>
#include "State.h"
#include "Handgun.h"
#include "Feedback.h"
#include "ShopButton.h"
#include "PlayerData.h"
#include "TextButton.h"

class PlayerUpgradeState
	: public State
{
public:
	PlayerUpgradeState(StateData& stateData);
	virtual ~PlayerUpgradeState();
	virtual void update(const float deltaTime) override;
	virtual void updateInput(const float deltaTime) override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
	virtual void handleSFMLEvent(sf::RenderWindow& window, sf::Event& event) override;

protected:
	PlayerData& playerData;
	std::unordered_map<UpgradeName, ShopButton> upgradeButtons;
	void initButtons();
	TextButton additionalInformationAboutButtons;
	TextButton resetUpgradesBought;
	std::unique_ptr<Feedback> feedback;

	virtual void savePlayerData() = 0;
	void handleUpgrading();
	void handleDowngrading();
	virtual void tryBoostUpgrade(UpgradeName upgradeName);
	virtual void tryDecreaseUpgrade(UpgradeName upgradeName);
	virtual void resetAllUpgrade();
	void handleResetingAllUpgrades();
	void setTextOfAdditionalInformation(UpgradeName upgradeName);
	void handleShowingAdditionalInformation();
	bool drawAdditionalInformation{ false };


	void drawUpgradeButtons(sf::RenderTarget& target, sf::RenderStates state) const;
	void updateUpgradeButtons(float deltaTime);

	std::array<sf::Text, 4> texts;
	void drawTexts(sf::RenderTarget& target, sf::RenderStates state) const;
	void initTexts();


	std::array<sf::Sprite, 8> weapons;
	void drawWeapons(sf::RenderTarget& target, sf::RenderStates state) const;
	void initWeaponsSprites();

	std::array<sf::Sprite, 4> backgrounds;
	void initBackgrounds();
	void drawBackgrounds(sf::RenderTarget& target, sf::RenderStates state) const;

	virtual bool isAbleToBoostUpgrade(UpgradeName upgradeName) const;
	bool isAbleToDecreaseUpgrade(UpgradeName upgradeName) const;
	bool isUpgradeMaxed(UpgradeName upgradeName) const;
	virtual void makeFeedbackWhyIsNotAbleToBoostUpgrade(UpgradeName upgradeName);
	void makeFeedbackWhyIsNotAbleToDecreaseUpgrade(UpgradeName upgradeName);
};

