#include "pch.h"
#include "Laser.h"


Laser::Laser(const sf::Vector2f& Position,
    const sf::Vector2f& Velocity, const int Damage,
    const sf::Texture& Texture)
    : EnemyProjectile(Position, Velocity, Damage, Texture,
        Animation(1, 1, sf::Vector2i(100, 150), 2, 0.05f), Hitbox(Position, sf::Vector2f(3700.f, 150.f), sf::Vector2f(0.f, -150 / 2.f)), false)
{

    hasAnimation = false;
    projectile.setTextureRect(sf::IntRect(0, 0, 3700, 150));
    projectile.setOrigin(0, 150 / 2.f);
    accelerationOfFalling = 0.f;
}

Laser::~Laser()
{
}

void Laser::addEffects(std::vector<std::unique_ptr< Effect> >& effects, const Resources& resources)
{
}
