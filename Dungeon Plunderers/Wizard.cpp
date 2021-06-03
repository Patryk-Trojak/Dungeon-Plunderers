#include "pch.h"
#include "Wizard.h"

Wizard::Wizard(const sf::Vector2f& Position, const Keybinds& keybinds,
	const Resources& resources, const PlayerData& PlayerData)
	:Player(Position, resources[TextureID::Wizard], keybinds),
	mana(100),
	initialMana(100),
	numberOfHealthPotions(1),
	numberOfManaPotions(1)
{
	name = PlayerType::wizard;
	player.setOrigin(80, 0);
	animation = Animation(1, 1, sf::Vector2i(152, 200.f), 3, 0.1f);
	WizardStats stats = StatsPlayerCreator::wizardStats(PlayerData);
	basicWand = std::make_shared<Wand>(player.getPosition(), sf::Vector2f(-25, -25),  resources[TextureID::BasicWand],  resources[TextureID::Electroball], 
		mana, stats.basicWandFireRate, stats.basicWandDamage, 0, WandsTypes::basic);
	fireWand = std::make_shared<Wand>(player.getPosition(), sf::Vector2f(-25, -25),  resources[TextureID::FireWand],  resources[TextureID::Fireball], 
		mana, stats.fireWandFireRate, stats.fireWandDamage, stats.fireWandCostOfShot, WandsTypes::fire);
	iceWand = std::make_shared<Wand>(player.getPosition(), sf::Vector2f(-25, -25),  resources[TextureID::IceWand],  resources[TextureID::Icicle], 
		mana, stats.iceWandFireRate, stats.iceWandDamage, stats.iceWandCostOfShot, WandsTypes::ice);
	currentWeapon = basicWand;

	animation.setFrame(player, 1);
	arm.setTexture(resources[TextureID::Wizard]);
	arm.setTextureRect(sf::IntRect(460, 0, 72, 40));
	arm.setOrigin(9, 15);
	pointOfArmRotation = sf::Vector2f(0, 15.f);
	globalBoundsOfHitboxes =  Hitbox(Position, sf::Vector2f(90.f, 198.f), sf::Vector2f(-45.6006f, 2), sf::Color(255, 0, 0, 100));

	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(108.17f, 6.35403f), sf::Vector2f(-53.9987f, 193.852f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(98.1849f, 5.79761f), sf::Vector2f(-46.1317f, 188.103f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(81.9614f, 6.11163f), sf::Vector2f(-37.8525f, 182.038f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(61.2256f, 62.0886f), sf::Vector2f(-20.0074f, 119.891f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(6.2738f, 37.8888f), sf::Vector2f(-26.2261f, 143.917f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(52.369f, 16.0092f), sf::Vector2f(-16.2806f, 103.904f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(42.1937f, 9.76831f), sf::Vector2f(-12.2106f, 94.1357f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(53.8615f, 19.9437f), sf::Vector2f(-16.0627f, 66.0335f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(42.1937f, 6.10519f), sf::Vector2f(-8.19385f, 85.8415f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(61.319f, 56.9244f), sf::Vector2f(-38.0441f, 9.46796f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(6.92493f, 42.9f), sf::Vector2f(23.0417f, 23.4571f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(6.86206f, 20.1482f), sf::Vector2f(51.228f, 47.8679f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(7.73804f, 16.2061f), sf::Vector2f(58.0901f, 51.81f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(44.1235f, 5.54018f), sf::Vector2f(-34.1047f, 3.95958f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(4.26917f, 37.3544f), sf::Vector2f(29.8878f, 29.8295f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(3.6543f, 16.1293f), sf::Vector2f(-29.8723f, 165.955f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(2.39417f, 10.2068f), sf::Vector2f(-32.1405f, 171.877f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(3.81787f, 4.1815f), sf::Vector2f(-41.9983f, 16.0013f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(5.90869f, 20.1803f), sf::Vector2f(-43.9982f, 20.0009f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(4.09058f, 9.99927f), sf::Vector2f(-47.9978f, 29.9093f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(1.90894f, 5.99956f), sf::Vector2f(-45.9071f, 24.0007f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(13.8812f, 25.9681f), sf::Vector2f(34.0536f, 41.8695f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(3.96606f, 22.0021f), sf::Vector2f(48.0292f, 45.93f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(36.1694f, 2.42746f), sf::Vector2f(-8.00598f, 91.739f)));	
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(3.96606f, 22.0021f), sf::Vector2f(48.0292f, 45.93f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(36.1694f, 2.42746f), sf::Vector2f(-8.00598f, 91.739f)));

}

Wizard::~Wizard()
{
}

void Wizard::matchHitboxesToAnimation()
{
	switch (animation.getNumberOfCurrentFrame())
	{
	case 1:
		hitboxComponent.setHitbox(0, sf::Vector2f(108.17f, 6.35403f), sf::Vector2f(-53.9987f, 193.852f));
		hitboxComponent.setHitbox(1, sf::Vector2f(98.1849f, 5.79761f), sf::Vector2f(-46.1317f, 188.103f));
		hitboxComponent.setHitbox(2, sf::Vector2f(81.9614f, 6.11163f), sf::Vector2f(-37.8525f, 182.038f));
		hitboxComponent.setHitbox(3, sf::Vector2f(61.2256f, 62.0886f), sf::Vector2f(-20.0074f, 119.891f));
		hitboxComponent.setHitbox(4, sf::Vector2f(6.2738f, 37.8888f), sf::Vector2f(-26.2261f, 143.917f));
		hitboxComponent.setHitbox(5, sf::Vector2f(52.369f, 16.0092f), sf::Vector2f(-16.2806f, 103.904f));
		hitboxComponent.setHitbox(6, sf::Vector2f(42.1937f, 9.76831f), sf::Vector2f(-12.2106f, 94.1357f));
		hitboxComponent.setHitbox(7, sf::Vector2f(53.8615f, 19.9437f), sf::Vector2f(-16.0627f, 66.0335f));
		hitboxComponent.setHitbox(8, sf::Vector2f(42.1937f, 6.10519f), sf::Vector2f(-8.19385f, 85.8415f));
		hitboxComponent.setHitbox(9, sf::Vector2f(61.319f, 56.9244f), sf::Vector2f(-38.0441f, 9.46796f));
		hitboxComponent.setHitbox(10, sf::Vector2f(6.92493f, 42.9f), sf::Vector2f(23.0417f, 23.4571f));
		hitboxComponent.setHitbox(11, sf::Vector2f(6.86206f, 20.1482f), sf::Vector2f(51.228f, 47.8679f));
		hitboxComponent.setHitbox(12, sf::Vector2f(7.73804f, 16.2061f), sf::Vector2f(58.0901f, 51.81f));
		hitboxComponent.setHitbox(13, sf::Vector2f(44.1235f, 5.54018f), sf::Vector2f(-34.1047f, 3.95958f));
		hitboxComponent.setHitbox(14, sf::Vector2f(4.26917f, 37.3544f), sf::Vector2f(29.8878f, 29.8295f));
		hitboxComponent.setHitbox(15, sf::Vector2f(3.6543f, 16.1293f), sf::Vector2f(-29.8723f, 165.955f));
		hitboxComponent.setHitbox(16, sf::Vector2f(2.39417f, 10.2068f), sf::Vector2f(-32.1405f, 171.877f));
		hitboxComponent.setHitbox(17, sf::Vector2f(3.81787f, 4.1815f), sf::Vector2f(-41.9983f, 16.0013f));
		hitboxComponent.setHitbox(18, sf::Vector2f(5.90869f, 20.1803f), sf::Vector2f(-43.9982f, 20.0009f));
		hitboxComponent.setHitbox(19, sf::Vector2f(4.09058f, 9.99927f), sf::Vector2f(-47.9978f, 29.9093f));
		hitboxComponent.setHitbox(20, sf::Vector2f(1.90894f, 5.99956f), sf::Vector2f(-45.9071f, 24.0007f));
		hitboxComponent.setHitbox(21, sf::Vector2f(13.8812f, 25.9681f), sf::Vector2f(34.0536f, 41.8695f));
		hitboxComponent.setHitbox(22, sf::Vector2f(3.96606f, 22.0021f), sf::Vector2f(48.0292f, 45.93f));
		for (int i = 23; i <= 24; i++)
			hitboxComponent.hitboxes[i].setHitbox(sf::Vector2f(0.f, 0.f), sf::Vector2f(-10000.f, -1000.f));
		break;
	case 2:
		hitboxComponent.setHitbox(0, sf::Vector2f(108.17f, 6.35403f), sf::Vector2f(-54.1067f, 193.655f));
		hitboxComponent.setHitbox(1, sf::Vector2f(98.1849f, 5.79761f), sf::Vector2f(-45.9836f, 187.906f));
		hitboxComponent.setHitbox(2, sf::Vector2f(81.9614f, 6.11163f), sf::Vector2f(-37.8751f, 182.012f));
		hitboxComponent.setHitbox(3, sf::Vector2f(61.2256f, 62.0886f), sf::Vector2f(-19.8594f, 120.255f));
		hitboxComponent.setHitbox(4, sf::Vector2f(6.2738f, 37.8888f), sf::Vector2f(-25.9927f, 143.915f));
		hitboxComponent.setHitbox(5, sf::Vector2f(52.369f, 16.0092f), sf::Vector2f(-16.3887f, 99.9511f));
		hitboxComponent.setHitbox(6, sf::Vector2f(42.1937f, 9.76831f), sf::Vector2f(-12.3186f, 90.1828f));
		hitboxComponent.setHitbox(7, sf::Vector2f(53.8615f, 19.9437f), sf::Vector2f(-16.1708f, 62.0806f));
		hitboxComponent.setHitbox(8, sf::Vector2f(42.1937f, 6.10519f), sf::Vector2f(-8.30188f, 81.8886f));
		hitboxComponent.setHitbox(9, sf::Vector2f(59.9189f, 56.5244f), sf::Vector2f(-37.8497f, 6.01888f));
		hitboxComponent.setHitbox(10, sf::Vector2f(7.72498f, 42.9f), sf::Vector2f(22.0267f, 20.008f));
		hitboxComponent.setHitbox(11, sf::Vector2f(6.86206f, 20.1482f), sf::Vector2f(51.12f, 43.9149f));
		hitboxComponent.setHitbox(12, sf::Vector2f(7.73804f, 16.2061f), sf::Vector2f(57.9821f, 47.857f));
		hitboxComponent.setHitbox(13, sf::Vector2f(44.0236f, 6.34018f), sf::Vector2f(-34.0111f, -0.0942078f));
		hitboxComponent.setHitbox(14, sf::Vector2f(4.26917f, 37.3544f), sf::Vector2f(29.7798f, 25.8765f));
		hitboxComponent.setHitbox(15, sf::Vector2f(11.8179f, 4.1815f), sf::Vector2f(-42.1063f, 12.0482f));
		hitboxComponent.setHitbox(16, sf::Vector2f(9.90869f, 20.1803f), sf::Vector2f(-44.1062f, 16.0479f));
		hitboxComponent.setHitbox(17, sf::Vector2f(4.09058f, 9.99927f), sf::Vector2f(-48.1058f, 25.9563f));
		hitboxComponent.setHitbox(18, sf::Vector2f(1.90894f, 5.99956f), sf::Vector2f(-46.0151f, 20.0477f));
		hitboxComponent.setHitbox(19, sf::Vector2f(13.8812f, 25.9681f), sf::Vector2f(34.0463f, 38.0173f));
		hitboxComponent.setHitbox(20, sf::Vector2f(3.96606f, 22.0021f), sf::Vector2f(47.9211f, 41.977f));
		hitboxComponent.setHitbox(21, sf::Vector2f(36.1694f, 2.42746f), sf::Vector2f(-8.11401f, 87.7861f));
		hitboxComponent.setHitbox(22, sf::Vector2f(3.84143f, 10.1584f), sf::Vector2f(-31.9265f, 172.024f));
		hitboxComponent.setHitbox(23, sf::Vector2f(5.46326f, 24.2435f), sf::Vector2f(-28.0851f, 157.939f));
		hitboxComponent.setHitbox(24, sf::Vector2f(58.0938f, 4.35025f), sf::Vector2f(-19.9647f, 115.903f));
		break;
	case 3:
		hitboxComponent.setHitbox(0, sf::Vector2f(108.17f, 6.35403f), sf::Vector2f(-53.7837f, 194.02f));
		hitboxComponent.setHitbox(1, sf::Vector2f(98.1849f, 5.79761f), sf::Vector2f(-46.09f, 188.056f));
		hitboxComponent.setHitbox(2, sf::Vector2f(81.9614f, 6.11163f), sf::Vector2f(-35.8807f, 181.947f));
		hitboxComponent.setHitbox(3, sf::Vector2f(61.2256f, 62.0886f), sf::Vector2f(-15.8862f, 120.19f));
		hitboxComponent.setHitbox(4, sf::Vector2f(6.2738f, 37.8888f), sf::Vector2f(-22.0195f, 143.85f));
		hitboxComponent.setHitbox(5, sf::Vector2f(52.369f, 16.0092f), sf::Vector2f(-12.4155f, 99.8864f));
		hitboxComponent.setHitbox(6, sf::Vector2f(42.1937f, 9.76831f), sf::Vector2f(-8.34546f, 90.118f));
		hitboxComponent.setHitbox(7, sf::Vector2f(53.8615f, 19.9437f), sf::Vector2f(-12.1976f, 62.0159f));
		hitboxComponent.setHitbox(8, sf::Vector2f(42.1937f, 6.10519f), sf::Vector2f(-4.32874f, 81.8239f));
		hitboxComponent.setHitbox(9, sf::Vector2f(59.9189f, 56.5244f), sf::Vector2f(-33.8766f, 5.95413f));
		hitboxComponent.setHitbox(10, sf::Vector2f(7.72498f, 42.9f), sf::Vector2f(25.9999f, 19.9433f));
		hitboxComponent.setHitbox(11, sf::Vector2f(6.86206f, 20.1482f), sf::Vector2f(55.0931f, 43.8502f));
		hitboxComponent.setHitbox(12, sf::Vector2f(7.73804f, 16.2061f), sf::Vector2f(61.9552f, 47.7922f));
		hitboxComponent.setHitbox(13, sf::Vector2f(44.0236f, 6.34018f), sf::Vector2f(-30.038f, -0.158951f));
		hitboxComponent.setHitbox(14, sf::Vector2f(4.26917f, 37.3543f), sf::Vector2f(33.7529f, 25.8117f));
		hitboxComponent.setHitbox(15, sf::Vector2f(11.8179f, 4.1815f), sf::Vector2f(-38.1332f, 11.9835f));
		hitboxComponent.setHitbox(16, sf::Vector2f(9.90869f, 20.1803f), sf::Vector2f(-40.1331f, 15.9832f));
		hitboxComponent.setHitbox(17, sf::Vector2f(4.09058f, 9.99927f), sf::Vector2f(-44.1327f, 25.8916f));
		hitboxComponent.setHitbox(18, sf::Vector2f(1.90894f, 5.99956f), sf::Vector2f(-42.042f, 19.9829f));
		hitboxComponent.setHitbox(19, sf::Vector2f(13.8812f, 25.9681f), sf::Vector2f(38.0194f, 37.9525f));
		hitboxComponent.setHitbox(20, sf::Vector2f(3.96606f, 22.0021f), sf::Vector2f(51.8943f, 41.9122f));
		hitboxComponent.setHitbox(21, sf::Vector2f(36.1694f, 2.42746f), sf::Vector2f(-4.14087f, 87.7213f));
		hitboxComponent.setHitbox(22, sf::Vector2f(3.84143f, 10.1584f), sf::Vector2f(-27.9534f, 171.96f));
		hitboxComponent.setHitbox(23, sf::Vector2f(5.46326f, 24.2435f), sf::Vector2f(-24.1119f, 157.875f));
		hitboxComponent.setHitbox(24, sf::Vector2f(58.0938f, 4.35025f), sf::Vector2f(-15.9916f, 115.839f));
		break;
	}

}

void Wizard::handleGettingBonus(BonusesTypes name)
{
	if (name == BonusesTypes::healthPotion)
	{
		if (getCurrentNumberOfHealthPotions() < 3)
		{
			addNumberOfHealthPotions();
		}
	}
	else
	{
		if (getCurrentNumberOfManaPotions() < 3)
		{
			addNumberOfManaPotions();
		}
	}
}


int Wizard::getCurrentNumberOfHealthPotions() const
{
	return numberOfHealthPotions;
}

void Wizard::addNumberOfHealthPotions(int value)
{
	numberOfHealthPotions += value;
}

int Wizard::getCurrentNumberOfManaPotions() const
{
	return numberOfManaPotions;
}

void Wizard::addNumberOfManaPotions(int value)
{
	numberOfManaPotions += value;
}

int Wizard::getMana() const
{
	return mana;
}

int Wizard::getInitialMana() const
{
	return initialMana;
}




void Wizard::setCurrentVelocityX(const float deltaTime)
{
	if (keybinds.isPressed(KeybindID::MoveLeft) && isAbleToMoveLeft && !keybinds.isPressed(KeybindID::MoveRight))
	{
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

void Wizard::setCurrentVelocityY(const float deltaTime)
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
		isJumping = true;
		currentVelocity.y += (accelerationOfFalling * deltaTime);
	}
	else
	{
		currentVelocity.y = 0;
		timeOfJump = 0;
		isJumping = false;
		stopJump = false;
	}
}


void Wizard::animate(const float deltaTime)
{
	if (isMovingLeft)
	{
		if (currentVelocity.x < 0)
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

void Wizard::setPositionOfArm()
{
	if (player.getScale().x == -1)
	{
		switch (animation.getNumberOfCurrentFrame())
		{
		case 1:
			arm.setPosition(player.getPosition() + sf::Vector2f(-10, 112));
			break;
		case 2:
			arm.setPosition(player.getPosition() + sf::Vector2f(-10, 112 - 4));
			break;
		case 3:
			arm.setPosition(player.getPosition() + sf::Vector2f(-10 - 4, 112 - 4));
			break;
		}
	}
	else
	{
		switch (animation.getNumberOfCurrentFrame())
		{
		case 1:
			arm.setPosition(player.getPosition() + sf::Vector2f(10, 112));
			break;
		case 2:
			arm.setPosition(player.getPosition() + sf::Vector2f(10, 112 - 4));
			break;
		case 3:
			arm.setPosition(player.getPosition() + sf::Vector2f(10 + 4, 112 - 4));
			break;
		}
	}
}

void Wizard::setCurrentWeapon()
{
	if (keybinds.isPressed(KeybindID::FirstWeapon))
	{
		currentWeapon = basicWand;
	}
	if (keybinds.isPressed(KeybindID::SecondWeapon))
	{
		currentWeapon = fireWand;
	}
	if (keybinds.isPressed(KeybindID::ThirdWeapon))
	{
		currentWeapon = iceWand;
	}
}

void Wizard::handleDrinkingPotions()
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

	if (keybinds.isPressed(KeybindID::DrinkManaPotion) and numberOfManaPotions > 0 and mana < initialMana and isKeyDrinkManaPotionReleased)
	{
		mana += 20;
		if (mana > initialMana)
			mana = initialMana;
		numberOfManaPotions--;
		isKeyDrinkManaPotionReleased = false;
	}
	if (!keybinds.isPressed(KeybindID::DrinkManaPotion))
	{
		isKeyDrinkManaPotionReleased = true;
	}
}

void Wizard::setScaleOfPlayer(const sf::Vector2f& MousePosition)
{
	if (MousePosition.x > player.getPosition().x)
	{
		player.setScale(1, 1);
		arm.setScale(1, 1);
	}
	else
	{
		player.setScale(-1, 1);
		arm.setScale(-1, 1);
	}
}

void Wizard::setRotationOfArm(const sf::Vector2f& MousePosition)
{

}
