#include "pch.h"
#include "LevelEditorState.h"


LevelEditorState::LevelEditorState(StateData& stateData, const std::string& filepath)
	: State(stateData),
	unitsTextures(loadAllUnitsTextures()),
	toolbar(sf::Vector2f(0.f, 930),
		stateData.resources, unitsTextures, stateData.resources.font),
	numberOfSelectedUnits(0),
	tileSize(50),
	filepath(filepath),
	sliderOfView(sf::Vector2f(850.f, 50.f), sf::Vector2f(300, 15),
		100, 5000, 300.f,
		stateData.resources[TextureID::Slider], stateData.resources[TextureID::Axis], stateData.resources[TextureID::SliderButton], stateData.resources.font),
	changeTracker(units, numberOfSelectedUnits, unitsTextures),
	clipboard(units, numberOfSelectedUnits, unitsTextures)
{
	initFunctionConvertUnitsToLevel();
	loadUnitsFromFile();
	tryAddPlayerToUnits();
	tryAddPortalToUnits();

	guineaPig = PersistenceLoader::loadLevelEditorPlayerData();
	stateData.savedPlayerData = guineaPig;
	initMessageOfIssues();


	for (auto& i : backgrounds)
	{
		i.setTexture(stateData.resources[TextureID::BackgroundGame]);
		i.setTextureRect(sf::IntRect(0, 0, 3400, 1500));
	}
	backgrounds[0].setPosition(view.getCenter().x - 1710.f, -200);
	backgrounds[1].setPosition(view.getCenter().x + 1690.f, -200);



	lastMousePosition = mousePositionView;
	textureOfHelpLines50x50.loadFromFile(".\\Textures\\HelpLines50x50.png");
	textureOfHelpLines50x50.setRepeated(true);

	for (auto& i : helpLines)
	{
		i.setTexture(textureOfHelpLines50x50);
		i.setTextureRect(sf::IntRect(0, 0, 3400, 1500));
		i.setColor(sf::Color(255, 255, 255, 150));
	}
	helpLines[0].setPosition(view.getCenter().x - 1710.f, -211);
	helpLines[1].setPosition(view.getCenter().x + 1690.f, -211);

	view.zoom(1.388888888);
	lastViewPosition = view.getCenter();

	setMovingDistanceWhenUnitIsOnBlock();
	setHitboxesWhenUnitIsSetOnMovingBlock();
	markIfSelectedUnitIsSetIncorrecly();
	
	updateMessageOfIssues();

	setSliderOfView();
	changeTracker.addCurrentUnitsToHistory();
	
}

LevelEditorState::~LevelEditorState()
{
}

void LevelEditorState::update(const float deltaTime)
{
	handleZoomingView(deltaTime);

	currentUnitType = toolbar.getCurrentUnitType();

	MouseShiftRelativeToHUDView = mousePositionHUD - lastMousePositionRelativeToHUDView;
	MouseShift = mousePositionView - lastMousePosition;
	if(currentAction == Action::none)
		sliderOfView.update(mousePositionHUD, wasMousePressed, deltaTime);
	
	
	if (currentAction != Action::none)
	{
		if (!wasUsedMouseSetPos)
			UnitShift += MouseShift;
		else
			wasUsedMouseSetPos = false;
	}
	else
		UnitShift = sf::Vector2f(0.f, 0.f);

	handleAddingUnits();
	handleSelectingUnitsByClick();
	handleChangingSizeOfBlocks();
	handleMovingUnits();

	updatePositionsOfBackgrounds(backgrounds);
	updatePositionsOfBackgrounds(helpLines);
	updateTransparentOfHelpLines();
	updatePositionOfView(deltaTime);
	rightOfView = view.getCenter().x + view.getSize().x / 2.f;
	leftOfView = view.getCenter().x - view.getSize().x / 2.f;

	toolbar.update(wasMousePressed, mousePositionHUD, deltaTime, HUDView.getCenter().y + HUDView.getSize().y / 2);

	if (toolbar.isRoundPositionTo5pxOn())
		tileSize = 5;
	else
		tileSize = 50;

	updateColorOfUnits();

	updateArea(selectedArea);
	updateArea(createBlockArea);
	lastMousePosition = mousePositionView;
	lastMousePositionRelativeToHUDView = mousePositionHUD;
	lastViewPosition = view.getCenter();
	


	handleFunctionalityToolbarButtons();
	if (feedback)
		feedback->update(deltaTime);

}

void LevelEditorState::handleSFMLEvent(sf::RenderWindow& window, sf::Event& event)
{
	wasMousePressed = false;
	wasLeftMouseReleased = false;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
		resizeWindowProportionally(window, event);

		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				wasMousePressed = true;
			}
			

			if (event.mouseButton.button == sf::Mouse::Middle)
			{
				deleteSelectedUnits();
			}

			if (event.mouseButton.button == sf::Mouse::Right)
			{
				if (toolbar.select())
				{
					createArea(selectedArea, sf::Color::Green);
					numberOfSelectedUnits = 0;
				}
			}	
		}
		if (event.type == sf::Event::MouseButtonReleased)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
				wasLeftMouseReleased = true;

			if (event.mouseButton.button == sf::Mouse::Right)
			{
				selectUnitsBySelectedArea();
				selectedArea.reset();
			}
		}

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				saveUnitsToFile();
				numberOfStatesPop = 1;
			}
			if (event.key.code == sf::Keyboard::Tab)
			{
				wasMousePressed = false;
				initFunctionConvertUnitsToLevel();
				stateData.states.push(std::make_unique<GameplayState>(stateData, convertUnitsToLevel));
			}
			if (event.key.code == sf::Keyboard::F5)
			{
				saveUnitsToFile();
				feedback = std::make_unique<Feedback>(sf::Vector2f(0, 700), L"Level zosta³ poprawnie zapisany", 50, stateData.resources.font);
			}
			if (event.key.code == sf::Keyboard::F2)
			{
				createCode();
				feedback = std::make_unique<Feedback>(sf::Vector2f(0, 700), L"Level zosta³ poprawnie zapisany do kodu", 50, stateData.resources.font);
			}
			if (event.key.code == sf::Keyboard::Delete)
			{
				deleteSelectedUnits();
			}
			handleKeyboardShortcuts(event.key.code);
		}
	}
	handleChangingMovingDistance(window);
}

void LevelEditorState::updateInput(const float deltaTime)
{
}

void LevelEditorState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.setView(view);
	drawBackgrounds(target, states);
	if(toolbar.getShowGrid())
		drawHelpLines(target, states);
	drawUnits(target, states);

	if(selectedArea)
		target.draw(*selectedArea, states);
	if(createBlockArea)
		target.draw(*createBlockArea, states);

	target.setView(HUDView); //HUD

	target.draw(toolbar, states);
	target.draw(messageOfIssues, states);
	target.draw(sliderOfView, states);
	if(feedback)
		target.draw(*feedback, states);
	target.setView(view);
}

