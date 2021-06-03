#include "pch.h"
#include "ControlSettingsState.h"


ControlSettingsState::ControlSettingsState(StateData& stateData, int numberOfStatesPopToBackMenu)
	: State(stateData), numberOfStatesPopToBackMenu(numberOfStatesPopToBackMenu),
	znfoButtons{
	TextButton(sf::Vector2f(510, 150.f), sf::Vector2f(900, 60),
		stateData.resources[TextureID::DarkRedButton750x86], stateData.resources.font,
		L"Strzelec i czarodziej:", 60),
	TextButton(sf::Vector2f(510, 150.f) + sf::Vector2f(-300, 60), sf::Vector2f(750, 50),
		stateData.resources[TextureID::GreyButton750x86], stateData.resources.font,
		L"IdŸ w prawo", 40),

	TextButton(sf::Vector2f(510, 150.f) + sf::Vector2f(-300, 110), sf::Vector2f(750, 50),
		stateData.resources[TextureID::GreyButton750x86], stateData.resources.font,
		L"IdŸ w lewo", 40),

	TextButton(sf::Vector2f(510, 150.f) + sf::Vector2f(-300, 160), sf::Vector2f(750, 50),
		stateData.resources[TextureID::GreyButton750x86], stateData.resources.font,
		L"Skacz", 40),

	TextButton(sf::Vector2f(510, 150.f) + sf::Vector2f(-300, 210), sf::Vector2f(750, 50),
		stateData.resources[TextureID::GreyButton750x86], stateData.resources.font,
		L"Zmieñ na pierwsz¹ broñ", 40),

	TextButton(sf::Vector2f(510, 150.f) + sf::Vector2f(-300, 260), sf::Vector2f(750, 50),
		stateData.resources[TextureID::GreyButton750x86], stateData.resources.font,
		L"Zmieñ na drug¹ broñ", 40),

	TextButton(sf::Vector2f(510, 150.f) + sf::Vector2f(-300, 310), sf::Vector2f(750, 50),
		stateData.resources[TextureID::GreyButton750x86], stateData.resources.font,
		L"Zmieñ na trzeci¹ broñ", 40),

	TextButton(sf::Vector2f(510, 150.f) + sf::Vector2f(0, 360), sf::Vector2f(900, 60),
		stateData.resources[TextureID::DarkRedButton750x86], stateData.resources.font,
		L"Samolot i czarodziej na chmurce:", 60),

	TextButton(sf::Vector2f(510, 150.f) + sf::Vector2f(-300, 420), sf::Vector2f(750, 50),
		stateData.resources[TextureID::GreyButton750x86], stateData.resources.font,
		L"Leæ w prawo", 40),

	TextButton(sf::Vector2f(510, 150.f) + sf::Vector2f(-300, 470), sf::Vector2f(750, 50),
		stateData.resources[TextureID::GreyButton750x86], stateData.resources.font,
		L"Leæ w lewo", 40),

	TextButton(sf::Vector2f(510, 150.f) + sf::Vector2f(-300, 520), sf::Vector2f(750, 50),
		stateData.resources[TextureID::GreyButton750x86], stateData.resources.font,
		L"Leæ do góry", 40),

	TextButton(sf::Vector2f(510, 150.f) + sf::Vector2f(-300, 570), sf::Vector2f(750, 50),
		stateData.resources[TextureID::GreyButton750x86], stateData.resources.font,
		L"Leæ na dól", 40),

	TextButton(sf::Vector2f(510, 150.f) + sf::Vector2f(-300, 620), sf::Vector2f(750, 50),
		stateData.resources[TextureID::GreyButton750x86], stateData.resources.font,
		L"Zmieñ na czarodzieja/strzelca", 40),

	TextButton(sf::Vector2f(510, 150.f) + sf::Vector2f(0, 670), sf::Vector2f(900, 60),
		stateData.resources[TextureID::DarkRedButton750x86], stateData.resources.font,
		L"Reszta", 60),

	TextButton(sf::Vector2f(510, 150.f) + sf::Vector2f(-300, 730), sf::Vector2f(750, 50),
		stateData.resources[TextureID::GreyButton750x86], stateData.resources.font,
		L"Atak", 40),

	TextButton(sf::Vector2f(510, 150.f) + sf::Vector2f(-300, 780), sf::Vector2f(750, 50),
		stateData.resources[TextureID::GreyButton750x86], stateData.resources.font,
		L"Picie mikstury ¿ycia", 40),

	TextButton(sf::Vector2f(510, 150.f) + sf::Vector2f(-300, 830), sf::Vector2f(750, 50),
		stateData.resources[TextureID::GreyButton750x86], stateData.resources.font,
		L"Picie mikstury many", 40) },


		buttonsChangingControl{
		TextButton(sf::Vector2f(510, 150.f) + sf::Vector2f(450, 60), sf::Vector2f(750, 50),
			stateData.resources[TextureID::GreyButton750x86], stateData.resources.font,
			L"", 40),

		TextButton(sf::Vector2f(510, 150.f) + sf::Vector2f(450, 110), sf::Vector2f(750, 50),
			stateData.resources[TextureID::GreyButton750x86], stateData.resources.font,
			L"", 40),
			
		TextButton(sf::Vector2f(510, 150.f) + sf::Vector2f(450, 160), sf::Vector2f(750, 50),
			stateData.resources[TextureID::GreyButton750x86], stateData.resources.font,
			L"", 40),

		TextButton(sf::Vector2f(510, 150.f) + sf::Vector2f(450, 210), sf::Vector2f(750, 50),
			stateData.resources[TextureID::GreyButton750x86], stateData.resources.font,
			L"", 40),

		TextButton(sf::Vector2f(510, 150.f) + sf::Vector2f(450, 260), sf::Vector2f(750, 50),
			stateData.resources[TextureID::GreyButton750x86], stateData.resources.font,
			L"", 40),

		TextButton(sf::Vector2f(510, 150.f) + sf::Vector2f(450, 310), sf::Vector2f(750, 50),
			stateData.resources[TextureID::GreyButton750x86], stateData.resources.font,
			L"", 40),

		TextButton(sf::Vector2f(510, 150.f) + sf::Vector2f(450, 420), sf::Vector2f(750, 50),
			stateData.resources[TextureID::GreyButton750x86], stateData.resources.font,
			L"", 40),

		TextButton(sf::Vector2f(510, 150.f) + sf::Vector2f(450, 470), sf::Vector2f(750, 50),
			stateData.resources[TextureID::GreyButton750x86], stateData.resources.font,
			L"", 40),

		TextButton(sf::Vector2f(510, 150.f) + sf::Vector2f(450, 520), sf::Vector2f(750, 50),
			stateData.resources[TextureID::GreyButton750x86], stateData.resources.font,
			L"", 40),

		TextButton(sf::Vector2f(510, 150.f) + sf::Vector2f(450, 570), sf::Vector2f(750, 50),
			stateData.resources[TextureID::GreyButton750x86], stateData.resources.font,
			L"", 40),

		TextButton(sf::Vector2f(510, 150.f) + sf::Vector2f(450, 620), sf::Vector2f(750, 50),
			stateData.resources[TextureID::GreyButton750x86], stateData.resources.font,
			L"", 40),

		TextButton(sf::Vector2f(510, 150.f) + sf::Vector2f(450, 730), sf::Vector2f(750, 50),
			stateData.resources[TextureID::GreyButton750x86], stateData.resources.font,
			L"", 40),

		TextButton(sf::Vector2f(510, 150.f) + sf::Vector2f(450, 780), sf::Vector2f(750, 50),
			stateData.resources[TextureID::GreyButton750x86], stateData.resources.font,
			L"", 40),

		TextButton(sf::Vector2f(510, 150.f) + sf::Vector2f(450, 830), sf::Vector2f(750, 50),
			stateData.resources[TextureID::GreyButton750x86], stateData.resources.font,
			L"", 40) },
			resetButton(sf::Vector2f(510, 150.f) + sf::Vector2f(450, 880), sf::Vector2f(750, 50),
			stateData.resources[TextureID::GreyButton750x86], stateData.resources.font,
			L"Przywróæ do ustawieñ domyœlnych", 40),
			informationAboutChangingKey(sf::Vector2f(560, 365), sf::Vector2f(800, 300),
			stateData.resources[TextureID::GreyButton750x86], stateData.resources.font,
			L"Wybierz dowolny przycisk", 54),
			controlSettings(sf::Vector2f(960, 50.f), sf::Vector2f(300, 50),
			stateData.resources[TextureID::GreyButton750x86], stateData.resources.font,
			L"Sterowanie", 40),
			generalSettings(sf::Vector2f(660, 50.f), sf::Vector2f(300, 50),
			stateData.resources[TextureID::GreyButton750x86], stateData.resources.font,
			L"Ogólne", 40)
{
	initSupportedKeys();
	setTextOfButtonsChangingControl();
	DefaultAndCurrentKey.setFont(stateData.resources.font);
	DefaultAndCurrentKey.setCharacterSize(35);
	DefaultAndCurrentKey.setString("Domyslny klawisz: A \n Obecny klawisz: B");
	DefaultAndCurrentKey.setPosition(sf::Vector2f(850, 540));
	DefaultAndCurrentKey.setOutlineThickness(2);
}


