#include "pch.h"
#include "Warning.h"


Warning::Warning(const sf::Vector2f& Position,
    const sf::Vector2f& Velocity, const int Damage,
    const sf::Texture& Texture)
    : EnemyProjectile(Position, Velocity, Damage, Texture,
        Animation(1, 1, sf::Vector2i(65, 145), 4, 0.05f), Hitbox(Position, sf::Vector2f(8.00266f, 32.0412f), sf::Vector2f(3.48335f, -13.5182f)), false)
{
    hasAnimation = true;
    projectile.setOrigin(0, 116 / 2.f);
    accelerationOfFalling = 0.f;
    animation.setFrame(projectile, 1);
}

Warning::~Warning()
{
}

void Warning::addEffects(std::vector<std::unique_ptr< Effect> >& effects, const Resources& resources)
{
 
}
