#pragma once
#include <SFML/Graphics.hpp>
#include "Bar.h"
#include "Resources.h"

class ManaBar
	: public Bar
{
public:
	ManaBar(const sf::Vector2f& position, const Resources& resources,
		const int initialMana, const int currentMana);
	virtual ~ManaBar();
};

