#include "pch.h"
#include "SettingsData.h"

SettingsData::SettingsData()
	:fullscreen(true),
	windowSize(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height),  //whole screen
	windowPosition(0, 0),
	resizeProportionally(true),
	isVerticalSyncEnabled(false),
	isLimitFPSEnabled(true),
	maxFPS(120),
	showFPS(false),
	FPSOnTop(true),
	FPSOnLeft(true),
	characterSizeOfFPS(25),
	colorOfFPS(255, 116, 0),
	showOutlineFPS(false),
	outlineThickness(2),
	colorOfOutlineFPS(sf::Color::Black)
{
}
