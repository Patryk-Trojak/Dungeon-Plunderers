#pragma once
#include "State.h"
#include "MessageBox.h"


class MenuState :
	public State
{
public:
	MenuState(StateData& stateData);
	virtual ~MenuState();
	virtual void handleSFMLEvent(sf::RenderWindow& window, sf::Event& event) override;

protected:
	std::map < std::string, TextButton > buttons;
	std::unique_ptr<game::MessageBox> MessageBoxAreYouSureToExit;
	void updateButtons();
	void drawButtons(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void makeMessageBoxAreYouSureToExit() = 0;

};	

