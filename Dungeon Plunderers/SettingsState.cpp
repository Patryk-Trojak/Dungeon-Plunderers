#include "pch.h"
#include "SettingsState.h"


SettingsState::SettingsState(StateData& stateData, const int numberOfStatesPopToBackMenu)
	: State(stateData),
	numberOfStatesPopToBackMenu(numberOfStatesPopToBackMenu),
	positionOfFirstButton(96, 315),
	textButton{
	TextButton(positionOfFirstButton, sf::Vector2f(864, 50),
		stateData.resources[TextureID::SaveButton], stateData.resources.font,
		L"Fullscreen", 40),
	TextButton(positionOfFirstButton + sf::Vector2f(0.f, 50.f), sf::Vector2f(864, 50),
		stateData.resources[TextureID::SaveButton], stateData.resources.font,
		L"Zmieniaj wielkoœæ okna proporcjonalnie", 40),
	TextButton(positionOfFirstButton + sf::Vector2f(0.f, 100.f), sf::Vector2f(864, 50),
		stateData.resources[TextureID::SaveButton], stateData.resources.font,
		L"Synchronizacja pionowa", 40),
	TextButton(positionOfFirstButton + sf::Vector2f(0.f, 150.f), sf::Vector2f(864, 50),
		stateData.resources[TextureID::SaveButton], stateData.resources.font,
		L"Limit FPS", 40),
	TextButton(positionOfFirstButton + sf::Vector2f(0.f, 200.f), sf::Vector2f(864, 50),
		stateData.resources[TextureID::SaveButton], stateData.resources.font,
		L"Maks FPS", 40),
	TextButton(positionOfFirstButton + sf::Vector2f(0.f, 250.f), sf::Vector2f(864, 50),
		stateData.resources[TextureID::SaveButton], stateData.resources.font,
		L"Pokazywac FPS", 40),
	TextButton(positionOfFirstButton + sf::Vector2f(0.f, 300.f), sf::Vector2f(864, 50),
		stateData.resources[TextureID::SaveButton], stateData.resources.font,
		L"Kolor FPS (RGBA)", 40),
	TextButton(positionOfFirstButton + sf::Vector2f(0.f, 350.f), sf::Vector2f(864, 50),
		stateData.resources[TextureID::SaveButton], stateData.resources.font,
		L"Pozycja FPS", 40),
	TextButton(positionOfFirstButton + sf::Vector2f(0.f, 400.f), sf::Vector2f(864, 50),
		stateData.resources[TextureID::SaveButton], stateData.resources.font,
		L"Zaawansowane ustawienia FPS", 40)
},
	settingsButton{
		TextButton(positionOfFirstButton + sf::Vector2f(864.f, 0.f), sf::Vector2f(432, 50),
			stateData.resources[TextureID::GreyButton750x86], stateData.resources.font,
			L"W³acz", 40),
		TextButton(positionOfFirstButton + sf::Vector2f(1296.f, 0.f), sf::Vector2f(432, 50),
			stateData.resources[TextureID::GreyButton750x86], stateData.resources.font,
			L"Wy³¹cz", 40),
		TextButton(positionOfFirstButton + sf::Vector2f(864.f, 50.f), sf::Vector2f(432, 50),
			stateData.resources[TextureID::GreyButton750x86], stateData.resources.font,
			L"W³acz", 40),
		TextButton(positionOfFirstButton + sf::Vector2f(1296.f, 50.f), sf::Vector2f(432, 50),
			stateData.resources[TextureID::GreyButton750x86], stateData.resources.font,
			L"Wy³¹cz", 40),
		TextButton(positionOfFirstButton + sf::Vector2f(864.f, 100.f), sf::Vector2f(432, 50),
			stateData.resources[TextureID::GreyButton750x86], stateData.resources.font,
			L"W³acz", 40),
		TextButton(positionOfFirstButton + sf::Vector2f(1296.f, 100.f), sf::Vector2f(432, 50),
			stateData.resources[TextureID::GreyButton750x86], stateData.resources.font,
			L"Wy³¹cz", 40),
		TextButton(positionOfFirstButton + sf::Vector2f(864.f, 150.f), sf::Vector2f(432, 50),
			stateData.resources[TextureID::GreyButton750x86], stateData.resources.font,
			L"W³acz", 40),
		TextButton(positionOfFirstButton + sf::Vector2f(1296.f, 150.f), sf::Vector2f(432, 50),
			stateData.resources[TextureID::GreyButton750x86], stateData.resources.font,
			L"Wy³¹cz", 40),
		TextButton(positionOfFirstButton + sf::Vector2f(864.f, 250.f), sf::Vector2f(432, 50),
			stateData.resources[TextureID::GreyButton750x86], stateData.resources.font,
			L"W³acz", 40),
		TextButton(positionOfFirstButton + sf::Vector2f(1296.f, 250.f), sf::Vector2f(432, 50),
			stateData.resources[TextureID::GreyButton750x86], stateData.resources.font,
			L"Wy³¹cz", 40),
		TextButton(positionOfFirstButton + sf::Vector2f(864.f, 400.f), sf::Vector2f(432, 50),
			stateData.resources[TextureID::GreyButton750x86], stateData.resources.font,
			L"W³acz", 40),
		TextButton(positionOfFirstButton + sf::Vector2f(1296.f, 400.f), sf::Vector2f(432, 50),
			stateData.resources[TextureID::GreyButton750x86], stateData.resources.font,
			L"Wy³¹cz", 40),
	},
	maxFPS(positionOfFirstButton + sf::Vector2f(864.f, 200.f), sf::Vector2f(864, 50), stateData.resources[TextureID::GreyButton750x86], stateData.resources.font, std::to_string(stateData.settings.maxFPS), 40, std::vector<sf::Uint32>(), ContentAlignment::center),
	colorOfFPS(positionOfFirstButton + sf::Vector2f(864.f, 300.f), sf::Vector2f(864, 50), L"Pomarañczowy", stateData.resources[TextureID::GreyButton750x86], stateData.resources.font, 40),
	positionOfFPS(positionOfFirstButton + sf::Vector2f(864.f, 350.f), sf::Vector2f(864, 50), L"Lewy górny", stateData.resources[TextureID::GreyButton750x86], stateData.resources.font, 40),
	reseterGeneralSettings(positionOfFirstButton + sf::Vector2f(1296.f, 450.f), sf::Vector2f(432, 50),
	stateData.resources[TextureID::GreyButton750x86], stateData.resources.font,
	L"Przywróæ ustawienia domyœlne", 40),
	controlSettings(sf::Vector2f(960, 50.f), sf::Vector2f(300, 50),
		stateData.resources[TextureID::GreyButton750x86], stateData.resources.font,
		L"Sterowanie", 40),
	generalSettings(sf::Vector2f(660, 50.f), sf::Vector2f(300, 50),
		stateData.resources[TextureID::GreyButton750x86], stateData.resources.font,
		L"Ogólne", 40)
{
	colorOfFPS.addOption(L"Niebieski");
	colorOfFPS.addOption(L"Czerwony");
	colorOfFPS.addOption(L"Zielony");

	positionOfFPS.addOption(L"Lewy dolny");
	positionOfFPS.addOption(L"Prawy górny");
	positionOfFPS.addOption(L"Prawy dolny");

	setColorToList();
}

