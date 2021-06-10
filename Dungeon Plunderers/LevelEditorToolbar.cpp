#include "pch.h"
#include "LevelEditorToolbar.h"


LevelEditorToolbar::LevelEditorToolbar(const sf::Vector2f& Position, const Resources& resources, const ResourceHolder<LevelEditorUnitsNames, sf::Texture>& UnitsTextures, const sf::Font& Font)
	: currentChosenUnit(Position + sf::Vector2f(1350, 0), sf::Vector2f(100, 100),
		resources[TextureID::GreyButton300x70], resources[TextureID::Brick],
		sf::Vector2f(70, 70)),
	resources(resources),
	font(Font),
	currentCategory(UnitsCategories::blocks),
	unitsTextures(UnitsTextures),
	velocityOfView(3000),
	IsRoundPositionTo5pxOn(false),
	showGrid(true),
	GridTransparentInPercent(50.f),
	togglerVisibilityOfGUI(sf::Vector2f(getPosition() + sf::Vector2f(1920.f / 2.f - 75.f, -35.f)), sf::Vector2f(150.f, 35.f),
		resources[TextureID::GreyButton300x70], resources.font, L"Ukryj",
		30)
{
	initUnitsInEachCategory();
	background.setSize(sf::Vector2f(1920.f, 150.f));
	background.setPosition(Position);
	background.setTexture(&resources[TextureID::ToolbarBackground]);
	background.setTextureRect(sf::IntRect(0, 0, 1920, 150));
	initCategoryButtons(font);
	createGivenCategory(UnitsCategories::blocks);

	buttons.insert(std::make_pair(ToolbarButtonName::copyButton, TextButton(Position + sf::Vector2f(1500, 0), sf::Vector2f(200, 50),
		resources[TextureID::GreyButton300x70], Font,
		L"Kopiuj", 30)));
	buttons.insert(std::make_pair(ToolbarButtonName::pasteButton, TextButton(Position + sf::Vector2f(1700, 0), sf::Vector2f(200, 50),
		resources[TextureID::GreyButton300x70], Font,
		L"Wklej", 30)));
	buttons.insert(std::make_pair(ToolbarButtonName::undoButton, TextButton(Position + sf::Vector2f(1100, 0), sf::Vector2f(200, 50),
		resources[TextureID::GreyButton300x70], Font,
		L"Cofnij", 30)));
	buttons.insert(std::make_pair(ToolbarButtonName::redoButton, TextButton(Position + sf::Vector2f(1300, 0), sf::Vector2f(200, 50),
		resources[TextureID::GreyButton300x70], Font,
		L"Ponów", 30)));
	buttons.insert(std::make_pair(ToolbarButtonName::saveButton, TextButton(Position + sf::Vector2f(1100.f, 50.f), sf::Vector2f(200, 50),
		resources[TextureID::GreyButton300x70], Font,
		L"Zapisz", 30)));
	buttons.insert(std::make_pair(ToolbarButtonName::upgradePlayerButton, TextButton(Position + sf::Vector2f(1300.f, 50.f), sf::Vector2f(400, 50),
		resources[TextureID::GreyButton300x70], Font,
		L"Modyfikuj królika doœwiadczalnego", 30)));
	buttons.insert(std::make_pair(ToolbarButtonName::playButton, TextButton(Position + sf::Vector2f(1100.f, 100.f), sf::Vector2f(600, 50),
		resources[TextureID::GreyButton300x70], Font,
		L"Testuj poziom(TAB)", 30)));
	setPosition(background.getPosition());

	currentState = ToolbarState::shown;
	togglerVisibilityOfGUI.setPosition(sf::Vector2f(getPosition() + sf::Vector2f(1920.f / 2.f - 75.f, -35.f)));
}

LevelEditorToolbar::~LevelEditorToolbar()
{
}

