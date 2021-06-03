#include "pch.h"
#include "SaveButton.h"

SaveButton::SaveButton(const sf::Vector2f& Position,
	const sf::Texture& TextureOfSaveButton, const sf::Texture& TextureOfTextbox,
	const sf::Texture& TextureOfNameChanger, const sf::Texture& TextureOfAcceptName, const sf::Texture& TextureOfDeleteName, const sf::Texture& TextureOfDeleteSave,
	const sf::Font& Font,  const SaveButtonState initialState)
	:TextButton(Position, sf::Vector2f(825, 241),
		TextureOfSaveButton, Font,
		L"", 40),
	textureOfSaveButton(TextureOfSaveButton),
	textureOfTextbox(TextureOfTextbox),
	textureOfNameChanger(TextureOfNameChanger),
	textureOfAcceptName(TextureOfAcceptName),
	textureOfDeleteChangeOfName(TextureOfDeleteName),
	deleteSave(Position + sf::Vector2f(20.f, 170.f), sf::Vector2f(33.f, 44.f), TextureOfDeleteSave),
	font(Font),
	unavailableASCIIUnicode({ 13, 34, 42, 47, 58, 60, 62, 63, 92, 124 })
{
	saveButtonState = initialState;
	if (initialState == SaveButtonState::unchangeableName)
		transformViewFromChangeableNameToUnchangeAble();
	else
		transformViewFromUnchangeableNameToChangeAble();
	alignText();
	dateOfLastRun.setFont(font);
	setDateOfLastRun("");
	dateOfLastRun.setCharacterSize(30);
	dateOfCreation.setFont(font);
	setDateOfCreation("");
	dateOfCreation.setCharacterSize(30);
}

SaveButton::~SaveButton()
{
}

void SaveButton::updateIfIsNotChangingName(const sf::Vector2f& MousePosition, const bool wasMouseLeftButtonPressed)
{
	if (saveButtonState == SaveButtonState::unchangeableName)
	{
		alignText();
		nameChanger->update(MousePosition);

		deleteSave.update(MousePosition);
		if (!deleteSave.isMouseOverButton(MousePosition) and !nameChanger->isMouseOverButton(MousePosition))
			TextButton::update(MousePosition);
		else
			shape.setFillColor(IdleColor);
		if (nameChanger->wasPressed(MousePosition, wasMouseLeftButtonPressed))
		{
			nameBeforeAttemptToChange = text.getString();
			transformViewFromUnchangeableNameToChangeAble();
			saveButtonState = SaveButtonState::changeableName;
		}
	}
}

void SaveButton::updateIfIsChangingName(const sf::Vector2f& MousePosition, const bool wasMouseLeftButtonPressed, const float deltaTime, const bool wasNameChangeCorrectly, const bool isNameAlreadyUse)
{
	if (saveButtonState == SaveButtonState::changeableName)
	{
		shape.setFillColor(IdleColor);
		if (textbox->getText() != "" and !isNameAlreadyUse)
		{
			acceptName->update(MousePosition);
			acceptName->setIdleColor(sf::Color::White);
		}
		else
			acceptName->setCurrentColor(sf::Color(50, 50, 50));

		DeleteChangeOfName->update(MousePosition);
		textbox->updateTextCursor(deltaTime);
		if (wasMouseLeftButtonPressed || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			if (DeleteChangeOfName->wasPressed(MousePosition, wasMouseLeftButtonPressed))
			{
				text.setString(nameBeforeAttemptToChange);
				saveButtonState = SaveButtonState::unchangeableName;
				transformViewFromChangeableNameToUnchangeAble();
			}
			else if (wasNameChangeCorrectly)
			{
				saveButtonState = SaveButtonState::unchangeableName;
				transformViewFromChangeableNameToUnchangeAble();
			}
		}
	}
}


SaveButtonState SaveButton::getSaveButtonState() const
{
	return saveButtonState;
}

void SaveButton::handleEnteredTextWhenIsChangingName(sf::Uint32 unicode)
{
	if (saveButtonState == SaveButtonState::changeableName)
	{
		textbox->handleTextEntered(unicode);
		text.setString(textbox->getText());
		text.setPosition(shape.getPosition().x + shape.getSize().x / 2 - text.getGlobalBounds().width / 2, text.getPosition().y);
	}
}

std::string SaveButton::getName() const
{
	return text.getString();
}

std::string SaveButton::getNameBeforeAttemptingToChange()
{
	return nameBeforeAttemptToChange;
}

bool SaveButton::wasDeleteChangeOfNamePressed(const sf::Vector2f& MousePosition, const bool wasMouseLeftButtonPressed) const
{
	if (saveButtonState == SaveButtonState::changeableName)
	{
		return DeleteChangeOfName->wasPressed(MousePosition, wasMouseLeftButtonPressed);
	}
	else
	{
		return false;
	}
}

bool SaveButton::wasNameChangerPressed(const sf::Vector2f& MousePosition, const bool wasMouseLeftButtonPressed) const
{
	if (saveButtonState == SaveButtonState::unchangeableName)
	{
		return nameChanger->wasPressed(MousePosition, wasMouseLeftButtonPressed);
	}
	else
	{
		return false;
	}
}

