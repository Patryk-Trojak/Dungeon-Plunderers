#include "pch.h"
#include "WizardOnCloud.h"

WizardOnCloud::WizardOnCloud(const sf::Vector2f& Position, const Keybinds& keybinds,
	const Resources& resources, const PlayerData& PlayerData)
	:Player(Position, resources[TextureID::ShadowWizard], keybinds),
	HasShield(true),
	shieldAnimation(1, 1, sf::Vector2i(274, 274), 4, 0.1f),
	initialShieldHp(100),
	initialCloudHp(100),
	shieldHp(100),
	cloudHp(100)
{
	name = PlayerType::wizardOnCloud;
	player.setOrigin(80, 0);
	player.setTextureRect(sf::IntRect(0, 0, 148, 194));
	WizardOnCloudStats stats = StatsPlayerCreator::wizardOnCloudStats(PlayerData);
	shadowWand = std::make_shared<Wand>(player.getPosition(), sf::Vector2f(-25, -25), resources[TextureID::ShadowWand], resources[TextureID::ShadowBall], 
		mana, stats.fireRate, stats.damage, 0, WandsTypes::shadow);
	currentWeapon = shadowWand;

	arm.setTexture(resources[TextureID::ShadowWizard]);
	arm.setTextureRect(sf::IntRect(148, 0, 72, 40));
	arm.setOrigin(9, 15);
	pointOfArmRotation = sf::Vector2f(-25.f, 20.f);
	globalBoundsOfHitboxes = Hitbox(Position, sf::Vector2f(274.f, 274.f), sf::Vector2f(-138.f, -15.f), sf::Color(255, 0, 0, 100));

	cloud.setTexture(resources[TextureID::Cloud]);
	cloud.setPosition(Position + sf::Vector2f(2.f, 175.f));
	cloud.setOrigin(72, 0);


	shield.setTexture(resources[TextureID::MagicShield]);
	shield.setPosition(Position + sf::Vector2f(-138.f, -15.f));
	shieldAnimation.setFrame(shield, 1);
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


	shieldHitboxes.addHitbox(Hitbox(Position, sf::Vector2f(271.009f, 54.0298f), sf::Vector2f(0.999878f, 110.012f) - sf::Vector2f(276.f, 0.f)));
	shieldHitboxes.addHitbox(Hitbox(Position, sf::Vector2f(266.013f, 70.0645f), sf::Vector2f(3.98984f, 102.002f) - sf::Vector2f(274.f, 0.f)));
	shieldHitboxes.addHitbox(Hitbox(Position, sf::Vector2f(262.006f, 89.9628f), sf::Vector2f(5.99756f, 92.0064f) - sf::Vector2f(274.f, 0.f)));
	shieldHitboxes.addHitbox(Hitbox(Position, sf::Vector2f(255.995f, 105.977f), sf::Vector2f(9.00427f, 84.0035f) - sf::Vector2f(274.f, 0.f)));
	shieldHitboxes.addHitbox(Hitbox(Position, sf::Vector2f(250.02f, 119.935f), sf::Vector2f(12.008f, 76.9955f) - sf::Vector2f(274.f, 0.f)));
	shieldHitboxes.addHitbox(Hitbox(Position, sf::Vector2f(244.035f, 132.039f), sf::Vector2f(14.9831f, 70.9908f) - sf::Vector2f(274.f, 0.f)));
	shieldHitboxes.addHitbox(Hitbox(Position, sf::Vector2f(238.018f, 141.987f), sf::Vector2f(17.9765f, 65.9929f) - sf::Vector2f(274.f, 0.f)));
	shieldHitboxes.addHitbox(Hitbox(Position, sf::Vector2f(232.018f, 151.984f), sf::Vector2f(21.0018f, 61.0019f) - sf::Vector2f(274.f, 0.f)));
	shieldHitboxes.addHitbox(Hitbox(Position, sf::Vector2f(225.997f, 162.011f), sf::Vector2f(23.9969f, 55.9889f) - sf::Vector2f(274.f, 0.f)));
	shieldHitboxes.addHitbox(Hitbox(Position, sf::Vector2f(220.009f, 170.018f), sf::Vector2f(26.996f, 51.9787f) - sf::Vector2f(274.f, 0.f)));
	shieldHitboxes.addHitbox(Hitbox(Position, sf::Vector2f(213.99f, 178.001f), sf::Vector2f(30.005f, 48.0059f) - sf::Vector2f(274.f, 0.f)));
	shieldHitboxes.addHitbox(Hitbox(Position, sf::Vector2f(205.983f, 185.992f), sf::Vector2f(34.0229f, 44.0013f) - sf::Vector2f(274.f, 0.f)));
	shieldHitboxes.addHitbox(Hitbox(Position, sf::Vector2f(197.974f, 195.992f), sf::Vector2f(38.0172f, 38.9978f) - sf::Vector2f(274.f, 0.f)));
	shieldHitboxes.addHitbox(Hitbox(Position,sf::Vector2f(188.013f, 203.999f), sf::Vector2f(42.9964f, 34.9952f) - sf::Vector2f(274.f, 0.f)));
	shieldHitboxes.addHitbox(Hitbox(Position,sf::Vector2f(180.029f, 211.961f), sf::Vector2f(46.9808f, 30.9926f) - sf::Vector2f(274.f, 0.f)));
	shieldHitboxes.addHitbox(Hitbox(Position, sf::Vector2f(170.025f, 220.025f), sf::Vector2f(51.9869f, 26.9812f) - sf::Vector2f(274.f, 0.f)));
	shieldHitboxes.addHitbox(Hitbox(Position,sf::Vector2f(160.003f, 228.008f), sf::Vector2f(56.9894f, 22.9834f) - sf::Vector2f(274.f, 0.f)));
	shieldHitboxes.addHitbox(Hitbox(Position,sf::Vector2f(148.006f, 235.021f), sf::Vector2f(62.9857f, 19.9769f) - sf::Vector2f(274.f, 0.f)));
	shieldHitboxes.addHitbox(Hitbox(Position, sf::Vector2f(136.009f, 243.027f), sf::Vector2f(67.997f, 15.9796f) - sf::Vector2f(274.f, 0.f)));
	shieldHitboxes.addHitbox(Hitbox(Position, sf::Vector2f(122.016f, 249.009f), sf::Vector2f(74.9876f, 12.9861f) - sf::Vector2f(274.f, 0.f)));
	shieldHitboxes.addHitbox(Hitbox(Position, sf::Vector2f(107.998f, 255.005f), sf::Vector2f(82.0091f, 9.99481f) - sf::Vector2f(274.f, 0.f)));
	shieldHitboxes.addHitbox(Hitbox(Position, sf::Vector2f(93.0274f, 260.991f), sf::Vector2f(88.987f, 6.99843f) - sf::Vector2f(274.f, 0.f)));
	shieldHitboxes.addHitbox(Hitbox(Position, sf::Vector2f(74.0175f, 267.016f), sf::Vector2f(97.9899f, 3.98477f) - sf::Vector2f(274.f, 0.f)));
	shieldHitboxes.addHitbox(Hitbox(Position, sf::Vector2f(53.9805f, 272.062f), sf::Vector2f(110.016f, 0.920715f) - sf::Vector2f(274.f, 0.f)));

	//shieldHitboxes.setScaleOfAllHitboxes(sf::Vector2f(-1, 1));

	cloudHitboxes.addHitbox(Hitbox(Position, sf::Vector2f(92.9366f, 39.0209f), sf::Vector2f(-38.9957f, 11.9787f)));
	cloudHitboxes.addHitbox(Hitbox(Position, sf::Vector2f(108.069f, 30.0048f), sf::Vector2f(-45.0646f, 14.9952f)));
	cloudHitboxes.addHitbox(Hitbox(Position, sf::Vector2f(111.006f, 24.0514f), sf::Vector2f(-66.0126f, 29.9636f)));
	cloudHitboxes.addHitbox(Hitbox(Position, sf::Vector2f(120.01f, 18.1377f), sf::Vector2f(-50.9964f, 23.9892f)));
	cloudHitboxes.addHitbox(Hitbox(Position, sf::Vector2f(129.012f, 9.01671f), sf::Vector2f(-72.0246f, 38.9963f)));
	cloudHitboxes.addHitbox(Hitbox(Position, sf::Vector2f(2.97041f, 15.0181f), sf::Vector2f(-68.9912f, 35.9781f)));
	cloudHitboxes.addHitbox(Hitbox(Position, sf::Vector2f(3.0629f, 6.12578f), sf::Vector2f(68.9616f, 32.9681f)));



}