SettingsState::~SettingsState()
{
}

void SettingsState::update(const float deltaTime)
{
	if (!areYouSureToResetSettings)
	{
		generalSettings.update(mousePositionView);
		controlSettings.update(mousePositionView);
		generalSettings.setCurrentColor(sf::Color::Red);
		if (controlSettings.wasPressed(mousePositionView, wasMousePressed))
			stateData.states.push(std::make_unique<ControlSettingsState>(stateData, numberOfStatesPopToBackMenu + 1));

		for (auto& i : settingsButton)
			i.update(mousePositionView);

		for (auto& i : advancedColorsOfFPS)
			i.update(mousePositionView, wasMousePressed, deltaTime);
		if(!stateData.settings.isVerticalSyncEnabled)
			maxFPS.update(mousePositionView, wasMousePressed, deltaTime);
		for (auto& i : sizesOfFPS)
			i.update(mousePositionView, wasMousePressed, deltaTime);
	
		if (stateData.settings.fullscreen)
			settingsButton[0].setCurrentColor(sf::Color::Red);
		else
			settingsButton[1].setCurrentColor(sf::Color::Red);
	
		if (stateData.settings.resizeProportionally)
			settingsButton[2].setCurrentColor(sf::Color::Red);
		else
			settingsButton[3].setCurrentColor(sf::Color::Red);

		if (stateData.settings.isVerticalSyncEnabled)
		{
			settingsButton[4].setCurrentColor(sf::Color::Red);
			stateData.settings.isLimitFPSEnabled = false;
			settingsButton[6].setCurrentColor(sf::Color(50, 50, 50));
			settingsButton[7].setCurrentColor(sf::Color(50, 50, 50));

			maxFPS.setColor(sf::Color(50, 50, 50));
		}
		else
		{
			settingsButton[5].setCurrentColor(sf::Color::Red);
			maxFPS.setColor(sf::Color(255, 255, 255));
		}

		if(stateData.settings.showFPS)
			settingsButton[8].setCurrentColor(sf::Color::Red);
		else
			settingsButton[9].setCurrentColor(sf::Color::Red);

		if (settingsButton.size() > 12)
		{
			settingsButton[10].setCurrentColor(sf::Color::Red);

			if (stateData.settings.showOutlineFPS)
				settingsButton[12].setCurrentColor(sf::Color::Red);
			else
				settingsButton[13].setCurrentColor(sf::Color::Red);
		}
		else
			settingsButton[11].setCurrentColor(sf::Color::Red);


		if (stateData.settings.isLimitFPSEnabled)
			settingsButton[6].setCurrentColor(sf::Color::Red);
		else if(!stateData.settings.isVerticalSyncEnabled)
			settingsButton[7].setCurrentColor(sf::Color::Red);
	
		reseterGeneralSettings.update(mousePositionView);
		updateBackToPreviousState();
	}
	
	if (WereSettingsChanged)
		PersistenceSaver::save(stateData.settings);
}

