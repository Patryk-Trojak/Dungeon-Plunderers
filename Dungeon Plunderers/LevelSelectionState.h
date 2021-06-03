#pragma once
#include <functional>
#include <unordered_map>
#include <vector>
#include "State.h"
#include "TextButton.h"
#include "GameplayState.h"
#include "Coin.h"
#include "Enemy.h"
#include "DeadlyFlower.h"
#include "LevelEditorState.h"
#include "Skeleton.h"
#include "Zombie.h"
#include "Fly.h"
#include "DeadlyFlowerBoss.h"
#include "SkeletonBoss.h"
#include "ZombieBoss.h"
#include "GunEnemy.h"
#include "Spikes.h"



class LevelSelectionState
	:public State
{
public:
	LevelSelectionState(StateData& stateData);
	virtual ~LevelSelectionState();
	virtual void update(const float deltaTime) override;
	virtual void handleSFMLEvent(sf::RenderWindow& window, sf::Event& event) override;
private:
	virtual void updateInput(const float deltaTime) override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	std::map<LevelName, TextButton> buttons;

	void handleFunctionalityOfButtons();
	void drawButtons(sf::RenderTarget& target, sf::RenderStates states) const;
	std::function<Level(const Resources& resources)> createCurrentLevel;
	Level createdLevel;
};