ResourceHolder<LevelEditorUnitsNames, sf::Texture> LevelEditorState::loadAllUnitsTextures()
{
	ResourceHolder<LevelEditorUnitsNames, sf::Texture> unitsTextures;
	//blocks 
	unitsTextures.add(LevelEditorUnitsNames::brick, loadTexture(".\\Textures\\Blocks.png", sf::IntRect(0, 0, 50, 50), true));
	unitsTextures.add(LevelEditorUnitsNames::dirt, loadTexture(".\\Textures\\Blocks.png", sf::IntRect(50, 0, 50, 50), true));
	unitsTextures.add(LevelEditorUnitsNames::concrete, loadTexture(".\\Textures\\Blocks.png", sf::IntRect(100, 0, 50, 50), true));
	unitsTextures.add(LevelEditorUnitsNames::granite, loadTexture(".\\Textures\\Blocks.png", sf::IntRect(150, 0, 50, 50), true));

	//moving blocks
	unitsTextures.add(LevelEditorUnitsNames::movingBrick, loadTexture(".\\Textures\\Blocks.png", sf::IntRect(0, 0, 50, 50), true));
	unitsTextures.add(LevelEditorUnitsNames::movingDirt, loadTexture(".\\Textures\\Blocks.png", sf::IntRect(50, 0, 50, 50), true));
	unitsTextures.add(LevelEditorUnitsNames::movingConcrete, loadTexture(".\\Textures\\Blocks.png", sf::IntRect(100, 0, 50, 50), true));
	unitsTextures.add(LevelEditorUnitsNames::movingGranite, loadTexture(".\\Textures\\Blocks.png", sf::IntRect(150, 0, 50, 50), true));

	//enemies
	unitsTextures.add(LevelEditorUnitsNames::deadlyFlower, loadTexture(".\\Textures\\DeadlyFlowerLvlEditor.png"));
	unitsTextures.add(LevelEditorUnitsNames::skeleton, loadTexture(".\\Textures\\Skeleton.png", sf::IntRect(695, 0, 139, 200)));
	unitsTextures.add(LevelEditorUnitsNames::fly, loadTexture(".\\Textures\\Fly.png", sf::IntRect(0, 0, 77, 57)));
	unitsTextures.add(LevelEditorUnitsNames::zombie, loadTexture(".\\Textures\\ZombieGirl.png", sf::IntRect(0, 0, 122, 184)));
	unitsTextures.add(LevelEditorUnitsNames::gunEnemy, loadTexture(".\\Textures\\GunEnemyLevelEditor.png"));
	unitsTextures.add(LevelEditorUnitsNames::movingGunEnemyOnFakeBlock, loadTexture(".\\Textures\\GunEnemyOnBrick.png"));
	unitsTextures.add(LevelEditorUnitsNames::gunEnemyOnFakeBlock, loadTexture(".\\Textures\\GunEnemyOnBrick.png"));
	unitsTextures.add(LevelEditorUnitsNames::spikes, loadTexture(".\\Textures\\Spikes.png", sf::IntRect(350, 0, 50, 50)));
	unitsTextures.add(LevelEditorUnitsNames::showingAfterDamageSpikes, loadTexture(".\\Textures\\Spikes.png", sf::IntRect(350, 0, 50, 50)));
	unitsTextures.add(LevelEditorUnitsNames::hidingSpikes, loadTexture(".\\Textures\\Spikes.png", sf::IntRect(350, 0, 50, 50)));
	unitsTextures.add(LevelEditorUnitsNames::slimeEnemy, loadTexture(".\\Textures\\Slime.png", sf::IntRect(0, 0, 96, 96)));
	unitsTextures.add(LevelEditorUnitsNames::zombieInGround, loadTexture(".\\Textures\\ZombieInGround.png", sf::IntRect(0, 0, 100, 108)));
	unitsTextures.add(LevelEditorUnitsNames::ghost, loadTexture(".\\Textures\\Ghost.png", sf::IntRect(0, 0, 80, 130)));
	unitsTextures.add(LevelEditorUnitsNames::bat, loadTexture(".\\Textures\\BatLevelEditor.png"));
	unitsTextures.add(LevelEditorUnitsNames::spinningSpikes, loadTexture(".\\Textures\\SpinningSpikes.png", sf::IntRect(0, 0, 150, 150)));
	unitsTextures.add(LevelEditorUnitsNames::movingSpinningSpikes, loadTexture(".\\Textures\\SpinningSpikes.png", sf::IntRect(0, 0, 150, 150)));

	//other
	unitsTextures.add(LevelEditorUnitsNames::player, loadTexture(".\\Textures\\Stormtrooper.png", sf::IntRect(0, 0, 117, 207)));
	unitsTextures.add(LevelEditorUnitsNames::portal, loadTexture(".\\Textures\\Portal.png", sf::IntRect(0, 0, 117, 207)));
	unitsTextures.add(LevelEditorUnitsNames::coin, loadTexture(".\\Textures\\Coin.png", sf::IntRect(0, 0, 50, 50)));
	unitsTextures.add(LevelEditorUnitsNames::trampoline, loadTexture(".\\Textures\\Trampoline.png", sf::IntRect(357, 0, 51, 60)));

	return unitsTextures;
}

void LevelEditorState::handleFunctionalityToolbarButtons()
{
	if (toolbar.wasButtonPressed(ToolbarButtonName::copyButton, mousePositionHUD, wasMousePressed))
		clipboard.copySelectedUnits();
	if (toolbar.wasButtonPressed(ToolbarButtonName::pasteButton, mousePositionHUD, wasMousePressed))
	{
		clipboard.paste(mousePositionHUD);
		updateAfterChanges();
	}
	if (toolbar.wasButtonPressed(ToolbarButtonName::redoButton, mousePositionHUD, wasMousePressed))
		changeTracker.redoChangeOfUnits();
	if (toolbar.wasButtonPressed(ToolbarButtonName::undoButton, mousePositionHUD, wasMousePressed))
		changeTracker.undoChangeOfUnits();
	if (toolbar.wasButtonPressed(ToolbarButtonName::saveButton, mousePositionHUD, wasMousePressed))
	{
		saveUnitsToFile();
		feedback = std::make_unique<Feedback>(sf::Vector2f(0, 700), L"Level zosta³ poprawnie zapisany", 50, stateData.resources.font);
	}
	if (toolbar.wasButtonPressed(ToolbarButtonName::upgradePlayerButton, mousePositionHUD, wasMousePressed))
	{
		wasMousePressed = false;
		stateData.states.push(std::make_unique<LevelEditorUpgradeClassState>(stateData));
	}
	if (toolbar.wasButtonPressed(ToolbarButtonName::playButton, mousePositionHUD, wasMousePressed))
	{
		wasMousePressed = false;
		initFunctionConvertUnitsToLevel();
		stateData.states.push(std::make_unique<GameplayState>(stateData, convertUnitsToLevel));
	}
}

void LevelEditorState::loadUnitsFromFile()
{
	std::ifstream file;
	file.open(filepath);
	sf::Vector2f position;
	sf::Vector2f movingDistance(100.f, 0.f);
	sf::Vector2f size(50.f, 50.f);
	LevelEditorUnitsNames name;
	int tempType;
	units.reserve(1000);
	if (file.is_open())
	{
		file >> dateOfLastRun;
		file >> dateOfCreation;

		while (!file.eof())
		{
			file >> position.x;
			file >> position.y;
			file >> tempType;
			name = static_cast<LevelEditorUnitsNames>(tempType);
			if (UnitTypeChecker::isMovable(name))
			{
				file >> movingDistance.x;
				file >> movingDistance.y;
			}
			if (UnitTypeChecker::isBlock(name))
			{
				file >> size.x;
				file >> size.y;
			}

			units.emplace_back(position, unitsTextures, name, movingDistance, size);

			movingDistance = sf::Vector2f(100.f, 0.f);
			size = sf::Vector2f(50.f, 50.f);
		}
		file.close();
	}
}

void LevelEditorState::saveUnitsToFile()
{
	std::ofstream file;
	file.open(filepath);
	file << dateOfLastRun << std::endl;
	file << dateOfCreation;

	for (auto i = units.begin(); i != units.end(); i++)
	{
		file << std::endl;
		file << i->getPosition().x << " " << i->getPosition().y << " " << static_cast<int>(i->getType());
		if (UnitTypeChecker::isMovable(i->getType()))
		{
			file << " " << i->getMovingDistance().x << " " << i->getMovingDistance().y;
		}
		if (UnitTypeChecker::isBlock(i->getType()))
		{
			file << " " << i->sizeOfAllHitboxes().x << " " << i->sizeOfAllHitboxes().y;
		}
	}

	file.close();
}

