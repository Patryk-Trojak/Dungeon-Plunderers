#pragma once
#include "State.h"
#include "TextButton.h"
#include "Feedback.h"
#include "Animation.h"
#include "PersistenceSaver.h"
#include "PersistenceLoader.h"

bool& getShowHitboxes();

class ClassSelectionState
	:public State
{
public:
	ClassSelectionState(StateData& stateData);
	~ClassSelectionState();
	virtual void update(const float deltaTime) override;
	virtual void handleSFMLEvent(sf::RenderWindow& window, sf::Event& event) override;

private:
	virtual void updateInput(const float deltaTime) override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	TextButton chooseStormtrooper;
	TextButton chooseWizard;

	sf::Sprite stormtrooper;
	sf::Sprite wizard;	
	
	sf::Sprite stormtrooperArm;
	sf::Sprite wizardArm;
	void updatePositionWizardArm();

	sf::Sprite handgun;
	sf::Sprite wand;

	Animation stormtrooperAnimation;
	Animation wizardAnimation;
	std::unique_ptr<Feedback> feedback;

	//temp
	sf::RectangleShape showHitboxes;
};

