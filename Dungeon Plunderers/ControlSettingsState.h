#pragma once
#include "State.h"
#include "TextButton.h"
#include "Messagebox.h"
#include "SettingsState.h"


class ControlSettingsState :
	public State
{
public:
	ControlSettingsState(StateData& stateDataconst, int numberOfStatesPopToBackMenu = 1);
	~ControlSettingsState();
	virtual void update(const float deltaTime) override;
	virtual void handleSFMLEvent(sf::RenderWindow& window, sf::Event& event) override;

private:
	virtual void updateInput(const float deltaTime) override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	std::map<int, std::string> supportedKeys;
	void initSupportedKeys();
	bool isChangingKey;
	int whatKeyChange;
	std::vector<TextButton> znfoButtons;
	std::vector<TextButton> buttonsChangingControl;
	void setPositionOfButtons();
	TextButton resetButton;
	TextButton informationAboutChangingKey;
	sf::Text DefaultAndCurrentKey;
	std::unique_ptr<game::MessageBox> messageBoxAreYouSureToResetControl;
	Keybinds defaultKeybinds;
	void setTextOfButtonsChangingControl();
	void makeMessageBoxAreYouSureToResetControl();
	TextButton generalSettings;
	TextButton controlSettings;
	int numberOfStatesPopToBackMenu;
};
