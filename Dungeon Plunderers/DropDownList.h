#pragma once
#include <SFML/Graphics.hpp>
#include "TextButton.h"

class DropDownList
	:public sf::Drawable
{
public:
	DropDownList(const sf::Vector2f& position, const sf::Vector2f& sizeOfOption, const std::wstring& textOfFirstOption,
		const sf::Texture& texturesOfOptions, const sf::Font& font,
		const float characterSize, ContentAlignment howAlignText = ContentAlignment::center, const float leftMarginOfOptions = 10,
		const sf::Color idleColorOfOptions = sf::Color::White, const sf::Color hoverColorOfOptions = sf::Color::Red);
	virtual ~DropDownList();
	void addOption(const std::wstring& textOfOption);
	void update(const sf::Vector2f& mousePosition, const bool wasMouseLeftButtonPressed); 
	int getNumberOfChosenOption() const;
	bool wasNewOptionChosen() const;
	bool wasPressed(const sf::Vector2f& mousePosition, const bool wasMouseLeftButtonPressed) const;
	void setPosition(const sf::Vector2f& position);
	void setTextOfChosenOption(const std::wstring& text);
private:
	TextButton chosenOption;
	std::vector<TextButton> options;
	int numberOfChosenOption; 
	bool isDropped;
	bool WasNewOptionChosen;
	const sf::Font& font;
	const sf::Texture& texturesOfOptions;
	const float characterSize;
	ContentAlignment alignmentOfOptions;
	const float leftMarginOfOptions;
	const sf::Color idleColorOfOptions;
	const sf::Color hoverColorOfOptions;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

