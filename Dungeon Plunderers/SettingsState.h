#pragma once
#include "State.h"
#include "TextButton.h"
#include "Messagebox.h"
#include "Slider.h"
#include "Textbox.h"
#include "DropDownList.h"
#include "ControlSettingsState.h"



class SettingsState:
	public State
{
public:
	SettingsState(StateData& stateData, const int numberOfStatesPopToBackMenu = 1);
	~SettingsState();
	virtual void update(const float deltaTime) override;
	virtual void handleSFMLEvent(sf::RenderWindow& window, sf::Event& event) override;

private:
	virtual void updateInput(const float deltaTime) override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	sf::Vector2f positionOfFirstButton;
	DropDownList colorOfFPS;
	DropDownList positionOfFPS;
	std::vector<TextButton> textButton;
	std::vector<TextButton> settingsButton;

	std::vector<Textbox> advancedColorsOfFPS;
	std::vector<Textbox> sizesOfFPS;

	std::vector<sf::Text> RGBA;
	TextButton reseterGeneralSettings;
	std::unique_ptr<game::MessageBox> areYouSureToResetSettings;
	void createAdvancedFPSSettings();
	void deleteAdvancedFPSSettings();
	void setPositionOfButtons();
	Textbox maxFPS;
	void resetGeneralSettings(sf::RenderWindow& window);

	TextButton generalSettings;
	TextButton controlSettings;

	void setColorToList();
	int numberOfStatesPopToBackMenu;

};