ControlSettingsState::~ControlSettingsState()
{
}

void ControlSettingsState::update(const float deltaTime)
{

	if (!isChangingKey)
	{
	
		if (messageBoxAreYouSureToResetControl)
		{
			messageBoxAreYouSureToResetControl->update(mousePositionView);
			if (messageBoxAreYouSureToResetControl->FirstOptionWasPressed(mousePositionView, wasMousePressed))
			{
				stateData.keybinds = Keybinds();
				setTextOfButtonsChangingControl();
				PersistenceSaver::save(stateData.keybinds);
				messageBoxAreYouSureToResetControl.reset();
			}
			else if (messageBoxAreYouSureToResetControl->SecondOptionWasPressed(mousePositionView, wasMousePressed))
			{
				messageBoxAreYouSureToResetControl.reset();
			}
		}
		else
		{
			generalSettings.update(mousePositionView);
			controlSettings.update(mousePositionView);
			controlSettings.setCurrentColor(sf::Color::Red);
			if(generalSettings.wasPressed(mousePositionView, wasMousePressed))
				stateData.states.push(std::make_unique<SettingsState>(stateData, numberOfStatesPopToBackMenu + 1));

			for (int i = 0; i < buttonsChangingControl.size(); i++)
			{
				buttonsChangingControl[i].update(mousePositionView);
				if (buttonsChangingControl[i].wasPressed(mousePositionView, wasMousePressed))
				{
					isChangingKey = true;
					whatKeyChange = i;
					switch (i)
					{
					case 0:
						DefaultAndCurrentKey.setString("Domyslny klawisz: " + supportedKeys[defaultKeybinds[KeybindID::MoveRight]] +
							"\nObecny klawisz: " + supportedKeys[stateData.keybinds[KeybindID::MoveRight]]);
						break;
					case 1:
						DefaultAndCurrentKey.setString("Domyslny klawisz: " + supportedKeys[defaultKeybinds[KeybindID::MoveLeft]] +
							"\nObecny klawisz: " + supportedKeys[stateData.keybinds[KeybindID::MoveLeft]]);
						break;
					case 2:
						DefaultAndCurrentKey.setString("Domyslny klawisz: " + supportedKeys[defaultKeybinds[KeybindID::Jump]] +
							"\nObecny klawisz: " + supportedKeys[stateData.keybinds[KeybindID::Jump]]);
						break;
					case 3:
						DefaultAndCurrentKey.setString("Domyslny klawisz: " + supportedKeys[defaultKeybinds[KeybindID::FirstWeapon]] +
							"\nObecny klawisz: " + supportedKeys[stateData.keybinds[KeybindID::FirstWeapon]]);
						break;
					case 4:
						DefaultAndCurrentKey.setString("Domyslny klawisz: " + supportedKeys[defaultKeybinds[KeybindID::SecondWeapon]] +
							"\nObecny klawisz: " + supportedKeys[stateData.keybinds[KeybindID::SecondWeapon]]);
						break;
					case 5:
						DefaultAndCurrentKey.setString("Domyslny klawisz: " + supportedKeys[defaultKeybinds[KeybindID::ThirdWeapon]] +
							"\nObecny klawisz: " + supportedKeys[stateData.keybinds[KeybindID::ThirdWeapon]]);
						break;
					case 6:
						DefaultAndCurrentKey.setString("Domyslny klawisz: " + supportedKeys[defaultKeybinds[KeybindID::MoveRightPlaneOrCloud]] +
							"\nObecny klawisz: " + supportedKeys[stateData.keybinds[KeybindID::MoveRightPlaneOrCloud]]);
						break;
					case 7:
						DefaultAndCurrentKey.setString("Domyslny klawisz: " + supportedKeys[defaultKeybinds[KeybindID::MoveLeftPlaneOrCloud]] +
							"\nObecny klawisz: " + supportedKeys[stateData.keybinds[KeybindID::MoveLeftPlaneOrCloud]]);
						break;
					case 8:
						DefaultAndCurrentKey.setString("Domyslny klawisz: " + supportedKeys[defaultKeybinds[KeybindID::MoveUpPlaneOrCloud]] +
							"\nObecny klawisz: " + supportedKeys[stateData.keybinds[KeybindID::MoveUpPlaneOrCloud]]);
						break;
					case 9:
						DefaultAndCurrentKey.setString("Domyslny klawisz: " + supportedKeys[defaultKeybinds[KeybindID::MoveDownPlaneOrCloud]] +
							"\nObecny klawisz: " + supportedKeys[stateData.keybinds[KeybindID::MoveDownPlaneOrCloud]]);
						break;
					case 10:
						DefaultAndCurrentKey.setString("Domyslny klawisz: " + supportedKeys[defaultKeybinds[KeybindID::GetOffPlaneOrCloud]] +
							"\nObecny klawisz: " + supportedKeys[stateData.keybinds[KeybindID::GetOffPlaneOrCloud]]);
						break;
					case 11:
						DefaultAndCurrentKey.setString("Domyslny klawisz: " + supportedKeys[defaultKeybinds[KeybindID::Attack]] +
							"\nObecny klawisz: " + supportedKeys[stateData.keybinds[KeybindID::Attack]]);
						break;
					case 12:
						DefaultAndCurrentKey.setString("Domyslny klawisz: " + supportedKeys[defaultKeybinds[KeybindID::DrinkHealthPotion]] +
							"\nObecny klawisz: " + supportedKeys[stateData.keybinds[KeybindID::DrinkHealthPotion]]);
						break;
					case 13:
						DefaultAndCurrentKey.setString("Domyslny klawisz: " + supportedKeys[defaultKeybinds[KeybindID::DrinkManaPotion]] +
							"\nObecny klawisz: " + supportedKeys[stateData.keybinds[KeybindID::DrinkManaPotion]]);
						break;
					}
				}
			}
			resetButton.update(mousePositionView);
			if (resetButton.wasPressed(mousePositionView, wasMousePressed))
				makeMessageBoxAreYouSureToResetControl();
		}
	}
}

