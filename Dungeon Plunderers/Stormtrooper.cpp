#include "pch.h"
#include "Stormtrooper.h"
#define _USE_MATH_DEFINES 

Stormtrooper::Stormtrooper(const sf::Vector2f& Position, const Keybinds& keybinds,
	const Resources& resources, const PlayerData& PlayerData)
	:Player(Position, resources[TextureID::Stormtrooper], keybinds),
	numberOfHealthPotions(3)
{
	name = PlayerType::stormtrooper;
	player.setTextureRect(sf::IntRect(0, 0, 117, 207));
	player.setOrigin(62, 0);
	arm.setTexture(resources[TextureID::Stormtrooper]);
	arm.setTextureRect(sf::IntRect(1053, 0, 87, 23));
	arm.setOrigin(8, 10);
	animation = Animation(1, 1, sf::Vector2i(117, 207), 9, 0.05f);
	StormtrooperStats stats = StatsPlayerCreator::stormtrooperStats(PlayerData);

	handgun = std::make_shared<Handgun>(player.getPosition(), sf::Vector2f(-45, -45), resources[TextureID::Handgun], resources[TextureID::Bullet], 
		stats.handgunFireRate, stats.handgunDamage);
	rifle = std::make_shared<Rifle>(player.getPosition(), sf::Vector2f(-86, 0), resources[TextureID::Rifle], resources[TextureID::Bullet], 
		stats.rifleFireRate, stats.rifleDamage, stats.rifleInitialAmmo);
	shotgun = std::make_shared<Shotgun>(player.getPosition(), sf::Vector2f(-86, 0), resources[TextureID::Shotgun], resources[TextureID::Bullet],
		stats.shotgunFireRate, stats.shotgunDamage, stats.shotgunInitialAmmo);

	currentWeapon = handgun;
	nameOfCurrentWeapon = WeaponsOfStormtrooper::handgun;
	globalBoundsOfHitboxes = Hitbox(Position, sf::Vector2f(90, 198), sf::Vector2f(-45.f, 9.f));
	animation.setFrame(player, 1);

	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(0, 0), sf::Vector2f(-10000.f, -1000.f), sf::Color(0, 0, 0, 0)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(78.0425f, 14.8848f), sf::Vector2f(-26.0032f, 9.01318f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(72.2735f, 12.3529f), sf::Vector2f(-29.0867f, 23.7234f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(66.0048f, 9.03418f), sf::Vector2f(-26.0445f, 36.1062f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(53.8363f, 9.21855f), sf::Vector2f(-16.826f, 44.9561f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(66.2793f, 6.00133f), sf::Vector2f(-20.2136f, 2.99539f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(54.1001f, 3.00066f), sf::Vector2f(-14.2123f, -0.0935211f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(18.126f, 72.9463f), sf::Vector2f(0.662369f, 54.2085f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(23.5471f, 64.0481f), sf::Vector2f(-22.9476f, 62.9911f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(7.53506f, 53.8219f), sf::Vector2f(-30.4921f, 66.0859f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(4.57486f, 32.1586f), sf::Vector2f(-35.067f, 74.6974f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(2.96021f, 12.1099f), sf::Vector2f(-38.0272f, 83.9817f))); //11

	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(39.4265f, 12.1635f), sf::Vector2f(-17.5035f, 129.026f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(21.391f, 12.3732f), sf::Vector2f(-22.9561f, 140.77f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(20.5521f, 12.7926f), sf::Vector2f(-28.8282f, 152.724f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(20.7618f, 15.5189f), sf::Vector2f(-34.7002f, 164.887f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(17.1967f, 15.3092f), sf::Vector2f(-39.9431f, 176.841f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(14.0509f, 23.6978f), sf::Vector2f(-43.5082f, 183.133f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(9.85661f, 9.43719f), sf::Vector2f(-29.8767f, 197.603f)));

	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(20.2724f, 12.1029f), sf::Vector2f(4.04974f, 140.874f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(20.575f, 12.2542f), sf::Vector2f(7.22676f, 149.8f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(21.3314f, 9.68234f), sf::Vector2f(9.64734f, 161.601f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(21.1801f, 9.22849f), sf::Vector2f(12.9756f, 170.98f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(21.634f, 9.37976f), sf::Vector2f(16.024f, 179.952f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(14.9774f, 18.4569f), sf::Vector2f(22.0755f, 188.726f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(8.62332f, 9.07718f), sf::Vector2f(37.3554f, 197.955f)));
}


void Stormtrooper::matchHitboxesToAnimation()
{
	switch (animation.getNumberOfCurrentFrame())
	{
	case 1:
	case 6:
		hitboxComponent.setHitbox(12, sf::Vector2f(39.4265f, 12.1635f), sf::Vector2f(-17.5035f, 129.026f));
		hitboxComponent.setHitbox(13, sf::Vector2f(21.391f, 12.3732f), sf::Vector2f(-22.9561f, 140.77f));
		hitboxComponent.setHitbox(14, sf::Vector2f(20.5521f, 12.7926f), sf::Vector2f(-28.8282f, 152.724f));
		hitboxComponent.setHitbox(15, sf::Vector2f(20.7618f, 15.5189f), sf::Vector2f(-34.7002f, 164.887f));
		hitboxComponent.setHitbox(16, sf::Vector2f(17.1967f, 15.3092f), sf::Vector2f(-39.9431f, 176.841f));
		hitboxComponent.setHitbox(17, sf::Vector2f(14.0509f, 23.6978f), sf::Vector2f(-43.5082f, 183.133f));
		hitboxComponent.setHitbox(18, sf::Vector2f(9.85661f, 9.43719f), sf::Vector2f(-29.8767f, 197.603f));
		hitboxComponent.setHitbox(19, sf::Vector2f(20.2724f, 12.1029f), sf::Vector2f(4.04974f, 140.874f));
		hitboxComponent.setHitbox(20, sf::Vector2f(20.575f, 12.2542f), sf::Vector2f(7.22676f, 149.8f));
		hitboxComponent.setHitbox(21, sf::Vector2f(21.3314f, 9.68234f), sf::Vector2f(9.64734f, 161.601f));
		hitboxComponent.setHitbox(22, sf::Vector2f(21.1801f, 9.22849f), sf::Vector2f(12.9756f, 170.98f));
		hitboxComponent.setHitbox(23, sf::Vector2f(21.634f, 9.37976f), sf::Vector2f(16.024f, 179.952f));
		hitboxComponent.setHitbox(24, sf::Vector2f(14.9774f, 18.4569f), sf::Vector2f(22.0755f, 188.726f));
		hitboxComponent.setHitbox(25, sf::Vector2f(8.62332f, 9.07718f), sf::Vector2f(37.3554f, 197.955f));

		break;
	case 2:
		hitboxComponent.setHitbox(12, sf::Vector2f(39.4265f, 12.1635f), sf::Vector2f(-17.5035f, 129.026f));
		hitboxComponent.setHitbox(13, sf::Vector2f(20.2724f, 12.1029f), sf::Vector2f(4.04974f, 140.874f));
		hitboxComponent.setHitbox(14, sf::Vector2f(20.575f, 12.2542f), sf::Vector2f(7.22676f, 149.8f));
		hitboxComponent.setHitbox(15, sf::Vector2f(21.3314f, 9.68234f), sf::Vector2f(9.64734f, 161.601f));
		hitboxComponent.setHitbox(16, sf::Vector2f(21.1801f, 9.22849f), sf::Vector2f(12.9756f, 170.98f));
		hitboxComponent.setHitbox(17, sf::Vector2f(21.634f, 9.37976f), sf::Vector2f(16.024f, 179.952f));
		hitboxComponent.setHitbox(18, sf::Vector2f(14.9774f, 18.4569f), sf::Vector2f(22.0755f, 188.726f));
		hitboxComponent.setHitbox(19, sf::Vector2f(8.62332f, 9.07718f), sf::Vector2f(37.3554f, 197.955f));

		hitboxComponent.setHitbox(20, sf::Vector2f(24.1592f, 18.2872f), sf::Vector2f(-23.1506f, 140.786f));
		hitboxComponent.setHitbox(21, sf::Vector2f(38.8897f, 21.0776f), sf::Vector2f(-49.7803f, 149.93f));
		hitboxComponent.setHitbox(22, sf::Vector2f(5.93735f, 9.05447f), sf::Vector2f(-10.8906f, 159.133f));
		hitboxComponent.setHitbox(23, sf::Vector2f(8.89182f, 24.0154f), sf::Vector2f(-61.8875f, 152.892f));

		for (int i = 24; i <= 25; i++)
			hitboxComponent.hitboxes[i].setHitbox(sf::Vector2f(0.f, 0.f), sf::Vector2f(-10000.f, -1000.f));

		break;
	case 3:
	case 7:
		hitboxComponent.setHitbox(12, sf::Vector2f(24.1592f, 18.2872f), sf::Vector2f(-23.1506f, 140.786f));
		hitboxComponent.setHitbox(13, sf::Vector2f(38.8897f, 21.0776f), sf::Vector2f(-49.7803f, 149.93f));
		hitboxComponent.setHitbox(14, sf::Vector2f(5.93735f, 9.05447f), sf::Vector2f(-10.8906f, 159.133f));
		hitboxComponent.setHitbox(15, sf::Vector2f(8.89182f, 24.0154f), sf::Vector2f(-61.8875f, 152.892f));

		hitboxComponent.setHitbox(16, sf::Vector2f(23.5812f, 35.3718f), sf::Vector2f(-4.5376f, 123.59f));
		hitboxComponent.setHitbox(17, sf::Vector2f(20.8603f, 36.5055f), sf::Vector2f(-1.93005f, 158.715f));
		hitboxComponent.setHitbox(18, sf::Vector2f(24.1481f, 8.84296f), sf::Vector2f(1.01758f, 198.055f));
		hitboxComponent.setHitbox(19, sf::Vector2f(3.19476f, 12.1399f), sf::Vector2f(18.6714f, 155.907f));
		hitboxComponent.setHitbox(20, sf::Vector2f(14.7785f, 3.11127f), sf::Vector2f(0.886292f, 195.297f));

		hitboxComponent.setHitbox(21, sf::Vector2f(12.4691f, 19.1712f), sf::Vector2f(-17.2374f, 128.349f));

		for (int i = 22; i <= 25; i++)
			hitboxComponent.hitboxes[i].setHitbox(sf::Vector2f(0.f, 0.f), sf::Vector2f(-10000.f, -1000.f));

		break;
	case 4:
		hitboxComponent.setHitbox(12, sf::Vector2f(23.5812f, 35.3718f), sf::Vector2f(-4.5376f, 123.59f));
		hitboxComponent.setHitbox(13, sf::Vector2f(20.8603f, 36.5055f), sf::Vector2f(-1.93005f, 158.715f));
		hitboxComponent.setHitbox(14, sf::Vector2f(24.1481f, 8.84296f), sf::Vector2f(1.01758f, 198.055f));
		hitboxComponent.setHitbox(15, sf::Vector2f(3.19476f, 12.1399f), sf::Vector2f(18.6714f, 155.907f));
		hitboxComponent.setHitbox(16, sf::Vector2f(14.7785f, 3.11127f), sf::Vector2f(0.886292f, 195.297f));

		hitboxComponent.setHitbox(17, sf::Vector2f(35.3328f, 21.2377f), sf::Vector2f(-25.9998f, 149.905f));
		hitboxComponent.setHitbox(18, sf::Vector2f(6.00732f, 23.9904f), sf::Vector2f(-38.0146f, 153.039f));
		hitboxComponent.setHitbox(19, sf::Vector2f(3.00366f, 20.9478f), sf::Vector2f(-31.9683f, 153.039f));
		hitboxComponent.setHitbox(20, sf::Vector2f(2.92566f, 14.9794f), sf::Vector2f(-28.9646f, 153.039f));

		for (int i = 21; i <= 25; i++)
			hitboxComponent.hitboxes[i].setHitbox(sf::Vector2f(0.f, 0.f), sf::Vector2f(-10000.f, -1000.f));
		break;
	case 5:
	case 9:
		hitboxComponent.setHitbox(12, sf::Vector2f(8.9751f, 66.1022f), sf::Vector2f(9.94617f, 122.829f));
		hitboxComponent.setHitbox(13, sf::Vector2f(3.13416f, 62.968f), sf::Vector2f(18.9213f, 131.661f));
		hitboxComponent.setHitbox(14, sf::Vector2f(2.9917f, 66.1022f), sf::Vector2f(21.913f, 140.921f));
		hitboxComponent.setHitbox(15, sf::Vector2f(8.71198f, 9.31696f), sf::Vector2f(37.3591f, 197.876f));

		hitboxComponent.setHitbox(16, sf::Vector2f(3.10449f, 56.8449f), sf::Vector2f(24.966f, 150.052f));
		hitboxComponent.setHitbox(17, sf::Vector2f(2.89044f, 48.1736f), sf::Vector2f(28.0705f, 158.83f));
		hitboxComponent.setHitbox(18, sf::Vector2f(2.89044f, 38.9671f), sf::Vector2f(30.9609f, 168.037f));
		hitboxComponent.setHitbox(19, sf::Vector2f(3.10449f, 29.9747f), sf::Vector2f(33.9584f, 177.029f));
		hitboxComponent.setHitbox(20, sf::Vector2f(23.8033f, 32.9948f), sf::Vector2f(-13.7396f, 123.043f));
		hitboxComponent.setHitbox(21, sf::Vector2f(20.7396f, 39.1223f), sf::Vector2f(-10.9114f, 155.802f));
		hitboxComponent.setHitbox(22, sf::Vector2f(24.033f, 9.08185f), sf::Vector2f(-8.01294f, 197.945f));
		hitboxComponent.setHitbox(23, sf::Vector2f(14.9716f, 2.99429f), sf::Vector2f(-7.97156f, 194.979f));

		for (int i = 24; i <= 25; i++)
			hitboxComponent.hitboxes[i].setHitbox(sf::Vector2f(0.f, 0.f), sf::Vector2f(-10000.f, -1000.f));
		break;
	
	case 8:

		hitboxComponent.setHitbox(12, sf::Vector2f(23.5812f, 35.3718f), sf::Vector2f(-4.5376f, 123.59f));
		hitboxComponent.setHitbox(13, sf::Vector2f(20.8603f, 36.5055f), sf::Vector2f(-1.93005f, 158.715f));
		hitboxComponent.setHitbox(14, sf::Vector2f(24.1481f, 8.84296f), sf::Vector2f(1.01758f, 198.055f));
		hitboxComponent.setHitbox(15, sf::Vector2f(3.19476f, 12.1399f), sf::Vector2f(18.6714f, 155.907f));
		hitboxComponent.setHitbox(16, sf::Vector2f(14.7785f, 3.11127f), sf::Vector2f(0.886292f, 195.297f));
		hitboxComponent.setHitbox(17, sf::Vector2f(24.2117f, 42.1129f), sf::Vector2f(-17.1815f, 128.871f));
		hitboxComponent.setHitbox(18, sf::Vector2f(42.3705f, 20.9921f), sf::Vector2f(-41.0068f, 149.992f));
		hitboxComponent.setHitbox(19, sf::Vector2f(5.96082f, 24.0543f), sf::Vector2f(-53.0204f, 153.017f));
		hitboxComponent.setHitbox(20, sf::Vector2f(3.1123f, 21.0475f), sf::Vector2f(-47.0068f, 152.964f));
		hitboxComponent.setHitbox(21, sf::Vector2f(3.05957f, 14.9812f), sf::Vector2f(-44.f, 153.069f));

		for (int i = 22; i <= 25; i++)
			hitboxComponent.hitboxes[i].setHitbox(sf::Vector2f(0.f, 0.f), sf::Vector2f(-10000.f, -1000.f));
		break;
	default:
		break;
	}
}

void Stormtrooper::handleGettingBonus(BonusesTypes name)
{
	if (name == BonusesTypes::healthPotion)
	{
		if (getCurrentNumberOfHealthPotions() < 3)
		{
			addNumberOfHealthPotions();
		}
	}
	else if (name == BonusesTypes::rifleAmmoBox)
	{
		addCurrentRifleAmmo(10);
	}
	else if (name == BonusesTypes::shotgunAmmoBox)
	{
		addCurrentShotgunAmmo(10);
	}
}

void Stormtrooper::addCurrentRifleAmmo(int value)
{
	rifle->addNumberOfAmmo(value);
}

void Stormtrooper::addCurrentShotgunAmmo(int value)
{
	shotgun->addNumberOfAmmo(value);
}

Stormtrooper::~Stormtrooper()
{
}

std::string Stormtrooper::getAmmo() const
{
	switch (nameOfCurrentWeapon)
	{
	case WeaponsOfStormtrooper::handgun:
		return "Nieskonczonosc";
		break;
	case WeaponsOfStormtrooper::rifle:
		return std::to_string(rifle->getNumberOfAmmo());
		break;
	case WeaponsOfStormtrooper::shotgun:
		return std::to_string(shotgun->getNumberOfAmmo());
		break;
	}
}

int Stormtrooper::getCurrentNumberOfHealthPotions() const
{
	return numberOfHealthPotions;
}

void Stormtrooper::addNumberOfHealthPotions(int value)
{
	if(numberOfHealthPotions < 3)
		numberOfHealthPotions += value;
}


void Stormtrooper::setCurrentVelocityX(const float deltaTime)
{
	if (keybinds.isPressed(KeybindID::MoveLeft) && isAbleToMoveLeft && !keybinds.isPressed(KeybindID::MoveRight))
	{
		if (!isMovingLeft)
			animation.setFrame(player, 2);
		currentVelocity.x = -maxVelocity.x;
		isTurnedLeft = true;
		isMovingLeft = true;
		isMovingRight = false;
	}
	else
	{
		isMovingLeft = false;
	}
	if (keybinds.isPressed(KeybindID::MoveRight) && isAbleToMoveRight && !keybinds.isPressed(KeybindID::MoveLeft))
	{
		if (!isMovingRight)
			animation.setFrame(player, 2);
		currentVelocity.x = maxVelocity.x;
		isTurnedLeft = false;
		isMovingLeft = false;
		isMovingRight = true;
	}
	else
	{
		isMovingRight = false;
	}
	if ((!isMovingLeft && !isMovingRight))
	{
		currentVelocity.x = 0;
		isMovingLeft = false;
		isMovingRight = false;
	}
}

void Stormtrooper::setCurrentVelocityY(const float deltaTime)
{
	if (keybinds.isPressed(KeybindID::Jump) && (timeOfJump < 0.15f) && !stopJump)
	{
		isJumping = true;
		timeOfJump += deltaTime;

		if (timeOfJump < 0.15f)
		{
			currentVelocity.y += (accelerationOfJumping * deltaTime);
		}
		else
		{
			currentVelocity.y += ((0.15f - lastTimeOfJump) * accelerationOfJumping);
			currentVelocity.y += ((timeOfJump - 0.15f) * accelerationOfFalling);
		}

		lastTimeOfJump = timeOfJump;
	}
	else if (isAbleToFall)
	{
		stopJump = true;
		currentVelocity.y += (accelerationOfFalling * deltaTime);
		isJumping = true;	
	}
	else
	{
		currentVelocity.y = 0;
		timeOfJump = 0;
		isJumping = false;
		stopJump = false;
	}
}

void Stormtrooper::animate(const float deltaTime)
{
	if (isMovingLeft)
	{
		if(currentVelocity.x < 0)
			animation.play(player, deltaTime);
		else
			animation.playBackwards(player, deltaTime);
	}
	else if (isMovingRight)
	{
		if (currentVelocity.x > 0)
			animation.play(player, deltaTime);
		else
			animation.playBackwards(player, deltaTime);
	}
	else
	{
		animation.setFrame(player, 1);
	}
}


void Stormtrooper::setPositionOfArm()
{
	if (player.getScale().x == -1)
	{
		arm.setPosition(player.getPosition() + sf::Vector2f(-7, 75));
	}
	else
	{
		arm.setPosition(player.getPosition() + sf::Vector2f(7, 75));
	}
}

void Stormtrooper::setCurrentWeapon()
{
	if (keybinds.isPressed(KeybindID::FirstWeapon))
	{
		nameOfCurrentWeapon = WeaponsOfStormtrooper::handgun;
		currentWeapon = handgun;
	}
	if (keybinds.isPressed(KeybindID::SecondWeapon))
	{
		nameOfCurrentWeapon = WeaponsOfStormtrooper::rifle;
		currentWeapon = rifle;
	}
	if (keybinds.isPressed(KeybindID::ThirdWeapon))
	{
		nameOfCurrentWeapon = WeaponsOfStormtrooper::shotgun;
		currentWeapon = shotgun;
	}
}

void Stormtrooper::handleDrinkingPotions()
{
	if (keybinds.isPressed(KeybindID::DrinkHealthPotion) and numberOfHealthPotions > 0 and currentHp < initialHp and isKeyDrinkHealhtPotionReleased)
	{
		currentHp += 20;
		if (currentHp > initialHp)
			currentHp = initialHp;
		numberOfHealthPotions--;
		isKeyDrinkHealhtPotionReleased = false;
	}
	if (!keybinds.isPressed(KeybindID::DrinkHealthPotion))
	{
		isKeyDrinkHealhtPotionReleased = true;
	}
}

