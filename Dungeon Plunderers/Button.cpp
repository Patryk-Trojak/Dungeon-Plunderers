#include "pch.h"
#include "Button.h"


Button::Button(const sf::Vector2f& Position, const sf::Vector2f& Size,
				const sf::Texture& Texture, const sf::Vector2f& Scale,
				const sf::Color IdleColor, const sf::Color HoverColor)
	:IdleColor(IdleColor), HoverColor(HoverColor), timeOfClick(0.f)
{
	state = ButtonState::idle;
	shape.setPosition(Position);
	shape.setSize(Size);
	shape.setTexture(&Texture);
	shape.setScale(Scale);
}

Button::~Button()
{
}

void Button::update(const sf::Vector2f& mousePosition)
{
	if (isMouseOverButton(mousePosition))
	{
		state = ButtonState::hover;
	}
	else
	{
		state = ButtonState::idle;
	}
	updateColorByButtonState();
}

bool Button::wasPressed(const sf::Vector2f& mousePosition, const bool wasMouseLeftButtonPressed) const
{
	if (isMouseOverButton(mousePosition) && wasMouseLeftButtonPressed)
	{
		return true;
	}
	else
	{
		return false;
	}
}


void Button::setPosition(const sf::Vector2f& Position)
{
	shape.setPosition(Position);
}

void Button::setCurrentColor(const sf::Color& color)
{
	shape.setFillColor(color);
}

void Button::setIdleColor(const sf::Color& color)
{
	IdleColor = color;
}

void Button::setHoverColor(const sf::Color& color)
{
	HoverColor = color;
}

sf::Vector2f Button::getPosition() const
{
	return shape.getPosition();
}

void Button::updateColorByButtonState()
{
	switch (state)
	{
		case ButtonState::idle:
			shape.setFillColor(IdleColor);
			break;
		case ButtonState::hover:
			shape.setFillColor(HoverColor);
			break;
	}
}


bool Button::isMouseOverButton(const sf::Vector2f& mousePosition) const
{
	if (shape.getGlobalBounds().contains(mousePosition))
	{
		return true;
	}
	else
	{
		return false;
	}
}

sf::Vector2f Button::getSize() const
{
	return shape.getSize();
}

void Button::setSize(const sf::Vector2f& size)
{
	shape.setSize(size);
}

void Button::countTimeOfClick(const sf::Vector2f& mousePosition, const bool wasMouseLeftButtonPressed, const float deltaTime)
{
	if (wasPressed(mousePosition, wasMouseLeftButtonPressed))
		isClicked = true;

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
		isClicked = false;

	if (isClicked)
		timeOfClick += deltaTime;
	else
		timeOfClick = 0;
}

float Button::getTimeOfClick() const
{
	return timeOfClick;
}


void Button::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(shape, states);
}