WizardOnCloud::~WizardOnCloud()
{
}

void WizardOnCloud::matchHitboxesToAnimation()
{
}

void WizardOnCloud::handleGettingBonus(BonusesTypes name)
{
}

void WizardOnCloud::addShieldHp(const int value)
{
	shieldHp += value;
	if (shieldHp <= 0)
	{
		shieldHitboxes.clearHitboxes();
		HasShield = false;
	}
}

void WizardOnCloud::addCloudHp(const int value)
{
	cloudHp += value;
}

int WizardOnCloud::getShieldHp() const
{
	return shieldHp;
}

int WizardOnCloud::getCloudHp() const
{
	return cloudHp;
}

int WizardOnCloud::getInitialShieldHp() const
{
	return initialShieldHp;
}

int WizardOnCloud::getInitialCloudHp() const
{
	return initialCloudHp;
}

bool WizardOnCloud::hasShield() const
{
	return HasShield;
}

void WizardOnCloud::setPosition(const sf::Vector2f& Position)
{
	player.setPosition(Position.x, Position.y);
	cloud.setPosition(Position + sf::Vector2f(2.f, 175.f));
	shield.setPosition(Position + sf::Vector2f(-138.f, -15.f));

	setPositionOfArm();
	setPositionOfWeapon();
	setPositionOfHitboxes();
}