void SettingsState::handleSFMLEvent(sf::RenderWindow& window, sf::Event& event)
{
	WereSettingsChanged = false;
	wasMousePressed = false;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
		
		resizeWindowProportionally(window, event);
		

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				if (!areYouSureToResetSettings)
					numberOfStatesPop = numberOfStatesPopToBackMenu;
				else
					areYouSureToResetSettings.reset();
			}
			if (event.key.code == sf::Keyboard::Enter)
			{
				if (!areYouSureToResetSettings)
				{		
					if (maxFPS.isActive() and !stateData.settings.isVerticalSyncEnabled and stateData.settings.isLimitFPSEnabled)
					{
						stateData.settings.maxFPS = std::stoi(maxFPS.getText());
						window.setFramerateLimit(stateData.settings.maxFPS);
						WereSettingsChanged = true;
					}
					if(maxFPS.isActive())
						maxFPS.setActive(false);
					for (auto & i : advancedColorsOfFPS)
					{
						if (i.isActive())
						{
							stateData.settings.colorOfFPS = sf::Color(std::stoi(advancedColorsOfFPS[0].getText()), std::stoi(advancedColorsOfFPS[1].getText()), std::stoi(advancedColorsOfFPS[2].getText()), std::stoi(advancedColorsOfFPS[3].getText()));
							stateData.settings.colorOfOutlineFPS = sf::Color(std::stoi(advancedColorsOfFPS[4].getText()), std::stoi(advancedColorsOfFPS[5].getText()), std::stoi(advancedColorsOfFPS[6].getText()), std::stoi(advancedColorsOfFPS[7].getText()));
							setColorToList();
							i.setActive(false);
							WereSettingsChanged = true;
							break;
						}
					}
					for (auto & i : sizesOfFPS)
					{
						if (i.isActive())
						{
							stateData.settings.characterSizeOfFPS = std::stoi(sizesOfFPS[0].getText());
							stateData.settings.outlineThickness = std::stoi(sizesOfFPS[1].getText());
							i.setActive(false);
							WereSettingsChanged = true;
							break;
						}
					}
				}
				else
				{
					resetGeneralSettings(window);
					areYouSureToResetSettings.reset();
				}
			}
		}

		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
				wasMousePressed = true;

			if (!areYouSureToResetSettings)
			{
				if (maxFPS.isActive() and !stateData.settings.isVerticalSyncEnabled and stateData.settings.isLimitFPSEnabled)
				{
					stateData.settings.maxFPS = std::stoi(maxFPS.getText());
					maxFPS.setActive(false);
					window.setFramerateLimit(stateData.settings.maxFPS);
				}
				for (auto & i : advancedColorsOfFPS)
				{
					if (i.isActive())
					{
						stateData.settings.colorOfFPS = sf::Color(std::stoi(advancedColorsOfFPS[0].getText()), std::stoi(advancedColorsOfFPS[1].getText()), std::stoi(advancedColorsOfFPS[2].getText()), std::stoi(advancedColorsOfFPS[3].getText()));
						stateData.settings.colorOfOutlineFPS = sf::Color(std::stoi(advancedColorsOfFPS[4].getText()), std::stoi(advancedColorsOfFPS[5].getText()), std::stoi(advancedColorsOfFPS[6].getText()), std::stoi(advancedColorsOfFPS[7].getText()));
						setColorToList();
						i.setActive(false);
						WereSettingsChanged = true;
						break;
					}
				}
				for (auto & i : sizesOfFPS)
				{
					if (i.isActive())
					{
						stateData.settings.characterSizeOfFPS = std::stoi(sizesOfFPS[0].getText());
						stateData.settings.outlineThickness = std::stoi(sizesOfFPS[1].getText());
						WereSettingsChanged = true;
						i.setActive(false);
						break;
					}
				}
			}
			
		}
		if (event.type == sf::Event::TextEntered)
		{
			if (!areYouSureToResetSettings)
			{
				if ((event.text.unicode >= 48 and event.text.unicode <= 57) or event.text.unicode == 8) // only numbers and backspace
				{
					if (maxFPS.isActive() and !stateData.settings.isVerticalSyncEnabled)
					{
						maxFPS.handleTextEntered(event.text.unicode);
						if (maxFPS.getText().size() > 4)
							maxFPS.setText("9999");
					}
					for (auto& i : advancedColorsOfFPS)
					{
						if (i.isActive())
						{
							if (i.getText() == "0")
								i.setText("");
							i.handleTextEntered(event.text.unicode);
							if (i.getText() == "")
								i.setText("0");

							if (i.getText().size() == 3)
							{
								if (std::stoi(i.getText()) > 255)
									i.setText("255");
							}
							if (i.getText().size() >= 4)
								i.setText("255");
						}
					}
					for (auto& i : sizesOfFPS)
					{
						if (i.isActive())
						{
							if (i.getText() == "0")
								i.setText("");
							i.handleTextEntered(event.text.unicode);
							if (i.getText() == "")
								i.setText("0");
						}
					}
					if (!sizesOfFPS.empty())
					{
						if (std::stoi(sizesOfFPS[0].getText()) > 100)
							sizesOfFPS[0].setText("100");
						if (std::stoi(sizesOfFPS[1].getText()) > 10)
							sizesOfFPS[1].setText("10");
					}
					
				}
			}
		
		}
	}
	if (!areYouSureToResetSettings)
	{
		colorOfFPS.update(mousePositionView, wasMousePressed);
		if (colorOfFPS.wasNewOptionChosen())
		{
			switch (colorOfFPS.getNumberOfChosenOption())
			{
			case 0:
				stateData.settings.colorOfFPS = sf::Color(255, 116, 0);
				break;
			case 1:
				stateData.settings.colorOfFPS = sf::Color(0, 0, 255);
				break;
			case 2:
				stateData.settings.colorOfFPS = sf::Color(255, 0, 0);
				break;
			case 3:
				stateData.settings.colorOfFPS = sf::Color(0, 255, 0);
				break;
			default:
				break;
			}
			if (!advancedColorsOfFPS.empty())
			{
				advancedColorsOfFPS[0].setText(std::to_string(static_cast<int>(stateData.settings.colorOfFPS.r)));
				advancedColorsOfFPS[1].setText(std::to_string(static_cast<int>(stateData.settings.colorOfFPS.g)));
				advancedColorsOfFPS[2].setText(std::to_string(static_cast<int>(stateData.settings.colorOfFPS.b)));
				advancedColorsOfFPS[3].setText(std::to_string(static_cast<int>(stateData.settings.colorOfFPS.a)));
				advancedColorsOfFPS[4].setText(std::to_string(static_cast<int>(stateData.settings.colorOfOutlineFPS.r)));
				advancedColorsOfFPS[5].setText(std::to_string(static_cast<int>(stateData.settings.colorOfOutlineFPS.g)));
				advancedColorsOfFPS[6].setText(std::to_string(static_cast<int>(stateData.settings.colorOfOutlineFPS.b)));
				advancedColorsOfFPS[7].setText(std::to_string(static_cast<int>(stateData.settings.colorOfOutlineFPS.a)));
			}
			WereSettingsChanged = true;
			wasMousePressed = false;
		}
		positionOfFPS.update(mousePositionView, wasMousePressed);
		if (positionOfFPS.wasNewOptionChosen())
		{
			switch (positionOfFPS.getNumberOfChosenOption())
			{
			case 0:
				stateData.settings.FPSOnLeft = true;
				stateData.settings.FPSOnTop = true;
				break;
			case 1:
				stateData.settings.FPSOnLeft = true;
				stateData.settings.FPSOnTop = false;
				break;
			case 2:
				stateData.settings.FPSOnLeft = false;
				stateData.settings.FPSOnTop = true;
				break;
			case 3:
				stateData.settings.FPSOnLeft = false;
				stateData.settings.FPSOnTop = false;
				break;

			}
			WereSettingsChanged = true;
			wasMousePressed = false;
		}
		for (auto i = settingsButton.begin(); i != settingsButton.end(); i++)
		{
			if (i->wasPressed(mousePositionView, wasMousePressed))
			{
				switch (i - settingsButton.begin())
				{
				case 0:
					if (!stateData.settings.fullscreen)
						window.create(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Dungeon Plunderers", sf::Style::Fullscreen);
					if (stateData.settings.isVerticalSyncEnabled)
						window.setVerticalSyncEnabled(true);
					else if (stateData.settings.isLimitFPSEnabled)
						window.setFramerateLimit(stateData.settings.maxFPS);
					stateData.settings.fullscreen = true;
					break;
				case 1:
					if (stateData.settings.fullscreen)
					{
						window.create(sf::VideoMode(stateData.settings.windowSize.x, stateData.settings.windowSize.y), "Dungeon Plunderers");
						window.setPosition(stateData.settings.windowPosition);
					}
					if (stateData.settings.isVerticalSyncEnabled)
						window.setVerticalSyncEnabled(true);
					else if (stateData.settings.isLimitFPSEnabled)
						window.setFramerateLimit(stateData.settings.maxFPS);
					stateData.settings.fullscreen = false;
					break;
				case 2:
					stateData.settings.resizeProportionally = true;
					break;
				case 3:
					stateData.settings.resizeProportionally = false;
					break;
				case 4:
					window.setVerticalSyncEnabled(true);
					stateData.settings.isVerticalSyncEnabled = true;
					maxFPS.setActive(false);
					break;
				case 5:
					window.setVerticalSyncEnabled(false);
					stateData.settings.isVerticalSyncEnabled = false;
					break;
				case 6:
					window.setFramerateLimit(std::stoi(maxFPS.getText()));
					stateData.settings.isLimitFPSEnabled = true;
					break;
				case 7:
					window.setFramerateLimit(0);
					stateData.settings.isLimitFPSEnabled = false;
					break;
				case 8:
					stateData.settings.showFPS = true;
					break;
				case 9:
					stateData.settings.showFPS = false;
					break;
				case 10:
					createAdvancedFPSSettings();
					break;
				case 11:
					deleteAdvancedFPSSettings();
					break;
				case 12:
					stateData.settings.showOutlineFPS = true;
					break;
				case 13:
					stateData.settings.showOutlineFPS = false;
					break;
				}
				WereSettingsChanged = true;
				break;
			}
		}
		if (reseterGeneralSettings.wasPressed(mousePositionView, wasMousePressed))
		{
			areYouSureToResetSettings = std::make_unique<game::MessageBox>(view.getCenter(), sf::Vector2f(650, 200), sf::Vector2f(100, 55),
				stateData.resources[TextureID::MessageboxBackground], stateData.resources[TextureID::GreyButton100x50], stateData.resources.font,
				L"Czy na pewno chcesz zresetowac sterowanie?", L"Tak", L"Nie");

		}
	}
	if(areYouSureToResetSettings)
	{
		areYouSureToResetSettings->update(mousePositionView);
		if (areYouSureToResetSettings->FirstOptionWasPressed(mousePositionView, wasMousePressed))
		{
			resetGeneralSettings(window);
			areYouSureToResetSettings.reset();
		}
		else if (areYouSureToResetSettings->SecondOptionWasPressed(mousePositionView, wasMousePressed))
		{
			areYouSureToResetSettings.reset();
		}
	}
	if (WereSettingsChanged)
		PersistenceSaver::save(stateData.settings);

}

