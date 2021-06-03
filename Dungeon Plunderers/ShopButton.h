#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>
#include <memory>
#include "Button.h"
#include "Resources.h"

class ShopButton
	: public sf::Drawable
{
public:
		ShopButton(const sf::Vector2f& Position,
			const Resources& resources, int numberOfMaxUpgrade,
			bool showPrice = true);
	virtual ~ShopButton();
	void update(const sf::Vector2f& mousePosition);
	void setPrice(int price);
	void setNumberOfUpgradeBought(int NumberOfUpgrageBought);
	
	bool wasUpgradeButtonPressed(const sf::Vector2f& mousePosition, bool wasMousePressed) const;
	bool wasDowngradeButtonPressed(const sf::Vector2f& mousePosition, bool wasMousePressed) const;

	bool isMouseOver(const sf::Vector2f& mousePosition) const;
	sf::Vector2f getPosition() const;
	int getPrice() const;
	int getNumberOfUpgradeBought() const;
	void setPosition(const sf::Vector2f& position);
private:
	sf::Text Price;
	sf::Text name;
	std::array<sf::RectangleShape, 5> states;
	Button downgrade;
	Button upgrade;

	sf::Color idleColorOfUpgradeButton;
	sf::Color hoverColorOfUpgradeButton;
	sf::Text NumberOfUpgrageBought;
	int numberOfUpgrageBought{0};
	int numberOfMaxUpgrade;
	int price{0};
	bool showPrice{ true };
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

