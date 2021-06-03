#pragma once
#include "Button.h"

class Checkbox
	:public Button
{
public:
	Checkbox(const sf::Vector2f& Position, const sf::Vector2f& Size,
		const sf::Texture& TextureOfChecked, const sf::Texture& TextureOfUnchecked, const bool checked = false,
		const sf::Color IdleColor = sf::Color::White, const sf::Color HoverColor = sf::Color::Red);
	virtual ~Checkbox();
	bool isChecked() const;
	void update(const sf::Vector2f& mousePosition, const bool wasMouseLeftButtonPressed);
private:
	const sf::Texture& textureOfChecked;
	const sf::Texture& textureOfUnchecked;
	bool IsChecked;
};

