#pragma once
#include "State.h"

class SupportGameState
	:public State
{
public:
	SupportGameState(StateData& stateData);
	~SupportGameState();
	virtual void update(const float deltaTime) override;
	virtual void handleSFMLEvent(sf::RenderWindow& window, sf::Event& event) override;
private:
	virtual void updateInput(const float deltaTime) override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	sf::Text text;
};

