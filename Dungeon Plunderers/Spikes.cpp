#include "pch.h"
#include "Spikes.h"

Spikes::Spikes(const sf::Vector2f& Position, const Resources& resources, SpikeType spikeType)
	:Enemy(Position, resources[TextureID::Spikes], resources,
		Animation(1, 1, sf::Vector2i(50, 50), 8, 0.05), sf::Vector2f(0.f,0.f),
		100, 30, false),
	hide(false),
	startAnimation(false),
	timeSinceHidden(0),
	timeToStartHiding(0)
{
	if (spikeType == SpikeType::basic)
	{
		name = EnemyType::spikes;
		animation.setFrame(enemy, 8);
		numberOfStartFrame = 3;
	}
	else
	{
		if (spikeType == SpikeType::showingAfterDamage)
		{
			numberOfStartFrame = 1;
			animation.setFrame(enemy, 1);
			name = EnemyType::showingAfterDamageSpikes;

		}
		else
		{
			numberOfStartFrame = 3;
			animation.setFrame(enemy, 3);
			name = EnemyType::hidingSpikes;
		}
	}
	isMortal = false;

	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(46.0693f, 7.97604f), sf::Vector2f(1.94141f, 42.0175f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(37.994f, 12.0128f), sf::Vector2f(6.00122f, 30.0313f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(26.0476f, 12.0368f), sf::Vector2f(11.953f, 18.0051f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(13.9843f, 12.1038f), sf::Vector2f(18.0231f, 5.99902f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(5.99327f, 4.15369f), sf::Vector2f(21.9975f, 2.0051f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(1.99776f, 2.00986f), sf::Vector2f(23.9953f, -0.00476074f)));
	
	base.addHitbox(Hitbox(Position, sf::Vector2f(15, 2), sf::Vector2f(0.f, 52.f)));
	base.addHitbox(Hitbox(Position, sf::Vector2f(20, 2), sf::Vector2f(15.f, 52.f)));
	base.addHitbox(Hitbox(Position, sf::Vector2f(15, 2), sf::Vector2f(35.f, 52.f)));
}

Spikes::~Spikes()
{
}

void Spikes::playAnimation(const float deltaTime)
{
	timeToStartHiding += deltaTime;
	if (name == EnemyType::showingAfterDamageSpikes)
	{
		if (wasDamageDealtToPlayer)
		{
			startAnimation = true;
		}
	}
	if (name == EnemyType::hidingSpikes)
	{
		if(timeSinceHidden > 1.f)
			startAnimation = true;

		if (!startAnimation)
			timeSinceHidden += deltaTime;
	}

	if (startAnimation)
	{
		if (!hide)
		{
			animation.setTimeOfFrameChange(0.01);
			if (animation.getNumberOfCurrentFrame() != 8)
				animation.play(enemy, deltaTime);
			else
			{
				hide = true;
				animation.setTimeOfFrameChange(0.07);
			}

			timeToStartHiding = 0;
		}
		else if(timeToStartHiding > 0.3)
		{
			if (animation.getNumberOfCurrentFrame() != numberOfStartFrame)
				animation.playBackwards(enemy, deltaTime);
			else
			{
				startAnimation = false;
				hide = false;
				timeSinceHidden = 0.f;
			}
		}
	}
	
}

void Spikes::attack(std::vector<std::unique_ptr<EnemyProjectile>>& Projectiles, const sf::Vector2f& PlayerPosition, const float deltaTime)
{
	matchHitboxesToAnimation();
	updatePositionOfHitboxes();
}

void Spikes::updateScale(const float PositionXOfPlayer)
{
}


void Spikes::matchHitboxesToAnimation()
{
	switch (animation.getNumberOfCurrentFrame())
	{
	case 8:
		hitboxComponent.setHitbox(0, sf::Vector2f(46.0693f, 7.97604f), sf::Vector2f(1.94141f, 42.0175f));
		hitboxComponent.setHitbox(1, sf::Vector2f(37.994f, 12.0128f), sf::Vector2f(6.00122f, 30.0313f));
		hitboxComponent.setHitbox(2, sf::Vector2f(26.0476f, 12.0368f), sf::Vector2f(11.953f, 18.0051f));
		hitboxComponent.setHitbox(3, sf::Vector2f(13.9843f, 12.1038f), sf::Vector2f(18.0231f, 5.99902f));
		hitboxComponent.setHitbox(4, sf::Vector2f(5.99327f, 4.15369f), sf::Vector2f(21.9975f, 2.0051f));
		hitboxComponent.setHitbox(5, sf::Vector2f(1.99776f, 2.00986f), sf::Vector2f(23.9953f, -0.00476074f));
		break;

	case 7:
		hitboxComponent.setHitbox(0, sf::Vector2f(37.9967f, 5.98749f), sf::Vector2f(5.99753f, 43.9974f));
		hitboxComponent.setHitbox(1, sf::Vector2f(30.0286f, 12.0478f), sf::Vector2f(9.98233f, 32.0125f));
		hitboxComponent.setHitbox(2, sf::Vector2f(17.998f, 13.0637f), sf::Vector2f(16.0063f, 20.0139f));
		hitboxComponent.setHitbox(3, sf::Vector2f(9.98999f, 4.01309f), sf::Vector2f(20.0121f, 16.0269f));
		hitboxComponent.setHitbox(4, sf::Vector2f(5.9678f, 4.03294f), sf::Vector2f(22.0066f, 12.0017f));
		hitboxComponent.setHitbox(5, sf::Vector2f(2.00174f, 2.06615f), sf::Vector2f(23.996f, 10.0058f));

		break;

	case 6:
		hitboxComponent.setHitbox(0, sf::Vector2f(25.9809f, 7.99721f), sf::Vector2f(12.0034f, 42.016f));
		hitboxComponent.setHitbox(1, sf::Vector2f(18.0109f, 8.12906f), sf::Vector2f(15.9884f, 34.0065f));
		hitboxComponent.setHitbox(2, sf::Vector2f(10.0109f, 4.06998f), sf::Vector2f(19.9736f, 25.956f));
		hitboxComponent.setHitbox(3, sf::Vector2f(1.99002f, 2.00763f), sf::Vector2f(24.0108f, 20.0037f));
		hitboxComponent.setHitbox(4, sf::Vector2f(6.00323f, 4.01526f), sf::Vector2f(21.9959f, 21.9937f));
		hitboxComponent.setHitbox(5, sf::Vector2f(14.0306f, 4.12689f), sf::Vector2f(17.9641f, 29.9831f));

		break;

	case 5:
		hitboxComponent.setHitbox(0, sf::Vector2f(17.9978f, 5.97266f), sf::Vector2f(15.9974f, 43.9993f));
		hitboxComponent.setHitbox(1, sf::Vector2f(13.9958f, 4.11163f), sf::Vector2f(17.9918f, 40.0127f));
		hitboxComponent.setHitbox(2, sf::Vector2f(10.0093f, 4.47711f), sf::Vector2f(19.9993f, 35.9924f));
		hitboxComponent.setHitbox(3, sf::Vector2f(6.02277f, 4.02026f), sf::Vector2f(21.9783f, 32.0026f));
		hitboxComponent.setHitbox(4, sf::Vector2f(1.97894f, 2.1015f), sf::Vector2f(23.9858f, 29.9925f));
		hitboxComponent.setHitbox(5, sf::Vector2f(21.9975f, 2.07104f), sf::Vector2f(14.0052f, 47.9619f));
		break;

	case 4:
		hitboxComponent.setHitbox(0, sf::Vector2f(10.0226f, 4.00246f), sf::Vector2f(19.9827f, 46.0035f));
		hitboxComponent.setHitbox(1, sf::Vector2f(6.00159f, 4.14267f), sf::Vector2f(21.9991f, 42.001f));
		hitboxComponent.setHitbox(2, sf::Vector2f(1.99255f, 2.14143f), sf::Vector2f(24.0037f, 39.9998f));
		for(int i = 3; i < 6; i++)
			hitboxComponent.setHitbox(i, sf::Vector2f(0.f, 0.f), sf::Vector2f(-10000.f, -1000.f));


		break;

	case 3:
		for (int i = 0; i < 6; i++)
			hitboxComponent.setHitbox(i, sf::Vector2f(0.f, 0.f), sf::Vector2f(-10000.f, -1000.f));
		break;
	case 2:
		hitboxComponent.setHitbox(0, sf::Vector2f(38.0164f, 1.99886f), sf::Vector2f(5.99463f, 48.0054f));
		hitboxComponent.setHitbox(1, sf::Vector2f(34.0095f, 2.02625f), sf::Vector2f(7.98792f, 45.9792f));
		hitboxComponent.setHitbox(2, sf::Vector2f(30.0645f, 2.16315f), sf::Vector2f(9.99915f, 43.9803f));
		hitboxComponent.setHitbox(3, sf::Vector2f(17.9975f, 3.9977f), sf::Vector2f(16.0068f, 39.9826f));
		for (int i = 4; i < 6; i++)
			hitboxComponent.setHitbox(i, sf::Vector2f(0.f, 0.f), sf::Vector2f(-10000.f, -1000.f));
		break;
	case 1:
		hitboxComponent.setHitbox(0, sf::Vector2f(38.0024f, 2.01511f), sf::Vector2f(5.99872f, 47.9916f));
		hitboxComponent.setHitbox(1, sf::Vector2f(34.0022f, 2.01511f), sf::Vector2f(7.99884f, 46.0038f));
		hitboxComponent.setHitbox(2, sf::Vector2f(30.0276f, 2.06956f), sf::Vector2f(9.99896f, 43.9614f));
		hitboxComponent.setHitbox(3, sf::Vector2f(18.0012f, 2.01511f), sf::Vector2f(15.9737f, 42.0008f));
		for (int i = 4; i < 6; i++)
			hitboxComponent.setHitbox(i, sf::Vector2f(0.f, 0.f), sf::Vector2f(-10000.f, -1000.f));
		break;
	default:
		break;
	}
}

void Spikes::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(enemy, states);
}
