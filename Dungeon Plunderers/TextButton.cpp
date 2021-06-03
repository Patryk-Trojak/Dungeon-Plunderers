#include "pch.h"
#include "TextButton.h"


TextButton::TextButton(const sf::Vector2f& Position, const sf::Vector2f& Size,
	const sf::Texture& Texture, const sf::Font& Font,
	const std::wstring Text, const unsigned CharacterSize, ContentAlignment howAlignText, const float LeftMargin,
	const sf::Color IdleColor, const sf::Color HoverColor)
	:Button(Position, Size, Texture, sf::Vector2f(1.f, 1.f),IdleColor, HoverColor),
	leftMargin(LeftMargin)
{
	state = ButtonState::idle;
	text.setString(Text);
	text.setCharacterSize(CharacterSize);
	text.setFillColor(sf::Color::White);
	text.setOutlineThickness(2);
	text.setOutlineColor(sf::Color::Black);
	text.setFont(Font);
	text.setOrigin(sf::Vector2f(0.f, text.getCharacterSize() * 0.4f));
	currentAlignment = howAlignText;
	alignContent(howAlignText);
}

TextButton::~TextButton()
{
}

void TextButton::setText(const std::string textOfButton, ContentAlignment howAlignText)
{
	text.setString(textOfButton);
	alignContent(howAlignText);
	currentAlignment = howAlignText;
}

void TextButton::setWstring(const std::wstring wstring, ContentAlignment howAlignText)
{
	text.setString(wstring);
	alignContent(howAlignText);
	currentAlignment = howAlignText;
}

void TextButton::setPosition(const sf::Vector2f& Position)
{
	shape.setPosition(Position);
	alignContent(currentAlignment);
}

void TextButton::adjustButtonsSizeToText()
{
	if (text.getGlobalBounds().width > shape.getSize().x)
	{
		shape.setSize(sf::Vector2f(text.getGlobalBounds().width + 20, shape.getSize().y));
		alignContent(currentAlignment);
	}
}

void TextButton::setSize(const sf::Vector2f& size)
{
	Button::setSize(size);
	alignContent(currentAlignment);
}

sf::String TextButton::getText() const
{
	return text.getString();
}

void TextButton::alignContent(ContentAlignment howAlignText)
{
	switch (howAlignText)
	{
	case ContentAlignment::center:
			text.setPosition(shape.getPosition().x + shape.getSize().x / 2 - text.getGlobalBounds().width / 2, shape.getPosition().y + shape.getSize().y / 2 - text.getCharacterSize() * 0.3f  - text.getCharacterSize() * countLines() );
		break;
	case ContentAlignment::left:
		text.setPosition(shape.getPosition().x + leftMargin, shape.getPosition().y + shape.getSize().y / 2 - text.getCharacterSize() * 0.3f  - text.getCharacterSize() * countLines() * 0.6);
		break;
	case ContentAlignment::right:
		text.setPosition(shape.getPosition().x + shape.getSize().x - text.getGlobalBounds().width - 10, shape.getPosition().y + shape.getSize().y / 2 - text.getCharacterSize() * 0.3f - text.getLineSpacing() * countLines());
		break;
	}
}


int TextButton::countLines()
{
	int numberOfLines = 0;
	for (auto const& i : text.getString())
		if (static_cast<int>(i) == 10)
			numberOfLines++;
	return numberOfLines;
}

void TextButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shape, states);
	target.draw(text, states);
}
