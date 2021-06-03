#include "pch.h"
#include "Slider.h"

Slider::Slider(const sf::Vector2f& Position, const sf::Vector2f& Size, const float min, const float max, const float innitialValue,
	const sf::Texture& textureOfSlider, const sf::Texture& textureOfAxis, const sf::Texture& textureOfButtons, const sf::Font& font)
	: value(innitialValue),
	slider(Size),
	axis(sf::Vector2f(Size.y - 1, Size.y * 2.33)),
	Value(std::to_string(value).substr(0, std::to_string(value).length() - 4), font),
	increaser(Position + sf::Vector2f(Size.x, -(ceil(Size.y * 1.53f) - slider.getSize().y) / 2), sf::Vector2f(Size.y * 2.f, ceil(Size.y * 1.53f)), textureOfButtons),
	decreaser(Position + sf::Vector2f(0.f, -(ceil(Size.y * 1.53f) - slider.getSize().y) / 2), sf::Vector2f(Size.y * 2.f, ceil(Size.y * 1.53f)), textureOfButtons, sf::Vector2f(-1.f, 1.f)),
	min(min),
	max(max),
	slide(false),
	wasSlided(false)
{
	slider.setPosition(Position);
	slider.setTexture(&textureOfSlider);
	axis.setPosition(sf::Vector2f(Position.x + (value - min) / max * Size.x, Position.y - (axis.getSize().y - slider.getSize().y) / 2));
	axis.setTexture(&textureOfAxis);

	Value.setString(std::to_string(value).substr(0, std::to_string(value).length() - 4));
	Value.setPosition(slider.getPosition() + sf::Vector2f(slider.getSize().x / 2.f - Value.getGlobalBounds().width / 2, -Value.getGlobalBounds().height * 2));
	Value.setOutlineColor(sf::Color::Black);
	Value.setOutlineThickness(2);
	PositionXOfAxisRelativeToSlider = axis.getPosition().x - slider.getPosition().x;
}

Slider::~Slider()
{
}

void Slider::update(const sf::Vector2f& mousePosition, const bool wasMouseLeftButtonPressed, const float deltaTime)
{
	lastValue = value;
	WasValueChanged = false;
	if ((slider.getGlobalBounds().contains(mousePosition) or axis.getGlobalBounds().contains(mousePosition))and sf::Mouse::isButtonPressed(sf::Mouse::Left))
		slide = true;
	if(!sf::Mouse::isButtonPressed(sf::Mouse::Left))
		slide = false;
	increaser.update(mousePosition);
	decreaser.update(mousePosition);
	increaser.countTimeOfClick(mousePosition, wasMouseLeftButtonPressed, deltaTime);
	decreaser.countTimeOfClick(mousePosition, wasMouseLeftButtonPressed, deltaTime);

	if (increaser.wasPressed(mousePosition, wasMouseLeftButtonPressed))
	{
		axis.move(sf::Vector2f(slider.getSize().x / 10.f, 0));
		wasSlided = true;
	}

	if (decreaser.wasPressed(mousePosition, wasMouseLeftButtonPressed))
	{
		axis.move(sf::Vector2f(-slider.getSize().x / 10.f, 0));
		wasSlided = true;
	}

	if (increaser.getTimeOfClick() > 0.4f)
	{
		axis.move(sf::Vector2f(slider.getSize().x / 25.f * deltaTime, 0));
		wasSlided = true;
	}

	if (decreaser.getTimeOfClick() > 0.4f)
	{
		axis.move(sf::Vector2f(-slider.getSize().x / 25.f * deltaTime, 0));
		wasSlided = true;
	}



	if (slide)
	{
		axis.setPosition(sf::Vector2f(mousePosition.x - axis.getSize().x / 2, axis.getPosition().y));	
		wasSlided = true;
	}

	if (wasSlided)
	{
		if (axis.getPosition().x < slider.getPosition().x)
			axis.setPosition(sf::Vector2f(slider.getPosition().x, axis.getPosition().y));
		if (axis.getPosition().x + axis.getSize().x > slider.getPosition().x + slider.getSize().x)
			axis.setPosition(sf::Vector2f(slider.getPosition().x + slider.getSize().x - axis.getSize().x, axis.getPosition().y));
		value = ((max - min) * ((axis.getPosition().x - slider.getPosition().x) / (slider.getSize().x - axis.getSize().x)) + min);
		Value.setString(std::to_string(value).substr(0, std::to_string(value).length() - 4));
		Value.setPosition(slider.getPosition() + sf::Vector2f(slider.getSize().x / 2.f - Value.getGlobalBounds().width / 2, -Value.getGlobalBounds().height * 2));
		PositionXOfAxisRelativeToSlider = axis.getPosition().x - slider.getPosition().x;
		wasSlided = false;
		if (lastValue == value)
			WasValueChanged = false;
		else
			WasValueChanged = true;
	}
}

