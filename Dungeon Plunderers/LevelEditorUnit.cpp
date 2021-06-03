#include "pch.h"
#include "LevelEditorUnit.h"

LevelEditorUnit::LevelEditorUnit(const sf::Vector2f& Position, const ResourceHolder<LevelEditorUnitsNames, sf::Texture>& unitsTextures, const LevelEditorUnitsNames name, const sf::Vector2f& changeDirectionDistance, const sf::Vector2f& size)
	:name(name),
	placementIssue(UnitPlacementIssues::none),
	IsSetCorrectly(true)
{
	if (name != LevelEditorUnitsNames::player)
	{
		unit.setTexture(unitsTextures.getResource(name));
	}
	unit.setPosition(Position);
	if (UnitTypeChecker::isBlock(name))
	{
		unit.setTextureRect(sf::IntRect(unit.getTextureRect().left, unit.getTextureRect().top, size.x, size.y));
	}

	if (name == LevelEditorUnitsNames::player)
	{
		unit.setTextureRect(sf::IntRect(unit.getTextureRect().left, unit.getTextureRect().top, 117, 207));
	}
	setOriginDependingOnType();
	setHitboxesDependingOnType();
	setPositionOfHitboxes();	
	setMovingHitboxes(changeDirectionDistance);
}

LevelEditorUnit::LevelEditorUnit(const LevelEditorUnitData& unitData, const ResourceHolder<LevelEditorUnitsNames, sf::Texture>& unitsTextures)
	:LevelEditorUnit(unitData.position, unitsTextures, unitData.name, unitData.movingDistance, unitData.size)
{
}

LevelEditorUnit::~LevelEditorUnit()
{
}

sf::Vector2f LevelEditorUnit::getPositionOfUpperLeftCorner()
{
	return unit.getPosition() - unit.getOrigin();
}

const sf::FloatRect& LevelEditorUnit::getGlobalBounds() const
{
	return unit.getGlobalBounds();
}

void LevelEditorUnit::move(const sf::Vector2f& offset)
{
	unit.move(offset);
	hitboxComponent.moveAllHitboxes(offset);
	base.moveAllHitboxes(offset);
	moveHitboxes.moveAllHitboxes(offset);
	changeSizeHitboxes.moveAllHitboxes(offset);
	line.move(offset);
}

void LevelEditorUnit::setPositionRelativeToHitbox(const sf::Vector2f& Position)
{
	sf::Vector2f offset = Position - sf::Vector2f(hitboxComponent[0].getLeft(), hitboxComponent[0].getTop());
	hitboxComponent.setPositionOfHitbox(0, Position);
	unit.setPosition(Position - hitboxComponent.getHitboxes()[0].getOffset());
	setPositionOfHitboxes();
	moveHitboxes.moveAllHitboxes(offset);
	line.move(offset);
}

void LevelEditorUnit::setPosition(const sf::Vector2f& Position)
{
	sf::Vector2f offset = Position - unit.getPosition();
	unit.setPosition(Position);
	setPositionOfHitboxes();
	moveHitboxes.moveAllHitboxes(offset);
	line.move(offset);
}

void LevelEditorUnit::setTexture(const sf::Texture& texture)
{
	unit.setTexture(texture);
}

sf::Vector2f LevelEditorUnit::getPosition() const
{
	return unit.getPosition();
}

void LevelEditorUnit::setColor(const sf::Color& color)
{
	unit.setColor(color);
	line.setFillColor(color);
}

LevelEditorUnitsNames LevelEditorUnit::getType() const
{
	return name;
}

void LevelEditorUnit::addSize(const sf::Vector2i value)
{
	if (getSize().x + value.x >= 50.f and getSize().y + value.y >= 50.f)
	{
		sf::Vector2f movingDistance = getMovingDistance();
		unit.setTextureRect(sf::IntRect(unit.getTextureRect().left, unit.getTextureRect().top, unit.getTextureRect().width + value.x, unit.getTextureRect().height + value.y));
		setOriginDependingOnType();
		setHitboxesDependingOnType();
		setPositionOfHitboxes();
		setMovingHitboxes(movingDistance);
	}
}