void SettingsState::updateInput(const float deltaTime)
{
}

void SettingsState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(background);

	for(auto const &i : settingsButton)
		target.draw(i);
	for(auto const &i : textButton)
		target.draw(i);

	for(auto const &i : advancedColorsOfFPS)
		target.draw(i);
	for(auto const &i : sizesOfFPS)
		target.draw(i);
	for(auto const &i : RGBA)
		target.draw(i);
	target.draw(reseterGeneralSettings);
	target.draw(generalSettings);
	target.draw(controlSettings);

	target.draw(positionOfFPS);
	target.draw(maxFPS);
	target.draw(colorOfFPS);
	target.draw(backToPreviousState);
	if (areYouSureToResetSettings)
		target.draw(*areYouSureToResetSettings);
}

void SettingsState::updateBackToPreviousState()
{
	backToPreviousState.update(mousePositionView);
	if (backToPreviousState.wasPressed(mousePositionView, wasMousePressed))
		numberOfStatesPop = numberOfStatesPopToBackMenu;
}

void SettingsState::createAdvancedFPSSettings()
{
	if (RGBA.empty())
	{
		positionOfFirstButton.y = 190;
		advancedColorsOfFPS.emplace_back(positionOfFirstButton + sf::Vector2f(864.f, 450.f), sf::Vector2f(216, 50),
			stateData.resources[TextureID::GreyButton750x86], stateData.resources.font,
			std::to_string(static_cast<int>(stateData.settings.colorOfFPS.r)), 40);

		advancedColorsOfFPS.emplace_back(positionOfFirstButton + sf::Vector2f(1080.f, 450.f), sf::Vector2f(216, 50),
			stateData.resources[TextureID::GreyButton750x86], stateData.resources.font,
			std::to_string(static_cast<int>(stateData.settings.colorOfFPS.g)), 40);

		advancedColorsOfFPS.emplace_back(positionOfFirstButton + sf::Vector2f(1296.f, 450.f), sf::Vector2f(216, 50),
			stateData.resources[TextureID::GreyButton750x86], stateData.resources.font,
			std::to_string(static_cast<int>(stateData.settings.colorOfFPS.b)), 40);

		advancedColorsOfFPS.emplace_back(positionOfFirstButton + sf::Vector2f(1512.f, 450.f), sf::Vector2f(216, 50),
			stateData.resources[TextureID::GreyButton750x86], stateData.resources.font,
			std::to_string(static_cast<int>(stateData.settings.colorOfFPS.a)), 40);

		textButton.emplace_back(positionOfFirstButton + sf::Vector2f(0.f, 450.f), sf::Vector2f(864, 50),
			stateData.resources[TextureID::SaveButton], stateData.resources.font,
			L"Kolor FPS", 40);

		textButton.emplace_back(positionOfFirstButton + sf::Vector2f(0.f, 500.f), sf::Vector2f(864, 50),
			stateData.resources[TextureID::SaveButton], stateData.resources.font,
			L"Wielkoœæ FPS", 40);

		textButton.emplace_back(positionOfFirstButton + sf::Vector2f(0.f, 550.f), sf::Vector2f(864, 50),
			stateData.resources[TextureID::SaveButton], stateData.resources.font,
			L"Obramowanie FPS", 40);

		textButton.emplace_back(positionOfFirstButton + sf::Vector2f(0.f, 600.f), sf::Vector2f(864, 50),
			stateData.resources[TextureID::SaveButton], stateData.resources.font,
			L"Kolor obramowania FPS (RGBA)", 40);

		textButton.emplace_back(positionOfFirstButton + sf::Vector2f(0.f, 650.f), sf::Vector2f(864, 50),
			stateData.resources[TextureID::SaveButton], stateData.resources.font,
			L"Gruboœæ obramowania", 40);

		settingsButton.emplace_back(positionOfFirstButton + sf::Vector2f(864.f, 550.f), sf::Vector2f(432, 50),
			stateData.resources[TextureID::GreyButton750x86], stateData.resources.font,
			L"W³¹cz", 40);

		settingsButton.emplace_back(positionOfFirstButton + sf::Vector2f(1296.f, 550.f), sf::Vector2f(432, 50),
			stateData.resources[TextureID::GreyButton750x86], stateData.resources.font,
			L"Wy³¹cz", 40);

		advancedColorsOfFPS.emplace_back(positionOfFirstButton + sf::Vector2f(864.f, 600.f), sf::Vector2f(216, 50),
			stateData.resources[TextureID::GreyButton750x86], stateData.resources.font,
			std::to_string(static_cast<int>(stateData.settings.colorOfOutlineFPS.r)), 40);

		advancedColorsOfFPS.emplace_back(positionOfFirstButton + sf::Vector2f(1080.f, 600.f), sf::Vector2f(216, 50),
			stateData.resources[TextureID::GreyButton750x86], stateData.resources.font,
			std::to_string(static_cast<int>(stateData.settings.colorOfOutlineFPS.g)), 40);

		advancedColorsOfFPS.emplace_back(positionOfFirstButton + sf::Vector2f(1296.f, 600.f), sf::Vector2f(216, 50),
			stateData.resources[TextureID::GreyButton750x86], stateData.resources.font,
			std::to_string(static_cast<int>(stateData.settings.colorOfOutlineFPS.b)), 40);

		advancedColorsOfFPS.emplace_back(positionOfFirstButton + sf::Vector2f(1512.f, 600.f), sf::Vector2f(216, 50),
			stateData.resources[TextureID::GreyButton750x86], stateData.resources.font,
			std::to_string(static_cast<int>(stateData.settings.colorOfOutlineFPS.a)), 40);

		sizesOfFPS.emplace_back(positionOfFirstButton + sf::Vector2f(864.f, 500.f), sf::Vector2f(864, 50),
			stateData.resources[TextureID::GreyButton750x86], stateData.resources.font, std::to_string(stateData.settings.characterSizeOfFPS), 40);

		sizesOfFPS.emplace_back(positionOfFirstButton + sf::Vector2f(864.f, 650.f), sf::Vector2f(864, 50),
			stateData.resources[TextureID::GreyButton750x86], stateData.resources.font, std::to_string(stateData.settings.outlineThickness), 40);

		for (int i = 0; i < 2; i++)
		{
			RGBA.emplace_back("R", stateData.resources.font, 40);
			RGBA.emplace_back("G", stateData.resources.font, 40);
			RGBA.emplace_back("B", stateData.resources.font, 40);
			RGBA.emplace_back("A", stateData.resources.font, 40);
		}
		for (auto& i : RGBA)
		{
			i.setOutlineThickness(2);
		}
		RGBA[0].setPosition(positionOfFirstButton + sf::Vector2f(884.f, 597.f));
		RGBA[1].setPosition(positionOfFirstButton + sf::Vector2f(1100.f, 597.f));
		RGBA[2].setPosition(positionOfFirstButton + sf::Vector2f(1316.f, 597.f));
		RGBA[3].setPosition(positionOfFirstButton + sf::Vector2f(1532.f, 597.f));

		RGBA[4].setPosition(positionOfFirstButton + sf::Vector2f(884.f, 447));
		RGBA[5].setPosition(positionOfFirstButton + sf::Vector2f(1100.f, 447));
		RGBA[6].setPosition(positionOfFirstButton + sf::Vector2f(1316.f, 447));
		RGBA[7].setPosition(positionOfFirstButton + sf::Vector2f(1532.f, 447));
		setPositionOfButtons();

	}
}

