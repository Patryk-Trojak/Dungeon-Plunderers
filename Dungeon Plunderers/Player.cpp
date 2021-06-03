#include "pch.h"
#include "Player.h"

Player::Player(const sf::Vector2f& Position, const sf::Texture& TextureOfPlayer, const Keybinds& keybinds)
	:Movable(sf::Vector2f(800, 3000)),
	keybinds(keybinds),
	currentHp(100),
	initialHp(100)
{
	player.setPosition(Position);
	player.setTexture(TextureOfPlayer);
}

Player::~Player()
{
}

void Player::update(const sf::Vector2f& MousePosition)
{	
	setCurrentWeapon();
	setRotationOfArm(MousePosition);
	setScaleOfPlayer(MousePosition);
	handleDrinkingPotions();
	currentWeapon->setRotation(arm.getRotation());
	currentWeapon->setScale(sf::Vector2f(currentWeapon->getInitialScale().x * arm.getScale().x, currentWeapon->getInitialScale().y * arm.getScale().y));
	calculateGlobalBoundsOfSprite();
}

void Player::attack(std::vector< std::unique_ptr< PlayerProjectile > >& Projectile, const sf::Vector2f& mousePosition)
{
	if (keybinds.isPressed(KeybindID::Attack))
	{
		currentWeapon->attack(Projectile, mousePosition);
	}
}

void Player::animateWeapon(float deltaTime)
{
	currentWeapon->animate(deltaTime);
}

void Player::move(const float deltaTime)
{
	player.move(currentVelocity * deltaTime);
	setPositionOfArm();
	setPositionOfWeapon();
	matchHitboxesToAnimation();
	setPositionOfHitboxes();
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(player, states);
	target.draw(*currentWeapon, states);
	target.draw(arm, states);
	//target.draw(globalBoundsOfHitboxes, states);
	//for(auto const &i : hitboxComponent.getHitboxes())
		//target.draw(i, states);
}


void Player::setPosition(const sf::Vector2f& Position)
{
	player.setPosition(Position.x, Position.y);
	setPositionOfArm();
	setPositionOfWeapon();
	setPositionOfHitboxes();
}

void Player::setPositionRelativeToHitbox(const sf::Vector2f& Position)
{
	sf::Vector2f distanceBetweenSpriteAndHitbox = sf::Vector2f(globalBoundsOfHitboxes.getGlobalBounds().left, globalBoundsOfHitboxes.getGlobalBounds().top) - player.getPosition();
	globalBoundsOfHitboxes.setPosition(Position);
	player.setPosition(Position - distanceBetweenSpriteAndHitbox);
	setPositionOfArm();
	setPositionOfWeapon();
	setPositionOfHitboxes();
}

void Player::move(const sf::Vector2f& offset)
{
	player.move(offset);
	setPositionOfArm();
	setPositionOfWeapon();
	setPositionOfHitboxes();

}

sf::Vector2f Player::getPosition() const
{
	return player.getPosition();
}

const sf::FloatRect& Player::getGlobalBoundsOfSprite() const
{
	return globalBoundsOfSprite;
}

float Player::centerX() const
{
	return globalBoundsOfHitboxes.getGlobalBounds().left + globalBoundsOfHitboxes.getGlobalBounds().width / 2;
}

float Player::right() const
{
	return globalBoundsOfHitboxes.getGlobalBounds().left + globalBoundsOfHitboxes.getGlobalBounds().width;
}

float Player::left() const
{
	return globalBoundsOfHitboxes.getGlobalBounds().left;
}

float Player::bottom() const
{
	return globalBoundsOfHitboxes.getGlobalBounds().top + globalBoundsOfHitboxes.getGlobalBounds().height;
}

void Player::addHp(const int value)
{
	currentHp += value;
	if (currentHp < 0)
		currentHp = 0;

	if (currentHp > initialHp)
		currentHp = initialHp;
}
 