void LevelEditorUnit::updateMoveDistance(const sf::Vector2f& offset)
{
	if (!moveHitboxes.getHitboxes().empty() and UnitTypeChecker::isMovable(name))
	{
		sf::Vector2f movingDistance = getMovingDistance();
		moveHitboxes.moveHitbox(0, offset);
		if (offset.x != 0)
		{
			if (movingDistance.x == 0.f)
			{
				if (offset.x > 0.f)
					moveHitboxes.setPositionOfHitbox(0, sf::Vector2f(maxRightHitboxes() + 100.f - moveHitboxes[0].getGlobalBounds().width, maxTopHitboxes()));
				else
				{
					moveHitboxes.setPositionOfHitbox(0, sf::Vector2f(maxLeftHitboxes(), maxTopHitboxes()));
				}
				WasMovingHitboxTeleported = true;
			}
			if (hitboxComponent.intersects(moveHitboxes[0].getGlobalBounds()))
			{

				if(offset.x > 0)
					moveHitboxes.setPositionOfHitbox(0, sf::Vector2f(maxRightHitboxes(), moveHitboxes[0].getTop()));
				else
				{
					moveHitboxes.setPositionOfHitbox(0, sf::Vector2f(maxLeftHitboxes() - 50.f, moveHitboxes[0].getTop()));
				}
				WasMovingHitboxTeleported = true;
			}

			moveHitboxes.setSizeOfHitbox(1, sf::Vector2f(moveHitboxes[0].getLeft() - maxLeftHitboxes(), sizeOfAllHitboxes().y));
			moveHitboxes.setPositionOfHitbox(1, sf::Vector2f(maxLeftHitboxes(), maxTopHitboxes()));
			moveHitboxes.setSizeOfHitbox(0, sf::Vector2f(50.f, sizeOfAllHitboxes().y));

			line.setPosition(sf::Vector2f(maxLeftHitboxes() + sizeOfAllHitboxes().x / 2, maxTopHitboxes() + sizeOfAllHitboxes().y / 2 - 2.5));
			line.setSize(sf::Vector2f(moveHitboxes[0].getCenter().x - line.getPosition().x, 5));

		}
		else
		{
			if (movingDistance.y == 0.f)
			{
				if (offset.y > 0.f)
					moveHitboxes.setPositionOfHitbox(0, sf::Vector2f(maxLeftHitboxes(), maxBottomHitboxes() + 100.f - moveHitboxes[0].getGlobalBounds().height));
				else
					moveHitboxes.setPositionOfHitbox(0, sf::Vector2f(maxLeftHitboxes(), maxTopHitboxes()));

				WasMovingHitboxTeleported = true;
			}
			if (hitboxComponent.intersects(moveHitboxes[0].getGlobalBounds()))
			{
				if (offset.y > 0)
					moveHitboxes.setPositionOfHitbox(0, sf::Vector2f(maxLeftHitboxes(), maxBottomHitboxes()));
				else
					moveHitboxes.setPositionOfHitbox(0, sf::Vector2f(maxLeftHitboxes(), maxTopHitboxes() - 50));

				WasMovingHitboxTeleported = true;
			}

			moveHitboxes.setSizeOfHitbox(0, sf::Vector2f(sizeOfAllHitboxes().x, 50.f));
			moveHitboxes.setSizeOfHitbox(1, sf::Vector2f(sizeOfAllHitboxes().x, moveHitboxes[0].getBottom() - maxTopHitboxes()));
			moveHitboxes.setPositionOfHitbox(1, sf::Vector2f(maxLeftHitboxes(), maxTopHitboxes()));

			line.setPosition(sf::Vector2f(maxLeftHitboxes() + sizeOfAllHitboxes().x / 2 - 2.5, maxTopHitboxes() + sizeOfAllHitboxes().y / 2));
			line.setSize(sf::Vector2f(5, moveHitboxes[0].getCenter().y - line.getPosition().y));
		}
	}
}