void SettingsState::deleteAdvancedFPSSettings()
{
	if (!RGBA.empty())
	{
		positionOfFirstButton.y = 315;
		RGBA.clear();
		sizesOfFPS.clear();
		advancedColorsOfFPS.clear();
		settingsButton.pop_back();
		settingsButton.pop_back();
		for (int i = 0; i < 5; i++)
			textButton.pop_back();
		setPositionOfButtons();

	}
}

void SettingsState::setPositionOfButtons()
{
	for (auto i = textButton.begin(); i != textButton.end(); i++)
	{
		i->setPosition(positionOfFirstButton + sf::Vector2f(0.f, 50.f * (i - textButton.begin())));
	}
	int line = 0;
	for (int i = 0; i < 8; i++)
	{
		if (i % 2 == 0)
			line++;
		settingsButton[i].setPosition(positionOfFirstButton + sf::Vector2f(864.f + 432 * (i % 2), 50.f * (line - 1)));
	}
	maxFPS.setPosition(positionOfFirstButton + sf::Vector2f(864.f, 200.f));
	colorOfFPS.setPosition(positionOfFirstButton + sf::Vector2f(864.f, 300.f));
	positionOfFPS.setPosition(positionOfFirstButton + sf::Vector2f(864.f, 350.f));
	settingsButton[8].setPosition(positionOfFirstButton + sf::Vector2f(864.f, 250.f));
	settingsButton[9].setPosition(positionOfFirstButton + sf::Vector2f(1296.f, 250.f));
	settingsButton[10].setPosition(positionOfFirstButton + sf::Vector2f(864.f, 400.f));
	settingsButton[11].setPosition(positionOfFirstButton + sf::Vector2f(1296.f, 400.f));

	if (RGBA.empty())
		reseterGeneralSettings.setPosition(positionOfFirstButton + sf::Vector2f(1296.f, 450.f));
	else
		reseterGeneralSettings.setPosition(positionOfFirstButton + sf::Vector2f(1296.f, 700.f));

}

