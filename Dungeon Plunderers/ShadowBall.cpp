#include "pch.h"
#include "ShadowBall.h"

ShadowBall::ShadowBall(const sf::Vector2f& Position,
    const sf::Vector2f& Velocity, const int Damage,
    const sf::Texture& Texture)
    : PlayerProjectile(Position, Velocity, Damage, Texture,
        Animation(1, 1, sf::Vector2i(68, 68), 4, 0.05f), Hitbox(Position, sf::Vector2f(8.00266f, 32.0412f), sf::Vector2f(3.48335f, -13.5182f)), true)
{

    hasAnimation = true;
    projectile.setOrigin(33.f, 33.f);
    accelerationOfFalling = 0.f;
    animation.setFrame(projectile, 1);
}

ShadowBall::~ShadowBall()
{
}

void ShadowBall::addEffects(std::vector<std::unique_ptr< Effect> >& effects, const Resources& resources)
{
}
