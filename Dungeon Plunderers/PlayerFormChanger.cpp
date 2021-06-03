#include "pch.h"
#include "PlayerFormChanger.h"

PlayerFormChanger::PlayerFormChanger(const sf::Vector2f& Position, const sf::Vector2f& initPosition, const Resources& resources, const WaysToChangePlayerForm& howChangeForm)
	:initPosition(initPosition),
	howChangeForm(howChangeForm)
{
	changer.setPosition(Position);
	if (howChangeForm == WaysToChangePlayerForm::StormtrooperToHelicopter)
	{
		hasAnimation = true;
		changer.setTexture(resources[TextureID::Helicopter]);
		animation = Animation(1, 1, sf::Vector2i(423, 141), 6, 0.05f);
		hitboxes.addHitbox(Hitbox(initPosition, sf::Vector2f(375.041f, 12.0725f), sf::Vector2f(5.99358f, 62.9836f)));
		hitboxes.addHitbox(Hitbox(initPosition, sf::Vector2f(320.961f, 21.0301f), sf::Vector2f(51.0047f, 59.9828f)));
		hitboxes.addHitbox(Hitbox(initPosition, sf::Vector2f(12.0069f, 59.8766f), sf::Vector2f(33.0486f, 17.9793f)));
		hitboxes.addHitbox(Hitbox(initPosition, sf::Vector2f(48.0644f, 23.991f), sf::Vector2f(15.0197f, 53.9176f)));
		hitboxes.addHitbox(Hitbox(initPosition, sf::Vector2f(39.1605f, 12.284f), sf::Vector2f(20.8732f, 41.8031f)));
		hitboxes.addHitbox(Hitbox(initPosition, sf::Vector2f(33.1422f, 6.51302f), sf::Vector2f(24.006f, 36.032f)));
		hitboxes.addHitbox(Hitbox(initPosition, sf::Vector2f(21.023f, 12.0367f), sf::Vector2f(30.0244f, 23.9129f)));
		hitboxes.addHitbox(Hitbox(initPosition, sf::Vector2f(393.065f, 5.96204f), sf::Vector2f(-0.0761871f, 68.981f)));
		hitboxes.addHitbox(Hitbox(initPosition, sf::Vector2f(222.06f, 12.0029f), sf::Vector2f(189.008f, 81.0208f)));
		hitboxes.addHitbox(Hitbox(initPosition, sf::Vector2f(213.073f, 12.0084f), sf::Vector2f(197.996f, 92.9882f)));
		hitboxes.addHitbox(Hitbox(initPosition, sf::Vector2f(149.917f, 9.0275f), sf::Vector2f(210.126f, 104.935f)));
		hitboxes.addHitbox(Hitbox(initPosition, sf::Vector2f(90.012f, 27.3685f), sf::Vector2f(240.044f, 113.681f)));
		hitboxes.addHitbox(Hitbox(initPosition, sf::Vector2f(137.907f, 9.12286f), sf::Vector2f(216.02f, 131.927f)));
		hitboxes.addHitbox(Hitbox(initPosition, sf::Vector2f(6.01855f, 8.92825f), sf::Vector2f(353.989f, 129.015f)));
		hitboxes.addHitbox(Hitbox(initPosition, sf::Vector2f(174.064f, 9.14998f), sf::Vector2f(189.03f, 50.9601f)));
		hitboxes.addHitbox(Hitbox(initPosition, sf::Vector2f(159.086f, 9.08615f), sf::Vector2f(194.978f, 41.9838f)));
		hitboxes.addHitbox(Hitbox(initPosition, sf::Vector2f(144.027f, 6.12914f), sf::Vector2f(201.022f, 35.9622f)));
		hitboxes.addHitbox(Hitbox(initPosition, sf::Vector2f(131.963f, 8.92487f), sf::Vector2f(207.032f, 27.0967f)));
		hitboxes.addHitbox(Hitbox(initPosition, sf::Vector2f(92.8547f, 6.49203f), sf::Vector2f(225.155f, 20.9018f)));
		hitboxes.addHitbox(Hitbox(initPosition, sf::Vector2f(51.1985f, 6.78712f), sf::Vector2f(246.007f, 14.8524f)));
		hitboxes.addHitbox(Hitbox(initPosition, sf::Vector2f(42.0074f, 33.1553f), sf::Vector2f(360.022f, 74.8627f)));

		hitboxes.addHitbox(Hitbox(initPosition, sf::Vector2f(6.06537f, 15.0634f), sf::Vector2f(410.964f, 86.8684f))); //21
		hitboxes.addHitbox(Hitbox(initPosition, sf::Vector2f(242.972f, 8.95033f), sf::Vector2f(162.024f, 0.020813f))); //22
		hitboxes.addHitbox(Hitbox(initPosition, sf::Vector2f(242.972f, 8.95033f), sf::Vector2f(162.024f, 0.020813f))); //23

		animation.setFrame(changer, 1);
	}
	else
	{
		hasAnimation = false;
		changer.setTexture(resources[TextureID::Cloud]);
		hitboxes.addHitbox(Hitbox(initPosition, sf::Vector2f(92.9366f, 39.0209f), sf::Vector2f(-38.9957f, 11.9787f)));
		hitboxes.addHitbox(Hitbox(initPosition, sf::Vector2f(108.069f, 30.0048f), sf::Vector2f(-45.0646f, 14.9952f)));
		hitboxes.addHitbox(Hitbox(initPosition, sf::Vector2f(111.006f, 24.0514f), sf::Vector2f(-66.0126f, 29.9636f)));
		hitboxes.addHitbox(Hitbox(initPosition, sf::Vector2f(120.01f, 18.1377f), sf::Vector2f(-50.9964f, 23.9892f)));
		hitboxes.addHitbox(Hitbox(initPosition, sf::Vector2f(129.012f, 9.01671f), sf::Vector2f(-72.0246f, 38.9963f)));
		hitboxes.addHitbox(Hitbox(initPosition, sf::Vector2f(2.97041f, 15.0181f), sf::Vector2f(-68.9912f, 35.9781f)));
		hitboxes.addHitbox(Hitbox(initPosition, sf::Vector2f(3.0629f, 6.12578f), sf::Vector2f(68.9616f, 32.9681f)));
	}
}

PlayerFormChanger::~PlayerFormChanger()
{
}

void PlayerFormChanger::backToInitPosition(const float deltaTime)
{
	velocity = initPosition - changer.getPosition();
	changer.move(velocity * deltaTime);
}

WaysToChangePlayerForm PlayerFormChanger::getHowChangeForm() const
{
	return howChangeForm;
}

void PlayerFormChanger::animate(const float deltaTime)
{
	if (hasAnimation)
	{
		if (abs(velocity.x + velocity.y) < 1)
		{
			animation.setTimeOfFrameChange(0.05 / abs(velocity.x + velocity.y));
		}
		else
			animation.setTimeOfFrameChange(0.05);

		if (abs(velocity.x + velocity.y) > 0.1)
			animation.play(changer, deltaTime);
		else
			animation.setFrame(changer, 1);
	}
}

sf::FloatRect PlayerFormChanger::getGlobalBoundsOfSprite() const
{
	return changer.getGlobalBounds();
}

sf::Vector2f PlayerFormChanger::getPosition() const
{
	return changer.getPosition();
}

void PlayerFormChanger::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(changer);
}
