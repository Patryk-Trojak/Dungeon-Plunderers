#pragma once
#include "State.h"
#include "Enemy.h"
#include "Block.h"
#include "Coin.h"
#include "LevelEditorToolbar.h"
#include "LevelEditorUpgradeClassState.h"
#include "LevelEditorUnit.h"
#include "DeadlyFlower.h"
#include "GameplayState.h"
#include "Feedback.h"
#include "Zombie.h"
#include "Fly.h"
#include "Skeleton.h"
#include "Spikes.h"
#include "GunEnemy.h"
#include <algorithm>
#include <cmath>
#include <functional>
#include "LevelEditorClipboard.h"
#include "LevelEditorUnitsChangeTracker.h"
#include "UnitTypeChecker.h"
#include "SlimeEnemy.h"
#include "ZombieInGround.h"
#include "Ghost.h"
#include "Bat.h"
#include "SpinningSpikes.h"

enum class Action {
	none, 
	addingUnit,
	movingUnit,
	changinSizeOfUnit,
	changingMovingDistance,
	creatingSelectedArea
};

class LevelEditorState
	: public State
{
public:
	LevelEditorState(StateData& stateData, const std::string& filepath);

	virtual ~LevelEditorState();
	virtual void update(const float deltaTime) override;
	virtual void handleSFMLEvent(sf::RenderWindow& window, sf::Event& event) override;
	virtual void updateInput(const float deltaTime) override;
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	std::vector<LevelEditorUnit> units;
	LevelEditorUnitsNames currentUnitType;
	int numberOfSelectedUnits;
	bool wasLeftMouseReleased;

	ResourceHolder<LevelEditorUnitsNames, sf::Texture> unitsTextures;
	ResourceHolder<LevelEditorUnitsNames, sf::Texture> loadAllUnitsTextures();

	LevelEditorToolbar toolbar;
	void handleFunctionalityToolbarButtons();
	Action currentAction;

	void loadUnitsFromFile();
	void saveUnitsToFile();
	void createCode();
	std::string filepath;
	std::string dateOfLastRun;
	std::string dateOfCreation;
	PlayerData guineaPig;

	sf::Vector2f lastMousePosition;
	sf::Vector2f MouseShift;
	sf::Vector2f UnitShift;
	bool wasUsedMouseSetPos;
	int tileSize;

	sf::Vector2f lastMousePositionRelativeToHUDView;
	sf::Vector2f MouseShiftRelativeToHUDView;

	sf::Vector2f lastViewPosition{ 0, 0 };
	bool isMouseOverUnits() const;
	bool isMouseOverBlocks() const;
	bool isMouseOverEnemyGuns() const;
	std::vector<LevelEditorUnit>::iterator findPlayerInUnits();
	void tryAddPlayerToUnits();

	std::vector<LevelEditorUnit>::iterator findPortalInUnits();
	void tryAddPortalToUnits();
	//Adding Units
	void addUnitByClick();
	void addBlocksByCreatedArea();
	void handleAddingUnits();
	bool isAbleToAddUnit();

	//Moving Units
	void handleMovingUnits();
	void tryStartMovingUnits();
	void tryMoveSelectedUnits();

	//Changing Moving Distance Of Units
	void handleChangingMovingDistance(const sf::RenderWindow& window);
	void tryStartChangingMovingDistance();
	void tryChangeMovingDistance(const sf::RenderWindow& window);

	//Changing size of blocks
	void handleChangingSizeOfBlocks();
	void tryStartChangingSizeOfBlocks();
	void tryChangeSizeOfBlocks();
	int numberOfHitboxChangingSize;

	void drawUnits(sf::RenderTarget& target, sf::RenderStates states) const;
	void updatePositionIfUnitsColliding();
	void markIfSelectedUnitIsSetIncorrecly();
	bool isGroundUnitOnBlock(const LevelEditorUnit& groundUnit, const LevelEditorUnit& block) const;
	void setMovingDistanceWhenUnitIsOnBlock();
	void setHitboxesWhenUnitIsSetOnMovingBlock();
	float calculateMaxMovingDistance(const LevelEditorUnit& movingUnit, const LevelEditorUnit& block);
	void setPositionsOfUnitsHitboxes(const std::vector<sf::Vector2f>& positionsOfUnitsHitboxes, const std::vector<sf::Vector2f>& positionsOfUnitsMoveHitboxes);
	std::vector<LevelEditorUnit>::reverse_iterator findCollidingSelectedUnit();
	bool isCollidingWithNoSelectedUnits(const std::vector<std::tuple<sf::FloatRect, sf::Vector2f, LevelEditorUnitsNames>>& unitsHitboxes, 
		const std::vector<std::tuple<sf::FloatRect, sf::Vector2f, LevelEditorUnitsNames>>& unitsMoveHitboxes) const;
	void roundPositionsOfUnits();
	
	std::unique_ptr<sf::Texture> loadTexture(const std::string& filepath, const sf::IntRect& area = sf::IntRect(), const bool isRepeated = false);
	
	//coping
	LevelEditorClipboard clipboard;
	LevelEditorUnitsChangeTracker changeTracker;
	void handleSelectingUnitsByClick();

	//Background
	std::array<sf::Sprite, 2> backgrounds;
	void updatePositionsOfBackgrounds(std::array<sf::Sprite, 2>& backgrounds);
	void drawBackgrounds(sf::RenderTarget& target, sf::RenderStates states) const;
	float rightOfView;
	float leftOfView;

	void updatePositionOfView(const float deltaTime);
	void handleZoomingView(float deltaTime);
	//helplines
	sf::Texture textureOfHelpLines50x50;
	std::array<sf::Sprite, 2> helpLines;
	void drawHelpLines(sf::RenderTarget& target, sf::RenderStates states) const; 
	void updateTransparentOfHelpLines();

	void updateColorOfUnits();

	//
	std::unique_ptr<sf::RectangleShape> selectedArea;
	std::unique_ptr<sf::RectangleShape> createBlockArea;
	void createArea(std::unique_ptr<sf::RectangleShape>& area, const sf::Color& colorOfArea);
	void updateArea(std::unique_ptr<sf::RectangleShape>& area);
	void selectUnitsBySelectedArea();
	
	void deleteSelectedUnits();
	std::function<Level(const Resources& resources)> convertUnitsToLevel;
	void initFunctionConvertUnitsToLevel();
	sf::Text messageOfIssues;
	void updateMessageOfIssues();
	void initMessageOfIssues();
	std::unique_ptr<Feedback> feedback;
	Slider sliderOfView;
	void setSliderOfView();

	float computeMinPositionXOfUnit();
	float computeMaxPositionXOfUnit();

	void updateAfterChanges();
	void handleKeyboardShortcuts(sf::Keyboard::Key codeOfPressedKey);
};
