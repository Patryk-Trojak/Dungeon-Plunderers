#include "pch.h"
#include "Helicopter.h"

Helicopter::Helicopter(const sf::Vector2f& Position, const Keybinds& keybinds,
	const Resources& resources, const PlayerData& PlayerData)
	:Player(Position, resources[TextureID::Helicopter], keybinds)

{
	name = PlayerType::helicopter;
	HelicopterStats stats = StatsPlayerCreator::helicopterStats(PlayerData);
	player.setTextureRect(sf::IntRect(0, 0, 282, 94));
	player.setOrigin(0, 0);
	animation = Animation(1, 1, sf::Vector2i(423, 141), 6, 0.05f);
	animation.setFrame(player, 1);
	currentWeapon = std::make_shared<WeaponOfHelicopter>(Position, sf::Vector2f(-50.f, -50.f), resources[TextureID::Bullet], 0.4, stats.damage);
	arm.setTexture(resources[TextureID::Helicopter]);
	arm.setTextureRect(sf::IntRect(2539, 0, 48, 27));
	arm.setOrigin(13.f, 13.f);

	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(375.041f, 12.0725f), sf::Vector2f(5.99358f, 62.9836f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(320.961f, 21.0301f), sf::Vector2f(51.0047f, 59.9828f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(12.0069f, 59.8766f), sf::Vector2f(33.0486f, 17.9793f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(48.0644f, 23.991f), sf::Vector2f(15.0197f, 53.9176f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(39.1605f, 12.284f), sf::Vector2f(20.8732f, 41.8031f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(33.1422f, 6.51302f), sf::Vector2f(24.006f, 36.032f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(21.023f, 12.0367f), sf::Vector2f(30.0244f, 23.9129f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(393.065f, 5.96204f), sf::Vector2f(-0.0761871f, 68.981f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(222.06f, 12.0029f), sf::Vector2f(189.008f, 81.0208f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(213.073f, 12.0084f), sf::Vector2f(197.996f, 92.9882f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(149.917f, 9.0275f), sf::Vector2f(210.126f, 104.935f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(90.012f, 27.3685f), sf::Vector2f(240.044f, 113.681f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(137.907f, 9.12286f), sf::Vector2f(216.02f, 131.927f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(6.01855f, 8.92825f), sf::Vector2f(353.989f, 129.015f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(174.064f, 9.14998f), sf::Vector2f(189.03f, 50.9601f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(159.086f, 9.08615f), sf::Vector2f(194.978f, 41.9838f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(144.027f, 6.12914f), sf::Vector2f(201.022f, 35.9622f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(131.963f, 8.92487f), sf::Vector2f(207.032f, 27.0967f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(92.8547f, 6.49203f), sf::Vector2f(225.155f, 20.9018f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(51.1985f, 6.78712f), sf::Vector2f(246.007f, 14.8524f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(42.0074f, 33.1553f), sf::Vector2f(360.022f, 74.8627f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(6.06537f, 15.0634f), sf::Vector2f(410.964f, 86.8684f))); //21
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(242.972f, 8.95033f), sf::Vector2f(162.024f, 0.020813f))); //22
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(242.972f, 8.95033f), sf::Vector2f(162.024f, 0.020813f))); //23
}

Helicopter::~Helicopter()
{
}

void Helicopter::matchHitboxesToAnimation()
{
	switch (animation.getNumberOfCurrentFrame())
	{
	case 1:
		hitboxComponent.setHitbox(22, sf::Vector2f(242.99f, 9.05804f), sf::Vector2f(162.001f, 0.0090332f));
		hitboxComponent.setHitbox(23, sf::Vector2f(249.032f, 2.98383f), sf::Vector2f(158.984f, 3.f));

		break;
	case 2:
	case 6:
		hitboxComponent.setHitbox(22, sf::Vector2f(152.932f, 9.05241f), sf::Vector2f(207.025f, 0.f));
		hitboxComponent.setHitbox(23, sf::Vector2f(195.001f, 3.00108f), sf::Vector2f(186.004f, 3.f));
		break;	
	case 3:
	case 5:
		hitboxComponent.setHitbox(22, sf::Vector2f(123.028f, 8.96623f), sf::Vector2f(224.983f, 0.00387573f));
		hitboxComponent.setHitbox(23, sf::Vector2f(165.016f, 3.00192f), sf::Vector2f(203.984f, 3.00002f));
		break;
	case 4:
		hitboxComponent.setHitbox(22, sf::Vector2f(194.998f, 3.00522f), sf::Vector2f(185.999f, 3.00002f));
		hitboxComponent.setHitbox(23, sf::Vector2f(26.9269f, 9.03586f), sf::Vector2f(270.042f, 0.0181732f));
		break;	
	}
}

void Helicopter::handleGettingBonus(BonusesTypes name)
{
}


void Helicopter::setCurrentVelocityX(const float deltaTime)
{
	if (keybinds.isPressed(KeybindID::MoveLeftPlaneOrCloud) and !keybinds.isPressed(KeybindID::MoveRightPlaneOrCloud) and player.getPosition().x > 400)
	{
		currentVelocity.x = -900;
	}
	else if (keybinds.isPressed(KeybindID::MoveRightPlaneOrCloud) and !keybinds.isPressed(KeybindID::MoveLeftPlaneOrCloud) and player.getPosition().x < 2700)
	{
		currentVelocity.x = 900;
	}
	else
	{
		currentVelocity.x = 0;
	}
}

void Helicopter::setCurrentVelocityY(const float deltaTime)
{
	if (keybinds.isPressed(KeybindID::MoveUpPlaneOrCloud) and !keybinds.isPressed(KeybindID::MoveDownPlaneOrCloud) and player.getPosition().y > -310)
	{
		currentVelocity.y = -900;
	}
	else if (keybinds.isPressed(KeybindID::MoveDownPlaneOrCloud) and !keybinds.isPressed(KeybindID::MoveUpPlaneOrCloud) and player.getPosition().y < 1273.f)
	{
		currentVelocity.y = 900;
	}
	else
	{
		currentVelocity.y = 0;
	}
}

void Helicopter::animate(const float deltaTime)
{
	animation.play(player, deltaTime);
}

void Helicopter::setPositionOfArm()
{
	arm.setPosition(player.getPosition() + sf::Vector2f(350.f, 95.f));
}

void Helicopter::setCurrentWeapon()
{
	
}

void Helicopter::handleDrinkingPotions()
{

}

void Helicopter::setRotationOfArm(const sf::Vector2f& MousePosition)
{
	sf::Vector2f distanceBetweenMouseAndArm = arm.getPosition() + pointOfArmRotation - MousePosition;
	float distance = sqrt(pow(distanceBetweenMouseAndArm.x, 2) + pow(distanceBetweenMouseAndArm.y, 2));
	float angle = (asin(distanceBetweenMouseAndArm.y / distance) * 180.0) / M_PI;

	if (MousePosition.x > arm.getPosition().x)
	{
		arm.setRotation(-angle);
	}
	else
	{
		arm.setRotation(-180 + angle);
	}
	setPositionOfWeapon();
}


void Helicopter::setScaleOfPlayer(const sf::Vector2f& MousePosition)
{
}