void LevelEditorState::createCode()
{
	
	std::ofstream file;
	file.open("currentLevelCode.txt");
	auto player = findPlayerInUnits();
	file << "initialPositionOfPlayer = sf::Vector2f(" << player->hitboxComponent[0].getLeft() << ".f, " << player->hitboxComponent[0].getTop() << ".f);" << std::endl;
	for (auto const &i : units)
	{
		switch (i.getType())
		{
		case LevelEditorUnitsNames::brick:
			file << "level.blocks.emplace_back(sf::Vector2f(" << i.getPosition().x << ", " << i.getPosition().y
				<< "), sf::Vector2f(" << i.sizeOfAllHitboxes().x << ", " << i.sizeOfAllHitboxes().y
				<< "), BlocksTypes::brick);" << std::endl;
			break;
		case LevelEditorUnitsNames::dirt:
			file << "level.blocks.emplace_back(sf::Vector2f(" << i.getPosition().x << ", " << i.getPosition().y
				<< "), sf::Vector2f(" << i.sizeOfAllHitboxes().x << ", " << i.sizeOfAllHitboxes().y
				<< "), BlocksTypes::dirt);" << std::endl;
			break;	
		case LevelEditorUnitsNames::concrete:
			file << "level.blocks.emplace_back(sf::Vector2f(" << i.getPosition().x << ", " << i.getPosition().y
				<< "), sf::Vector2f(" << i.sizeOfAllHitboxes().x << ", " << i.sizeOfAllHitboxes().y
				<< "), BlocksTypes::concrete);" << std::endl;
			break;	
		case LevelEditorUnitsNames::granite:
			file << "level.blocks.emplace_back(sf::Vector2f(" << i.getPosition().x << ", " << i.getPosition().y
				<< "), sf::Vector2f(" << i.sizeOfAllHitboxes().x << ", " << i.sizeOfAllHitboxes().y
				<< "), BlocksTypes::granite);" << std::endl;
			break;
		case LevelEditorUnitsNames::coin:
			file << "level.coins.emplace_back(std::make_unique<Coin>(sf::Vector2f(" << i.getPosition().x << ", " << i.getPosition().y
				<< "), resources.textures.getResource(TextureID::Coin)));" << std::endl;
			break;
		case LevelEditorUnitsNames::deadlyFlower:
			file << "level.enemies.emplace_back(std::make_unique<DeadlyFlower>(sf::Vector2f(" << i.getPosition().x << ", " << i.getPosition().y
				<< "), resources));" << std::endl;
			break;
		case LevelEditorUnitsNames::zombie:
			file << "level.enemies.emplace_back(std::make_unique<Zombie>(sf::Vector2f(" << i.getPosition().x << ", " << i.getPosition().y
				<< "), sf::Vector2f(" << i.getMovingDistance().x << ", " << i.getMovingDistance().y
				<< "), resources));" << std::endl;
			break;
		case LevelEditorUnitsNames::skeleton:
			file << "level.enemies.emplace_back(std::make_unique<Skeleton>(sf::Vector2f(" << i.getPosition().x << ", " << i.getPosition().y
				<< "), sf::Vector2f(" << i.getMovingDistance().x << ", " << i.getMovingDistance().y
				<< "), resources));" << std::endl;
			break;
		case LevelEditorUnitsNames::spikes:
			file << "level.enemies.emplace_back(std::make_unique<Spikes>(sf::Vector2f(" << i.getPosition().x << ", " << i.getPosition().y
				<< "), resources, SpikeType::basic));" << std::endl;
			break;
		case LevelEditorUnitsNames::hidingSpikes:
			file << "level.enemies.emplace_back(std::make_unique<Spikes>(sf::Vector2f(" << i.getPosition().x << ", " << i.getPosition().y
				<< "), resources, SpikeType::hiding));" << std::endl;
			break; 
		case LevelEditorUnitsNames::showingAfterDamageSpikes:
			file << "level.enemies.emplace_back(std::make_unique<Spikes>(sf::Vector2f(" << i.getPosition().x << ", " << i.getPosition().y
				<< "), resources, SpikeType::showingAfterDamage));" << std::endl;
			break;
		case LevelEditorUnitsNames::fly:
			file << "level.enemies.emplace_back(std::make_unique<Fly>(sf::Vector2f(" << i.getPosition().x << ", " << i.getPosition().y
				<< "), sf::Vector2f(" << i.getMovingDistance().x << ", " << i.getMovingDistance().y
				<< "), resources));" << std::endl;
			break;
		case LevelEditorUnitsNames::gunEnemy:
			file << "level.enemies.emplace_back(std::make_unique<GunEnemy>(sf::Vector2f(" << i.getPosition().x << ", " << i.getPosition().y
				<< "), resources));" << std::endl;
			break;
		case LevelEditorUnitsNames::gunEnemyOnFakeBlock:
			file << "level.enemies.emplace_back(std::make_unique<GunEnemy>(sf::Vector2f(" << i.getPosition().x << ", " << i.getPosition().y
				<< "), stateData.resources));" << std::endl;
			file << "level.decorationBlocks.emplace_back(sf::Vector2f(" << i.getPosition().x << ", " << i.getPosition().y
				<< "), sf::Vector2f(" << i.sizeOfAllHitboxes().x << ", " << i.sizeOfAllHitboxes().y
				<< "), BlocksTypes::brick);" << std::endl;
			break;
		
		case LevelEditorUnitsNames::movingGunEnemyOnFakeBlock:
			file << "level.enemies.emplace_back(std::make_unique<GunEnemy>(sf::Vector2f(" << i.getPosition().x << ", " << i.getPosition().y
				<< "), stateData.resources));" << std::endl;
			file << "level.decorationBlocks.emplace_back(sf::Vector2f(" << i.getPosition().x << ", " << i.getPosition().y
				<< "), sf::Vector2f(" << i.sizeOfAllHitboxes().x << ", " << i.sizeOfAllHitboxes().y
				<< "), BlocksTypes::brick, sf::Vector2f(200.f, 200.f), sf::Vector2f("
				<< i.getMovingDistance().x << ", " << i.getMovingDistance().y
				<< "));" << std::endl;
			break;

		case LevelEditorUnitsNames::movingBrick:
			file << "level.blocks.emplace_back(sf::Vector2f(" << i.getPosition().x << ", " << i.getPosition().y
				<< "), sf::Vector2f(" << i.sizeOfAllHitboxes().x << ", " << i.sizeOfAllHitboxes().y
				<< "), BlocksTypes::brick, sf::Vector2f(200.f, 200.f), sf::Vector2f("
				<< i.getMovingDistance().x << ", " << i.getMovingDistance().y 
				<< "));" << std::endl;
			break;
		case LevelEditorUnitsNames::movingDirt:
			file << "level.blocks.emplace_back(sf::Vector2f(" << i.getPosition().x << ", " << i.getPosition().y
				<< "), sf::Vector2f(" << i.sizeOfAllHitboxes().x << ", " << i.sizeOfAllHitboxes().y
				<< "), BlocksTypes::dirt, sf::Vector2f(200.f, 200.f), sf::Vector2f("
				<< i.getMovingDistance().x << ", " << i.getMovingDistance().y
				<< "));" << std::endl;
			break;
		case LevelEditorUnitsNames::movingConcrete:
			file << "level.blocks.emplace_back(sf::Vector2f(" << i.getPosition().x << ", " << i.getPosition().y
				<< "), sf::Vector2f(" << i.sizeOfAllHitboxes().x << ", " << i.sizeOfAllHitboxes().y
				<< "), BlocksTypes::concrete, sf::Vector2f(200.f, 200.f), sf::Vector2f("
				<< i.getMovingDistance().x << ", " << i.getMovingDistance().y
				<< "));" << std::endl;
			break;
		case LevelEditorUnitsNames::movingGranite:
			file << "level.blocks.emplace_back(sf::Vector2f(" << i.getPosition().x << ", " << i.getPosition().y
				<< "), sf::Vector2f(" << i.sizeOfAllHitboxes().x << ", " << i.sizeOfAllHitboxes().y
				<< "), BlocksTypes::granite, sf::Vector2f(200.f, 200.f), sf::Vector2f("
				<< i.getMovingDistance().x << ", " << i.getMovingDistance().y
				<< "));" << std::endl;
			break;

		}
	}
	file.close();
	
}

std::unique_ptr<sf::Texture> LevelEditorState::loadTexture(const std::string& filepath, const sf::IntRect& area, const bool isRepeated)
{
	std::unique_ptr < sf::Texture > texture = std::make_unique< sf::Texture >();
	texture->loadFromFile(filepath, area);
	texture->setRepeated(isRepeated);
	return texture;
}

void LevelEditorState::handleSelectingUnitsByClick()
{
	if (wasMousePressed and units.size() >= 1 and !toolbar.isMouseOverToolbar(mousePositionHUD) and !sliderOfView.isSliding() and !sliderOfView.isMouseOver(mousePositionHUD))
	{
		bool isMouseOverEnemyGun = false;
		for (auto i = units.begin(); i != units.end() - numberOfSelectedUnits; ++i)
		{
			if (i->getType() == LevelEditorUnitsNames::gunEnemy) //first we are searching for a gun enemy, because it can be on blocks
			{
				if (i->hitboxComponent.contains(lastMousePosition))
				{
					isMouseOverEnemyGun = true;
					std::rotate(i, i + 1, units.end()); //move selected unit to back of the vector
					numberOfSelectedUnits = 1;
					break;
				}
			}
		}
		if (!isMouseOverEnemyGun)//if there is no enemy gun found, we are searching for others units
		{
			for (auto i = units.begin(); i != units.end() - numberOfSelectedUnits; ++i)
			{
				if (i->hitboxComponent.contains(lastMousePosition))
				{
					std::rotate(i, i + 1, units.end());
					numberOfSelectedUnits = 1;
					break;
				}
				if (!i->moveHitboxes.getHitboxes().empty() and UnitTypeChecker::isMovable(i->getType()))
				{
					if (i->moveHitboxes[0].getGlobalBounds().contains(lastMousePosition))
					{
						std::rotate(i, i + 1, units.end());
						numberOfSelectedUnits = 1;
						break;
					}
				}
			}
		}
	}
}

bool LevelEditorState::isMouseOverUnits() const
{
	for (auto const &i : units)
	{
		if (i.hitboxComponent.contains(mousePositionView))
		{
			return true;
		}
		if (UnitTypeChecker::isMovable(i.getType()))
		{
			if (i.moveHitboxes[0].getGlobalBounds().contains(mousePositionView))
			{
				return true;
			}
		}
	}

	return false;
}

bool LevelEditorState::isMouseOverBlocks() const
{
	for (auto const& i : units)
	{
		if (UnitTypeChecker::isBlock(i.getType()))
		{
			if (i.hitboxComponent.contains(mousePositionView))
			{
				return true;
			}
			if (UnitTypeChecker::isMovable(i.getType()))
			{
				if (i.moveHitboxes[0].getGlobalBounds().contains(mousePositionView))
				{
					return true;
				}
			}
		}	
	}

	return false;
}

bool LevelEditorState::isMouseOverEnemyGuns() const
{
	for (auto const& i : units)
	{
		if (i.getType() == LevelEditorUnitsNames::gunEnemy)
		{
			if (i.hitboxComponent.contains(mousePositionView))
			{
				return true;
			}
		}
	}
	return false;
}

std::vector<LevelEditorUnit>::iterator LevelEditorState::findPlayerInUnits()
{
	return std::find_if(units.begin(), units.end(), [](const LevelEditorUnit& unit){
		return unit.getType() == LevelEditorUnitsNames::player; });
}

void LevelEditorState::tryAddPlayerToUnits()
{
	if (findPlayerInUnits() == units.end())
	{
		units.emplace_back(sf::Vector2f(0.f, 400.f), unitsTextures, LevelEditorUnitsNames::player);
	}
}

std::vector<LevelEditorUnit>::iterator LevelEditorState::findPortalInUnits()
{
	return std::find_if(units.begin(), units.end(), [](const LevelEditorUnit& unit) {
		return unit.getType() == LevelEditorUnitsNames::portal; });
}

