#pragma once
#include<SFML/Graphics.hpp>
#include<array>
#include<unordered_map>
#include<optional>
#include "TextButton.h"
#include"Resources.h"
#include "LevelEditorUnit.h"
#include "IconButton.h"
#include "Checkbox.h"
#include "Slider.h"

enum class UnitsCategories {
	options = -2,
	optionsPage2 = -1,
	blocks,
	movingBlocks,
	enemies,
	enemiesPage2,
	enemiesPage3,
	others
};

enum class ToolbarButtonName {
	copyButton,
	pasteButton,
	undoButton,
	redoButton,
	saveButton,
	upgradePlayerButton,
	playButton
};

enum class ToolbarState {
	shown,
	beingShown,
	hidden,
	beingHidden
};

struct ChangePageButton
{
	ChangePageButton(const Button& button, UnitsCategories categoryToChangeAfterPressed)
		:button(button), categoryToChangeAfterPressed(categoryToChangeAfterPressed){};

	UnitsCategories categoryToChangeAfterPressed;
	Button button;
};

class LevelEditorToolbar
	: public sf::Drawable
{
public:
	LevelEditorToolbar(const sf::Vector2f& Position, const Resources& resources, const ResourceHolder<LevelEditorUnitsNames, sf::Texture>& UnitsTextures, const sf::Font& Font);
	virtual ~LevelEditorToolbar();

	void update(const bool wasMousePressed, const sf::Vector2f& mousePosition, const float deltaTime, const float positionOfViewBottom);
	bool isMouseOverToolbar(const sf::Vector2f& MousePosition);
	void move(const sf::Vector2f& offset);
	sf::Vector2f getPosition() const;
	void setPosition(const sf::Vector2f& Position);
	bool isRoundPositionTo5pxOn() const;
	bool isDrawBlockOn() const;
	bool getShowGrid() const;
	bool select() const;
	float getVelocityOfView() const;
	float getGridTransparent() const;
	LevelEditorUnitsNames getCurrentUnitType();
	bool wasButtonPressed(ToolbarButtonName name, const sf::Vector2f& Position, const bool wasMousePressed) const;
	
private:
	sf::RectangleShape background;
	std::unordered_map<UnitsCategories,TextButton> categoryButtons;
	void initCategoryButtons(const sf::Font& font);
	std::unordered_map<LevelEditorUnitsNames, IconButton> unitsButtons;
	std::vector<Checkbox> checkboxes;
	std::vector<sf::Text> texts;
	std::unique_ptr<Slider> SliderOfVelocityOfView;
	std::unique_ptr<Slider> SliderOfGridTransparent;
	TextButton togglerVisibilityOfGUI;
	ToolbarState currentState;
	void toggleVisibilityOfGUI(const bool wasMousePressed, const sf::Vector2f& mousePosition);
	void handleShowingGUI(const float deltaTime, const float positionOfViewBottom);
	void handleHidingGUI(const float deltaTime, const float positionOfViewBottom);

	LevelEditorUnitsNames currentUnitType;

	bool IsRoundPositionTo5pxOn;
	bool showGrid;
	bool drawBlock;
	bool Select;

	float velocityOfView;
	float GridTransparentInPercent;
	IconButton currentChosenUnit;
	std::unordered_map<ToolbarButtonName, TextButton> buttons;
	UnitsCategories currentCategory;
	const ResourceHolder<LevelEditorUnitsNames, sf::Texture> & unitsTextures;
	const Resources& resources;

	void handleSwitchingCategories(const bool wasMousePressed, const sf::Vector2f& mousePosition);
	void changeCategory(UnitsCategories categoryToChange);
	void tryCreateNextPageButton(UnitsCategories currentCategory);
	void tryCreatePreviousPageButton(UnitsCategories currentCategory);
	void createGivenCategory(UnitsCategories categoryToCreate);
	void setRedColorToButtonOfCurrentCategory(UnitsCategories currentCategory);
	void makeOptions();
	void makeOptionsPage2();
	void clearCurrentCategory();
	std::unique_ptr<ChangePageButton> nextPage;
	std::unique_ptr<ChangePageButton> previousPage;
	std::optional<UnitsCategories> getCategoryNameOfNextPage(UnitsCategories nameOfCurrentCategory);
	std::optional<UnitsCategories> getCategoryNameOfPreviousPage(UnitsCategories nameOfCurrentCategory);
	void updateCurrentUnitType(const bool wasMousePressed, const sf::Vector2f& mousePosition);

	const sf::Font& font;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	std::unordered_map<UnitsCategories, std::vector<LevelEditorUnitsNames> > unitsInEachCategory;
	void initUnitsInEachCategory();
};

