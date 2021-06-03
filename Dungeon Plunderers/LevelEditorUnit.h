#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include"HitboxComponent.h"
#include"ResourceHolder.h"
#include"LevelEditorUnitsNames.h"
#include"UnitTypeChecker.h"

enum class UnitPlacementIssues {
	none = 0,
	NotOnBlock,
	NotPlaceToMove
};

struct LevelEditorUnitData
{
	LevelEditorUnitData(LevelEditorUnitsNames name, sf::Vector2f position, sf::Vector2f movingDistance, sf::Vector2f size)
		:name(name), position(position), movingDistance(movingDistance), size(size) {};
	LevelEditorUnitsNames name;
	sf::Vector2f position;
	sf::Vector2f movingDistance;
	sf::Vector2f size;
};

class LevelEditorUnit
	:public sf::Drawable
{
public:
	LevelEditorUnit(const sf::Vector2f& Position, const ResourceHolder<LevelEditorUnitsNames, sf::Texture>& unitsTextures, const LevelEditorUnitsNames name, const sf::Vector2f& changeDirectionDistance = sf::Vector2f(100.f, 0.f), const sf::Vector2f& size = sf::Vector2f(50.f, 50.f));
	LevelEditorUnit(const LevelEditorUnitData& unitData, const ResourceHolder<LevelEditorUnitsNames, sf::Texture>& unitsTextures);
	virtual ~LevelEditorUnit();
	HitboxComponent hitboxComponent;
	HitboxComponent base;
	HitboxComponent changeSizeHitboxes;

	sf::Vector2f getPositionOfUpperLeftCorner();
	const sf::FloatRect& getGlobalBounds() const;
	void move(const sf::Vector2f& offset);
	void setPositionRelativeToHitbox(const sf::Vector2f& Position);
	void setPosition(const sf::Vector2f& Position);
	void setTexture(const sf::Texture& texture);
	sf::Vector2f getPosition() const;
	void setColor(const sf::Color& color);
	LevelEditorUnitsNames getType() const;
	void addSize(const sf::Vector2i value);
	sf::Vector2f sizeOfAllHitboxes() const;
	float maxLeftHitboxes() const;
	float maxRightHitboxes() const;	
	float maxTopHitboxes() const;
	float maxBottomHitboxes() const;
	sf::Vector2f centerHitboxes() const;

	sf::Vector2f getMovingDistance() const;

	void isSetCorrectly(bool isSetCorrectly);
	UnitPlacementIssues getPlacementIssue() const;
	void setPlacementIssue(const UnitPlacementIssues& issue);
	void drawBlueHitboxes(sf::RenderTarget& target) const;
	void drawChangeSizeHitboxes(sf::RenderTarget& target) const;
	sf::Vector2f getSize() const;

	//only moving
	HitboxComponent moveHitboxes;
	void setMovingHitboxes(const sf::Vector2f& movingDistance);
	void drawLines(sf::RenderTarget& target) const;
	bool wasMovingHitboxTeleported() const;
	bool setMovingHitboxWasTeleported(const bool wasMovingHitboxTeleported);
	void drawMoveHitboxes(sf::RenderTarget& target) const;
	sf::RectangleShape line;
	bool hasLine{ false };	
	void updateMoveDistance(const sf::Vector2f& offset);

private:
	sf::Sprite unit;
	LevelEditorUnitsNames name;
	UnitPlacementIssues placementIssue;
	std::array<bool, 6> types;
	void initTypesOfUnit(LevelEditorUnitsNames name);
	sf::Vector2f getUpperLeftCorner() const;
	void setPositionOfHitboxes();
	bool WasMovingHitboxTeleported{ false };

	void setOriginDependingOnType();
	void setHitboxesDependingOnType();
	bool IsSetCorrectly;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

