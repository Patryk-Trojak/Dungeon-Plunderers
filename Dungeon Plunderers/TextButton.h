#pragma once
#include "Button.h"
#include <set>

class TextButton
	:public Button
{
public:
	TextButton(const sf::Vector2f& Position, const sf::Vector2f& Size,
		const sf::Texture& Texture, const sf::Font& Font,
		const std::wstring Text, const unsigned CharacterSize, ContentAlignment howAlignText = ContentAlignment::center, const float LeftMargin = 10,
		const sf::Color IdleColor = sf::Color::White, const sf::Color HoverColor = sf::Color::Red);

	virtual ~TextButton();
	void setText(const std::string textOfButton, ContentAlignment howAlignText = ContentAlignment::center);
	void setWstring(const std::wstring wstring, ContentAlignment howAlignText = ContentAlignment::center);
	void setPosition(const sf::Vector2f& Position);
	void adjustButtonsSizeToText();
	void setSize(const sf::Vector2f& size);
	sf::String getText() const;
protected:
	sf::Text text;
	ContentAlignment currentAlignment;
	void updateOriginOfText();
	void alignContent(ContentAlignment howAlignText);
	float leftMargin;
	int countLines();
	sf::String::ConstIterator findFirstCharacterOfLastLine();
	void centerContentVertically();
	bool isLetterWithDescenderInLastLineOfText();
	float calculateDescenderHeight();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