void SettingsState::resetGeneralSettings(sf::RenderWindow& window)
{
	bool wasFullscreenOnBeforeReset = stateData.settings.fullscreen;
	stateData.settings.fullscreen = true;
	stateData.settings.windowSize.x = sf::VideoMode::getDesktopMode().width;  //whole screen
	stateData.settings.windowSize.y = sf::VideoMode::getDesktopMode().height; //whole screen
	stateData.settings.windowPosition.x = 0;
	stateData.settings.windowPosition.y = 0;
	stateData.settings.resizeProportionally = true;
	stateData.settings.isVerticalSyncEnabled = false;
	stateData.settings.isLimitFPSEnabled = true;
	stateData.settings.maxFPS = 120;
	stateData.settings.showFPS = false;
	stateData.settings.FPSOnTop = true;
	stateData.settings.FPSOnLeft = true;
	stateData.settings.characterSizeOfFPS = 25;
	stateData.settings.colorOfFPS = sf::Color(255, 116, 0);
	stateData.settings.showOutlineFPS = false;
	stateData.settings.outlineThickness = 2;
	stateData.settings.colorOfOutlineFPS = sf::Color::Black;
	WereSettingsChanged = true;
	if (!advancedColorsOfFPS.empty())
	{
		advancedColorsOfFPS[0].setText(std::to_string(static_cast<int>(stateData.settings.colorOfFPS.r)));
		advancedColorsOfFPS[1].setText(std::to_string(static_cast<int>(stateData.settings.colorOfFPS.g)));
		advancedColorsOfFPS[2].setText(std::to_string(static_cast<int>(stateData.settings.colorOfFPS.b)));
		advancedColorsOfFPS[3].setText(std::to_string(static_cast<int>(stateData.settings.colorOfFPS.a)));
		advancedColorsOfFPS[4].setText(std::to_string(static_cast<int>(stateData.settings.colorOfOutlineFPS.r)));
		advancedColorsOfFPS[5].setText(std::to_string(static_cast<int>(stateData.settings.colorOfOutlineFPS.g)));
		advancedColorsOfFPS[6].setText(std::to_string(static_cast<int>(stateData.settings.colorOfOutlineFPS.b)));
		advancedColorsOfFPS[7].setText(std::to_string(static_cast<int>(stateData.settings.colorOfOutlineFPS.a)));
	}
	setColorToList();
	if (!wasFullscreenOnBeforeReset)
	{
		window.create(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Dungeon Plunderers", sf::Style::Fullscreen);
	}
	if (stateData.settings.isVerticalSyncEnabled)
		window.setVerticalSyncEnabled(true);
	else if (stateData.settings.isLimitFPSEnabled)
		window.setFramerateLimit(stateData.settings.maxFPS);
}

void SettingsState::setColorToList()
{
	if (stateData.settings.colorOfFPS == sf::Color(255, 116, 0))
		colorOfFPS.setTextOfChosenOption(L"Pomarañczowy");
	else if (stateData.settings.colorOfFPS == sf::Color(0, 0, 255))
		colorOfFPS.setTextOfChosenOption(L"Niebieski");
	else if (stateData.settings.colorOfFPS == sf::Color(255, 0, 0))
		colorOfFPS.setTextOfChosenOption(L"Czerwony");
	else if (stateData.settings.colorOfFPS == sf::Color(0, 255, 0))
		colorOfFPS.setTextOfChosenOption(L"Zielony");
	else
		colorOfFPS.setTextOfChosenOption(L"Inny");
}