void LevelEditorToolbar::update(const bool wasMousePressed, const sf::Vector2f& mousePosition, const float deltaTime, const float positionOfViewBottom)
{
	for (auto i = categoryButtons.begin(); i != categoryButtons.end(); i++)
	{
		i->second.update(mousePosition);
		if (i->second.wasPressed(mousePosition, wasMousePressed))
		{
			clearCurrentCategory();
			switch (i->first)
			{
			case UnitsCategories::blocks:
				currentCategory = UnitsCategories::blocks;
				break;
			case UnitsCategories::movingBlocks:
				currentCategory = UnitsCategories::movingBlocks;
				break;
			case UnitsCategories::enemies:
				nextPage = std::make_unique<Button>(sf::Vector2f(0, 0), sf::Vector2f(46.f * 2.f, 42.f * 2.f), resources[TextureID::Arrow]);
				currentCategory = UnitsCategories::enemies;
				break;
			case UnitsCategories::coins:
				currentCategory = UnitsCategories::coins;
				break;
			case UnitsCategories::options:
				currentCategory = UnitsCategories::options;
				break;
			}
			createGivenCategory(currentCategory);
			setPosition(background.getPosition());
		}
	}

	if (nextPage and nextPage->wasPressed(mousePosition, wasMousePressed))
	{
		clearCurrentCategory();
		switch (currentCategory)
		{
		case UnitsCategories::options:
			currentCategory = UnitsCategories::optionsPage2;
			break;
		case UnitsCategories::optionsPage2:
			currentCategory = UnitsCategories::options;
			break;
		case UnitsCategories::enemies:
			nextPage = std::make_unique<Button>(sf::Vector2f(0, 0), sf::Vector2f(46.f * 2.f, 42.f * 2.f), resources[TextureID::Arrow], sf::Vector2f(-1, 1));
			currentCategory = UnitsCategories::enemiesPage2;
			break;
		case UnitsCategories::enemiesPage2:
			nextPage = std::make_unique<Button>(sf::Vector2f(0, 0), sf::Vector2f(46.f * 2.f, 42.f * 2.f), resources[TextureID::Arrow]);
			currentCategory = UnitsCategories::enemies;
			break;
		}
		createGivenCategory(currentCategory);
		setPosition(background.getPosition());
	}

	switch (currentCategory)
	{
	case UnitsCategories::options:
	case UnitsCategories::optionsPage2:
		categoryButtons.at(UnitsCategories::options).setCurrentColor(sf::Color::Red);
		break;
	case UnitsCategories::blocks:
		categoryButtons.at(UnitsCategories::blocks).setCurrentColor(sf::Color::Red);
		break;
	case UnitsCategories::movingBlocks:
		categoryButtons.at(UnitsCategories::movingBlocks).setCurrentColor(sf::Color::Red);
		break;
	case UnitsCategories::enemies:
	case UnitsCategories::enemiesPage2:
		categoryButtons.at(UnitsCategories::enemies).setCurrentColor(sf::Color::Red);
		break;
	case UnitsCategories::coins:
		categoryButtons.at(UnitsCategories::coins).setCurrentColor(sf::Color::Red);
		break;
	default:
		break;
	}
	for (auto i = unitsButtons.begin(); i != unitsButtons.end(); i++)
		i->update(mousePosition);

	for (auto i = checkboxes.begin(); i != checkboxes.end(); i++)
		i->update(mousePosition, wasMousePressed);

	if (currentCategory == UnitsCategories::options)
	{
		IsRoundPositionTo5pxOn = checkboxes[0].isChecked();
		drawBlock = checkboxes[1].isChecked();
		Select = checkboxes[2].isChecked();
	}
	if (currentCategory == UnitsCategories::optionsPage2)
	{
		showGrid = checkboxes[0].isChecked();
	}

	if (SliderOfVelocityOfView)
	{
		SliderOfVelocityOfView->update(mousePosition, wasMousePressed, deltaTime);
		velocityOfView = SliderOfVelocityOfView->getValue();
	}
	if (SliderOfGridTransparent)
	{
		SliderOfGridTransparent->update(mousePosition, wasMousePressed, deltaTime);
		GridTransparentInPercent = SliderOfGridTransparent->getValue();
	}
	if (nextPage)
		nextPage->update(mousePosition);


	updateCurrentUnitType(wasMousePressed, mousePosition);
	currentChosenUnit.setTextureOfIcon(unitsTextures.getResource(currentUnitType));

	for (auto& i : buttons)
		i.second.update(mousePosition);

	toggleVisibilityOfGUI(wasMousePressed, mousePosition);
	handleShowingGUI(deltaTime, positionOfViewBottom);
	handleHidingGUI(deltaTime, positionOfViewBottom);
}