sf::Vector2f LevelEditorUnit::sizeOfAllHitboxes() const
{
	return sf::Vector2f(maxRightHitboxes() - maxLeftHitboxes(), maxBottomHitboxes() - maxTopHitboxes());
}

float LevelEditorUnit::maxLeftHitboxes() const
{
	return std::max_element(hitboxComponent.getHitboxes().begin(), hitboxComponent.getHitboxes().end(), [](const Hitbox& a, const Hitbox& b) {
		return a.getLeft() > b.getLeft();
		})->getLeft();
}

float LevelEditorUnit::maxRightHitboxes() const
{
	return std::max_element(hitboxComponent.getHitboxes().begin(), hitboxComponent.getHitboxes().end(), [](const Hitbox& a, const Hitbox& b) {
		return a.getRight() < b.getRight();
		})->getRight();
	return 100;
}

float LevelEditorUnit::maxTopHitboxes() const
{
	return std::max_element(hitboxComponent.getHitboxes().begin(), hitboxComponent.getHitboxes().end(), [](const Hitbox& a, const Hitbox& b) {
		return a.getTop() > b.getTop();
		})->getTop();
}

float LevelEditorUnit::maxBottomHitboxes() const
{
	return std::max_element(hitboxComponent.getHitboxes().begin(), hitboxComponent.getHitboxes().end(), [](const Hitbox& a, const Hitbox& b) {
		return a.getBottom() < b.getBottom();
		})->getBottom();
}

sf::Vector2f LevelEditorUnit::centerHitboxes() const
{
	return sf::Vector2f(maxLeftHitboxes() + sizeOfAllHitboxes().x / 2.f, maxTopHitboxes() + sizeOfAllHitboxes().y / 2.f);
}

sf::Vector2f LevelEditorUnit::getMovingDistance() const
{
	if (!moveHitboxes.getHitboxes().empty() and UnitTypeChecker::isMovable(name))
	{
		if (moveHitboxes[0].getCenter().x > centerHitboxes().x and moveHitboxes[0].getTop() == maxTopHitboxes()) //moving right
			return sf::Vector2f(moveHitboxes[0].getRight() - maxRightHitboxes(), 0.f);
		else if(moveHitboxes[0].getCenter().x < centerHitboxes().x and moveHitboxes[0].getTop() == maxTopHitboxes())//moving left
			return sf::Vector2f(moveHitboxes[0].getLeft() - maxLeftHitboxes(), 0.f);
		else if (moveHitboxes[0].getCenter().y > centerHitboxes().y and moveHitboxes[0].getLeft() == maxLeftHitboxes()) //moving down
			return sf::Vector2f(0.f, moveHitboxes[0].getBottom() - maxBottomHitboxes());
		else //moving up
			return sf::Vector2f(0.f, moveHitboxes[0].getTop() - maxTopHitboxes());
	}

	return sf::Vector2f(0.f, 0.f);
}

void LevelEditorUnit::isSetCorrectly(bool isSetCorrectly)
{
	if (isSetCorrectly)
	{
		IsSetCorrectly = true;
		setColor(sf::Color::White);
	}
	else
	{
		IsSetCorrectly = false;
		setColor(sf::Color::Red);
	}
}

UnitPlacementIssues LevelEditorUnit::getPlacementIssue() const
{
	return placementIssue;
}

void LevelEditorUnit::setPlacementIssue(const UnitPlacementIssues& issue)
{
	placementIssue = issue;
}


sf::Vector2f LevelEditorUnit::getSize() const
{
	return sf::Vector2f(unit.getGlobalBounds().width, unit.getGlobalBounds().height);
}

