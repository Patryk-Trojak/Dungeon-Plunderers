#include "pch.h"
#include "AmmoHUD.h"

AmmoHUD::AmmoHUD(const sf::Vector2f& Position, const Resources& resources,
	const std::string& CurrentAmmo)
{
	currentAmmo.setFont(resources.font);
	currentAmmo.setPosition(Position);
	currentAmmo.setCharacterSize(40);
	currentAmmo.setFillColor(sf::Color::White);	
	currentAmmo.setOutlineThickness(1.5);

	infinitySymbol.setTexture(resources[TextureID::InfinitySymbol]);
	infinitySymbol.setPosition(sf::Vector2f(Position.x + 100, Position.y + 12));
	setCurrentAmmo(CurrentAmmo);
}

AmmoHUD::~AmmoHUD()
{
}


void AmmoHUD::setCurrentAmmo(const std::string& CurrentAmmo)
{
	if (CurrentAmmo != "Nieskonczonosc")
	{
		currentAmmo.setString("Ammo: " + CurrentAmmo);
	}
	else
	{
		currentAmmo.setString("Ammo: ");
	}
}

void AmmoHUD::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (currentAmmo.getString() == "Ammo: ")
	{
		target.draw(infinitySymbol, states);
	}
	target.draw(currentAmmo);
}