bool LevelEditorToolbar::isMouseOverToolbar(const sf::Vector2f& MousePosition)
{
	if (background.getGlobalBounds().contains(MousePosition) or togglerVisibilityOfGUI.isMouseOverButton(MousePosition))
		return true;

	return false;
}

void LevelEditorToolbar::move(const sf::Vector2f& offset)
{
	background.move(offset);
	for (auto& i : categoryButtons)
		i.second.setPosition(i.second.getPosition() + offset);
	for (auto& i : unitsButtons)
		i.setPosition(i.getPosition() + offset);
	for (auto& i : texts)
		i.setPosition(i.getPosition() + offset);
	for (auto& i : checkboxes)
		i.setPosition(i.getPosition() + offset);
	if (SliderOfGridTransparent)
		SliderOfGridTransparent->setPosition(SliderOfGridTransparent->getPosition() + offset);
	if (SliderOfVelocityOfView)
		SliderOfVelocityOfView->setPosition(SliderOfVelocityOfView->getPosition() + offset);
	for (auto& i : buttons)
		i.second.setPosition(i.second.getPosition() + offset);

	if (nextPage)
		nextPage->setPosition(nextPage->getPosition() + offset);
	currentChosenUnit.setPosition(currentChosenUnit.getPosition() + offset);
}

sf::Vector2f LevelEditorToolbar::getPosition() const
{
	return background.getPosition();
}

void LevelEditorToolbar::setPosition(const sf::Vector2f& Position)
{
	background.setPosition(Position);
	int numberOfCategoryButton = 0;;
	for (auto i = categoryButtons.begin(); i != categoryButtons.end(); i++)
	{
		i->second.setPosition(Position + sf::Vector2f(i->second.getSize().x * numberOfCategoryButton, 0.f));
		numberOfCategoryButton++;
	}
	float leftMarginOfUnitButtons = 0;
	if (currentCategory == UnitsCategories::enemiesPage2)
		leftMarginOfUnitButtons = 150;

	for (auto i = unitsButtons.begin(); i != unitsButtons.end(); i++)
		i->setPosition(Position + sf::Vector2f((i->getSize().x + 25.f) * (i - unitsButtons.begin()) + leftMarginOfUnitButtons, 50.f));
	currentChosenUnit.setPosition(Position + sf::Vector2f(background.getSize().x - currentChosenUnit.getSize().x - 50.f, 50.f));

	if (currentCategory == UnitsCategories::options)
	{
		checkboxes[0].setPosition(Position + sf::Vector2f(170.f, 50));
		checkboxes[1].setPosition(Position + sf::Vector2f(170.f, 100));
		checkboxes[2].setPosition(Position + sf::Vector2f(350.f, 50));

		texts[0].setPosition(Position + sf::Vector2f(5, 50));
		texts[1].setPosition(Position + sf::Vector2f(5, 100));
		texts[2].setPosition(Position + sf::Vector2f(250, 50));
		texts[3].setPosition(Position + sf::Vector2f(670, 110));

		if (nextPage)
			nextPage->setPosition(Position + sf::Vector2f(1000.f, 58.f));
	}
	if (currentCategory == UnitsCategories::optionsPage2)
	{
		checkboxes[0].setPosition(Position + sf::Vector2f(270.f, 50));

		texts[0].setPosition(Position + sf::Vector2f(105, 50));
		texts[1].setPosition(Position + sf::Vector2f(540, 110));

		if (nextPage)
			nextPage->setPosition(Position + sf::Vector2f(100.f, 58.f));
	}
	if (nextPage and currentCategory == UnitsCategories::enemies)
		nextPage->setPosition(Position + sf::Vector2f(1000.f, 58.f));
	if (nextPage and currentCategory == UnitsCategories::enemiesPage2)
		nextPage->setPosition(Position + sf::Vector2f(100.f, 58.f));



	if (SliderOfVelocityOfView)
		SliderOfVelocityOfView->setPosition(Position + sf::Vector2f(600, 88));

	if (SliderOfGridTransparent)
		SliderOfGridTransparent->setPosition(Position + sf::Vector2f(500, 88));

	buttons.at(ToolbarButtonName::copyButton).setPosition(Position + sf::Vector2f(1500.f, 0.f));
	buttons.at(ToolbarButtonName::pasteButton).setPosition(Position + sf::Vector2f(1700.f, 0.f));
	buttons.at(ToolbarButtonName::undoButton).setPosition(Position + sf::Vector2f(1100.f, 0.f));
	buttons.at(ToolbarButtonName::redoButton).setPosition(Position + sf::Vector2f(1300.f, 0.f));
	buttons.at(ToolbarButtonName::saveButton).setPosition(Position + sf::Vector2f(1100.f, 50.f));
	buttons.at(ToolbarButtonName::upgradePlayerButton).setPosition(Position + sf::Vector2f(1300.f, 50.f));
	buttons.at(ToolbarButtonName::playButton).setPosition(Position + sf::Vector2f(1100.f, 100.f));
}

