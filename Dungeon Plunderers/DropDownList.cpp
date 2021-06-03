#include "pch.h"
#include "DropDownList.h"

DropDownList::DropDownList(const sf::Vector2f& position, const sf::Vector2f& sizeOfOption,  const std::wstring& textOfFirstOption,
	const sf::Texture& texturesOfOptions, const sf::Font& font, const float characterSize,
	ContentAlignment howAlignText, const float leftMarginOfOptions,
	const sf::Color idleColorOfOptions, const sf::Color hoverColorOfOptions)
	:font(font),
	texturesOfOptions(texturesOfOptions),
	characterSize(characterSize),
	alignmentOfOptions(howAlignText),
	leftMarginOfOptions(leftMarginOfOptions),
	idleColorOfOptions(idleColorOfOptions),
	hoverColorOfOptions(hoverColorOfOptions),
	chosenOption(position, sizeOfOption, texturesOfOptions, font, textOfFirstOption, characterSize, howAlignText, leftMarginOfOptions, idleColorOfOptions, hoverColorOfOptions),
	numberOfChosenOption(0),
	isDropped(false),
	WasNewOptionChosen(false)
{
	options.emplace_back(chosenOption);
	options.back().setPosition(position + sf::Vector2f(0.f, sizeOfOption.y));
	chosenOption.setIdleColor(sf::Color(160, 160, 160));
}

DropDownList::~DropDownList()
{
}

void DropDownList::addOption(const std::wstring& textOfOption)
{
	options.emplace_back(sf::Vector2f(chosenOption.getPosition().x, options.back().getPosition().y + chosenOption.getSize().y), chosenOption.getSize(), 
		texturesOfOptions, font, 
		textOfOption, characterSize, alignmentOfOptions, leftMarginOfOptions, 
		idleColorOfOptions, hoverColorOfOptions);
}

void DropDownList::update(const sf::Vector2f& mousePosition, const bool wasMouseLeftButtonPressed)
{
	chosenOption.update(mousePosition);
	WasNewOptionChosen = false;
	if (isDropped)
	{
		for (auto i = options.begin(); i != options.end(); i ++)
		{
			i->update(mousePosition);
			if (i->wasPressed(mousePosition, wasMouseLeftButtonPressed))
			{
				chosenOption.setWstring(i->getText());
				numberOfChosenOption = i - options.begin();
				WasNewOptionChosen = true;
			}
		}
	}
	
	if (isDropped)
	{
		if (wasMouseLeftButtonPressed)
			isDropped = false;
	}
	else
	{
		if (chosenOption.wasPressed(mousePosition, wasMouseLeftButtonPressed))
			isDropped = true;
	}
}

int DropDownList::getNumberOfChosenOption() const
{
	return numberOfChosenOption;
}

bool DropDownList::wasNewOptionChosen() const
{
	return WasNewOptionChosen;
}

bool DropDownList::wasPressed(const sf::Vector2f& mousePosition, const bool wasMouseLeftButtonPressed) const
{
	if (chosenOption.wasPressed(mousePosition, wasMouseLeftButtonPressed))
		return true;
	if (isDropped)
	{
		for (auto const& i : options)
		{
			if (i.wasPressed(mousePosition, wasMouseLeftButtonPressed))
				return true;
		}	
	}
		
	return false;
}

void DropDownList::setPosition(const sf::Vector2f& position)
{
	chosenOption.setPosition(position);
	for (auto i = options.begin(); i != options.end(); i++)
		i->setPosition(sf::Vector2f(position.x, position.y + chosenOption.getSize().y + (i - options.begin()) * i->getSize().y ));
}

void DropDownList::setTextOfChosenOption(const std::wstring& text)
{
	chosenOption.setWstring(text, alignmentOfOptions);
}

void DropDownList::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(chosenOption, states);
	if (isDropped)
		for (auto const& i : options)
			target.draw(i, states);
}