void LevelEditorState::tryAddPortalToUnits()
{
	if (findPortalInUnits() == units.end())
	{
		units.emplace_back(sf::Vector2f(500.f, 400.f), unitsTextures, LevelEditorUnitsNames::portal);
	}
}

void LevelEditorState::addUnitByClick()
{
	if (tileSize == 50)
		units.emplace_back(mousePositionView + sf::Vector2f(25, 25), unitsTextures, currentUnitType);
	else
		units.emplace_back(mousePositionView, unitsTextures, currentUnitType);
}

void LevelEditorState::addBlocksByCreatedArea()
{
	if (createBlockArea)
	{
		float width = static_cast<int>(createBlockArea->getGlobalBounds().width / 50) * 50;
		float height = static_cast<int>(createBlockArea->getGlobalBounds().height / 50) * 50;
		if (width < 50.f)
			width = 50.f;
		if (height < 50.f)
			height = 50.f;
		units.emplace_back(sf::Vector2f(createBlockArea->getGlobalBounds().left + width / 2 + (tileSize == 50 ? 25 : 0), createBlockArea->getGlobalBounds().top + height / 2 + (tileSize == 50 ? 25 : 0)), unitsTextures, currentUnitType, sf::Vector2f(100.f, 0.f), sf::Vector2f(width, height));
		createBlockArea.reset();
	}
}

void LevelEditorState::handleAddingUnits()
{
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (currentAction == Action::addingUnit)
			currentAction = Action::none;
	}
	if (wasMousePressed)
	{
		if (isAbleToAddUnit())
		{
			if (toolbar.isDrawBlockOn() and UnitTypeChecker::isBlock(currentUnitType) )
			{
				createArea(createBlockArea, sf::Color::Red);
				numberOfSelectedUnits = 0;
				currentAction = Action::creatingSelectedArea;
			}
			else
			{
				addUnitByClick();
				currentAction = Action::addingUnit;
				numberOfSelectedUnits = 1;
				updateAfterChanges();
			}
		}
	}
	if (wasLeftMouseReleased)
	{
		if (createBlockArea)
		{
			if (isAbleToAddUnit())
			{
				addBlocksByCreatedArea();
				numberOfSelectedUnits = 1;
				updateAfterChanges();
			}
			else
			{
				//to do- make feedback why you cant add unit
			}
			currentAction = Action::none;
			createBlockArea.reset();
		}
	}

}

bool LevelEditorState::isAbleToAddUnit()
{
	if (currentAction == Action::none or currentAction == Action::creatingSelectedArea)
	{
		if (!isMouseOverUnits() and !toolbar.isMouseOverToolbar(mousePositionHUD) and !sliderOfView.isMouseOver(mousePositionHUD))
		{
			return true;
		}
		else
		{
			if (currentUnitType == LevelEditorUnitsNames::gunEnemy) //gun enemy can be on a block(and only on a block) so it can be added when mouse is over a block
			{
				if (isMouseOverBlocks() and !isMouseOverEnemyGuns()) 
					return true;
			}
		}
	}
	return false;
}

void LevelEditorState::drawUnits(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto const& i : units)
	{
		i.drawBlueHitboxes(target);
	}
	for (auto const& i : units)
	{
		i.drawLines(target);
	}

	for (auto const& i : units)
	{
		if (i.getGlobalBounds().left < rightOfView and i.getGlobalBounds().left + i.getGlobalBounds().width > leftOfView)
			target.draw(i, states);
	}

	for (auto const& i : units)
	{
		i.drawMoveHitboxes(target);
	}
	if (numberOfSelectedUnits == 1)
	{
		units.back().drawChangeSizeHitboxes(target);
	}
	for (auto const& i : units)
	{
		if(i.getType() == LevelEditorUnitsNames::gunEnemy)
			target.draw(i, states);
	}
}

void LevelEditorState::handleMovingUnits()
{	
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (currentAction == Action::movingUnit)
		{
			updateAfterChanges();
			currentAction = Action::none;
		}
	}
	tryStartMovingUnits();
	tryMoveSelectedUnits();
}

void LevelEditorState::tryStartMovingUnits()
{
	if (currentAction == Action::none and !toolbar.isMouseOverToolbar(mousePositionHUD) and !sliderOfView.isSliding() and !sliderOfView.isMouseOver(mousePositionHUD))
	{
		if (wasMousePressed)
		{
			for (auto i = units.rbegin(); i != units.rbegin() + numberOfSelectedUnits; ++i)
			{
				if ((i->hitboxComponent.contains(lastMousePosition)))
				{
					currentAction = Action::movingUnit;
					break;
				}
			}
		}
	}
}

void LevelEditorState::tryMoveSelectedUnits()
{
	if (currentAction == Action::movingUnit)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2f numberOfTileToMove = sf::Vector2f();
			numberOfTileToMove.x = static_cast<int>(UnitShift.x) / tileSize;
			numberOfTileToMove.y = static_cast<int>(UnitShift.y) / tileSize;
			UnitShift -= numberOfTileToMove * static_cast<float>(tileSize);
			for (auto j = units.rbegin(); j != units.rbegin() + numberOfSelectedUnits; ++j)
			{
				j->move(numberOfTileToMove * static_cast<float>(tileSize));
			}
		}
	}
}

void LevelEditorState::handleChangingMovingDistance(const sf::RenderWindow& window)
{
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (currentAction == Action::changingMovingDistance)
		{
			updateAfterChanges();

			currentAction = Action::none;
		}
	}
	tryStartChangingMovingDistance();
	tryChangeMovingDistance(window);
}

void LevelEditorState::tryStartChangingMovingDistance()
{
	if (numberOfSelectedUnits == 1 ) //changing size is only possible if one unit is selected. if more are selected, moving move hitboxes will cause movement of all selected unit
	{
		if (!toolbar.isMouseOverToolbar(mousePositionHUD) and !sliderOfView.isSliding() and !sliderOfView.isMouseOver(mousePositionHUD))
		{
			if (UnitTypeChecker::isMovable(units.back().getType()))
			{
				if (units.back().moveHitboxes[0].getGlobalBounds().contains(lastMousePosition) and wasMousePressed)
				{
					currentAction = Action::changingMovingDistance;
				}
			}
		}	
	}
}

void LevelEditorState::tryChangeMovingDistance(const sf::RenderWindow& window)
{
	if (currentAction == Action::changingMovingDistance)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if ((units.back().getMovingDistance().y == 0))
			{
				if (abs(UnitShift.x) >= tileSize)
				{
					int numberOfTileToShift = static_cast<int>(UnitShift.x) / tileSize;
					units.back().updateMoveDistance(sf::Vector2f(numberOfTileToShift * tileSize, 0));
					UnitShift.x -= numberOfTileToShift * tileSize;
				}
				if (abs(UnitShift.y) >= 150 and !UnitTypeChecker::isGround(units.back().getType()))
				{
					int numberOfTileToShift = static_cast<int>(UnitShift.y) / tileSize;
					units.back().updateMoveDistance(sf::Vector2f(0, numberOfTileToShift * tileSize));
					sf::Mouse::setPosition(window.mapCoordsToPixel(units.back().moveHitboxes[0].getCenter()), window);
					wasUsedMouseSetPos = true;
					UnitShift.y -= numberOfTileToShift * tileSize;
				}
			}
			else
			{
				if (abs(UnitShift.y) >= tileSize)
				{
					int numberOfTileToShift = static_cast<int>(UnitShift.y) / tileSize;
					units.back().updateMoveDistance(sf::Vector2f(0, numberOfTileToShift * tileSize));
					UnitShift.y -= numberOfTileToShift * tileSize;
				}
				if (abs(UnitShift.x) >= 150)
				{
					int numberOfTileToShift = static_cast<int>(UnitShift.x) / tileSize;
					units.back().updateMoveDistance(sf::Vector2f(numberOfTileToShift * tileSize, 0));
					sf::Mouse::setPosition(window.mapCoordsToPixel(units.back().moveHitboxes[0].getCenter()), window);
					wasUsedMouseSetPos = true;
					UnitShift.x -= numberOfTileToShift * tileSize;
				}
			}
			if ((units.back().wasMovingHitboxTeleported()))
			{
				sf::Mouse::setPosition(window.mapCoordsToPixel(units.back().moveHitboxes[0].getCenter()), window);
				units.back().setMovingHitboxWasTeleported(false);
				wasUsedMouseSetPos = true;
			}
		}
	}
}

void LevelEditorState::handleChangingSizeOfBlocks()
{
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (currentAction == Action::changinSizeOfUnit)
		{
			updateAfterChanges();
			currentAction = Action::none;
		}
	}
	tryStartChangingSizeOfBlocks();
	tryChangeSizeOfBlocks();
}

void LevelEditorState::tryStartChangingSizeOfBlocks()
{
	if (numberOfSelectedUnits == 1 and !toolbar.isMouseOverToolbar(mousePositionHUD) and !sliderOfView.isSliding() and !sliderOfView.isMouseOver(mousePositionHUD))
	{
		if (currentAction == Action::none)
		{			
			if (wasMousePressed)
			{
				auto changeSizeHitboxes = &units.back().changeSizeHitboxes.hitboxes;
				for (auto i = changeSizeHitboxes->begin(); i < changeSizeHitboxes->end(); i++)
				{
					if (i->contains(lastMousePosition))
					{
						currentAction = Action::changinSizeOfUnit;
						numberOfHitboxChangingSize = std::distance(changeSizeHitboxes->begin(), i);
						break;
					}
				}
			}
		}
	}
}