bool LevelEditorToolbar::isRoundPositionTo5pxOn() const
{
	return IsRoundPositionTo5pxOn;
}

bool LevelEditorToolbar::isDrawBlockOn() const
{
	return drawBlock;
}

bool LevelEditorToolbar::getShowGrid() const
{
	return showGrid;
}

bool LevelEditorToolbar::select() const
{
	return Select;
}

float LevelEditorToolbar::getVelocityOfView() const
{
	return velocityOfView;
}

float LevelEditorToolbar::getGridTransparent() const
{
	return GridTransparentInPercent / 100.f * 255;
}

LevelEditorUnitsNames LevelEditorToolbar::getCurrentUnitType()
{
	return currentUnitType;
}

bool LevelEditorToolbar::wasButtonPressed(ToolbarButtonName name, const sf::Vector2f& Position, const bool wasMousePressed) const
{
	return buttons.at(name).wasPressed(Position, wasMousePressed);
}

void LevelEditorToolbar::initCategoryButtons(const sf::Font& font)
{
	categoryButtons.emplace(std::make_pair(UnitsCategories::blocks,
		TextButton(sf::Vector2f(0.f, 0.f), sf::Vector2f(200.f, 50.f),
		resources[TextureID::GreyButton300x70], font,
		L"Bloki", 30)));

	categoryButtons.emplace(std::make_pair(UnitsCategories::movingBlocks,
		TextButton(sf::Vector2f(0.f, 0.f), sf::Vector2f(200.f, 50.f),
		resources[TextureID::GreyButton300x70], font,
		L"Ruszaj¹ce siê bloki", 30)));

	categoryButtons.emplace(std::make_pair(UnitsCategories::enemies,
		TextButton(sf::Vector2f(0.f, 0.f), sf::Vector2f(200.f, 50.f),
		resources[TextureID::GreyButton300x70], font,
		L"Potworki", 30)));

	categoryButtons.emplace(std::make_pair(UnitsCategories::coins,
		TextButton(sf::Vector2f(0.f, 0.f), sf::Vector2f(200.f, 50.f),
		resources[TextureID::GreyButton300x70], font,
		L"Monety", 30)));

	categoryButtons.emplace(std::make_pair(UnitsCategories::options,
		TextButton(sf::Vector2f(0.f, 0.f), sf::Vector2f(200.f, 50.f),
		resources[TextureID::GreyButton300x70], font,
		L"Opcje", 30)));
}

void LevelEditorToolbar::toggleVisibilityOfGUI(const bool wasMousePressed, const sf::Vector2f& mousePosition)
{
	if (togglerVisibilityOfGUI.wasPressed(mousePosition, wasMousePressed))
	{
		if (currentState == ToolbarState::shown or currentState == ToolbarState::beingShown)
		{
			togglerVisibilityOfGUI.setWstring(L"Poka¿");
			currentState = ToolbarState::beingHidden;
		}
		else
		{
			togglerVisibilityOfGUI.setWstring(L"Ukryj");
			currentState = ToolbarState::beingShown;
		}
	}
}