void ControlSettingsState::handleSFMLEvent(sf::RenderWindow& window, sf::Event& event)
{
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
				if (isChangingKey)
					isChangingKey = false;
				else
					numberOfStatesPop = numberOfStatesPopToBackMenu;
			}
			if (isChangingKey and event.key.code != sf::Keyboard::Escape)
			{
				switch (whatKeyChange)
				{
				case 0:
					stateData.keybinds.changeKeybind(KeybindID::MoveRight, event.key.code);
					break;
				case 1:
					stateData.keybinds.changeKeybind(KeybindID::MoveLeft, event.key.code);
					break;
				case 2:
					stateData.keybinds.changeKeybind(KeybindID::Jump, event.key.code);
					break;
				case 3:
					stateData.keybinds.changeKeybind(KeybindID::FirstWeapon, event.key.code);
					break;
				case 4:
					stateData.keybinds.changeKeybind(KeybindID::SecondWeapon, event.key.code);
					break;
				case 5:
					stateData.keybinds.changeKeybind(KeybindID::ThirdWeapon, event.key.code);
					break;
				case 6:
					stateData.keybinds.changeKeybind(KeybindID::MoveRightPlaneOrCloud, event.key.code);
					break;
				case 7:
					stateData.keybinds.changeKeybind(KeybindID::MoveLeftPlaneOrCloud, event.key.code);
					break;
				case 8:
					stateData.keybinds.changeKeybind(KeybindID::MoveUpPlaneOrCloud, event.key.code);
					break;
				case 9:
					stateData.keybinds.changeKeybind(KeybindID::MoveDownPlaneOrCloud, event.key.code);
					break;
				case 10:
					stateData.keybinds.changeKeybind(KeybindID::GetOffPlaneOrCloud, event.key.code);
					break;
				case 11:
					stateData.keybinds.changeKeybind(KeybindID::Attack, event.key.code);
					break;
				case 12:
					stateData.keybinds.changeKeybind(KeybindID::DrinkHealthPotion, event.key.code);
					break;
				case 13:
					stateData.keybinds.changeKeybind(KeybindID::DrinkManaPotion, event.key.code);
					break;
				}
				setTextOfButtonsChangingControl();
				isChangingKey = false;
				PersistenceSaver::save(stateData.keybinds);
			}
		}


		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (isChangingKey)
			{

				switch (whatKeyChange)
				{
				case 0:
					stateData.keybinds.changeKeybind(KeybindID::MoveRight, event.mouseButton.button);
					break;
				case 1:
					stateData.keybinds.changeKeybind(KeybindID::MoveLeft, event.mouseButton.button);
					break;
				case 2:
					stateData.keybinds.changeKeybind(KeybindID::Jump, event.mouseButton.button);
					break;
				case 3:
					stateData.keybinds.changeKeybind(KeybindID::FirstWeapon, event.mouseButton.button);
					break;
				case 4:
					stateData.keybinds.changeKeybind(KeybindID::SecondWeapon, event.mouseButton.button);
					break;
				case 5:
					stateData.keybinds.changeKeybind(KeybindID::ThirdWeapon, event.mouseButton.button);
					break;
				case 6:
					stateData.keybinds.changeKeybind(KeybindID::MoveRightPlaneOrCloud, event.mouseButton.button);
					break;
				case 7:
					stateData.keybinds.changeKeybind(KeybindID::MoveLeftPlaneOrCloud, event.mouseButton.button);
					break;
				case 8:
					stateData.keybinds.changeKeybind(KeybindID::MoveUpPlaneOrCloud, event.mouseButton.button);
					break;
				case 9:
					stateData.keybinds.changeKeybind(KeybindID::MoveDownPlaneOrCloud, event.mouseButton.button);
					break;
				case 10:
					stateData.keybinds.changeKeybind(KeybindID::GetOffPlaneOrCloud, event.mouseButton.button);
					break;
				case 11:
					stateData.keybinds.changeKeybind(KeybindID::Attack, event.mouseButton.button);
					break;
				case 12:
					stateData.keybinds.changeKeybind(KeybindID::DrinkHealthPotion, event.mouseButton.button);
					break;
				case 13:
					stateData.keybinds.changeKeybind(KeybindID::DrinkManaPotion, event.mouseButton.button);
					break;
				}
				setTextOfButtonsChangingControl();
				isChangingKey = false;
				PersistenceSaver::save(stateData.keybinds);

			}
			else
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					wasMousePressed = true;
				}
			}
		}
	}
}

