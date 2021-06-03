#include "pch.h"
#include "ProjectileOfBoss.h"

ProjectileOfBoss::ProjectileOfBoss(const sf::Vector2f& Position,
    const sf::Vector2f& Velocity, const int Damage,
    const sf::Texture& Texture, float distanceOfErase)
    : EnemyProjectile(Position, Velocity, Damage, Texture,
        Animation(1, 1, sf::Vector2i(84, 84), 4, 0.05f), Hitbox(Position, sf::Vector2f(24.0066f, 84.0337f), sf::Vector2f(-12.0068f, -41.9955f)), false)
{
    this->distanceOfErase = distanceOfErase;
    hasAnimation = true;
    projectile.setOrigin(84.f / 2.f, 84.f / 2.f);
    accelerationOfFalling = 0.f;
    animation.setFrame(projectile, 1);

    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(42.021f, 77.9577f), sf::Vector2f(-21.0143f, -38.9932f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(53.9967f, 72.023f), sf::Vector2f(-26.9991f, -36.0262f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(71.995f, 54.0368f), sf::Vector2f(-35.9904f, -27.0485f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(78.011f, 41.998f), sf::Vector2f(-39.0035f, -20.9921f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(83.9586f, 23.9845f), sf::Vector2f(-42.0175f, -11.9958f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(0.0422363f, 0.0134888f), sf::Vector2f(43.7693f, -12.3135f)));

}

ProjectileOfBoss::~ProjectileOfBoss()
{
}

void ProjectileOfBoss::addEffects(std::vector<std::unique_ptr< Effect> >& effects, const Resources& resources)
{
}