void LevelEditorToolbar::handleShowingGUI(const float deltaTime, const float positionOfViewBottom)
{
	if (currentState == ToolbarState::beingShown)
	{
		move(sf::Vector2f(0.f, -500 * deltaTime));
		togglerVisibilityOfGUI.setPosition(sf::Vector2f(togglerVisibilityOfGUI.getPosition().x, togglerVisibilityOfGUI.getPosition().y - 500 * deltaTime));
		if (getPosition().y < positionOfViewBottom - background.getSize().y)
		{
			currentState = ToolbarState::shown;
			setPosition(sf::Vector2f(getPosition().x, positionOfViewBottom - background.getSize().y));
			togglerVisibilityOfGUI.setPosition(sf::Vector2f(togglerVisibilityOfGUI.getPosition().x, getPosition().y - 35.f));
		}
	}
}

void LevelEditorToolbar::handleHidingGUI(const float deltaTime, const float positionOfViewBottom)
{
	if (currentState == ToolbarState::beingHidden)
	{
		move(sf::Vector2f(0.f, 500 * deltaTime));
		togglerVisibilityOfGUI.setPosition(sf::Vector2f(togglerVisibilityOfGUI.getPosition().x, togglerVisibilityOfGUI.getPosition().y + 500 * deltaTime));
		if (getPosition().y > positionOfViewBottom)
		{
			currentState = ToolbarState::hidden;
			setPosition(sf::Vector2f(getPosition().x, positionOfViewBottom));
			togglerVisibilityOfGUI.setPosition(sf::Vector2f(togglerVisibilityOfGUI.getPosition().x, getPosition().y - 35.f));
		}
	}
}


void LevelEditorToolbar::createGivenCategory(UnitsCategories categoryToCreate)
{
	if (categoryToCreate == UnitsCategories::options)
		makeOptions();
	else if (categoryToCreate == UnitsCategories::optionsPage2)
		makeOptionsPage2();
	else
	{
		auto& unitsInGivenCategory = unitsInEachCategory[categoryToCreate];

		for (auto const& i : unitsInGivenCategory)
		{
			unitsButtons.emplace_back(background.getPosition(), sf::Vector2f(100, 100),
				resources[TextureID::GreyButton300x70], unitsTextures.getResource(i),
				sf::Vector2f(70, 70));
		}
	}
}

void LevelEditorToolbar::makeBlocksButton()
{
	unitsButtons.emplace_back(background.getPosition(), sf::Vector2f(100, 100),
		resources[TextureID::GreyButton300x70], resources[TextureID::Brick],
		sf::Vector2f(70, 70));

	unitsButtons.emplace_back(background.getPosition() + sf::Vector2f(200, 0), sf::Vector2f(100, 100),
		resources[TextureID::GreyButton300x70], resources[TextureID::Dirt],
		sf::Vector2f(70, 70));

	unitsButtons.emplace_back(background.getPosition() + sf::Vector2f(200, 0), sf::Vector2f(100, 100),
		resources[TextureID::GreyButton300x70], resources[TextureID::Concrate],
		sf::Vector2f(70, 70));

	unitsButtons.emplace_back(background.getPosition() + sf::Vector2f(200, 0), sf::Vector2f(100, 100),
		resources[TextureID::GreyButton300x70], resources[TextureID::Granite],
		sf::Vector2f(70, 70));
}

