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
	updateOriginOfText();
	currentAlignment = howAlignText;
	alignContent(howAlignText);
}

TextButton::~TextButton()
{
}

void TextButton::setText(const std::string textOfButton, ContentAlignment howAlignText)
{
	text.setString(textOfButton);
	updateOriginOfText();
	alignContent(howAlignText);
	currentAlignment = howAlignText;
}

void TextButton::setWstring(const std::wstring wstring, ContentAlignment howAlignText)
{
	text.setString(wstring);
	updateOriginOfText();
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
		text.setPosition(shape.getPosition().x + shape.getSize().x / 2 - text.getGlobalBounds().width / 2, text.getPosition().y);
		break;
	case ContentAlignment::left:
		text.setPosition(shape.getPosition().x + leftMargin, text.getPosition().y);
		break;
	case ContentAlignment::right:
		text.setPosition(shape.getPosition().x + shape.getSize().x - text.getGlobalBounds().width - 10, text.getPosition().y);
		break;
	}

	centerContentVertically();
}


int TextButton::countLines()
{
	int numberOfLines = 1;
	for (auto const& i : text.getString())
		if (static_cast<int>(i) == 10)
			numberOfLines++;
	return numberOfLines;
}

sf::String::ConstIterator TextButton::findFirstCharacterOfLastLine()
{
	int numberOfLines = countLines();
	if (numberOfLines == 1)
		return text.getString().begin();

	int endOfLineCharacterFound = 0;
	for (auto i = text.getString().begin(); i != text.getString().end(); i++)
	{
		if (static_cast<int>(*i) == 10)
		{
			endOfLineCharacterFound++; 
			if (endOfLineCharacterFound == numberOfLines - 1)
				return i;
		}
	}
	return text.getString().begin();
}

void TextButton::centerContentVertically()
{
	float heightOfTextWithoutDescenderHeight = text.getGlobalBounds().height;
	if (isLetterWithDescenderInLastLineOfText())
		heightOfTextWithoutDescenderHeight -= calculateDescenderHeight();

	float positionY = shape.getPosition().y + (shape.getSize().y - heightOfTextWithoutDescenderHeight) / 2.f;
	text.setPosition(text.getPosition().x, positionY);
}

bool TextButton::isLetterWithDescenderInLastLineOfText()
{
	std::set<char> lettersWithDescender{ 'q', 'y', 'p', 'g', 'j' };

	auto firstCharacterOfLastLine = findFirstCharacterOfLastLine();
	for (auto i = firstCharacterOfLastLine; i < text.getString().end(); i++)
	{
		if (lettersWithDescender.find(*i) != lettersWithDescender.end())
			return true;
	}

	return false;
}

float TextButton::calculateDescenderHeight()
{
	sf::Text a = text;
	a.setString("a");

	sf::Text y = a;
	y.setString("y");

	return y.getGlobalBounds().height - a.getGlobalBounds().height;
}

void TextButton::updateOriginOfText()
{
	text.setOrigin(0.f, 0.f);
	text.setOrigin(sf::Vector2f((text.getGlobalBounds().left - text.getPosition().x) / text.getScale().x, (text.getGlobalBounds().top - text.getPosition().y) / text.getScale().y));
}

void TextButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shape, states);
	target.draw(text, states);
}
