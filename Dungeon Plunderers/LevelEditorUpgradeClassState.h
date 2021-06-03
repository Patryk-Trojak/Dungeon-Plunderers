#pragma once
#include "PlayerUpgradeState.h"


class LevelEditorUpgradeClassState :
	public PlayerUpgradeState
{
public:
	LevelEditorUpgradeClassState(StateData& stateData);
	virtual ~LevelEditorUpgradeClassState();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
	virtual void handleSFMLEvent(sf::RenderWindow& window, sf::Event& event) override;
	virtual void update(const float deltaTime) override;

private:
	TextButton stormtrooper;
	TextButton wizard;
	void handleChangingClass();
	void updateColorOfClassButtonDependingOnChosenClass();
	virtual void savePlayerData() override;

	bool drawAdditionalInformation{ false };
};

