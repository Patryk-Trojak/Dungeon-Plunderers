#include "pch.h"
#include "PotionBar.h"

PotionBar::PotionBar(const sf::Vector2f& Position,
	const sf::Texture& TextureOfPotionBar, const sf::Texture& TextureOfPotion,
	const int CurrentNumberOfPotion)

	:currentNumberOfPotion(CurrentNumberOfPotion)
{
	potionBar.setTexture(TextureOfPotionBar);
	potionBar.setPosition(Position);

	for (auto& i : potions)
		i.setTexture(TextureOfPotion);
	setPositionOfPotions(Position);
}

PotionBar::~PotionBar()
{
}

void PotionBar::setCurrentNumberOfPotion(const int CurrentNumberOfPotion)
{
	currentNumberOfPotion = CurrentNumberOfPotion;
}

void PotionBar::setPositionOfPotions(const sf::Vector2f& Position)
{
	auto potion = potions.begin();
	while (potion != potions.end())
	{
		potion->setPosition(sf::Vector2f(Position.x + 12.f + (potion - potions.begin()) * 56.f, Position.y + 8.f));
		potion++;
	}
}

void PotionBar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(potionBar);
	for (int i = 0; i < currentNumberOfPotion; i++)
		target.draw(potions[i]);
}
