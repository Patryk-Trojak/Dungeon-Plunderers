#include "pch.h"
#include "ShopButton.h"

ShopButton::ShopButton(const sf::Vector2f& Position,
	const Resources& resources, int numberOfMaxUpgrade,
	bool showPrice)
	:upgrade(Position, sf::Vector2f(50.f, 50.f), resources[TextureID::Plus]),
	downgrade(Position, sf::Vector2f(50.f, 50.f), resources[TextureID::Minus]),
	showPrice(showPrice),
	numberOfMaxUpgrade(numberOfMaxUpgrade)
{
	Price.setFont(resources.font);
	Price.setCharacterSize(30);

	NumberOfUpgrageBought.setFont(resources.font);
	NumberOfUpgrageBought.setCharacterSize(30);


	for (auto i = states.begin(); i != states.end(); i++)
	{
		i->setSize(sf::Vector2f(20.f, 30.f));
		i->setFillColor(sf::Color::Transparent);
		i->setOutlineColor(sf::Color::White);
		i->setOutlineThickness(3.f);
	}



	setPosition(Position);
}

ShopButton::~ShopButton()
{
}

void ShopButton::update(const sf::Vector2f& mousePosition)
{
	upgrade.update(mousePosition);
	downgrade.update(mousePosition);
}

void ShopButton::setPrice(int price)
{
	this->price = price;
	Price.setString(std::to_string(price));
}

void ShopButton::setNumberOfUpgradeBought(int NumberOfUpgrageBought)
{
	numberOfUpgrageBought = NumberOfUpgrageBought;
	this->NumberOfUpgrageBought.setString(std::to_string(NumberOfUpgrageBought) + "/5");

	for (auto& i : states)
		i.setFillColor(sf::Color::Transparent);

	for (int i = 0; i < numberOfUpgrageBought; i++)
		states[i].setFillColor(sf::Color::Green);


	if (NumberOfUpgrageBought >= numberOfMaxUpgrade)
	{
		upgrade.setIdleColor(sf::Color(150, 150, 150));
		upgrade.setHoverColor(sf::Color(150, 150, 150));
		downgrade.setIdleColor(sf::Color::White);
		downgrade.setHoverColor(sf::Color::Red);
	}
	else if (NumberOfUpgrageBought <= 0)
	{
		downgrade.setIdleColor(sf::Color(150, 150, 150));
		downgrade.setHoverColor(sf::Color(150, 150, 150));
		upgrade.setIdleColor(sf::Color::White);
		upgrade.setHoverColor(sf::Color::Red);
	}
	else
	{
		upgrade.setIdleColor(sf::Color::White);
		upgrade.setHoverColor(sf::Color::Red);
		downgrade.setIdleColor(sf::Color::White);
		downgrade.setHoverColor(sf::Color::Red);
	}
}

bool ShopButton::wasUpgradeButtonPressed(const sf::Vector2f& mousePosition, bool wasMousePressed) const
{
	return upgrade.wasPressed(mousePosition, wasMousePressed);
}

bool ShopButton::wasDowngradeButtonPressed(const sf::Vector2f& mousePosition, bool wasMousePressed) const
{
	return downgrade.wasPressed(mousePosition, wasMousePressed);
}

bool ShopButton::isMouseOver(const sf::Vector2f& mousePosition) const
{
	if (mousePosition.x > states.front().getPosition().x - 3.f and mousePosition.x < downgrade.getPosition().x
		and mousePosition.y > states.front().getPosition().y - 3.f and mousePosition.y < states.front().getPosition().y + states.front().getSize().y + 3.f)
		return true;

	if (mousePosition.x > downgrade.getPosition().x and mousePosition.x < upgrade.getPosition().x + upgrade.getSize().x
		and mousePosition.y > downgrade.getPosition().y and mousePosition.y < downgrade.getPosition().y + downgrade.getSize().y)
		return true;

	return false;
}

sf::Vector2f ShopButton::getPosition() const
{
	return states.front().getPosition();
}

int ShopButton::getPrice() const
{
	return price;
}

int ShopButton::getNumberOfUpgradeBought() const
{
	return numberOfUpgrageBought;
}

void ShopButton::setPosition(const sf::Vector2f& position)
{
	for (auto i = states.begin(); i != states.end(); i++)
		i->setPosition(sf::Vector2f(position.x + (i - states.begin()) * 35.f, position.y));


	downgrade.setPosition(sf::Vector2f(states.back().getPosition().x + states.back().getSize().x + 20.f, states.back().getPosition().y + states.back().getSize().y / 2 - upgrade.getSize().y / 2));
	upgrade.setPosition(sf::Vector2f(downgrade.getPosition().x + downgrade.getSize().x + 10, downgrade.getPosition().y));

	NumberOfUpgrageBought.setPosition(upgrade.getPosition().x + upgrade.getSize().x + 8, position.y - 5.f);


	Price.setPosition(position.x + 70, position.y + 30.f);
}

void ShopButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for(auto const &i : this->states)
		target.draw(i, states);

	target.draw(upgrade, states);
	target.draw(downgrade, states);
	if (showPrice)
		target.draw(Price, states);
	target.draw(NumberOfUpgrageBought, states);
}
