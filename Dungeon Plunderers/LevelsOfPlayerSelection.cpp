#include "pch.h"
#include "LevelsOfPlayerSelection.h"

LevelsOfPlayerSelection::LevelsOfPlayerSelection(StateData& stateData, const bool moveToCreatorAfterSelected)
	:FileSelection(stateData, "\\Levels"),
	moveToCreatorAfterSelected(moveToCreatorAfterSelected)
{
	std::ifstream file;
	std::string temp;
	for (auto& i : saveButtons)
	{
		file.open(makeFilePathByNameOfSaveButton(i->getName()));
		file >> temp;
		i->setDateOfLastRun(temp);
		file >> temp;
		i->setDateOfCreation(temp);
		file.close();
	}
}

LevelsOfPlayerSelection::~LevelsOfPlayerSelection()
{
}

void LevelsOfPlayerSelection::handleInfoAboutCurrentSave()
{
}


void LevelsOfPlayerSelection::createSaveFile(const std::string& fileName)
{
	DefaultPersistenceCreator::createNewPlayerLevelSave(fileName);
}

void LevelsOfPlayerSelection::loadFile(const std::string& filepath)
{
	currentFilepath = filepath;
	if (!moveToCreatorAfterSelected)
	{
		loadUnitsFromFile(filepath);
	}
}

void LevelsOfPlayerSelection::moveToNextState(SaveButton& clicked)
{
	wasMousePressed = false;
	PersistenceSaver::saveDateOfLastRunToPlayerLevelFile(clicked.getName(), Date::getCurrentDate());
	clicked.setDateOfLastRun(Date::getCurrentDate());
	if (moveToCreatorAfterSelected)
		stateData.states.push(std::make_unique<LevelEditorState>(stateData, makeFilePathByNameOfSaveButton(clicked.getName())));
	else
	{
		initFunctionConvertUnitsToLevel();
		stateData.states.push(std::make_unique<GameplayState>(stateData, convertUnitsToLevel));
	}
}

void LevelsOfPlayerSelection::initFunctionConvertUnitsToLevel()
{
	const std::vector<LevelEditorUnit>& levelEditorUnits = units;
	convertUnitsToLevel = [&levelEditorUnits](const Resources& resources)
	{
		Level level;
		level.endOfLevelPosition = sf::Vector2f(200.f, 200.f);
		for (auto const& i : levelEditorUnits)
		{
			switch (i.getType())
			{
			case LevelEditorUnitsNames::player:
				level.initialPositionOfPlayer = i.getPosition();
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
				level.enemies.emplace_back(std::make_unique<SpinningSpikes>(i.getPosition(), sf::Vector2f(0.f, 0.f), resources));
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
			}
		}
		return level;
	};

}

void LevelsOfPlayerSelection::loadUnitsFromFile(const std::string& filepath)
{
	std::ifstream file;
	file.open(filepath);
	sf::Vector2f position;
	sf::Vector2f movingDistance(100.f, 0.f);
	sf::Vector2f size(50.f, 50.f);
	LevelEditorUnitsNames name;
	int tempType;
	int useless;
	units.reserve(1000);
	if (file.is_open())
	{
		file >> useless;
		file >> useless;

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

			units.emplace_back(position, ResourceHolder<LevelEditorUnitsNames, sf::Texture>(), name, movingDistance, size);

			movingDistance = sf::Vector2f(100.f, 0.f);
			size = sf::Vector2f(50.f, 50.f);
		}
		file.close();
	}
}
