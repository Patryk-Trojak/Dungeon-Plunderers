#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include <fstream>
#include <iostream>

enum class KeybindID {
	MoveRight,
	MoveLeft,
	Jump,
	FirstWeapon,
	SecondWeapon,
	ThirdWeapon,
	MoveRightPlaneOrCloud,
	MoveLeftPlaneOrCloud,
	MoveUpPlaneOrCloud,
	MoveDownPlaneOrCloud,
	GetOffPlaneOrCloud,
	Attack,
	DrinkHealthPotion,
	DrinkManaPotion
};


class Keybinds
{
public:
	Keybinds();
	bool isPressed(KeybindID ID) const;
	void add(KeybindID ID, int numberOfKey);
	void changeKeybind(KeybindID ID, int numberOfKey);
	int operator[](KeybindID ID) const;

private:
	std::map<KeybindID, int> keybinds;
};

