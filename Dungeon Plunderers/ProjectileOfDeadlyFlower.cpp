#include "pch.h"
#include "ProjectileOfDeadlyFlower.h"


ProjectileOfDeadlyFlower::ProjectileOfDeadlyFlower(const sf::Vector2f& Position,
	const sf::Vector2f& Velocity, const int Damage,
	const sf::Texture& Texture)

	: EnemyProjectile(Position, Velocity, Damage, Texture,
		Animation(1, 1, sf::Vector2i(90, 63), 12, 0.01f), Hitbox(Position, sf::Vector2f(13.7166f, 63.1369f), sf::Vector2f(1.38216f, -0.182159f)), false)
{
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(6.05145f, 58.1949f), sf::Vector2f(15.0988f, 1.93585f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(7.96776f, 54.0597f), sf::Vector2f(21.0494f, 3.85214f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(8.27032f, 47.1005f), sf::Vector2f(29.0172f, 6.87787f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(10.3883f, 41.9568f), sf::Vector2f(37.1866f, 10.0045f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(7.96776f, 36.2079f), sf::Vector2f(47.2724f, 13.7362f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(7.76605f, 27.635f), sf::Vector2f(55.1393f, 17.1654f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(8.47205f, 21.7852f), sf::Vector2f(62.8044f, 19.9894f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(6.05145f, 16.0364f), sf::Vector2f(71.0748f, 23.0151f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(5.14374f, 12.5063f), sf::Vector2f(76.9245f, 24.6288f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(4.99173f, 8.07982f), sf::Vector2f(82.0294f, 26.9718f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(2.94006f, 4.01877f), sf::Vector2f(87.0634f, 28.9601f)));

    animation.setFrame(projectile, 1);

    accelerationOfFalling = 100.f;
}

ProjectileOfDeadlyFlower::~ProjectileOfDeadlyFlower()
{
}

void ProjectileOfDeadlyFlower::addEffects(std::vector<std::unique_ptr< Effect> >& effects, const Resources& resources)
{
}