void LevelEditorUnit::initTypesOfUnit(LevelEditorUnitsNames name)
{

}

sf::Vector2f LevelEditorUnit::getUpperLeftCorner() const
{
	return sf::Vector2f(unit.getGlobalBounds().left, unit.getGlobalBounds().top);
}

void LevelEditorUnit::setPositionOfHitboxes()
{
	for (int i = 0; i < hitboxComponent.getHitboxes().size(); i++)
	{
		hitboxComponent.setPositionOfHitbox(i, unit.getPosition() + hitboxComponent.getHitboxes()[i].getOffset());
	}
	for (int i = 0; i < base.getHitboxes().size(); i++)
	{
		base.setPositionOfHitbox(i, unit.getPosition() + base.getHitboxes()[i].getOffset());
	}	
	for (int i = 0; i < changeSizeHitboxes.getHitboxes().size(); i++)
	{
		changeSizeHitboxes.setPositionOfHitbox(i, unit.getPosition() + changeSizeHitboxes.getHitboxes()[i].getOffset());
	}
}

void LevelEditorUnit::setOriginDependingOnType()
{
	switch (name)
	{
	case LevelEditorUnitsNames::brick:
	case LevelEditorUnitsNames::coin:
	case LevelEditorUnitsNames::dirt:
	case LevelEditorUnitsNames::concrete:
	case LevelEditorUnitsNames::granite:
	case LevelEditorUnitsNames::movingConcrete:
	case LevelEditorUnitsNames::movingBrick:
	case LevelEditorUnitsNames::movingDirt:
	case LevelEditorUnitsNames::movingGranite:
		unit.setOrigin(getSize() / 2.f);
		break;
	case LevelEditorUnitsNames::deadlyFlower:
		unit.setOrigin(103.f, 0.f);
		break;
	case LevelEditorUnitsNames::zombie:
		unit.setOrigin(46.f, 0.f);
		break;	
	case LevelEditorUnitsNames::skeleton:
		unit.setOrigin(45.f, 0.f);
		break;
	case LevelEditorUnitsNames::fly:
		unit.setOrigin(38.f, 0.f);
		break;
	case LevelEditorUnitsNames::player:
		unit.setOrigin(62, 0);
		break;	
	case LevelEditorUnitsNames::gunEnemy:
	case LevelEditorUnitsNames::gunEnemyOnFakeBlock:
	case LevelEditorUnitsNames::movingGunEnemyOnFakeBlock:
		unit.setOrigin(100, 100);
		break;
	case LevelEditorUnitsNames::showingAfterDamageSpikes:
	case LevelEditorUnitsNames::spikes:
	case LevelEditorUnitsNames::hidingSpikes:
		unit.setOrigin(0, 0);
		break;
	default:
		break;
	}
}


