#include "pch.h"
#include "Fireball.h"


Fireball::Fireball(const sf::Vector2f& Position,
    const sf::Vector2f& Velocity, const int Damage,
    const sf::Texture& Texture, const float rotation)
    : PlayerProjectile(Position, Velocity, Damage, Texture,
        Animation(1, 1, sf::Vector2i(53 * 2, 48 * 2), 5, 0.05f), Hitbox(Position, sf::Vector2f(35.5102f, 86.0126f), sf::Vector2f(0.f, 0.f), sf::Vector2f(-16.5265f, 20.0592)), true)
{
    projectile.setOrigin(36, 24);
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(35.5102f, 86.0126f), sf::Vector2f(0.f, 0.f), sf::Vector2f(-16.5265f, 20.0592)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(5.98485f, 80.0806f), sf::Vector2f(0.f, 0.f), sf::Vector2f(-52.0367f, 18.0466)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(3.98993f, 68.2169f), sf::Vector2f(0.f, 0.f), sf::Vector2f(-57.9975f, 12.1147)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(1.96112f, 60.0017f), sf::Vector2f(0.f, 0.f), sf::Vector2f(-62.0254f, 8.00919)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(2.00195f, 49.9913f), sf::Vector2f(0.f, 0.f), sf::Vector2f(-63.9667f, 3.94287)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(2.04285f, 38.0076f), sf::Vector2f(0.f, 0.f), sf::Vector2f(-65.9687f, -1.9787)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(1.96112f, 18.0059f), sf::Vector2f(0.f, 0.f), sf::Vector2f(-68.0524f, -12.0012)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(18.0756f, 4.09583f), sf::Vector2f(0.f, 0.f), sf::Vector2f(-27.8964f, -65.9293)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(4.14471f, 2.20074f), sf::Vector2f(0.f, 0.f), sf::Vector2f(-45.8569f, -65.9293)));


    projectile.setRotation(rotation);
    hitboxComponent.setRotationOfAllHitboxes(rotation);
    hitboxComponent.setScaleOfAllHitboxes(projectile.getScale());

    accelerationOfFalling = 0.f;
    animation.setFrame(projectile, 1);
}

Fireball::~Fireball()
{
}

void Fireball::addEffects(std::vector<std::unique_ptr< Effect> >& effects, const Resources& resources)
{
    effects.emplace_back(std::make_unique<FireExplosion>(projectile.getPosition(), resources[TextureID::FireExplosion]));
}
