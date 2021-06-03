#include "pch.h"
#include "Textbox.h"


Textbox::Textbox(const sf::Vector2f& Position, const sf::Vector2f& Size,
	const sf::Texture& Background,
	const sf::Font& Font, const std::string& InitialText, const unsigned int CharacterSize,
	const std::vector<sf::Uint32>& UnavailableASCIIUnicode, ContentAlignment howAlignText, bool isActive)
	:textCursor(Position, sf::Vector2f(3, Size.y * 0.8f)),
	unavailableASCIIUnicode(UnavailableASCIIUnicode),
	IsActive(isActive),
	currentAlignment(howAlignText)
{
	background.setPosition(Position);
	background.setSize(Size);
	background.setTexture(&Background);
	text.setFont(Font);
	text.setString(InitialText);
	text.setCharacterSize(CharacterSize);
	text.setOrigin(sf::Vector2f(0.f, text.getCharacterSize() * 0.4f));
	AlignText(howAlignText);
	text.setOutlineThickness(2);
	text.setOutlineColor(sf::Color::Black);
}


Textbox::~Textbox()
{
}

void Textbox::handleTextEntered(sf::Uint32 unicode)
{
	if (isASCIIUnicodeAvaible(unicode))
	{
		if (unicode == 8) //BACKSPACE
		{
			deleteLastCharacterOfSaveButtonName();
		}
		else if(unicode != 13 and unicode != 27) //ENTER AND ESCAPE
		{
			if (text.getGlobalBounds().width <= background.getSize().x - 60)
				text.setString(text.getString() + static_cast<char>(unicode));
		}
		AlignText(currentAlignment);
	}
}

void Textbox::updateTextCursor(const float deltaTime)
{
	textCursor.update(deltaTime, sf::Vector2f(text.getPosition().x + text.getGlobalBounds().width + 4, background.getPosition().y + background.getSize().y * 0.1f));
}

std::string Textbox::getText() const
{
	return text.getString();
}

void Textbox::update(const sf::Vector2f& mousePosition, const bool wasMouseLeftButtonPressed, const float deltaTime)
{
	updateTextCursor(deltaTime);
	if (wasMouseLeftButtonPressed and background.getGlobalBounds().contains(mousePosition))
		IsActive = true;

	if (wasMouseLeftButtonPressed and !background.getGlobalBounds().contains(mousePosition))
		IsActive = false;

}

bool Textbox::isActive() const
{
	return IsActive;
}

void Textbox::setActive(const bool isActive)
{
	IsActive = isActive;
}

bool Textbox::wasPressed(const sf::Vector2f& mousePosition, const bool wasMouseLeftButtonPressed)
{
	if (background.getGlobalBounds().contains(mousePosition) and wasMouseLeftButtonPressed)
		return true;

	return false;
}

void Textbox::setPosition(const sf::Vector2f& Position)
{
	background.setPosition(Position);
	AlignText(currentAlignment);
}

void Textbox::setText(const std::string& Text)
{
	text.setString(Text);
	AlignText(currentAlignment);
}

void Textbox::setColor(const sf::Color& color)
{
	background.setFillColor(color);
}

void Textbox::AlignText(ContentAlignment howAlignText)
{
	switch (howAlignText)
	{
	case ContentAlignment::center:
		text.setPosition(background.getPosition().x + background.getSize().x / 2 - text.getGlobalBounds().width / 2, background.getPosition().y + background.getSize().y / 2 - text.getCharacterSize() * 0.3f);
		break;
	case ContentAlignment::left:
		text.setPosition(background.getPosition().x + 13, background.getPosition().y + background.getSize().y / 2 - text.getCharacterSize() * 0.3f);
		break;
	case ContentAlignment::right:
		text.setPosition(background.getPosition().x + background.getSize().x - text.getGlobalBounds().width - 10, background.getPosition().y + background.getSize().y / 2 - text.getCharacterSize() * 0.3f);
		break;
	}
}

void Textbox::deleteLastCharacterOfSaveButtonName()
{
	if (text.getString().getSize() > 0)
	{
		std::string newName = text.getString();
		newName.pop_back();
		text.setString(newName);
	}
}

bool Textbox::isASCIIUnicodeAvaible(sf::Uint32 unicode)
{
	for (auto const & i : unavailableASCIIUnicode)
	{
		if (unicode == i)
		{
			return false;
		}
	}
	return true;
}

void Textbox::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(background, states);
	target.draw(text, states);
	if(isActive())
		target.draw(textCursor);
}