void LevelEditorState::tryChangeSizeOfBlocks()
{
	if (currentAction == Action::changinSizeOfUnit)
	{
		auto blockChangingSize = &units.back();
		sf::Vector2i sizeDifference(0, 0);
		sf::Vector2f offset;
		if (numberOfHitboxChangingSize == 0 or numberOfHitboxChangingSize == 4 or numberOfHitboxChangingSize == 5 or
			numberOfHitboxChangingSize == 1 or numberOfHitboxChangingSize == 6 or numberOfHitboxChangingSize == 7)
		{
			if (UnitShift.x < -50.f)
			{
				UnitShift.x += 50.f;
				if (numberOfHitboxChangingSize == 0 or numberOfHitboxChangingSize == 4 or numberOfHitboxChangingSize == 5)
					sizeDifference = sf::Vector2i(50, 0);
				else
					sizeDifference = sf::Vector2i(-50, 0);

				offset = sf::Vector2f(-25.f, 0.f);
			}
			if (UnitShift.x > 50.f)
			{
				UnitShift.x -= 50.f;
				if (numberOfHitboxChangingSize == 0 or numberOfHitboxChangingSize == 4 or numberOfHitboxChangingSize == 5)
					sizeDifference = sf::Vector2i(-50, 0);
				else
					sizeDifference = sf::Vector2i(50, 0);

				offset = sf::Vector2f(25.f, 0.f);
			}
		}

		if (numberOfHitboxChangingSize == 2 or numberOfHitboxChangingSize == 4 or numberOfHitboxChangingSize == 6 or
			numberOfHitboxChangingSize == 3 or numberOfHitboxChangingSize == 5 or numberOfHitboxChangingSize == 7)
		{
			if (UnitShift.y > 50.f)
			{
				UnitShift.y -= 50.f;
				if (numberOfHitboxChangingSize == 2 or numberOfHitboxChangingSize == 4 or numberOfHitboxChangingSize == 6)
					sizeDifference = sf::Vector2i(0, -50);
				else
					sizeDifference = sf::Vector2i(0, 50);

				offset = sf::Vector2f(0.f, 25.f);
			}

			if (UnitShift.y < -50.f)
			{
				UnitShift.y += 50.f;
				if (numberOfHitboxChangingSize == 2 or numberOfHitboxChangingSize == 4 or numberOfHitboxChangingSize == 6)
					sizeDifference = sf::Vector2i(0, 50);
				else
					sizeDifference = sf::Vector2i(0, -50);

				offset = sf::Vector2f(0.f, -25.f);
			}
		}
		if (sizeDifference != sf::Vector2i(0, 0))
		{
			if (blockChangingSize->getSize().x + sizeDifference.x >= 50 and blockChangingSize->getSize().y + sizeDifference.y >= 50 and
				blockChangingSize->getSize().y + sizeDifference.y <= 1600)
			{
				blockChangingSize->addSize(sizeDifference);
				blockChangingSize->move(offset);
			}
		}
	}
}

void LevelEditorState::updatePositionIfUnitsColliding()
{
	if (units.size() >= 1 and !sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		bool isColliding = false;
		std::reverse_iterator<std::vector<LevelEditorUnit>::iterator> collidingUnit;

		collidingUnit = findCollidingSelectedUnit();
		if (collidingUnit != units.rend())
			isColliding = true;
		
		if (isColliding)
		{
			sf::Vector2f currentShift;

			int totalShift = tileSize;

			float maxTopOfUnitsOnClipboard = std::max_element(units.rbegin(), units.rbegin() + numberOfSelectedUnits, [](const LevelEditorUnit& a, const LevelEditorUnit& b) {
				return a.maxTopHitboxes() > b.maxTopHitboxes();
				})->maxTopHitboxes();
			float maxBottomOfUnitsOnClipboard = std::max_element(units.rbegin(), units.rbegin() + numberOfSelectedUnits, [](const LevelEditorUnit& a, const LevelEditorUnit& b) {
				return a.maxBottomHitboxes() < b.maxBottomHitboxes();
				})->maxBottomHitboxes();

			std::vector<std::tuple<sf::FloatRect, sf::Vector2f, LevelEditorUnitsNames>> unitsHitboxes;
			std::vector<std::tuple<sf::FloatRect, sf::Vector2f, LevelEditorUnitsNames>> unitsMoveHitboxes;
			sf::Vector2f initialPostionOfPoint = collidingUnit->hitboxComponent.getHitboxes()[0].getCenter();

			for (auto i = units.rbegin(); i != units.rbegin() + numberOfSelectedUnits; ++i)
			{
				for (auto const& hitbox : i->hitboxComponent.getHitboxes())
					unitsHitboxes.emplace_back(hitbox.getGlobalBounds(), sf::Vector2f(hitbox.getGlobalBounds().left, hitbox.getGlobalBounds().top), i->getType());
			

				for (auto const& hitbox : i->moveHitboxes.getHitboxes())
					unitsMoveHitboxes.emplace_back(hitbox.getGlobalBounds(), sf::Vector2f(hitbox.getGlobalBounds().left, hitbox.getGlobalBounds().top), i->getType());
			}

			bool isContainsPoint = false;
			sf::Vector2f point;

			while (isColliding)
			{
				for (int j = 0; j < 4; j++)
				{
					for (int i = 0; i <= totalShift; i += tileSize)
					{
						isContainsPoint = false;
						switch (j)
						{
						case 0:
							point.x = initialPostionOfPoint.x + (totalShift - i);
							point.y = initialPostionOfPoint.y + i;
							break;
						case 1:
							point.x = initialPostionOfPoint.x - (totalShift - i);
							point.y = initialPostionOfPoint.y + i;
							break;
						case 2:
							point.x = initialPostionOfPoint.x + (totalShift - i);
							point.y = initialPostionOfPoint.y - i;
							break;
						case 3:
							point.x = initialPostionOfPoint.x - (totalShift - i);
							point.y = initialPostionOfPoint.y - i;
							break;
						}
						currentShift = point - initialPostionOfPoint;
						if (maxTopOfUnitsOnClipboard + currentShift.y >= -310.f and maxBottomOfUnitsOnClipboard + currentShift.y <= 1390)
						{			
							for (auto i = units.begin(); i != units.end() - numberOfSelectedUnits; i++)
							{
								if (i->hitboxComponent.contains(point) and i->moveHitboxes.contains(point))
								{
									isContainsPoint = true;
									break;
								}
							}

							if (!isContainsPoint)
							{
								for (auto& i : unitsHitboxes)
								{
									std::get<0>(i).left = (std::get<1>(i).x + currentShift.x);
									std::get<0>(i).top = (std::get<1>(i).y + currentShift.y);
								}
								for (auto& i : unitsMoveHitboxes)
								{
									std::get<0>(i).left = (std::get<1>(i).x + currentShift.x);
									std::get<0>(i).top = (std::get<1>(i).y + currentShift.y);
								}

								if (!isCollidingWithNoSelectedUnits(unitsHitboxes, unitsMoveHitboxes))
								{
									isColliding = false;
									for (auto i = units.rbegin(); i != units.rbegin() + numberOfSelectedUnits; ++i)
										i->move(currentShift);
									break;
								}
							}
						}
					}
					if (!isColliding)
					{
						break;
					}
				}
				totalShift += tileSize;
			}
		}
	}
}


void LevelEditorState::setPositionsOfUnitsHitboxes(const std::vector<sf::Vector2f>& positionsOfUnitsHitboxes, const std::vector<sf::Vector2f>& positionsOfUnitsMoveHitboxes)
{
	int numberOfHitbox = 0;
	for (auto i = units.rbegin(); i != units.rbegin() + numberOfSelectedUnits; ++i)
	{
		for (auto j =  i->hitboxComponent.hitboxes.begin(); j != i->hitboxComponent.hitboxes.end(); j++)
		{
			j->setPosition(positionsOfUnitsHitboxes[numberOfHitbox]);
			numberOfHitbox++;
		}
	}
	numberOfHitbox = 0;
	for (auto i = units.rbegin(); i != units.rbegin() + numberOfSelectedUnits; ++i)
	{
		for (auto j = i->moveHitboxes.hitboxes.begin(); j != i->moveHitboxes.hitboxes.end(); j++)
		{
			j->setPosition(positionsOfUnitsMoveHitboxes[numberOfHitbox]);
			numberOfHitbox++;
		}
	}
	
}

