#pragma once
#include <SFML/Graphics.hpp>
#include <stack>
#include "Resources.h"

class AmmoHUD
	:public sf::Drawable
{
public:
	AmmoHUD(const sf::Vector2f& Position, const Resources& resources,
		const std::string& CurrentAmmo);
	virtual ~AmmoHUD();
	void setCurrentAmmo(const std::string& CurrentAmmo);
private:
	sf::Text currentAmmo;
	sf::Sprite infinitySymbol;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

