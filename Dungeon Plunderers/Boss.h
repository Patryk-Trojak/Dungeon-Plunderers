#pragma once
#include <SFML/System/Vector2.hpp>
#include <random>
#include <cmath>
#define _USE_MATH_DEFINES 
#include <math.h>

class Boss
{
public:
	Boss();
protected:
	float timerOfWave{ 0 };
	bool Move{ false };
	bool jump{false};
	float distanceMovedFalling{ 0 };
	sf::Vector2f initialPositionOfProjectiles;
	int numberOfCurrentWave{ 0 };
	int numberOfAttacksInWave{ 0 };
	int damageOfProjectiles{ 0 };

	std::random_device dev;
	std::mt19937 rng;
	int rand(const int min, const int max);
};

