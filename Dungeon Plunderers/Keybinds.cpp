#include "pch.h"
#include "Keybinds.h"

Keybinds::Keybinds()
{
	add(KeybindID::MoveRight, sf::Keyboard::Key::D);
	add(KeybindID::MoveLeft, sf::Keyboard::Key::A);
	add(KeybindID::Jump, sf::Keyboard::Key::Space);
	add(KeybindID::FirstWeapon, sf::Keyboard::Key::Num1);
	add(KeybindID::SecondWeapon, sf::Keyboard::Key::Num2);
	add(KeybindID::ThirdWeapon, sf::Keyboard::Key::Num3);
	add(KeybindID::MoveRightPlaneOrCloud, sf::Keyboard::Key::D);
	add(KeybindID::MoveLeftPlaneOrCloud, sf::Keyboard::Key::A);
	add(KeybindID::MoveUpPlaneOrCloud, sf::Keyboard::Key::W);
	add(KeybindID::MoveDownPlaneOrCloud, sf::Keyboard::Key::S);
	add(KeybindID::GetOffPlaneOrCloud, sf::Keyboard::Key::E);
	add(KeybindID::Attack, 101); //Left mouse button
	add(KeybindID::DrinkHealthPotion, sf::Keyboard::Key::Z);
	add(KeybindID::DrinkManaPotion, sf::Keyboard::Key::X);
}

bool Keybinds::isPressed(KeybindID ID) const
{
	if (auto found = keybinds.find(ID); found != keybinds.end())
	{
		if (found->second <= 100)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(found->second)))
				return true;
		}
		else
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button((found->second - 101))))
				return true;
		}
	}
 
	return false;
}

void Keybinds::add(KeybindID ID, int numberOfKey)
{
	keybinds.insert(std::pair< KeybindID, int >(ID, numberOfKey));
}

void Keybinds::changeKeybind(KeybindID ID, int numberOfKey)
{
	keybinds[ID] = numberOfKey;
}

int Keybinds::operator[](KeybindID ID) const
{
	return keybinds.at(ID);
}