std::vector<LevelEditorUnit>::reverse_iterator LevelEditorState::findCollidingSelectedUnit()
{
	for (auto selected = units.rbegin(); selected != units.rbegin() + numberOfSelectedUnits; ++selected)
	{
		if (selected->maxTopHitboxes() < -310.f or selected->maxBottomHitboxes() > 1390)
			return selected;
	}

	for (auto i = units.begin(); i != units.end() - numberOfSelectedUnits; i++)
	{
		for (auto selected = units.rbegin(); selected != units.rbegin() + numberOfSelectedUnits; ++selected)
		{
			if (selected->hitboxComponent.intersects(i->hitboxComponent))
			{
				if (UnitTypeChecker::isBlock(i->getType()) and selected->getType() == LevelEditorUnitsNames::gunEnemy)
				{
				}
				else if (UnitTypeChecker::isBlock(selected->getType()) and i->getType() == LevelEditorUnitsNames::gunEnemy)
				{
				}
				else
				{
					return selected;
				}
			}
			
			if (UnitTypeChecker::isBlock(i->getType()))
			{
				if (selected->getType() != LevelEditorUnitsNames::gunEnemy)
				{
					if (i->hitboxComponent.intersects(selected->moveHitboxes))
					{
						return selected;
					}

					if (i->moveHitboxes.intersects(selected->moveHitboxes) or
						i->moveHitboxes.intersects(selected->hitboxComponent))
					{
						if (!selected->base.intersects(i->hitboxComponent))
						{
							return selected;
						}
					}
				}
			}

			if (UnitTypeChecker::isBlock(selected->getType()))
			{
				if (i->getType() != LevelEditorUnitsNames::gunEnemy)
				{
					if (selected->hitboxComponent.intersects(i->moveHitboxes))
						return selected;

					if (selected->moveHitboxes.intersects(i->moveHitboxes) or
						selected->moveHitboxes.intersects(i->hitboxComponent))
					{
						if (!i->base.intersects(selected->hitboxComponent))
						{
							return selected;
						}
					}
				}			
			}			
		}
	}

	return units.rend();
}

bool LevelEditorState::isCollidingWithNoSelectedUnits(const std::vector<std::tuple<sf::FloatRect, sf::Vector2f, LevelEditorUnitsNames>>& unitsHitboxes, const std::vector<std::tuple<sf::FloatRect, sf::Vector2f, LevelEditorUnitsNames>>& unitsMoveHitboxes) const
{
	for (auto i = units.begin(); i != units.end() - numberOfSelectedUnits; i++)
	{
		for (auto const & selected : unitsHitboxes)
		{
			if (i->hitboxComponent.intersects(std::get<0>(selected)))
			{
				if (UnitTypeChecker::isBlock(i->getType()) and std::get<2>(selected) == LevelEditorUnitsNames::gunEnemy)
				{
				}
				else if (UnitTypeChecker::isBlock(std::get<2>(selected)) and i->getType() == LevelEditorUnitsNames::gunEnemy)
				{
				}
				else
					return true;
			}

			if (UnitTypeChecker::isBlock(i->getType()) or UnitTypeChecker::isBlock(std::get<2>(selected)))
			{
				if (i->moveHitboxes.intersects(std::get<0>(selected)))
					return true;
			}
		}
		for (auto const& selected : unitsMoveHitboxes)
		{
			if (UnitTypeChecker::isBlock(i->getType()) or UnitTypeChecker::isBlock(std::get<2>(selected)))
			{
				if (i->moveHitboxes.intersects(std::get<0>(selected)))
					return true;
			
				if(i->hitboxComponent.intersects(std::get<0>(selected)))
					return true;
			}
		}
	}
	return false;
}

void LevelEditorState::roundPositionsOfUnits()
{
	//if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (!units.empty())
		{			
			for (auto i = units.rbegin(); i != units.rbegin() + numberOfSelectedUnits; i++)
			{
				bool isPositionXDivisibleBy5 = false;
				bool isPositionYDivisibleBy5 = false;
				if (static_cast<int>(std::round(i->hitboxComponent.getHitboxes()[0].getLeft())) % tileSize == 0 and 
					static_cast<int>(std::round(i->hitboxComponent.getHitboxes()[0].getLeft())) == std::round(i->hitboxComponent.getHitboxes()[0].getLeft()))
				{
					isPositionXDivisibleBy5 = true;
				}
				

				if (static_cast<int>(std::round(i->hitboxComponent.getHitboxes()[0].getTop()) + 10) % tileSize == 0 and 
					static_cast<int>(std::round(i->hitboxComponent.getHitboxes()[0].getTop())) == std::round(i->hitboxComponent.getHitboxes()[0].getTop()))
					isPositionYDivisibleBy5 = true;

				if (!isPositionXDivisibleBy5)
				{
					int newPositionX{ 0 };
					if (i->hitboxComponent.getHitboxes()[0].getLeft() < 0)
						newPositionX = (static_cast<int>(i->hitboxComponent.getHitboxes()[0].getLeft()) / tileSize) * tileSize - tileSize;
					else
						newPositionX = (static_cast<int>(i->hitboxComponent.getHitboxes()[0].getLeft()) / tileSize) * tileSize;
					i->setPositionRelativeToHitbox(sf::Vector2f(newPositionX, i->hitboxComponent.getHitboxes()[0].getTop()));
				}
				
				if (!isPositionYDivisibleBy5)
				{
					int newPositionY{ 0 };
					if (i->hitboxComponent.getHitboxes()[0].getTop() < 0)
						newPositionY = (static_cast<int>(i->hitboxComponent.getHitboxes()[0].getTop()) / tileSize) * tileSize - tileSize - (tileSize == 50 ? 10 : 0);
					else
						newPositionY = (static_cast<int>(i->hitboxComponent.getHitboxes()[0].getTop()) / tileSize) * tileSize - (tileSize == 50 ? 10 : 0);
					i->setPositionRelativeToHitbox(sf::Vector2f(i->hitboxComponent.getHitboxes()[0].getLeft(), newPositionY));
				}
			}			
		}	
	}
}




void LevelEditorState::updatePositionsOfBackgrounds(std::array<sf::Sprite, 2>& backgrounds)
{
	for (auto& i : backgrounds)
	{
		if (view.getCenter().x - i.getPosition().x > 5000)
		{
			i.move(6800, 0);
		}
		if (view.getCenter().x - i.getPosition().x < -1900)
		{
			i.move(-6800, 0);
		}
	}
}

void LevelEditorState::drawBackgrounds(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto const& i : backgrounds)
		target.draw(i, states);
}

void LevelEditorState::updatePositionOfView(const float deltaTime)
{
	if (sliderOfView.wasValueChanged())
		view.setCenter(sf::Vector2f(sliderOfView.getValue(), view.getCenter().y));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) and !sliderOfView.wasValueChanged() and !sliderOfView.isSliding())
	{
		view.move(sf::Vector2f(toolbar.getVelocityOfView(), 0) * deltaTime);
		sliderOfView.setValue(view.getCenter().x);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) and !sliderOfView.wasValueChanged() and !sliderOfView.isSliding())
	{
		view.move(sf::Vector2f(-toolbar.getVelocityOfView(), 0) * deltaTime);
		sliderOfView.setValue(view.getCenter().x);
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) and !toolbar.select() and !toolbar.isMouseOverToolbar(mousePositionHUD) and !sliderOfView.isSliding())
	{
		view.move(sf::Vector2f(-MouseShiftRelativeToHUDView.x, 0.f));
		sliderOfView.setValue(view.getCenter().x);
	}
}

void LevelEditorState::handleZoomingView(float deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		view.zoom(1 + deltaTime * 2);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
		view.zoom(1 - deltaTime * 2);


	if (view.getSize().y >= 1700)
		view.setSize(3022, 1700);

	if (view.getSize().y < 1500)
		view.setSize(2666.666, 1500);
}

void LevelEditorState::drawHelpLines(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto const& i : helpLines)
		target.draw(i, states);
}

void LevelEditorState::updateTransparentOfHelpLines()
{
	for (auto& i : helpLines)
		i.setColor(sf::Color(255, 255, 255, toolbar.getGridTransparent()));
}


void LevelEditorState::updateColorOfUnits()
{
	if (!units.empty())
	{
		for (auto i = units.rbegin(); i != units.rbegin() + numberOfSelectedUnits; ++i)
		{
			i->setColor(sf::Color::Green);
		}
		for (auto i = units.begin(); i != units.end() - numberOfSelectedUnits; i++)
		{
			if (i->getPlacementIssue() == UnitPlacementIssues::none)
				i->setColor(sf::Color::White);
			else
				i->setColor(sf::Color::Red);
		}
	}
}


void LevelEditorState::createArea(std::unique_ptr<sf::RectangleShape>& area, const sf::Color& colorOfArea)
{
	area = std::make_unique<sf::RectangleShape>();
	area->setOutlineColor(colorOfArea);
	area->setFillColor(sf::Color(colorOfArea.r, colorOfArea.g, colorOfArea.b, 100));
	area->setPosition(mousePositionView);
	area->setOutlineThickness(1);
}

void LevelEditorState::updateArea(std::unique_ptr<sf::RectangleShape>& area)
{
	if (area)
		area->setSize(area->getSize() + MouseShift);
}

void LevelEditorState::selectUnitsBySelectedArea()
{
	if (selectedArea)
	{
		numberOfSelectedUnits = 0;
		if (units.size() >= 1)
		{
			auto i = units.begin();
			while (i != units.end() - numberOfSelectedUnits)
			{
				if (i->hitboxComponent.intersects(selectedArea->getGlobalBounds()))
				{
					std::rotate(i, i + 1, units.end());
					numberOfSelectedUnits++;
				}
				else
				{
					i++;
				}
			}
		}
	}
}