void LevelEditorToolbar::makeOptions()
{
	nextPage = std::make_unique<Button>(sf::Vector2f(0, 0), sf::Vector2f(46.f * 2.f, 42.f * 2.f), resources[TextureID::Arrow]);
	texts.emplace_back(L"Tryb swobodny ", font);
	texts.emplace_back(L"Rysuj bloki", font);
	texts.emplace_back(L"Zaznacz", font);
	texts.emplace_back(L"Prêdkoœæ kamery", font);
	checkboxes.emplace_back(background.getPosition() + sf::Vector2f(150, 40), sf::Vector2f(50, 50), resources[TextureID::Checbox50x50], resources[TextureID::Checbox50x50], IsRoundPositionTo5pxOn);
	checkboxes.emplace_back(background.getPosition() + sf::Vector2f(150, 40), sf::Vector2f(50, 50), resources[TextureID::Checbox50x50], resources[TextureID::Checbox50x50], drawBlock);
	checkboxes.emplace_back(background.getPosition() + sf::Vector2f(150, 40), sf::Vector2f(50, 50), resources[TextureID::Checbox50x50], resources[TextureID::Checbox50x50], Select);

	for (auto& i : texts)
	{
		i.setOutlineColor(sf::Color::Black);
		i.setOutlineThickness(3);
	}
	SliderOfVelocityOfView = std::make_unique<Slider>(background.getPosition() + sf::Vector2f(700, 100), sf::Vector2f(300, 15), 100, 10000, velocityOfView, resources[TextureID::Slider], resources[TextureID::Axis], resources[TextureID::SliderButton], font);
}

void LevelEditorToolbar::makeOptionsPage2()
{
	nextPage = std::make_unique<Button>(sf::Vector2f(0, 0), sf::Vector2f(46.f * 2.f, 42.f * 2.f), resources[TextureID::Arrow], sf::Vector2f(-1, 1));
	checkboxes.emplace_back(background.getPosition() + sf::Vector2f(150, 40), sf::Vector2f(50, 50), resources[TextureID::Checbox50x50], resources[TextureID::Checbox50x50], showGrid);
	texts.emplace_back(L"Poka¿ siatkê", font);

	SliderOfGridTransparent = std::make_unique<Slider>(background.getPosition() + sf::Vector2f(730, 100), sf::Vector2f(300, 15), 1, 100, GridTransparentInPercent, resources[TextureID::Slider], resources[TextureID::Axis], resources[TextureID::SliderButton], font);
	texts.emplace_back(L"Przezroczystoœæ siatki", font);


	for (auto& i : texts)
	{
		i.setOutlineColor(sf::Color::Black);
		i.setOutlineThickness(3);
	}
}

void LevelEditorToolbar::clearCurrentCategory()
{
	unitsButtons.clear();
	texts.clear();
	checkboxes.clear();
	SliderOfVelocityOfView.reset();
	SliderOfGridTransparent.reset();
	nextPage.reset();
}

void LevelEditorToolbar::updateCurrentUnitType(const bool wasMousePressed, const sf::Vector2f& mousePosition)
{
	switch (currentCategory)
	{
	case UnitsCategories::options:
		break;
	case UnitsCategories::blocks:
		if (unitsButtons[0].wasPressed(mousePosition, wasMousePressed))
			currentUnitType = LevelEditorUnitsNames::brick;
		if (unitsButtons[1].wasPressed(mousePosition, wasMousePressed))
			currentUnitType = LevelEditorUnitsNames::dirt;
		if (unitsButtons[2].wasPressed(mousePosition, wasMousePressed))
			currentUnitType = LevelEditorUnitsNames::concrete;
		if (unitsButtons[3].wasPressed(mousePosition, wasMousePressed))
			currentUnitType = LevelEditorUnitsNames::granite;

		break;
	case UnitsCategories::movingBlocks:
		if (unitsButtons[0].wasPressed(mousePosition, wasMousePressed))
			currentUnitType = LevelEditorUnitsNames::movingBrick;
		if (unitsButtons[1].wasPressed(mousePosition, wasMousePressed))
			currentUnitType = LevelEditorUnitsNames::movingDirt;
		if (unitsButtons[2].wasPressed(mousePosition, wasMousePressed))
			currentUnitType = LevelEditorUnitsNames::movingConcrete;
		if (unitsButtons[3].wasPressed(mousePosition, wasMousePressed))
			currentUnitType = LevelEditorUnitsNames::movingGranite;
		break;
	case UnitsCategories::enemies:
		if (unitsButtons[0].wasPressed(mousePosition, wasMousePressed))
			currentUnitType = LevelEditorUnitsNames::deadlyFlower;
		if (unitsButtons[1].wasPressed(mousePosition, wasMousePressed))
			currentUnitType = LevelEditorUnitsNames::zombie;
		if (unitsButtons[2].wasPressed(mousePosition, wasMousePressed))
			currentUnitType = LevelEditorUnitsNames::skeleton;
		if (unitsButtons[3].wasPressed(mousePosition, wasMousePressed))
			currentUnitType = LevelEditorUnitsNames::fly;
		if (unitsButtons[4].wasPressed(mousePosition, wasMousePressed))
			currentUnitType = LevelEditorUnitsNames::gunEnemy;
		if (unitsButtons[5].wasPressed(mousePosition, wasMousePressed))
			currentUnitType = LevelEditorUnitsNames::gunEnemyOnFakeBlock;
		if (unitsButtons[6].wasPressed(mousePosition, wasMousePressed))
			currentUnitType = LevelEditorUnitsNames::movingGunEnemyOnFakeBlock;
		break;
	case UnitsCategories::enemiesPage2:
		if (unitsButtons[0].wasPressed(mousePosition, wasMousePressed))
			currentUnitType = LevelEditorUnitsNames::spikes;
		if (unitsButtons[1].wasPressed(mousePosition, wasMousePressed))
			currentUnitType = LevelEditorUnitsNames::hidingSpikes;
		if (unitsButtons[2].wasPressed(mousePosition, wasMousePressed))
			currentUnitType = LevelEditorUnitsNames::showingAfterDamageSpikes;
		if (unitsButtons[3].wasPressed(mousePosition, wasMousePressed))
			currentUnitType = LevelEditorUnitsNames::slimeEnemy;
		break;
	case UnitsCategories::coins:
		if (unitsButtons[0].wasPressed(mousePosition, wasMousePressed))
			currentUnitType = LevelEditorUnitsNames::coin;
		break;
	}
}