void LevelEditorUnit::setHitboxesDependingOnType()
{
	hitboxComponent.clearHitboxes();
	base.clearHitboxes();
	changeSizeHitboxes.clearHitboxes();
	sf::Vector2f sizeOfHitbox(15.f, 15.f);
	sf::Vector2f offset;
	switch (name)
	{
	case LevelEditorUnitsNames::brick:
	case LevelEditorUnitsNames::dirt:
	case LevelEditorUnitsNames::concrete:
	case LevelEditorUnitsNames::granite:
	case LevelEditorUnitsNames::movingBrick:
	case LevelEditorUnitsNames::movingDirt:
	case LevelEditorUnitsNames::movingConcrete:
	case LevelEditorUnitsNames::movingGranite:
		hitboxComponent.addHitbox(Hitbox(getUpperLeftCorner(), getSize(), getSize() / -2.f));

		offset = sf::Vector2f(-getSize().x / 2, -sizeOfHitbox.y / 2);//left
		changeSizeHitboxes.addHitbox(Hitbox(offset, sizeOfHitbox, offset, sf::Color(255, 0, 0, 255)));
		offset = sf::Vector2f(getSize().x / 2 -sizeOfHitbox.y, -sizeOfHitbox.y / 2);//right
		changeSizeHitboxes.addHitbox(Hitbox(offset, sizeOfHitbox, offset, sf::Color(255, 0, 0, 255)));
		offset = sf::Vector2f(-sizeOfHitbox.x / 2, -getSize().y / 2);//top
		changeSizeHitboxes.addHitbox(Hitbox(offset, sizeOfHitbox, offset, sf::Color(255, 0, 0, 255)));
		offset = sf::Vector2f(-sizeOfHitbox.x / 2, getSize().y / 2 - sizeOfHitbox.y);//bottom
		changeSizeHitboxes.addHitbox(Hitbox(offset, sizeOfHitbox, offset, sf::Color(255, 0, 0, 255)));

		offset = sf::Vector2f(-getSize() / 2.f);//top left
		changeSizeHitboxes.addHitbox(Hitbox(offset, sizeOfHitbox, offset, sf::Color(255, 0, 0, 255)));
		offset = sf::Vector2f(-getSize().x / 2, getSize().y / 2 - sizeOfHitbox.y);//bottom left
		changeSizeHitboxes.addHitbox(Hitbox(offset, sizeOfHitbox, offset, sf::Color(255, 0, 0, 255)));

		offset = sf::Vector2f(getSize().x / 2 - sizeOfHitbox.y, -getSize().y / 2);//top right
		changeSizeHitboxes.addHitbox(Hitbox(offset, sizeOfHitbox, offset, sf::Color(255, 0, 0, 255)));
		offset = sf::Vector2f(getSize().x / 2 - sizeOfHitbox.y, getSize().y / 2 - sizeOfHitbox.y);//bottom right
		changeSizeHitboxes.addHitbox(Hitbox(offset, sizeOfHitbox, offset, sf::Color(255, 0, 0, 255)));
		
		break;
	case LevelEditorUnitsNames::deadlyFlower:
		hitboxComponent.addHitbox(Hitbox(getUpperLeftCorner(), sf::Vector2f(50, 50), sf::Vector2f(-25.f, 156.f)));
		hitboxComponent.addHitbox(Hitbox(getUpperLeftCorner(), sf::Vector2f(200, 100), sf::Vector2f(-100.f, 6.f)));
		hitboxComponent.addHitbox(Hitbox(getUpperLeftCorner(), sf::Vector2f(27, 60), sf::Vector2f(-13.5f, 100.f)));
		base.addHitbox(Hitbox(getUpperLeftCorner(), sf::Vector2f(20, 2), sf::Vector2f(-25.f, 208.f), sf::Color(255, 0, 0, 100)));
		base.addHitbox(Hitbox(getUpperLeftCorner(), sf::Vector2f(46, 2), sf::Vector2f(-23.f, 208.f), sf::Color(0, 255, 0, 100)));
		base.addHitbox(Hitbox(getUpperLeftCorner(), sf::Vector2f(20, 2), sf::Vector2f(5.f, 208.f), sf::Color(0, 0, 255, 100)));
		break;
	case LevelEditorUnitsNames::coin:
		hitboxComponent.addHitbox(Hitbox(getUpperLeftCorner(), getSize(), getSize() / -2.f));
		base.addHitbox(Hitbox(getUpperLeftCorner(), sf::Vector2f(20, 2), sf::Vector2f(0.f - 25.f, getSize().y / 2 + 2.f)));
		base.addHitbox(Hitbox(getUpperLeftCorner(), sf::Vector2f(20, 2), sf::Vector2f(15.f - 25.f, getSize().y / 2 + 2.f)));
		base.addHitbox(Hitbox(getUpperLeftCorner(), sf::Vector2f(20, 2), sf::Vector2f(30.f - 25.f, getSize().y / 2 + 2.f)));
		break;
	case LevelEditorUnitsNames::skeleton:
		hitboxComponent.addHitbox(Hitbox(getUpperLeftCorner(), sf::Vector2f(70.2126f, 200.f), sf::Vector2f(-28.9539f, 0)));
		hitboxComponent.addHitbox(Hitbox(getUpperLeftCorner(), sf::Vector2f(54.3583f, 40.0137f), sf::Vector2f(40.1263f, 50.6356f)));
		hitboxComponent.addHitbox(Hitbox(getUpperLeftCorner(), sf::Vector2f(17.542f, 46.0535f), sf::Vector2f(-45.1858f, 61.5827f)));
		base.addHitbox(Hitbox(getUpperLeftCorner(), sf::Vector2f(7, 4), sf::Vector2f(-13.9254f, 199.97f), sf::Color(255, 0, 0, 100)));
		base.addHitbox(Hitbox(getUpperLeftCorner(), sf::Vector2f(54.0173f, 4), sf::Vector2f(-12.9769f, 199.982f), sf::Color(0, 255, 0, 100)));
		base.addHitbox(Hitbox(getUpperLeftCorner(), sf::Vector2f(10.965576f, 4), sf::Vector2f(30.9761f, 199.91f), sf::Color(0, 0, 255, 100)));
		break;
	case LevelEditorUnitsNames::fly:
		hitboxComponent.addHitbox(Hitbox(getUpperLeftCorner(), sf::Vector2f(70.f, 57.9338f), sf::Vector2f(-31.206f, -0.292297f)));
		base.addHitbox(Hitbox(getUpperLeftCorner(), sf::Vector2f(7, 4), sf::Vector2f(0 - 31.206f, 98), sf::Color(255, 0, 0, 100)));
		base.addHitbox(Hitbox(getUpperLeftCorner(), sf::Vector2f(56, 4), sf::Vector2f(7 - 31.206f, 98), sf::Color(0, 255, 0, 100)));
		base.addHitbox(Hitbox(getUpperLeftCorner(), sf::Vector2f(7, 4), sf::Vector2f(63 - 31.206f, 98), sf::Color(0, 0, 255, 100)));
	break;
	case LevelEditorUnitsNames::zombie:
		hitboxComponent.addHitbox(Hitbox(getUpperLeftCorner(), sf::Vector2f(36.5503f, 50.f), sf::Vector2f(-16.0823f, 133.761f)));
		hitboxComponent.addHitbox(Hitbox(getUpperLeftCorner(), sf::Vector2f(75.8718f, 146.202f), sf::Vector2f(-44.0322f, -0.476501f)));
		hitboxComponent.addHitbox(Hitbox(getUpperLeftCorner(), sf::Vector2f(44.2454f, 16.5439f), sf::Vector2f(32.4675f, 69.539f)));
		base.addHitbox(Hitbox(getUpperLeftCorner(), sf::Vector2f(6.17529f, 1.582f), sf::Vector2f(-13.9492f, 183.989f), sf::Color(255, 0, 0, 100)));
		base.addHitbox(Hitbox(getUpperLeftCorner(), sf::Vector2f(30.1931f, 1.62155f), sf::Vector2f(-11.7739f, 183.949f), sf::Color(0, 255, 0, 100)));
		base.addHitbox(Hitbox(getUpperLeftCorner(), sf::Vector2f(7.58203f, 1.62155f), sf::Vector2f(11.3796f, 183.949f), sf::Color(0, 0, 255, 100)));
		break;

	case LevelEditorUnitsNames::player:
		hitboxComponent.addHitbox(Hitbox(sf::Vector2f(-45.f, 7.f), sf::Vector2f(90, 200), sf::Vector2f(-45.f, 7.f)));
	break;
	case LevelEditorUnitsNames::gunEnemy:
		hitboxComponent.addHitbox(Hitbox(getUpperLeftCorner() + sf::Vector2f(-28.f, -28.f), sf::Vector2f(56.f, 56.f), sf::Vector2f(-28.f, -28.f)));
		hitboxComponent.addHitbox(Hitbox(getUpperLeftCorner() + sf::Vector2f(-100.f, -12.f), sf::Vector2f(200.f, 24.f), sf::Vector2f(-100.f, -12.f)));
		hitboxComponent.addHitbox(Hitbox(getUpperLeftCorner() + sf::Vector2f(-12.f, -100.f), sf::Vector2f(24.f, 200.f), sf::Vector2f(-12.f, -100.f)));
		base.addHitbox(Hitbox(getUpperLeftCorner() + sf::Vector2f(-28.f, -28.f), sf::Vector2f(1.f, 56.f), sf::Vector2f(-28.f, -28.f)));
		base.addHitbox(Hitbox(getUpperLeftCorner() + sf::Vector2f(-28.f, -28.f), sf::Vector2f(56.f, 1.f), sf::Vector2f(-28.f, -28.f)));
		base.addHitbox(Hitbox(getUpperLeftCorner() + sf::Vector2f(27.f, -28.f), sf::Vector2f(1.f, 56.f), sf::Vector2f(27.f, -28.f)));
		base.addHitbox(Hitbox(getUpperLeftCorner() + sf::Vector2f(-28.f, 27.f), sf::Vector2f(56.f, 1.f), sf::Vector2f(-28.f, 27.f)));
		break;
	case LevelEditorUnitsNames::gunEnemyOnFakeBlock:
	case LevelEditorUnitsNames::movingGunEnemyOnFakeBlock:
		hitboxComponent.addHitbox(Hitbox(getUpperLeftCorner() + sf::Vector2f(-28.f, -28.f), sf::Vector2f(100.f, 100.f), sf::Vector2f(-50.f, -50.f)));
		hitboxComponent.addHitbox(Hitbox(getUpperLeftCorner() + sf::Vector2f(-100.f, -12.f), sf::Vector2f(200.f, 24.f), sf::Vector2f(-100.f, -12.f)));
		hitboxComponent.addHitbox(Hitbox(getUpperLeftCorner() + sf::Vector2f(-12.f, -100.f), sf::Vector2f(24.f, 200.f), sf::Vector2f(-12.f, -100.f)));
		break;

	case LevelEditorUnitsNames::showingAfterDamageSpikes:
	case LevelEditorUnitsNames::spikes:
	case LevelEditorUnitsNames::hidingSpikes:
		hitboxComponent.addHitbox(Hitbox(getUpperLeftCorner(), sf::Vector2f(50, 50), sf::Vector2f(0, 0)));
		base.addHitbox(Hitbox(getUpperLeftCorner(), sf::Vector2f(15, 2), sf::Vector2f(0.f, 52.f)));
		base.addHitbox(Hitbox(getUpperLeftCorner(), sf::Vector2f(20, 2), sf::Vector2f(15.f, 52.f)));
		base.addHitbox(Hitbox(getUpperLeftCorner(), sf::Vector2f(15, 2), sf::Vector2f(35.f, 52.f)));
		break;
	default:
		break;
	}
}

