#pragma once
#include <SFML/Graphics.hpp>

class SettingsData
{
public:
	SettingsData();
	bool fullscreen;
	sf::Vector2u windowSize;
	sf::Vector2i windowPosition;
	bool resizeProportionally;
	bool isVerticalSyncEnabled;
	bool isLimitFPSEnabled;
	unsigned maxFPS;
	bool showFPS;
	bool FPSOnTop;
	bool FPSOnLeft;
	unsigned int characterSizeOfFPS;
	sf::Color colorOfFPS;
	bool showOutlineFPS;
	unsigned int outlineThickness;
	sf::Color colorOfOutlineFPS;
};