void ControlSettingsState::updateInput(const float deltaTime)
{
}

void ControlSettingsState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(background, states);
	for (auto const& i : znfoButtons)
		target.draw(i, states);
	for (auto const& i : buttonsChangingControl)
		target.draw(i, states);
	target.draw(resetButton, states);
	target.draw(generalSettings);
	target.draw(controlSettings);
	if (messageBoxAreYouSureToResetControl)
		target.draw(*messageBoxAreYouSureToResetControl, states);

	if (isChangingKey)
	{
		target.draw(informationAboutChangingKey, states);
		target.draw(DefaultAndCurrentKey, states);
	}
}

void ControlSettingsState::initSupportedKeys()
{
	supportedKeys[sf::Keyboard::Key::A] = "A";
	supportedKeys[sf::Keyboard::Key::B] = "B";
	supportedKeys[sf::Keyboard::Key::C] = "C";
	supportedKeys[sf::Keyboard::Key::D] = "D";
	supportedKeys[sf::Keyboard::Key::E] = "E";
	supportedKeys[sf::Keyboard::Key::F] = "F";
	supportedKeys[sf::Keyboard::Key::G] = "G";
	supportedKeys[sf::Keyboard::Key::H] = "H";
	supportedKeys[sf::Keyboard::Key::I] = "I";
	supportedKeys[sf::Keyboard::Key::J] = "J";
	supportedKeys[sf::Keyboard::Key::K] = "K";
	supportedKeys[sf::Keyboard::Key::L] = "L";
	supportedKeys[sf::Keyboard::Key::M] = "M";
	supportedKeys[sf::Keyboard::Key::N] = "N";
	supportedKeys[sf::Keyboard::Key::O] = "O";
	supportedKeys[sf::Keyboard::Key::P] = "P";
	supportedKeys[sf::Keyboard::Key::Q] = "Q";
	supportedKeys[sf::Keyboard::Key::R] = "R";
	supportedKeys[sf::Keyboard::Key::S] = "S";
	supportedKeys[sf::Keyboard::Key::T] = "T";
	supportedKeys[sf::Keyboard::Key::U] = "U";
	supportedKeys[sf::Keyboard::Key::V] = "V";
	supportedKeys[sf::Keyboard::Key::W] = "W";
	supportedKeys[sf::Keyboard::Key::X] = "X";
	supportedKeys[sf::Keyboard::Key::Y] = "Y";
	supportedKeys[sf::Keyboard::Key::Z] = "Z";
	supportedKeys[sf::Keyboard::Key::Num0] = "Num0";
	supportedKeys[sf::Keyboard::Key::Num1] = "Num1";
	supportedKeys[sf::Keyboard::Key::Num2] = "Num2";
	supportedKeys[sf::Keyboard::Key::Num3] = "Num3";
	supportedKeys[sf::Keyboard::Key::Num4] = "Num4";
	supportedKeys[sf::Keyboard::Key::Num5] = "Num5";
	supportedKeys[sf::Keyboard::Key::Num6] = "Num6";
	supportedKeys[sf::Keyboard::Key::Num7] = "Num7";
	supportedKeys[sf::Keyboard::Key::Num8] = "Num8";
	supportedKeys[sf::Keyboard::Key::Num9] = "Num9";
	supportedKeys[sf::Keyboard::Key::Escape] = "Escape";

	supportedKeys[sf::Keyboard::Key::LControl] = "LControl";
	supportedKeys[sf::Keyboard::Key::LShift] = "LShift";
	supportedKeys[sf::Keyboard::Key::LAlt] = "LAlt";
	supportedKeys[sf::Keyboard::Key::LSystem] = "LSystem";
	supportedKeys[sf::Keyboard::Key::RControl] = "RControl";
	supportedKeys[sf::Keyboard::Key::RShift] = "RShift";
	supportedKeys[sf::Keyboard::Key::RAlt] = "RAlt";
	supportedKeys[sf::Keyboard::Key::RSystem] = "RSystem";
	supportedKeys[sf::Keyboard::Key::Menu] = "Menu";
	supportedKeys[sf::Keyboard::Key::LBracket] = "LBracket";
	supportedKeys[sf::Keyboard::Key::RBracket] = "RBracket";
	supportedKeys[sf::Keyboard::Key::Semicolon] = "Semicolon";
	supportedKeys[sf::Keyboard::Key::Comma] = "Comma";
	supportedKeys[sf::Keyboard::Key::Period] = "Period";
	supportedKeys[sf::Keyboard::Key::Quote] = "Quote";
	supportedKeys[sf::Keyboard::Key::Slash] = "Slash";
	supportedKeys[sf::Keyboard::Key::Backslash] = "Backslash";
	supportedKeys[sf::Keyboard::Key::Tilde] = "Tilde";
	supportedKeys[sf::Keyboard::Key::Equal] = "Equal";
	supportedKeys[sf::Keyboard::Key::Hyphen] = "Hyphen";
	supportedKeys[sf::Keyboard::Key::Space] = "Space";
	supportedKeys[sf::Keyboard::Key::Enter] = "Enter";
	supportedKeys[sf::Keyboard::Key::Backspace] = "Backspace";
	supportedKeys[sf::Keyboard::Key::Tab] = "Tab";
	supportedKeys[sf::Keyboard::Key::PageUp] = "PageUp";
	supportedKeys[sf::Keyboard::Key::PageDown] = "PageDown";
	supportedKeys[sf::Keyboard::Key::End] = "End";
	supportedKeys[sf::Keyboard::Key::Home] = "Home";

	supportedKeys[sf::Keyboard::Key::Insert] = "Insert";
	supportedKeys[sf::Keyboard::Key::Delete] = "Delete";
	supportedKeys[sf::Keyboard::Key::Add] = "Add";
	supportedKeys[sf::Keyboard::Key::Subtract] = "Subtract";
	supportedKeys[sf::Keyboard::Key::Multiply] = "Multiply";
	supportedKeys[sf::Keyboard::Key::Divide] = "Divide";
	supportedKeys[sf::Keyboard::Key::Left] = "Left";
	supportedKeys[sf::Keyboard::Key::Right] = "Right";
	supportedKeys[sf::Keyboard::Key::Up] = "Up";
	supportedKeys[sf::Keyboard::Key::Down] = "Down";

	supportedKeys[sf::Keyboard::Key::Numpad0] = "Numpad0";
	supportedKeys[sf::Keyboard::Key::Numpad1] = "Numpad1";
	supportedKeys[sf::Keyboard::Key::Numpad2] = "Numpad2";
	supportedKeys[sf::Keyboard::Key::Numpad3] = "Numpad3";
	supportedKeys[sf::Keyboard::Key::Numpad4] = "Numpad4";
	supportedKeys[sf::Keyboard::Key::Numpad5] = "Numpad5";
	supportedKeys[sf::Keyboard::Key::Numpad6] = "Numpad6";
	supportedKeys[sf::Keyboard::Key::Numpad7] = "Numpad7";
	supportedKeys[sf::Keyboard::Key::Numpad8] = "Numpad8";
	supportedKeys[sf::Keyboard::Key::Numpad9] = "Numpad9";

	supportedKeys[sf::Keyboard::Key::F1] = "F1";
	supportedKeys[sf::Keyboard::Key::F2] = "F2";
	supportedKeys[sf::Keyboard::Key::F3] = "F3";
	supportedKeys[sf::Keyboard::Key::F4] = "F4";
	supportedKeys[sf::Keyboard::Key::F5] = "F5";
	supportedKeys[sf::Keyboard::Key::F6] = "F6";
	supportedKeys[sf::Keyboard::Key::F7] = "F7";
	supportedKeys[sf::Keyboard::Key::F8] = "F8";
	supportedKeys[sf::Keyboard::Key::F9] = "F9";
	supportedKeys[sf::Keyboard::Key::F10] = "F10";
	supportedKeys[sf::Keyboard::Key::F11] = "F11";
	supportedKeys[sf::Keyboard::Key::F12] = "F12";
	supportedKeys[sf::Keyboard::Key::F13] = "F13";
	supportedKeys[sf::Keyboard::Key::F14] = "F14";
	supportedKeys[sf::Keyboard::Key::F15] = "F15";

	supportedKeys[sf::Keyboard::Key::Pause] = "Pause";
	//Mouse
	supportedKeys[101] = "LPM";
	supportedKeys[102] = "PPM";
	supportedKeys[103] = "Srodkowy";
	supportedKeys[104] = "1 dodatkowy";
	supportedKeys[105] = "2 dodatkowy";
}