void Slider::setPosition(const sf::Vector2f& Position)
{
	slider.setPosition(Position);
	axis.setPosition(sf::Vector2f(Position.x + PositionXOfAxisRelativeToSlider, Position.y - (axis.getSize().y - slider.getSize().y) / 2));
	increaser.setPosition(Position + sf::Vector2f(slider.getSize().x, -(increaser.getSize().y - slider.getSize().y) / 2));
	decreaser.setPosition(Position + sf::Vector2f(0.f, -(increaser.getSize().y - slider.getSize().y) / 2));
	Value.setPosition(slider.getPosition() + sf::Vector2f(slider.getSize().x / 2.f - Value.getGlobalBounds().width / 2, -Value.getGlobalBounds().height * 2));
}

sf::Vector2f Slider::getPosition() const
{
	return slider.getPosition();
}

float Slider::getValue() const
{
	return value;
}

void Slider::setMin(const float newMin)
{
	min = newMin;
	axis.setPosition(slider.getPosition().x + (value - min) * (slider.getSize().x - axis.getSize().x) / (max - min), axis.getPosition().y);
}

void Slider::setMax(const float newMax)
{
	max = newMax;
	axis.setPosition(slider.getPosition().x + (value - min) * (slider.getSize().x - axis.getSize().x) / (max - min), axis.getPosition().y);
}

void Slider::setValue(const float newValue)
{
	value = newValue;
	axis.setPosition(slider.getPosition().x + (value - min) * (slider.getSize().x - axis.getSize().x) / (max - min), axis.getPosition().y);
	if (axis.getPosition().x < slider.getPosition().x)
		axis.setPosition(sf::Vector2f(slider.getPosition().x, axis.getPosition().y));
	if (axis.getPosition().x + axis.getSize().x > slider.getPosition().x + slider.getSize().x)
		axis.setPosition(sf::Vector2f(slider.getPosition().x + slider.getSize().x - axis.getSize().x, axis.getPosition().y));
	value = ((max - min) * ((axis.getPosition().x - slider.getPosition().x) / (slider.getSize().x - axis.getSize().x)) + min);
	Value.setString(std::to_string(value).substr(0, std::to_string(value).length() - 4));
	Value.setPosition(slider.getPosition() + sf::Vector2f(slider.getSize().x / 2.f - Value.getGlobalBounds().width / 2, -Value.getGlobalBounds().height * 2));
	PositionXOfAxisRelativeToSlider = axis.getPosition().x - slider.getPosition().x;
}

bool Slider::isSliding() const
{
	return slide;
}


bool Slider::wasValueChanged() const
{
	return WasValueChanged;
}

bool Slider::isMouseOver(const sf::Vector2f& mousePosition) const
{
	if (increaser.isMouseOverButton(mousePosition) or decreaser.isMouseOverButton(mousePosition)
		or slider.getGlobalBounds().contains(mousePosition) or axis.getGlobalBounds().contains(mousePosition))
		return true;

	return false;
}

void Slider::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(slider, states);
	target.draw(axis, states);
	target.draw(increaser, states);
	target.draw(decreaser, states);
	target.draw(Value, states);
}
