#pragma once
#include "TextButton.h"
#include "Textbox.h"

enum class SaveButtonState { changeableName, unchangeableName  };

class SaveButton
	:public TextButton
{
public:
	SaveButton(const sf::Vector2f& Position,
		const sf::Texture& TextureOfSaveButton, const sf::Texture& TextureOfTextbox,
		const sf::Texture& TextureOfNameChanger, const sf::Texture& TextureOfAcceptName, const sf::Texture& TextureOfDeleteName, const sf::Texture& TextureOfDeleteSave,
		const sf::Font& Font, const SaveButtonState initialState = SaveButtonState::unchangeableName);
	~SaveButton();
	void updateIfIsNotChangingName(const sf::Vector2f& MousePosition, const bool wasMouseLeftButtonPressed);
	void updateIfIsChangingName(const sf::Vector2f& MousePosition, const bool wasMouseLeftButtonPressed, const float deltaTime, const bool wasNameChangeCorrectly, const bool isNameAlreadyUse);
	SaveButtonState getSaveButtonState() const;
	void handleEnteredTextWhenIsChangingName(sf::Uint32 unicode);
	std::string getName() const;
	std::string getNameBeforeAttemptingToChange();
	bool wasDeleteChangeOfNamePressed(const sf::Vector2f& MousePosition, const bool wasMouseLeftButtonPressed) const;
	bool wasNameChangerPressed(const sf::Vector2f& MousePosition, const bool wasMouseLeftButtonPressed) const;
	void deleteChangeOfName();
	void setName(const std::string Name);
	void setDateOfLastRun(const std::string& dateOfLastRun);
	const std::string getDateOfLastRun() const;
	void setDateOfCreation(const std::string& dateOfCreation);
	const std::string getDateOfCreation() const;
	void setPosition(const sf::Vector2f& Position);
	bool wasDeleteSavePressed(const sf::Vector2f& MousePosition, const bool wasMouseLeftButtonPressed);
private:
	SaveButtonState saveButtonState;
	sf::Text dateOfLastRun;
	sf::Text dateOfCreation;
	std::string nameBeforeAttemptToChange;
	const sf::Texture& textureOfSaveButton;
	const sf::Texture& textureOfTextbox;
	const sf::Texture& textureOfNameChanger;
	const sf::Texture& textureOfAcceptName;
	const sf::Texture& textureOfDeleteChangeOfName;
	const sf::Font& font;
	Button deleteSave;
	std::shared_ptr< TextButton > nameChanger;
	std::shared_ptr< TextButton > acceptName;
	std::shared_ptr< TextButton > DeleteChangeOfName;
	std::shared_ptr< Textbox > textbox;
	void createNameChanger();
	void createAcceptName();
	void createDeleteChangeOfName();
	void createTextbox();
	void alignText();
	void transformViewFromUnchangeableNameToChangeAble();
	void transformViewFromChangeableNameToUnchangeAble();
	std::vector<sf::Uint32> unavailableASCIIUnicode;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