void LevelEditorState::deleteSelectedUnits()
{
	units.erase(std::remove_if(units.end() - numberOfSelectedUnits, units.end(),
		[](const LevelEditorUnit& unit) 
		{
			return !UnitTypeChecker::isUndeletable(unit.getType()); 
		}), units.end());

	numberOfSelectedUnits = 0;
	updateAfterChanges();
}

void LevelEditorState::initFunctionConvertUnitsToLevel()
{
		const std::vector<LevelEditorUnit>& levelEditorUnits = units;
		convertUnitsToLevel = [&levelEditorUnits](const Resources& resources)
		{ 
			Level level;
			for (auto const& i : levelEditorUnits)
			{
				switch (i.getType())
				{
				case LevelEditorUnitsNames::player:
					level.initialPositionOfPlayer = i.getPosition();
					break;
				case LevelEditorUnitsNames::portal:
					level.endOfLevelPosition = i.getPosition();
					break;
				case LevelEditorUnitsNames::brick:
					level.blocks.emplace_back(i.getPosition(), sf::Vector2f(i.getGlobalBounds().width, i.getGlobalBounds().height), BlocksTypes::brick);
					break;
				case LevelEditorUnitsNames::dirt:
					level.blocks.emplace_back(i.getPosition(), sf::Vector2f(i.getGlobalBounds().width, i.getGlobalBounds().height), BlocksTypes::dirt);
					break;
				case LevelEditorUnitsNames::concrete:
					level.blocks.emplace_back(i.getPosition(), sf::Vector2f(i.getGlobalBounds().width, i.getGlobalBounds().height), BlocksTypes::concrete);
					break;
				case LevelEditorUnitsNames::granite:
					level.blocks.emplace_back(i.getPosition(), sf::Vector2f(i.getGlobalBounds().width, i.getGlobalBounds().height), BlocksTypes::granite);
					break;
				case LevelEditorUnitsNames::deadlyFlower:
					level.enemies.emplace_back(std::make_unique<DeadlyFlower>(i.getPosition(), resources));
					break;
				case LevelEditorUnitsNames::spikes:
					level.enemies.emplace_back(std::make_unique<Spikes>(i.getPosition(), resources, SpikeType::basic));
					break;
				case LevelEditorUnitsNames::hidingSpikes:
					level.enemies.emplace_back(std::make_unique<Spikes>(i.getPosition(), resources, SpikeType::hiding));
					break;
				case LevelEditorUnitsNames::showingAfterDamageSpikes:
					level.enemies.emplace_back(std::make_unique<Spikes>(i.getPosition(), resources, SpikeType::showingAfterDamage));
					break;
				case LevelEditorUnitsNames::coin:
					level.coins.emplace_back(std::make_unique<Coin>(i.getPosition(), resources[TextureID::Coin]));
					break;
				case LevelEditorUnitsNames::movingBrick:
					level.blocks.emplace_back(i.getPosition(), sf::Vector2f(i.getGlobalBounds().width, i.getGlobalBounds().height), BlocksTypes::brick, sf::Vector2f(200.f, 200.f), i.getMovingDistance());
					break;
				case LevelEditorUnitsNames::movingDirt:
					level.blocks.emplace_back(i.getPosition(), sf::Vector2f(i.getGlobalBounds().width, i.getGlobalBounds().height), BlocksTypes::dirt, sf::Vector2f(200.f, 200.f), i.getMovingDistance());
					break;
				case LevelEditorUnitsNames::movingConcrete:
					level.blocks.emplace_back(i.getPosition(), sf::Vector2f(i.getGlobalBounds().width, i.getGlobalBounds().height), BlocksTypes::concrete, sf::Vector2f(200.f, 200.f), i.getMovingDistance());
					break;
				case LevelEditorUnitsNames::movingGranite:
					level.blocks.emplace_back(i.getPosition(), sf::Vector2f(i.getGlobalBounds().width, i.getGlobalBounds().height), BlocksTypes::granite, sf::Vector2f(200.f, 200.f), i.getMovingDistance());
					break;
				case LevelEditorUnitsNames::zombie:
					level.enemies.emplace_back(std::make_unique<Zombie>(i.getPosition(), i.getMovingDistance(), resources));
					break;
				case LevelEditorUnitsNames::skeleton:
					level.enemies.emplace_back(std::make_unique<Skeleton>(i.getPosition(), i.getMovingDistance(), resources));
					break;
				case LevelEditorUnitsNames::fly:
					level.enemies.emplace_back(std::make_unique<Fly>(i.getPosition(), i.getMovingDistance(), resources));
					break;	
				case LevelEditorUnitsNames::slimeEnemy:
					level.enemies.emplace_back(std::make_unique<SlimeEnemy>(i.getPosition(), i.getMovingDistance(), resources));
					break;
				case LevelEditorUnitsNames::zombieInGround:
					level.enemies.emplace_back(std::make_unique<ZombieInGround>(i.getPosition(), resources));
					break;
				case LevelEditorUnitsNames::ghost:
					level.enemies.emplace_back(std::make_unique<Ghost>(i.getPosition(), i.getMovingDistance(), resources));
					break;
				case LevelEditorUnitsNames::bat:
					level.enemies.emplace_back(std::make_unique<Bat>(i.getPosition(), i.getMovingDistance(), resources));
					break;
				case LevelEditorUnitsNames::spinningSpikes:
					level.enemies.emplace_back(std::make_unique<SpinningSpikes>(i.getPosition(), sf::Vector2f( 0.f, 0.f ), resources));
					break;
				case LevelEditorUnitsNames::movingSpinningSpikes:
					level.enemies.emplace_back(std::make_unique<SpinningSpikes>(i.getPosition(), i.getMovingDistance(), resources));
					break;
				case LevelEditorUnitsNames::gunEnemyOnFakeBlock:
					level.enemies.emplace_back(std::make_unique<GunEnemy>(i.getPosition(), resources));
					level.decorationBlocks.emplace_back(i.getPosition(), sf::Vector2f(100.f, 100.f), BlocksTypes::brick);
					break;
				case LevelEditorUnitsNames::movingGunEnemyOnFakeBlock:
					level.enemies.emplace_back(std::make_unique<GunEnemy>(i.getPosition(), resources));
					level.decorationBlocks.emplace_back(i.getPosition(), sf::Vector2f(100.f, 100.f), BlocksTypes::brick, sf::Vector2f(200.f, 200.f), i.getMovingDistance());
					break;
				case LevelEditorUnitsNames::gunEnemy:
					level.enemies.emplace_back(std::make_unique<GunEnemy>(i.getPosition(), resources));
					break;
				case LevelEditorUnitsNames::trampoline:
					level.trampolines.emplace_back(i.getPosition(), resources);
					break;
				}
			} 
			return level;
		};
		
}

void LevelEditorState::updateMessageOfIssues()
{
	messageOfIssues.setString(L"");
	bool wasNotOnBlockIssue = false;
	bool wasNotPlaceToMoveIssue = false;

	for (auto const& i : units)
	{
		if (!wasNotOnBlockIssue)
		{
			if (i.getPlacementIssue() == UnitPlacementIssues::NotOnBlock)
			{
				messageOfIssues.setString(messageOfIssues.getString() + L"\nNaziemne potwory musz¹ staæ na bloku!");
				wasNotOnBlockIssue = true;

				if (wasNotPlaceToMoveIssue)
					break;
			}
		}
		if (!wasNotPlaceToMoveIssue)
		{
			if (i.getPlacementIssue() == UnitPlacementIssues::NotPlaceToMove)
			{
				messageOfIssues.setString(messageOfIssues.getString() + L"\nChodz¹ce potwory musz¹ mieæ miejsce na poruszanie siê!");
				wasNotPlaceToMoveIssue = true;
				if (wasNotOnBlockIssue)
					break;
			}
		}

	}
}

void LevelEditorState::initMessageOfIssues()
{
	messageOfIssues.setPosition(sf::Vector2f(1500.f, 20.f));
	messageOfIssues.setFont(stateData.resources.font);
	messageOfIssues.setCharacterSize(30.f);
	messageOfIssues.setFillColor(sf::Color::Red);
	messageOfIssues.setOutlineThickness(2.f);
}


void LevelEditorState::setSliderOfView()
{
	float minPosition = computeMinPositionXOfUnit();
	float maxPosition = computeMaxPositionXOfUnit();

	sliderOfView.setMin(minPosition);
	sliderOfView.setMax(maxPosition);
	sliderOfView.setValue(view.getCenter().x);
}

float LevelEditorState::computeMinPositionXOfUnit()
{
	if (!units.empty())
	{
		return std::max_element(units.begin(), units.end(), [](const LevelEditorUnit& a, const LevelEditorUnit& b) {
			return a.maxLeftHitboxes() > b.maxLeftHitboxes();
			})->maxLeftHitboxes();

	}
	else
	{
		return 0.f;
	}
}

float LevelEditorState::computeMaxPositionXOfUnit()
{
	if (!units.empty())
	{
		return std::max_element(units.begin(), units.end(), [](const LevelEditorUnit& a, const LevelEditorUnit& b) {
			return a.maxRightHitboxes() < b.maxRightHitboxes();
			})->maxRightHitboxes();
	}
	else
	{
		return 1000.f;
	}
}