const int& Player::getCurrentHp() const
{
	return currentHp;
}

const int& Player::getInitialHp() const
{
	return initialHp;
}

void Player::updateMove(const float deltaTime)
{
	setCurrentVelocityX(deltaTime);
	setCurrentVelocityY(deltaTime);
	move(deltaTime);
}

void Player::updateCurrentWeaponShootTimer(const float deltaTime)
{
	currentWeapon->updateTimerOfShooting(deltaTime);
}

void Player::calculateGlobalBoundsOfSprite()
{
	globalBoundsOfSprite = player.getGlobalBounds();
}

void Player::setValue(int currentHp)
{
	this->currentHp = currentHp;
}

void Player::setInitialHp(int initHp)
{
	this->initialHp = initHp;
}

PlayerType Player::getType()
{
	return name;
}


float Player::top() const
{
	return globalBoundsOfHitboxes.getGlobalBounds().top;
}

void Player::setRotationOfArm(const sf::Vector2f& MousePosition)
{
	sf::Vector2f distanceBetweenMouseAndArm = arm.getPosition() + pointOfArmRotation - MousePosition;
	float distance = sqrt(pow(distanceBetweenMouseAndArm.x, 2) + pow(distanceBetweenMouseAndArm.y, 2));
	float angle = (asin(distanceBetweenMouseAndArm.y / distance) * 180.0) / M_PI;
	//if (MousePosition.x > arm.getPosition().x)
	if (MousePosition.x > player.getPosition().x)
	{
		if (MousePosition.x > arm.getPosition().x)
		{
			arm.setRotation(-angle);
		}
		else
		{
			if (angle <= 0 and angle > -84.5)
				angle = -84.5;
			if (angle > 0 and angle < 84.5)
				angle = 84.5;
			arm.setRotation(-180 + angle);
		}

		arm.setScale(1, 1);
	}
	else
	{
		arm.setScale(-1, 1);
		if (MousePosition.x < arm.getPosition().x)
		{
			arm.setRotation(angle);
		}
		else
		{
			if (angle <= 0 and angle > -84.5)
				angle = -84.5;
			if (angle > 0 and angle < 84.5)
				angle = 84.5;
			arm.setRotation(180 - angle);
		}
	}
	setPositionOfWeapon();
}

void Player::setScaleOfPlayer(const sf::Vector2f& MousePosition)
{
	if (MousePosition.x > player.getPosition().x)
	{
		player.setScale(1, 1);
	}
	else
	{
		player.setScale(-1, 1);
	}
}

void Player::setPositionOfHitboxes()
{
	globalBoundsOfHitboxes.setPosition(player.getPosition() + globalBoundsOfHitboxes.getOffset());
	if (player.getScale().x > 0)
	{
		for (auto& i : hitboxComponent.hitboxes)
		{
			i.setPosition(player.getPosition() + i.getOffset());
		}
	}
	else
	{
		for (auto& i : hitboxComponent.hitboxes)
		{
			i.setPosition(sf::Vector2f(player.getPosition().x - i.getGlobalBounds().width - i.getOffset().x, player.getPosition().y + i.getOffset().y));
		}
	}
}


void Player::setPositionOfWeapon()
{
	if (player.getScale().x == 1)
	{
		currentWeapon->setPosition(sf::Vector2f(arm.getPosition().x + cos((arm.getRotation()) * M_PI / 180) * (87 + currentWeapon->getOffset().x), arm.getPosition().y + sin((arm.getRotation()) * M_PI / 180) * (87 + currentWeapon->getOffset().x)));
	}
	else
	{
		currentWeapon->setPosition(sf::Vector2f(arm.getPosition().x - cos((arm.getRotation()) * M_PI / 180) * (87 + currentWeapon->getOffset().x), arm.getPosition().y - sin((arm.getRotation()) * M_PI / 180) * (87 + currentWeapon->getOffset().x)));
	}
}
