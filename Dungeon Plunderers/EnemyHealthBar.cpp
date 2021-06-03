#include "pch.h"
#include "EnemyHealthBar.h"

EnemyHealthBar::EnemyHealthBar(const sf::Vector2f& Position, const Resources& resources, const sf::Font& font,
	const int InitialHp, const sf::Vector2f& offset)
	:Bar(Position, resources[TextureID::EnemyHealthBarBackground], resources[TextureID::EnemyHealthBarHealth], font, InitialHp, InitialHp, sf::Vector2f(1.f, 1.f), offset)
{
	value.setCharacterSize(28.f);
	value.setOrigin(0.f, 9.f);
	value.setPosition(Position + offset + sf::Vector2f(resources[TextureID::EnemyHealthBarBackground].getSize().x / 2 - value.getGlobalBounds().width / 2, -60.f));
}

EnemyHealthBar::~EnemyHealthBar()
{
}
