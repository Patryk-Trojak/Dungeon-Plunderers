#pragma once
#include "Bar.h"
#include "Resources.h"

class PlayerHealthBar :
	public Bar
{
public:
	PlayerHealthBar(const sf::Vector2f& Position, const Resources& resources,
		const int InitialHp, const int currentHp);
	virtual ~PlayerHealthBar();
};

