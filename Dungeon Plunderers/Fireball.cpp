#include "pch.h"
#include "Fireball.h"


Fireball::Fireball(const sf::Vector2f& Position,
    const sf::Vector2f& Velocity, const int Damage,
    const sf::Texture& Texture, const float rotation)
    : PlayerProjectile(Position, Velocity, Damage, Texture,
        Animation(1, 1, sf::Vector2i(53 * 2, 48 * 2), 5, 0.05f), Hitbox(Position, sf::Vector2f(35.5102f, 86.0126f), sf::Vector2f(0.f, 0.f), sf::Vector2f(-16.5265f, 20.0592)), true)
{
    //hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(43.2852f, 95.9657f), sf::Vector2f(0.f, 0.f), sf::Vector2f(-26.1299f, 23.943)));

    /*
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
    */
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
