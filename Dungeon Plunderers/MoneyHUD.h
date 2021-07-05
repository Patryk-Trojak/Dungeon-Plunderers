#pragma once
#include<SFML/Graphics.hpp>
#include "Resources.h"

class MoneyHUD
	:public sf::Drawable
{
public:
	MoneyHUD(const sf::Vector2f& Position, const Resources& resources, const int Money);
	virtual ~MoneyHUD();
	void setMoney(const int Money);
	void setPosition(const sf::Vector2f& position);
private:
	sf::Text money;
	sf::Sprite coin;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

