#include "pch.h"
#include "PlayerHealthBar.h"

PlayerHealthBar::PlayerHealthBar(const sf::Vector2f& Position, const Resources& resources,
	const int InitialHp, const int currentHp)
	:Bar(Position, resources[TextureID::PlayerHealthBarBackground], resources[TextureID::PlayerHealthBarHealth], resources.font,
		InitialHp, currentHp, sf::Vector2f(57.f, 3.f))
{
	value.setOrigin(0.f, 10.f);
}

PlayerHealthBar::~PlayerHealthBar()
{
}