void LevelEditorUnit::setMovingHitboxes(const sf::Vector2f& initialChangeDirectionDistance)
{	
	if (UnitTypeChecker::isMovable(name))
	{
		hasLine = true;
		moveHitboxes.clearHitboxes();
		if (initialChangeDirectionDistance.x > 0)
			moveHitboxes.addHitbox(Hitbox(sf::Vector2f(maxRightHitboxes() + initialChangeDirectionDistance.x - 50.f, maxTopHitboxes()), sf::Vector2f(50.f, sizeOfAllHitboxes().y)));
		else if(initialChangeDirectionDistance.x < 0)
			moveHitboxes.addHitbox(Hitbox(sf::Vector2f(maxLeftHitboxes() + initialChangeDirectionDistance.x, maxTopHitboxes()), sf::Vector2f(50.f, sizeOfAllHitboxes().y)));
		else if (initialChangeDirectionDistance.y > 0)
			moveHitboxes.addHitbox(Hitbox(sf::Vector2f(maxLeftHitboxes(), maxBottomHitboxes() + initialChangeDirectionDistance.y - 50.f), sf::Vector2f(sizeOfAllHitboxes().x, 50.f)));
		else if(initialChangeDirectionDistance.y < 0)
			moveHitboxes.addHitbox(Hitbox(sf::Vector2f(maxLeftHitboxes(), maxTopHitboxes() + initialChangeDirectionDistance.y), sf::Vector2f(sizeOfAllHitboxes().x, 50.f)));

		if (initialChangeDirectionDistance.y == 0)
		{
			moveHitboxes.addHitbox(Hitbox(sf::Vector2f(maxLeftHitboxes(), maxTopHitboxes()), sf::Vector2f(moveHitboxes[0].getLeft() - maxLeftHitboxes(), sizeOfAllHitboxes().y), sf::Vector2f(0.f, 0.f), sf::Color(255.f, 0.f, 0.f, 0.f)));
			line.setPosition(sf::Vector2f(maxLeftHitboxes() + sizeOfAllHitboxes().x / 2, maxTopHitboxes() + sizeOfAllHitboxes().y / 2 - 2.5f));
			line.setSize(sf::Vector2f(moveHitboxes[0].getCenter().x - line.getPosition().x, 5));
			line.setFillColor(sf::Color::Red);
		}
		else if(initialChangeDirectionDistance.x == 0)
		{
			moveHitboxes.addHitbox(Hitbox(sf::Vector2f(maxLeftHitboxes(), maxTopHitboxes()), sf::Vector2f(sizeOfAllHitboxes().x, moveHitboxes[0].getTop() - maxTopHitboxes()), sf::Vector2f(0.f, 0.f), sf::Color(255.f, 0.f, 0.f, 0.f)));
			line.setPosition(sf::Vector2f(maxLeftHitboxes() + sizeOfAllHitboxes().x / 2, maxTopHitboxes() + sizeOfAllHitboxes().y / 2 - 2.5f));
			line.setSize(sf::Vector2f(5, moveHitboxes[0].getCenter().y - line.getPosition().y - 2.5f));
			line.setFillColor(sf::Color::Red);
		}
	}
}