void SaveButton::deleteChangeOfName()
{
	text.setString(nameBeforeAttemptToChange);
	text.setPosition(shape.getPosition().x + shape.getSize().x / 2 - text.getGlobalBounds().width / 2, text.getPosition().y);
	saveButtonState = SaveButtonState::unchangeableName;
	transformViewFromChangeableNameToUnchangeAble();
}

void SaveButton::setName(const std::string Name)
{
	text.setString(Name);
	text.setPosition(sf::Vector2f(shape.getPosition().x + shape.getSize().x / 2 - text.getGlobalBounds().width / 2 + 2, shape.getPosition().y + 29.5));
}

void SaveButton::setDateOfLastRun(const std::string& dateOfLastRun)
{
	this->dateOfLastRun.setString("Data ostatniego uruchomienia: " + dateOfLastRun);
	this->dateOfLastRun.setPosition(sf::Vector2f(shape.getPosition().x + shape.getSize().x / 2 - this->dateOfLastRun.getGlobalBounds().width / 2, shape.getPosition().y + 120));
}

const std::string SaveButton::getDateOfLastRun() const
{
	return dateOfLastRun.getString().substring(30);
}

void SaveButton::setDateOfCreation(const std::string& dateOfCreation)
{
	this->dateOfCreation.setString("Data utworzenia: " + dateOfCreation);
	this->dateOfCreation.setPosition(sf::Vector2f(shape.getPosition().x + shape.getSize().x / 2 - this->dateOfCreation.getGlobalBounds().width / 2 , shape.getPosition().y + 160));
}

const std::string SaveButton::getDateOfCreation() const
{
	return dateOfCreation.getString().substring(17);
}

void SaveButton::setPosition(const sf::Vector2f& Position)
{
	shape.setPosition(Position);
	alignText();
	this->dateOfLastRun.setPosition(sf::Vector2f(shape.getPosition().x + shape.getSize().x / 2 - this->dateOfLastRun.getGlobalBounds().width / 2 , shape.getPosition().y + 120));
	this->dateOfCreation.setPosition(sf::Vector2f(shape.getPosition().x + shape.getSize().x / 2 - this->dateOfCreation.getGlobalBounds().width / 2 , shape.getPosition().y + 160));
	if (nameChanger)
		nameChanger->setPosition(sf::Vector2f(shape.getPosition().x + 654, shape.getPosition().y + 180));
	if (acceptName)
		acceptName->setPosition(sf::Vector2f(shape.getPosition().x + 660, shape.getPosition().y + 180));
	if (DeleteChangeOfName)
		DeleteChangeOfName->setPosition(sf::Vector2f(shape.getPosition().x + 730, shape.getPosition().y + 180));
	if (textbox)
		textbox->setPosition(sf::Vector2f(shape.getPosition().x + 24, shape.getPosition().y + 20));
	deleteSave.setPosition(Position + sf::Vector2f(20.f, 170.f));

}

bool SaveButton::wasDeleteSavePressed(const sf::Vector2f& MousePosition, const bool wasMouseLeftButtonPressed)
{
	return deleteSave.wasPressed(MousePosition, wasMouseLeftButtonPressed);
}

void SaveButton::createNameChanger()
{
	nameChanger = std::make_shared<TextButton>(sf::Vector2f(shape.getPosition().x + 650, shape.getPosition().y + 180), sf::Vector2f(160, 50),
		textureOfNameChanger, font,
		L"Zmieñ nazwê", 30);
}

void SaveButton::createAcceptName()
{
	acceptName = std::make_shared<TextButton>(sf::Vector2f(shape.getPosition().x + 660, shape.getPosition().y + 180), sf::Vector2f(40, 40),
		textureOfAcceptName, font,
		L"", 40);
}

void SaveButton::createDeleteChangeOfName()
{
	DeleteChangeOfName = std::make_shared<TextButton>(sf::Vector2f(shape.getPosition().x + 730, shape.getPosition().y + 180), sf::Vector2f(40, 40),
		textureOfDeleteChangeOfName, font,
		L"", 40, ContentAlignment::center, 0,
		sf::Color::White, sf::Color(70, 0, 0));
}

void SaveButton::createTextbox()
{
	textbox = std::make_shared< Textbox >(sf::Vector2f(shape.getPosition().x + 24, shape.getPosition().y + 20), sf::Vector2f(777, 75),
		textureOfTextbox,
		font, text.getString(), 40,
		unavailableASCIIUnicode, ContentAlignment::center, true);
}

void SaveButton::alignText()
{
	text.setPosition(sf::Vector2f(shape.getPosition().x + shape.getSize().x / 2 - text.getGlobalBounds().width / 2 + 2, shape.getPosition().y + 45.5));
}

void SaveButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shape, states);
	target.draw(text, states);
	target.draw(dateOfLastRun, states);
	target.draw(dateOfCreation, states);
	target.draw(deleteSave, states);
	if (saveButtonState == SaveButtonState::unchangeableName)
	{
		target.draw(*nameChanger, states);
	}
	else
	{
		target.draw(*acceptName, states);
		target.draw(*DeleteChangeOfName, states);
		target.draw(*textbox, states);
	}
}

void SaveButton::transformViewFromUnchangeableNameToChangeAble()
{
	nameChanger.reset();
	createAcceptName();
	createDeleteChangeOfName();
	createTextbox();
}

void SaveButton::transformViewFromChangeableNameToUnchangeAble()
{
	acceptName.reset();
	DeleteChangeOfName.reset();
	textbox.reset();
	createNameChanger();
}
