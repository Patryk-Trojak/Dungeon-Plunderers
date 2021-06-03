#include "pch.h"
#include "ProjectileOfBoss2.h"


ProjectileOfBoss2::ProjectileOfBoss2(const sf::Vector2f& Position,
    const sf::Vector2f& Velocity, const int Damage,
    const sf::Texture& Texture, const float distanceOfErase)
    : EnemyProjectile(Position, Velocity, Damage, Texture,
        Animation(1, 1, sf::Vector2i(88, 88), 3, 0.05f), Hitbox(Position, sf::Vector2f(8.00266f, 32.0412f), sf::Vector2f(3.48335f, -13.5182f)), false)
{
    hasAnimation = true;
    projectile.setOrigin(88.f / 2.f, 88.f / 2.f);
    accelerationOfFalling = 0.f;
    animation.setFrame(projectile, 1);

    this->distanceOfErase = distanceOfErase;
}

ProjectileOfBoss2::~ProjectileOfBoss2()
{
}

void ProjectileOfBoss2::addEffects(std::vector<std::unique_ptr< Effect> >& effects, const Resources& resources)
{
}
