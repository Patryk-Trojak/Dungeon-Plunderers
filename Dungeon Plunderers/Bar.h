#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Bar
	: public sf::Drawable
{
public:
	Bar(const sf::Vector2f& Position, const sf::Texture& textureOfBackground, const sf::Texture& textureOfBar, const sf::Font& font,
		const int maxValue, const int currentValue, 
		const sf::Vector2f& offsetOfBar = sf::Vector2f(0.f, 0.f), const sf::Vector2f& offset = sf::Vector2f(0.f, 0.f));
	virtual ~Bar();
	void setValue(const int newValue);
	void setMaxValue(const int newMaxValue);
	void setPosition(const sf::Vector2f& Position);
	sf::Vector2f getOffset() const;
	sf::Vector2f getSize() const;
protected:
	sf::Sprite background;
	sf::Sprite bar;
	sf::Text value;
	const sf::Vector2f initialSizeOfBarTexture;
	const sf::Vector2f offset;
	const sf::Vector2f offsetOfBar;
	int maxValue;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