void WizardOnCloud::setPositionRelativeToHitbox(const sf::Vector2f& Position)
{
	sf::Vector2f distanceBetweenSpriteAndHitbox = sf::Vector2f(globalBoundsOfHitboxes.getGlobalBounds().left, globalBoundsOfHitboxes.getGlobalBounds().top) - player.getPosition();
	globalBoundsOfHitboxes.setPosition(Position);
	player.setPosition(Position - distanceBetweenSpriteAndHitbox);
	cloud.setPosition(player.getPosition() + sf::Vector2f(2.f, 175.f));
	shield.setPosition(player.getPosition() + sf::Vector2f(-138.f, -15.f));

	setPositionOfArm();
	setPositionOfWeapon();
	setPositionOfHitboxes();
}


void WizardOnCloud::move(const float deltaTime)
{
	player.move(currentVelocity * deltaTime);
	shield.move(currentVelocity * deltaTime);
	cloud.move(currentVelocity * deltaTime);

	setPositionOfArm();
	setPositionOfWeapon();
	matchHitboxesToAnimation();
	setPositionOfHitboxes();
}


void WizardOnCloud::setCurrentVelocityX(const float deltaTime)
{
	if (keybinds.isPressed(KeybindID::MoveLeftPlaneOrCloud) and !keybinds.isPressed(KeybindID::MoveRightPlaneOrCloud) and player.getPosition().x > 470)
	{
		currentVelocity.x = -maxVelocity.x;
	}
	else if (keybinds.isPressed(KeybindID::MoveRightPlaneOrCloud) and !keybinds.isPressed(KeybindID::MoveLeftPlaneOrCloud) and player.getPosition().x < 2950)
	{
		currentVelocity.x = maxVelocity.x;
	}
	else
	{
		currentVelocity.x = 0;
	}
}

void WizardOnCloud::setCurrentVelocityY(const float deltaTime)
{
	if (keybinds.isPressed(KeybindID::MoveUpPlaneOrCloud) and !keybinds.isPressed(KeybindID::MoveDownPlaneOrCloud) and player.getPosition().y > -310)
	{
		currentVelocity.y = -maxVelocity.y;
	}
	else if (keybinds.isPressed(KeybindID::MoveDownPlaneOrCloud) and !keybinds.isPressed(KeybindID::MoveUpPlaneOrCloud) and player.getPosition().y < 1180.f)
	{
		currentVelocity.y = maxVelocity.y;
	}
	else
	{
		currentVelocity.y = 0;
	}
}

void WizardOnCloud::animate(const float deltaTime)
{
	shieldAnimation.play(shield, deltaTime);
}

void WizardOnCloud::setPositionOfArm()
{
	if (player.getScale().x == -1)
	{
		arm.setPosition(player.getPosition() + sf::Vector2f(-10, 107));
	}
	else
	{
		arm.setPosition(player.getPosition() + sf::Vector2f(10, 107));
	}
}

void WizardOnCloud::setCurrentWeapon()
{
}

void WizardOnCloud::handleDrinkingPotions()
{
}

void WizardOnCloud::setPositionOfHitboxes()
{
	globalBoundsOfHitboxes.setPosition(player.getPosition() + globalBoundsOfHitboxes.getOffset());
	if (player.getScale().x > 0)
	{
		for (auto& i : hitboxComponent.hitboxes)
		{
			i.setPosition(player.getPosition() + i.getOffset());
		}	
		for (auto& i : cloudHitboxes.hitboxes)
		{
			i.setPosition(cloud.getPosition() + i.getOffset());
		}
	}
	else
	{
		for (auto& i : hitboxComponent.hitboxes)
		{
			i.setPosition(sf::Vector2f(player.getPosition().x - i.getGlobalBounds().width - i.getOffset().x, player.getPosition().y + i.getOffset().y));
		}
		for (auto& i : cloudHitboxes.hitboxes)
		{
			i.setPosition(sf::Vector2f(cloud.getPosition().x - i.getGlobalBounds().width - i.getOffset().x, cloud.getPosition().y + i.getOffset().y));
		}
	}
	for (auto& i : shieldHitboxes.hitboxes)
	{
		i.setPosition(sf::Vector2f(shield.getPosition().x - i.getGlobalBounds().width - i.getOffset().x, shield.getPosition().y + i.getOffset().y));
	}
}

void WizardOnCloud::setScaleOfPlayer(const sf::Vector2f& MousePosition)
{
	if (MousePosition.x > player.getPosition().x)
	if (MousePosition.x > player.getPosition().x)
	{
		player.setScale(1, 1);
		cloud.setScale(1, 1);
		arm.setScale(1, 1);
	}
	else
	{
		player.setScale(-1, 1);
		cloud.setScale(-1, 1);
		arm.setScale(-1, 1);
	}
}

void WizardOnCloud::setRotationOfArm(const sf::Vector2f& MousePosition)
{

}

void WizardOnCloud::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(player, states);
	target.draw(cloud, states);
	if(HasShield)
		target.draw(shield, states);
	target.draw(*currentWeapon, states);
	target.draw(arm, states);
	//target.draw(globalBoundsOfHitboxes, states);
	//for (auto const& i : hitboxComponent.getHitboxes())
	//	target.draw(i, states);	
//	for (auto const& i : shieldHitboxes.getHitboxes())
		//target.draw(i, states);
}