void ControlSettingsState::setPositionOfButtons()
{
}
void ControlSettingsState::setTextOfButtonsChangingControl()
{
	buttonsChangingControl[0].setText(supportedKeys[stateData.keybinds[KeybindID::MoveRight]]);
	buttonsChangingControl[1].setText(supportedKeys[stateData.keybinds[KeybindID::MoveLeft]]);
	buttonsChangingControl[2].setText(supportedKeys[stateData.keybinds[KeybindID::Jump]]);
	buttonsChangingControl[3].setText(supportedKeys[stateData.keybinds[KeybindID::FirstWeapon]]);
	buttonsChangingControl[4].setText(supportedKeys[stateData.keybinds[KeybindID::SecondWeapon]]);
	buttonsChangingControl[5].setText(supportedKeys[stateData.keybinds[KeybindID::ThirdWeapon]]);
	buttonsChangingControl[6].setText(supportedKeys[stateData.keybinds[KeybindID::MoveRightPlaneOrCloud]]);
	buttonsChangingControl[7].setText(supportedKeys[stateData.keybinds[KeybindID::MoveLeftPlaneOrCloud]]);
	buttonsChangingControl[8].setText(supportedKeys[stateData.keybinds[KeybindID::MoveUpPlaneOrCloud]]);
	buttonsChangingControl[9].setText(supportedKeys[stateData.keybinds[KeybindID::MoveDownPlaneOrCloud]]);
	buttonsChangingControl[10].setText(supportedKeys[stateData.keybinds[KeybindID::GetOffPlaneOrCloud]]);
	buttonsChangingControl[11].setText(supportedKeys[stateData.keybinds[KeybindID::Attack]]);
	buttonsChangingControl[12].setText(supportedKeys[stateData.keybinds[KeybindID::DrinkHealthPotion]]);
	buttonsChangingControl[13].setText(supportedKeys[stateData.keybinds[KeybindID::DrinkManaPotion]]);
}

void ControlSettingsState::makeMessageBoxAreYouSureToResetControl()
{
	messageBoxAreYouSureToResetControl = std::make_unique<game::MessageBox>(view.getCenter(), sf::Vector2f(650, 200), sf::Vector2f(100, 55),
		stateData.resources[TextureID::MessageboxBackground], stateData.resources[TextureID::GreyButton100x50], stateData.resources.font,
		L"Czy na pewno chcesz zresetowac sterowanie?", L"Tak", L"Nie");
}

