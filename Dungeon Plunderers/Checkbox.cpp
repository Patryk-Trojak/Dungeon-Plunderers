#include "pch.h"
#include "Checkbox.h"

Checkbox::Checkbox(const sf::Vector2f& Position, const sf::Vector2f& Size,
	const sf::Texture& TextureOfChecked, const sf::Texture& TextureOfUnchecked, const bool checked,
	const sf::Color IdleColor, const sf::Color HoverColor)
	:Button(Position, Size, TextureOfUnchecked, sf::Vector2f(1.f, 1.f), IdleColor, HoverColor),
	textureOfChecked(TextureOfChecked),
	textureOfUnchecked(TextureOfUnchecked),
	IsChecked(checked)
{
}

Checkbox::~Checkbox()
{
}

bool Checkbox::isChecked() const
{
	return IsChecked;
}

void Checkbox::update(const sf::Vector2f& mousePosition, const bool wasMouseLeftButtonPressed)
{
	Button::update(mousePosition);
	if (wasPressed(mousePosition, wasMouseLeftButtonPressed))
	{
		if (isChecked())
		{
			IsChecked = false;
			shape.setTexture(&textureOfUnchecked);
		}
		else
		{
			IsChecked = true;
			shape.setTexture(&textureOfChecked);
		}
	}

	if(isChecked())
		shape.setFillColor(sf::Color::Green);
	else
		shape.setFillColor(sf::Color::White);

}
