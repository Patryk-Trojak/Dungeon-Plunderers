#include "pch.h"
#include "DeadlyFlower.h"


DeadlyFlower::DeadlyFlower(const sf::Vector2f& Position, const Resources& resources, const sf::Vector2f& initialScale)
	:RangedEnemy(Position, resources[TextureID::DeadlyFlower], resources[TextureID::ProjectileOfDeadlyFlower], resources,
		Animation(1, 1, sf::Vector2i(174, 206), 31, 0.07f), sf::Vector2f(-20.f, -30.f),
		200, 20,
		1.f, 30,
		false),
	canShoot(true)
{
	name = EnemyType::deadlyFlower;
	enemy.setOrigin(33.f, 0.f);
	this->initialScale = initialScale;

	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(42.0048f, 42.1977f)* initialScale.x, sf::Vector2f(-21.0032f, 163.809f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(49.9075f, 7.98862f) * initialScale.x, sf::Vector2f(-24.9546f, 155.921f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(49.9075f, 7.98862f) * initialScale.x, sf::Vector2f(-24.9546f, 155.921f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(14.0298f, 6.01294f) * initialScale.x, sf::Vector2f(-8.99692f, 149.994f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(13.9157f, 11.94f) * initialScale.x, sf::Vector2f(-6.93025f, 138.068f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(13.9157f, 10.1361f) * initialScale.x, sf::Vector2f(-5.04047f, 127.932f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(13.9439f, 8.16043f) * initialScale.x, sf::Vector2f(-2.983f, 119.943f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(13.9936f, 8.04163f) * initialScale.x, sf::Vector2f(-1.004f, 111.985f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(14.0224f, 3.992f) * initialScale.x, sf::Vector2f(1.01361f, 108.011f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(13.9504f, 3.992f) * initialScale.x, sf::Vector2f(3.03043f, 103.994f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(11.555f, 4.33313f) * initialScale.x, sf::Vector2f(4.98178f, 99.7501f))); //10
	

	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(42.0048f, 42.1977f) * initialScale.x, sf::Vector2f(-21.0032f, 163.809f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(49.9075f, 7.98862f) * initialScale.x, sf::Vector2f(-24.9546f, 155.921f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(14.0298f, 6.01294f) * initialScale.x, sf::Vector2f(-8.99692f, 149.994f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(13.9157f, 11.94f) * initialScale.x, sf::Vector2f(-6.93025f, 138.068f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(13.9157f, 10.1361f) * initialScale.x, sf::Vector2f(-5.04047f, 127.932f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(13.9439f, 8.16043f) * initialScale.x, sf::Vector2f(-2.983f, 119.943f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(13.9936f, 8.04163f) * initialScale.x, sf::Vector2f(-1.004f, 111.985f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(14.0224f, 3.992f) * initialScale.x, sf::Vector2f(1.01361f, 108.011f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(13.9504f, 3.992f) * initialScale.x, sf::Vector2f(3.03043f, 103.994f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(11.555f, 4.33313f) * initialScale.x, sf::Vector2f(4.98178f, 99.7501f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(13.9504f, 3.992f) * initialScale.x, sf::Vector2f(3.03043f, 103.994f))); //21

	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(13.9504f, 3.992f) * initialScale.x, sf::Vector2f(3.03043f, 103.994f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(13.9504f, 3.992f) * initialScale.x, sf::Vector2f(3.03043f, 103.994f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(13.9504f, 3.992f) * initialScale.x, sf::Vector2f(3.03043f, 103.994f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(13.9504f, 3.992f) * initialScale.x, sf::Vector2f(3.03043f, 103.994f)));

	base.addHitbox(Hitbox(Position, sf::Vector2f(40, 5), sf::Vector2f(-20.f, 206))); 

	fire.setOrigin(sf::Vector2f(13.5f, -15.f));
	fire.setScale(sf::Vector2f(3.f, 3.f));
}

DeadlyFlower::~DeadlyFlower()
{
}

void DeadlyFlower::attack(std::vector<std::unique_ptr<EnemyProjectile> >& Projectiles, const sf::Vector2f & PlayerPosition, const float deltaTime)
{
	timerOfShooting += deltaTime;
	if (animation.getNumberOfCurrentFrame() == 24 and canShoot)
	{
		if (enemy.getScale().x > 0)
		{
			Projectiles.emplace_back(std::make_unique<ProjectileOfDeadlyFlower>(enemy.getPosition() + sf::Vector2f(120, 25), sf::Vector2f(900.f * enemy.getScale().x, 0.f), 20, textureOfProjectile));
		}
		else
		{
			Projectiles.emplace_back(std::make_unique<ProjectileOfDeadlyFlower>(enemy.getPosition() + sf::Vector2f(-120, 25), sf::Vector2f(900.f * enemy.getScale().x, 0.f), 20, textureOfProjectile));
		}
		timerOfShooting = 0;
		canShoot = false;
	}
	if (animation.getNumberOfCurrentFrame() == 1)
		canShoot = true;
}

void DeadlyFlower::matchHitboxesToAnimation()
{
	if (animation.wasFrameChanged())
	{
		if (animation.getNumberOfCurrentFrame() >= 19)
		{
			hitboxComponent.setHitbox(2, sf::Vector2f(14.0034f, 6.1221f) * initialScale.x, sf::Vector2f(-9.05171f, 150.002f));
			hitboxComponent.setHitbox(3, sf::Vector2f(13.9682f, 12.0331f) * initialScale.x, sf::Vector2f(-7.01102f, 138.004f));
			hitboxComponent.setHitbox(4, sf::Vector2f(14.0034f, 10.0979f) * initialScale.x, sf::Vector2f(-5.00169f, 127.965f));
			hitboxComponent.setHitbox(5, sf::Vector2f(14.0034f, 8.02203f) * initialScale.x, sf::Vector2f(-2.99236f, 119.97f));
			hitboxComponent.setHitbox(6, sf::Vector2f(14.0034f, 8.02203f) * initialScale.x, sf::Vector2f(-0.979218f, 112.015f));
			hitboxComponent.setHitbox(7, sf::Vector2f(14.0386f, 4.0462f) * initialScale.x, sf::Vector2f(0.991104f, 108.004f));
			hitboxComponent.setHitbox(8, sf::Vector2f(14.0034f, 4.01102f) * initialScale.x, sf::Vector2f(2.99661f, 103.993f));
		}
		if (animation.getNumberOfCurrentFrame() >= 20 and animation.getNumberOfCurrentFrame() <= 30)
		{
			hitboxComponent.setHitbox(9, sf::Vector2f(124.613f, 49.0262f) * initialScale.x, sf::Vector2f(-23.2052f, 35.929f));
			hitboxComponent.setHitbox(10, sf::Vector2f(110.415f, 6.18155f) * initialScale.x, sf::Vector2f(-16.4631f, 84.742f));
			hitboxComponent.setHitbox(11, sf::Vector2f(94.8549f, 6.18158f) * initialScale.x, sf::Vector2f(-8.3631f, 90.2841f));
			hitboxComponent.setHitbox(12, sf::Vector2f(77.163f, 4.04999f) * initialScale.x, sf::Vector2f(0.163147f, 96.2525f));
			hitboxComponent.setHitbox(13, sf::Vector2f(55.2077f, 3.83682f) * initialScale.x, sf::Vector2f(12.7394f, 99.8762f));
			hitboxComponent.setHitbox(14, sf::Vector2f(105.513f, 5.9684f) * initialScale.x, sf::Vector2f(-13.2657f, 29.9606f));
			hitboxComponent.setHitbox(15, sf::Vector2f(93.7892f, 6.18156f) * initialScale.x, sf::Vector2f(-7.5105f, 24.4185f));
			hitboxComponent.setHitbox(16, sf::Vector2f(75.0313f, 5.54208f) * initialScale.x, sf::Vector2f(0.802673f, 19.3028f));
			hitboxComponent.setHitbox(17, sf::Vector2f(33.892f, 3.83684f) * initialScale.x, sf::Vector2f(20.6263f, 15.8922f));
			hitboxComponent.setHitbox(18, sf::Vector2f(7.03418f, 34.9578f) * initialScale.x, sf::Vector2f(-29.6237f, 42.1106f));
			hitboxComponent.setHitbox(19, sf::Vector2f(4.68945f, 9.37891f) * initialScale.x, sf::Vector2f(-34.1f, 55.1132f));
			hitboxComponent.setHitbox(20, sf::Vector2f(33.8521f, 4.88931f) * initialScale.x, sf::Vector2f(21.1655f, 103.588f));
			for (int i = 21; i <= 25; i++)
				hitboxComponent.hitboxes[i].setHitbox(sf::Vector2f(0.f, 0.f), sf::Vector2f(-10000.f, -1000.f));
		}
		switch (animation.getNumberOfCurrentFrame())
		{
		case 1:
		case 2:
		case 3:
		case 7:
		case 8:
		case 9:
		case 13:
		case 14:
		case 15:
			hitboxComponent.setHitbox(2, sf::Vector2f(14.0034f, 6.1221f) * initialScale.x, sf::Vector2f(-9.05171f, 150.002f));
			hitboxComponent.setHitbox(3, sf::Vector2f(13.9682f, 12.0331f) * initialScale.x, sf::Vector2f(-7.01102f, 138.004f));
			hitboxComponent.setHitbox(4, sf::Vector2f(14.0034f, 10.0979f) * initialScale.x, sf::Vector2f(-5.00169f, 127.965f));
			hitboxComponent.setHitbox(5, sf::Vector2f(14.0034f, 8.02203f) * initialScale.x, sf::Vector2f(-2.99236f, 119.97f));
			hitboxComponent.setHitbox(6, sf::Vector2f(14.0034f, 8.02203f) * initialScale.x, sf::Vector2f(-0.979218f, 112.015f));
			hitboxComponent.setHitbox(7, sf::Vector2f(14.0386f, 4.0462f) * initialScale.x, sf::Vector2f(0.991104f, 108.004f));
			hitboxComponent.setHitbox(8, sf::Vector2f(14.0034f, 4.01102f) * initialScale.x, sf::Vector2f(2.99661f, 103.993f));
			hitboxComponent.setHitbox(9, sf::Vector2f(121.997f, 59.9094f) * initialScale.x, sf::Vector2f(-20.8654f, 21.9711f));
			hitboxComponent.setHitbox(10, sf::Vector2f(118.003f, 8.16946f) * initialScale.x, sf::Vector2f(-20.1393f, 81.699f));
			hitboxComponent.setHitbox(11, sf::Vector2f(101.664f, 6.71713f) * initialScale.x, sf::Vector2f(-12.8775f, 89.5054f));
			hitboxComponent.setHitbox(12, sf::Vector2f(82.4209f, 5.80942f) * initialScale.x, sf::Vector2f(-3.25571f, 95.8594f));
			hitboxComponent.setHitbox(13, sf::Vector2f(49.3799f, 4.17551f) * initialScale.x, sf::Vector2f(13.6279f, 100.943f));
			hitboxComponent.setHitbox(14, sf::Vector2f(15.6128f, 4.17551f) * initialScale.x, sf::Vector2f(29.9668f, 104.392f));
			hitboxComponent.setHitbox(15, sf::Vector2f(6.89867f, 57.9124f) * initialScale.x, sf::Vector2f(-27.7641f, 23.9681f));
			hitboxComponent.setHitbox(16, sf::Vector2f(4.72012f, 37.398f) * initialScale.x, sf::Vector2f(-32.3027f, 35.95f));
			hitboxComponent.setHitbox(17, sf::Vector2f(114.373f, 6.89867f) * initialScale.x, sf::Vector2f(-19.3527f, 15.2919f));
			hitboxComponent.setHitbox(18, sf::Vector2f(98.3967f, 7.44328f) * initialScale.x, sf::Vector2f(-11.0017f, 7.84865f));
			hitboxComponent.setHitbox(19, sf::Vector2f(76.2484f, 7.15404f) * initialScale.x, sf::Vector2f(0.79863f, 0.949982f));
			for(int i = 20; i <= 25; i++)
				hitboxComponent.hitboxes[i].setHitbox(sf::Vector2f(0.f, 0.f), sf::Vector2f(-10000.f, -1000.f));

			break;
		case 4:
		case 5:
		case 6:
		case 10:
		case 11:
		case 12:
		case 16:
		case 17:
		case 18:
			hitboxComponent.setHitbox(2, sf::Vector2f(13.9612f, 5.99542f) * initialScale.x, sf::Vector2f(-8.99414f, 149.998f));
			hitboxComponent.setHitbox(3, sf::Vector2f(14.0173f, 10.0768f) * initialScale.x, sf::Vector2f(-7.00562f, 139.959f));
			hitboxComponent.setHitbox(4, sf::Vector2f(14.0173f, 10.0205f) * initialScale.x, sf::Vector2f(-4.98926f, 129.972f));
			hitboxComponent.setHitbox(5, sf::Vector2f(13.9612f, 7.9939f) * initialScale.x, sf::Vector2f(-2.98657f, 122.013f));
			hitboxComponent.setHitbox(6, sf::Vector2f(13.9893f, 8.05017f) * initialScale.x, sf::Vector2f(-0.988037f, 113.97f));
			hitboxComponent.setHitbox(7, sf::Vector2f(13.9612f, 3.96878f) * initialScale.x, sf::Vector2f(0.99707f, 109.997f));
			hitboxComponent.setHitbox(8, sf::Vector2f(14.0176f, 4.05322f) * initialScale.x, sf::Vector2f(2.99561f, 105.972f));
			hitboxComponent.setHitbox(9, sf::Vector2f(123.597f, 7.87718f) * initialScale.x, sf::Vector2f(-23.3308f, 19.9261f));
			hitboxComponent.setHitbox(10, sf::Vector2f(107.28f, 7.50209f) * initialScale.x, sf::Vector2f(-15.4536f, 12.6116f));
			hitboxComponent.setHitbox(11, sf::Vector2f(83.6482f, 6.75186f) * initialScale.x, sf::Vector2f(-3.26294f, 6.04727f));
			hitboxComponent.setHitbox(12, sf::Vector2f(50.5137f, 4.80167f) * initialScale.x, sf::Vector2f(12.8667f, 1.54602f));
			hitboxComponent.setHitbox(13, sf::Vector2f(117.407f, 6.18924f) * initialScale.x, sf::Vector2f(-20.1426f, 83.5062f));
			hitboxComponent.setHitbox(14, sf::Vector2f(105.592f, 6.37677f) * initialScale.x, sf::Vector2f(-14.7036f, 89.1328f));
			hitboxComponent.setHitbox(15, sf::Vector2f(89.8374f, 6.93942f) * initialScale.x, sf::Vector2f(-6.07617f, 95.1345f));
			hitboxComponent.setHitbox(16, sf::Vector2f(56.4531f, 4.87637f) * initialScale.x, sf::Vector2f(13.6169f, 101.136f));
			hitboxComponent.setHitbox(17, sf::Vector2f(33.5718f, 4.50125f) * initialScale.x, sf::Vector2f(21.6816f, 105.637f));
			hitboxComponent.setHitbox(18, sf::Vector2f(124.91f, 55.8905f) * initialScale.x, sf::Vector2f(-23.8936f, 27.8033f));
			hitboxComponent.setHitbox(19, sf::Vector2f(6.00171f, 52.7021f) * initialScale.x, sf::Vector2f(-29.7078f, 29.4913f));
			hitboxComponent.setHitbox(20, sf::Vector2f(3.56348f, 33.0092f) * initialScale.x, sf::Vector2f(-32.896f, 37.556f));
			for (int i = 21; i <= 25; i++)
				hitboxComponent.hitboxes[i].setHitbox(sf::Vector2f(0.f, 0.f), sf::Vector2f(-10000.f, -1000.f));
			break;
		case 19:
		case 31:
			hitboxComponent.setHitbox(9, sf::Vector2f(124.932f, 47.7772f) * initialScale.x, sf::Vector2f(-23.1789f, 34.9116f));
			hitboxComponent.setHitbox(10, sf::Vector2f(116.119f, 7.11246f) * initialScale.x, sf::Vector2f(-19.6226f, 82.5342f));
			hitboxComponent.setHitbox(11, sf::Vector2f(102.667f, 6.95782f) * initialScale.x, sf::Vector2f(-12.974f, 89.1828f));
			hitboxComponent.setHitbox(12, sf::Vector2f(83.6488f, 5.56628f) * initialScale.x, sf::Vector2f(-3.38763f, 95.986f));
			hitboxComponent.setHitbox(13, sf::Vector2f(49.7873f, 6.03012f) * initialScale.x, sf::Vector2f(13.4658f, 101.552f));
			hitboxComponent.setHitbox(14, sf::Vector2f(119.83f, 6.18475f) * initialScale.x, sf::Vector2f(-22.0965f, 28.7268f));
			hitboxComponent.setHitbox(15, sf::Vector2f(106.687f, 7.57632f) * initialScale.x, sf::Vector2f(-14.211f, 21.1505f));
			hitboxComponent.setHitbox(16, sf::Vector2f(89.3697f, 6.494f) * initialScale.x, sf::Vector2f(-6.94388f, 15.0662f));
			hitboxComponent.setHitbox(17, sf::Vector2f(61.2291f, 5.7209f) * initialScale.x, sf::Vector2f(7.5903f, 9.80916f));
			hitboxComponent.setHitbox(18, sf::Vector2f(5.25705f, 44.221f)* initialScale.x, sf::Vector2f(-28.2813f, 35.6305f));
			hitboxComponent.setHitbox(19, sf::Vector2f(5.10245f, 24.2751f)* initialScale.x, sf::Vector2f(-33.2291f, 45.8354f));
			for (int i = 20; i <= 25; i++)
				hitboxComponent.hitboxes[i].setHitbox(sf::Vector2f(0.f, 0.f), sf::Vector2f(-10000.f, -1000.f));
			break;

		case 23:
		case 27:
			hitboxComponent.setHitbox(21, sf::Vector2f(15.7695f, 34.1992f) * initialScale.x, sf::Vector2f(96.5503f, 39.7003f));
			for (int i = 22; i <= 25; i++)
				hitboxComponent.hitboxes[i].setHitbox(sf::Vector2f(0.f, 0.f), sf::Vector2f(-10000.f, -1000.f));
			break;
		case 24:
		case 25:
		case 26:
			hitboxComponent.setHitbox(21, sf::Vector2f(43.8047f, 34.0459f) * initialScale.x, sf::Vector2f(97.1404f, 39.9628f));
			hitboxComponent.setHitbox(22, sf::Vector2f(24.6567f, 8.15714f)* initialScale.x, sf::Vector2f(110.607f, 31.7674f));
			hitboxComponent.setHitbox(23, sf::Vector2f(6.02515f, 1.94658f)* initialScale.x, sf::Vector2f(120.896f, 29.9135f));
			hitboxComponent.setHitbox(24, sf::Vector2f(24.0087f, 7.98892f)* initialScale.x, sf::Vector2f(111.028f, 73.97f));
			hitboxComponent.setHitbox(25, sf::Vector2f(12.1113f, 4.10846f)* initialScale.x, sf::Vector2f(116.934f, 81.9301f));
			break;		
		}
	}
}
 