void LevelEditorState::updateAfterChanges()
{
	roundPositionsOfUnits();
	do {
		updatePositionIfUnitsColliding();
		setMovingDistanceWhenUnitIsOnBlock();
		setHitboxesWhenUnitIsSetOnMovingBlock();
	} while (findCollidingSelectedUnit() != units.rend());

	markIfSelectedUnitIsSetIncorrecly();
	updateMessageOfIssues();
	changeTracker.addCurrentUnitsToHistory();
	setSliderOfView();
}

void LevelEditorState::handleKeyboardShortcuts(sf::Keyboard::Key codeOfPressedKey)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) or sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
	{
		if (codeOfPressedKey == sf::Keyboard::C)
			clipboard.copySelectedUnits();

		if (codeOfPressedKey == sf::Keyboard::V)
		{
			clipboard.paste(mousePositionView);
			updateAfterChanges();
		}

		if (codeOfPressedKey == sf::Keyboard::Z)
			changeTracker.undoChangeOfUnits();

		if (codeOfPressedKey == sf::Keyboard::Y)
			changeTracker.redoChangeOfUnits();

		if (codeOfPressedKey == sf::Keyboard::S)
		{
			saveUnitsToFile();
			feedback = std::make_unique<Feedback>(sf::Vector2f(0, 700), L"Level zosta³ poprawnie zapisany", 50, stateData.resources.font);
		}
	}
}


void LevelEditorState::markIfSelectedUnitIsSetIncorrecly()
{
	bool isBlock = false;
	for (auto& block : units)
	{
		if (UnitTypeChecker::isBlock(block.getType()))
		{
			isBlock = true;
		}
	}
	for (auto& groundUnit : units)
	{
		if (UnitTypeChecker::isGround(groundUnit.getType()))
		{
			if (isBlock)
			{
				for (auto& block : units)
				{
					if (UnitTypeChecker::isBlock(block.getType()))
					{
						isBlock = true;
						if (isGroundUnitOnBlock(groundUnit, block))
						{
							groundUnit.setPlacementIssue(UnitPlacementIssues::none);
							if (UnitTypeChecker::isMovingEnemy(groundUnit.getType()))
							{
								if (abs(calculateMaxMovingDistance(groundUnit, block)) < 50.f)
									groundUnit.setPlacementIssue(UnitPlacementIssues::NotPlaceToMove);
							}
							break;
						}
						else
						{
							groundUnit.setPlacementIssue(UnitPlacementIssues::NotOnBlock);
						}
					}
				}
			}
			else
			{
				groundUnit.setPlacementIssue(UnitPlacementIssues::NotOnBlock);
			}	
		}
	}
}

bool LevelEditorState::isGroundUnitOnBlock(const LevelEditorUnit& groundUnit, const LevelEditorUnit& block) const
{
	for (auto const& i : groundUnit.base.getHitboxes())
	{
		if (!block.hitboxComponent.intersects(i))
		{
			return false;
		}
	}
	if (groundUnit.base.size() > 0)
		return true;
	else
		return false;
}



void LevelEditorState::setMovingDistanceWhenUnitIsOnBlock()
{
	for (auto& movingUnit : units)
	{
		if (UnitTypeChecker::isMovingEnemy(movingUnit.getType()))
		{
			for (auto& block : units)
			{
				if (UnitTypeChecker::isBlock(block.getType()))
				{
					if (isGroundUnitOnBlock(movingUnit, block))
					{
						if (movingUnit.getMovingDistance().y != 0)
							movingUnit.setMovingHitboxes(sf::Vector2f(50.f, 0.f));
						float maxMovingDistance = calculateMaxMovingDistance(movingUnit, block);
						if (abs(maxMovingDistance) >= 50.f)
						{
							if (abs(movingUnit.getMovingDistance().x) > abs(maxMovingDistance))
								movingUnit.setMovingHitboxes(sf::Vector2f(maxMovingDistance, 0.f));
						}
						else
						{
							if (movingUnit.getMovingDistance().x >= 0)
								movingUnit.setMovingHitboxes(sf::Vector2f(50.f, 0.f));
							else
								movingUnit.setMovingHitboxes(sf::Vector2f(-50.f, 0.f));
						}
						break;
					}
				}
			}
		}
	}
}

void LevelEditorState::setHitboxesWhenUnitIsSetOnMovingBlock()
{
	for (auto& unit : units)
	{
		if ((UnitTypeChecker::isEnemy(unit.getType()) or UnitTypeChecker::isCoin(unit.getType())) and unit.getType() != LevelEditorUnitsNames::gunEnemy)
		{
			for (auto& block : units)
			{
				if (UnitTypeChecker::isMovingBlock(block.getType()))
				{
					if (isGroundUnitOnBlock(unit, block))
					{
						if(unit.moveHitboxes.getHitboxes().size() == 4)
						{
							unit.moveHitboxes.hitboxes.pop_back();
							unit.moveHitboxes.hitboxes.pop_back();
						}
						if (!UnitTypeChecker::isMovable(unit.getType()))
						{
							if (unit.moveHitboxes.getHitboxes().size() == 2)
							{
								unit.moveHitboxes.hitboxes.pop_back();
								unit.moveHitboxes.hitboxes.pop_back();
							}
						}
						
						if (block.getMovingDistance().y < 0.f)
						{
							unit.moveHitboxes.addHitbox(Hitbox(sf::Vector2f(unit.maxLeftHitboxes(), unit.maxTopHitboxes()), sf::Vector2f(unit.sizeOfAllHitboxes().x + unit.getMovingDistance().x, block.getMovingDistance().y), sf::Vector2f(0.f, 0.f), sf::Color(48, 213, 200, 150)));
							unit.moveHitboxes.addHitbox(Hitbox(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f), sf::Color(48, 213, 200, 150)));

						}
						if (block.getMovingDistance().x > 0.f)
						{
							if (unit.getMovingDistance().x >= 0)
								unit.moveHitboxes.addHitbox(Hitbox(sf::Vector2f(unit.maxRightHitboxes() + unit.getMovingDistance().x, unit.maxTopHitboxes()), sf::Vector2f(block.getMovingDistance().x, unit.sizeOfAllHitboxes().y), sf::Vector2f(0.f, 0.f), sf::Color(48, 213, 200, 150)));
							else
								unit.moveHitboxes.addHitbox(Hitbox(sf::Vector2f(unit.maxRightHitboxes(), unit.maxTopHitboxes()), sf::Vector2f(block.getMovingDistance().x, unit.sizeOfAllHitboxes().y), sf::Vector2f(0.f, 0.f), sf::Color(48, 213, 200, 150)));

							unit.moveHitboxes.addHitbox(Hitbox(sf::Vector2f(unit.centerHitboxes().x, unit.maxTopHitboxes()), sf::Vector2f(unit.sizeOfAllHitboxes().x / 2.f, unit.sizeOfAllHitboxes().y), sf::Vector2f(0.f, 0.f), sf::Color(48, 213, 200, 150)));

						}
						if (block.getMovingDistance().x < 0.f)
						{
							if (unit.getMovingDistance().x <= 0)
								unit.moveHitboxes.addHitbox(Hitbox(sf::Vector2f(unit.maxLeftHitboxes() + unit.getMovingDistance().x, unit.maxTopHitboxes()), sf::Vector2f(block.getMovingDistance().x, unit.sizeOfAllHitboxes().y), sf::Vector2f(0.f, 0.f), sf::Color(48, 213, 200, 150)));
							else
								unit.moveHitboxes.addHitbox(Hitbox(sf::Vector2f(unit.maxLeftHitboxes(), unit.maxTopHitboxes()), sf::Vector2f(block.getMovingDistance().x, unit.sizeOfAllHitboxes().y), sf::Vector2f(0.f, 0.f), sf::Color(48, 213, 200, 150)));

							unit.moveHitboxes.addHitbox(Hitbox(sf::Vector2f(unit.centerHitboxes().x, unit.maxTopHitboxes()), sf::Vector2f(unit.sizeOfAllHitboxes().x / -2.f, unit.sizeOfAllHitboxes().y), sf::Vector2f(0.f, 0.f), sf::Color(48, 213, 200, 150)));

						}
						
						break;
					}
					else
					{
						if (unit.moveHitboxes.getHitboxes().size() == 4)
						{
							unit.moveHitboxes.hitboxes.pop_back();
							unit.moveHitboxes.hitboxes.pop_back();
						}
						if (!UnitTypeChecker::isMovable(unit.getType()))
						{
							if (unit.moveHitboxes.getHitboxes().size() == 2)
							{
								unit.moveHitboxes.hitboxes.pop_back();
								unit.moveHitboxes.hitboxes.pop_back();
							}
						}
					}
				}
			}
		}
	}
}

float LevelEditorState::calculateMaxMovingDistance(const LevelEditorUnit& movingUnit, const LevelEditorUnit& block)
{
	float maxDistance = 0.f;
	if (movingUnit.getMovingDistance().x > 0.f)
	{
		maxDistance = block.maxRightHitboxes() - movingUnit.maxRightHitboxes();
		if (maxDistance < 0.f)
			maxDistance = 0;
	}
	else
	{
		maxDistance = block.maxLeftHitboxes() - movingUnit.maxLeftHitboxes();
		if (maxDistance > 0.f)
			maxDistance = 0;
	}

	return maxDistance;
}
