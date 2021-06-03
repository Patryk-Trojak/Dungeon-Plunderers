#include "pch.h"
#include "MessageBox.h"

using namespace game;

MessageBox::MessageBox(const sf::Vector2f& Position, const sf::Vector2f& Size, const sf::Vector2f& sizeOfButtons,
	const sf::Texture& BackgroundTexture, const sf::Texture& ButtonsTexture, const sf::Font& Font,
	const std::wstring& TextOfMessageBox, const std::wstring& TextOfFirstOptionButton, const std::wstring& TextOfSecondOptionButton)
	:firstOption(sf::Vector2f(Position.x + 50, Position.y + Size.y - 70) - Size / 2.f, sizeOfButtons, ButtonsTexture, Font, TextOfFirstOptionButton, 35),
	secondOption(sf::Vector2f(Position.x + Size.x - 150, Position.y + Size.y - 70) - Size / 2.f, sizeOfButtons, ButtonsTexture, Font, TextOfSecondOptionButton, 35),
	background(Size)
{
	background.setPosition(Position - Size / 2.f);
	background.setTexture(&BackgroundTexture);
	text.setFont(Font);
	text.setString(TextOfMessageBox);
	text.setCharacterSize(40);
	text.setFillColor(sf::Color::White);
	text.setOutlineThickness(2);
	text.setOutlineColor(sf::Color::Black);
	text.setPosition(background.getPosition().x + background.getSize().x / 2 - text.getGlobalBounds().width / 2, background.getPosition().y + 20);

	firstOption.adjustButtonsSizeToText();
	secondOption.adjustButtonsSizeToText();

	if (firstOption.getSize().x > secondOption.getSize().x)
		secondOption.setSize(firstOption.getSize());
	else
		firstOption.setSize(secondOption.getSize());

	alignButtons();
}


MessageBox::~MessageBox()
{
}

bool MessageBox::FirstOptionWasPressed(const sf::Vector2f& mousePosition, const bool wasMouseLeftButtonPressed)
{
	if (firstOption.wasPressed(mousePosition, wasMouseLeftButtonPressed))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool MessageBox::SecondOptionWasPressed(const sf::Vector2f& mousePosition, const bool wasMouseLeftButtonPressed)
{
	if (secondOption.wasPressed(mousePosition, wasMouseLeftButtonPressed))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void MessageBox::update(const sf::Vector2f& mousePosition)
{
	firstOption.update(mousePosition);
	secondOption.update(mousePosition);
}

void MessageBox::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(background, states);
	target.draw(text, states);
	target.draw(firstOption, states);
	target.draw(secondOption, states);
}

void game::MessageBox::alignButtons()
{
	firstOption.setPosition(sf::Vector2f(background.getPosition().x + 50, background.getPosition().y + background.getSize().y - 70));
	secondOption.setPosition(sf::Vector2f(background.getPosition().x + background.getSize().x - 50.f - secondOption.getSize().x, background.getPosition().y + background.getSize().y - 70) );
}
