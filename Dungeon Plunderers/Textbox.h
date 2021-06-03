#pragma once
#include "TextCursor.h"
#include <vector>
#include "Button.h"

class Textbox
	:public sf::Drawable
{
public:
	Textbox(const sf::Vector2f& Position, const sf::Vector2f& Size,
		const sf::Texture& Background, 
		const sf::Font& Font, const std::string& InitialText, const unsigned int CharacterSize, 
		const std::vector<sf::Uint32>& UnavailableASCIIUnicode = std::vector<sf::Uint32>(), ContentAlignment howAlignText = ContentAlignment::center, bool isActive = false);
	~Textbox();
	void handleTextEntered(sf::Uint32 unicode);
	void updateTextCursor(const float deltaTime);
	std::string getText() const;
	void update(const sf::Vector2f& mousePosition, const bool wasMouseLeftButtonPressed, const float deltaTime);
	bool isActive() const;
	void setActive(const bool isActive);
	bool wasPressed(const sf::Vector2f& mousePosition, const bool wasMouseLeftButtonPressed);
	void setPosition(const sf::Vector2f& Position);
	void setText(const std::string& Text);
	void setColor(const sf::Color& color);
	void setSize(const sf::Vector2f& size);
private:
	sf::RectangleShape background;
	sf::Text text;
	TextCursor textCursor;
	std::vector<sf::Uint32> unavailableASCIIUnicode;
	ContentAlignment currentAlignment;
	bool IsActive;
	void AlignText(ContentAlignment howAlignText);
	void deleteLastCharacterOfSaveButtonName();
	bool isASCIIUnicodeAvaible(sf::Uint32 unicode);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

