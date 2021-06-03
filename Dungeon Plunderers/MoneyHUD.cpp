#include "pch.h"
#include "MoneyHUD.h"

MoneyHUD::MoneyHUD(const sf::Vector2f& Position, const Resources& resources, const int Money)
{
	money.setFont(resources.font);
	money.setString(std::to_string(Money));
	money.setPosition(sf::Vector2f(Position.x + 80, Position.y - 12));
	money.setCharacterSize(65);
	money.setOutlineThickness(3.f);
	money.setLetterSpacing(1.2);

	coin.setTexture(resources[TextureID::Coin]);
	coin.setTextureRect(sf::IntRect(0, 0, 50.f, 50.f));
	coin.setPosition(Position);
}

MoneyHUD::~MoneyHUD()
{
}

void MoneyHUD::setMoney(const int Money)
{
	money.setString(std::to_string(Money));
}

void MoneyHUD::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(coin, states);
	target.draw(money, states);
}