void LevelEditorToolbar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(background);
	target.draw(togglerVisibilityOfGUI);
	for (auto const& i : categoryButtons)
		target.draw(i.second, states);
	for (auto const& i : unitsButtons)
		target.draw(i, states);
	for (auto const& i : texts)
		target.draw(i, states);
	for (auto const& i : checkboxes)
		target.draw(i, states);
	if (SliderOfVelocityOfView)
		target.draw(*SliderOfVelocityOfView, states);
	if (SliderOfGridTransparent)
		target.draw(*SliderOfGridTransparent, states);
	if (nextPage)
		target.draw(*nextPage, states);

	target.draw(currentChosenUnit);
	for (auto const& i : buttons)
		target.draw(i.second);
}

void LevelEditorToolbar::initUnitsInEachCategory()
{
	using UnitName = LevelEditorUnitsNames;

	std::vector<LevelEditorUnitsNames> blocks
	{ UnitName::brick, UnitName::dirt, UnitName::concrete, UnitName::granite };

	std::vector<LevelEditorUnitsNames> movingBlocks
	{ UnitName::movingBrick, UnitName::movingDirt, UnitName::movingConcrete, UnitName::movingGranite };

	std::vector<LevelEditorUnitsNames> enemiesPage1
	{ UnitName::deadlyFlower, UnitName::zombie, UnitName::skeleton, UnitName::fly, UnitName::gunEnemy, 
	  UnitName::gunEnemyOnFakeBlock, UnitName::movingGunEnemyOnFakeBlock };
	
	std::vector<LevelEditorUnitsNames> enemiesPage2
	{ UnitName::spikes, UnitName::hidingSpikes, UnitName::showingAfterDamageSpikes, UnitName::fly, UnitName::slimeEnemy};	
	
	std::vector<LevelEditorUnitsNames> coins
	{ UnitName::coin};

	unitsInEachCategory.emplace(std::make_pair(UnitsCategories::blocks, blocks));
	unitsInEachCategory.emplace(std::make_pair(UnitsCategories::movingBlocks, movingBlocks));
	unitsInEachCategory.emplace(std::make_pair(UnitsCategories::enemies, enemiesPage1));
	unitsInEachCategory.emplace(std::make_pair(UnitsCategories::enemiesPage2, enemiesPage2));
	unitsInEachCategory.emplace(std::make_pair(UnitsCategories::coins, coins));
}
