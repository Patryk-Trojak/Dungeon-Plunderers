#pragma once
#include "State.h"
#include <Chrono>

class LoadDataState
	: public State
{
public:
	LoadDataState(StateData& stateData);
	virtual ~LoadDataState();
	virtual void handleSFMLEvent(sf::RenderWindow& window, sf::Event& event) override;
	virtual void update(const float deltaTime) override;
protected:
	void loadAllTextures();
	void loadKeybinds();
	void loadSettings();

	virtual void updateInput(const float deltaTime) override;

	std::unique_ptr<sf::Texture> loadTexture(const std::string& filepath, const bool repeated = false, const sf::IntRect& area = sf::IntRect());

	virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
};

