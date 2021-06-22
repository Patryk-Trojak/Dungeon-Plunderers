#include "pch.h"
#include "RockProjectile.h"

RockProjectile::RockProjectile(const sf::Vector2f& Position,
    const sf::Vector2f& Velocity, const int Damage,
    const sf::Texture& Texture)

    : EnemyProjectile(Position, Velocity, Damage, Texture,
        Animation(1, 1, sf::Vector2i(66, 28), 1, 1.f), Hitbox(Position, sf::Vector2f(13.7166f, 63.1369f), sf::Vector2f(1.38216f, -0.182159f)), false)
{
    hasAnimation = false;
    animation.setFrame(projectile, 1);
    accelerationOfFalling = 100.f;

    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(48.f, 22.f), sf::Vector2f(4.f, 2.f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(58.f, 16.f), sf::Vector2f(2.f, 6.f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(66.f, 8.f), sf::Vector2f(0.f, 12.f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(26.f, 28.f), sf::Vector2f(14.f, 0.f)));
    setPositionOfHitboxes();
}

RockProjectile::~RockProjectile()
{
}

void RockProjectile::addEffects(std::vector<std::unique_ptr< Effect> >& effects, const Resources& resources)
{
}