void LevelEditorUnit::drawMoveHitboxes(sf::RenderTarget& target) const
{
	if (UnitTypeChecker::isMovable(name))
	{
		target.draw(moveHitboxes[0]);
	}
}

void LevelEditorUnit::drawBlueHitboxes(sf::RenderTarget& target) const
{
	if (UnitTypeChecker::isMovable(name))
	{
		if (moveHitboxes.hitboxes.size() > 2)
			target.draw(moveHitboxes[2]);
	}
	else
	{
		if (!moveHitboxes.hitboxes.empty())
			target.draw(moveHitboxes[0]);
	}
}

void LevelEditorUnit::drawLines(sf::RenderTarget& target) const
{
	if(hasLine)
		target.draw(line);
}

void LevelEditorUnit::drawChangeSizeHitboxes(sf::RenderTarget& target) const
{
	for (auto const& i : changeSizeHitboxes.getHitboxes())
	{
		target.draw(i);
	}
}

bool LevelEditorUnit::wasMovingHitboxTeleported() const
{
	return WasMovingHitboxTeleported;
}

bool LevelEditorUnit::setMovingHitboxWasTeleported(const bool wasMovingHitboxTeleported)
{
	return WasMovingHitboxTeleported = wasMovingHitboxTeleported;
}

void LevelEditorUnit::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(unit, states);
}
