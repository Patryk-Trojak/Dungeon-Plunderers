#pragma once
#include "MenuState.h"
#include "feedback.h"
#include "SettingsState.h"
#include "ShopState.h"
#include "ClassSelectionState.h"
#include "LevelSelectionState.h"
#include "LevelsOfPlayerSelection.h"


class SecondMenuState :
	public MenuState
{
public:
	SecondMenuState(StateData& stateData);
	virtual ~SecondMenuState();
	virtual void update(const float deltaTime) override;
	virtual void updateInput(const float deltaTime) override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override;

private:
	std::unique_ptr<Feedback> feedback;
	void initButtons();
	void handleFunctionalityOfButtons();
	void handleFunctionalityOfMessageBox();
	void makeMessageBoxAreYouSureToExit();
};

