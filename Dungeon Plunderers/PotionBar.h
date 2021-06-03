#pragma once
#include<SFML/Graphics.hpp>
#include<array>

class PotionBar
	:public sf::Drawable
{
public:
	PotionBar(const sf::Vector2f& Position,
		const sf::Texture& TextureOfPotionBar, const sf::Texture&TextureOfPotion,
		const int CurrentNumberOfPotion);
	virtual ~PotionBar();
	void setCurrentNumberOfPotion(const int CurrentNumberOfPotion);
private:
	void setPositionOfPotions(const sf::Vector2f& Position);
	sf::Sprite potionBar;
	std::array<sf::Sprite, 3> potions;
	int currentNumberOfPotion;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

