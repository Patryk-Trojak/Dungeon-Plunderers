#include "pch.h"
#include "ManaBar.h"
#include "pch.h"
#include "ManaBar.h"

ManaBar::ManaBar(const sf::Vector2f& position, const Resources& resources,
	const int initialMana, const int currentMana)
	:Bar(position, resources[TextureID::ManaBarBackground], 
		resources[TextureID::ManaBarMana], resources.font,
		initialMana, currentMana, 
		sf::Vector2f(54.f, 3.f))
{
	value.setOrigin(0.f, 10.f);
}


ManaBar::~ManaBar()
{
}