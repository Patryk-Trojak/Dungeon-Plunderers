#pragma once
#include "Bar.h"
#include"Resources.h"

class EnemyHealthBar :
	public Bar
{
public:
	EnemyHealthBar(const sf::Vector2f& Position, const Resources& resources, const sf::Font& font,
		const int InitialHp, const sf::Vector2f& offset);
	virtual ~EnemyHealthBar();
};

