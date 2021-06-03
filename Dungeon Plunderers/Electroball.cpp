#include "pch.h"
#include "Electroball.h"


Electroball::Electroball(const sf::Vector2f& Position,
    const sf::Vector2f& Velocity, const int Damage,
    const sf::Texture& Texture)
    : PlayerProjectile(Position, Velocity, Damage, Texture,
        Animation(1, 1, sf::Vector2i(62, 57), 10, 0.05f), Hitbox(Position, sf::Vector2f(8.00266f, 32.0412f), sf::Vector2f(3.48335f, -13.5182f)), true)
{
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(13.9866f, 30.0506f), sf::Vector2f(0.52742f, -12.5229f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(18.024f, 28.0217f), sf::Vector2f(-1.49126f, -11.5276f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(21.9893f, 23.9639f), sf::Vector2f(-3.47391f, -9.46046f)));

    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(25.9545f, 19.9827f), sf::Vector2f(-5.45654f, -7.46985f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(27.9732f, 18.0303f), sf::Vector2f(-6.46588f, -6.47455f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(29.9919f, 13.9726f), sf::Vector2f(-7.47522f, -4.48393f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(31.9745f, 8.07729f), sf::Vector2f(-8.44852f, -1.5363f)));

    hasAnimation = true;
    projectile.setOrigin(20.5f, 30.5f);
    accelerationOfFalling = 0.f;
    animation.setFrame(projectile, 1);
}

Electroball::~Electroball()
{
}

void Electroball::addEffects(std::vector<std::unique_ptr< Effect> >& effects, const Resources& resources)
{
}
