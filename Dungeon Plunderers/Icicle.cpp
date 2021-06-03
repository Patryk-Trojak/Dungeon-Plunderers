#include "pch.h"
#include "Icicle.h"


Icicle::Icicle(const sf::Vector2f& Position,
    const sf::Vector2f& Velocity, const int Damage,
    const sf::Texture& Texture, const float rotation)
    : PlayerProjectile(Position, Velocity, Damage, Texture,
        Animation(1, 1, sf::Vector2i(74 * 2, 31 * 2), 10, 0.05f, true, 5), Hitbox(Position, sf::Vector2f(99.0425f, 2.03961f), sf::Vector2f(0.f, 0.f), sf::Vector2f(10.0213f, 1.04309)), true)
{
    projectile.setOrigin(10, 12);
   
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(99.0425f, 2.03961f), sf::Vector2f(0.f, 0.f), sf::Vector2f(10.0213f, 1.04309)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(97.1669f, 5.03633f), sf::Vector2f(0.f, 0.f), sf::Vector2f(10.1546f, 2.0242)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(92.9893f, 8.03351f), sf::Vector2f(0.f, 0.f), sf::Vector2f(9.99498f, 3.00537)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(89.0116f, 11.0923f), sf::Vector2f(0.f, 0.f), sf::Vector2f(10.0074f, 4.02899)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(80.0427f, 15.0049f), sf::Vector2f(0.f, 0.f), sf::Vector2f(10.0207f, 4.98582)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(75.0089f, 17.0194f), sf::Vector2f(0.f, 0.f), sf::Vector2f(10.0199f, 6.01566)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(67.9915f, 19.0377f), sf::Vector2f(0.f, 0.f), sf::Vector2f(10.014f, 7.00972)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(59.0393f, 21.9803f), sf::Vector2f(0.f, 0.f), sf::Vector2f(10.1413f, 9.00349)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(33.9975f, 27.0459f), sf::Vector2f(0.f, 0.f), sf::Vector2f(10.0149f, 11.0072)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(11.0004f, 24.972f), sf::Vector2f(0.f, 0.f), sf::Vector2f(-23.9894f, 9.99135)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(12.0366f, 31.0668f), sf::Vector2f(0.f, 0.f), sf::Vector2f(10.033f, 12.023)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(6.00879f, 1.96211f), sf::Vector2f(0.f, 0.f), sf::Vector2f(10.0066f, -19.0414)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(3.01486f, 0.989395f), sf::Vector2f(0.f, 0.f), sf::Vector2f(10.0014f, -21.0091)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(3.96492f, 1.99821f), sf::Vector2f(0.f, 0.f), sf::Vector2f(-2.00844f, -15.9576)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(4.97748f, 1.99312f), sf::Vector2f(0.f, 0.f), sf::Vector2f(-70.0226f, -7.00922)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(2.00629f, 2.01186f), sf::Vector2f(0.f, 0.f), sf::Vector2f(-82.9943f, -3.00392)));

    projectile.setRotation(rotation);
    hitboxComponent.setRotationOfAllHitboxes(rotation);
    hitboxComponent.setScaleOfAllHitboxes(projectile.getScale());
    accelerationOfFalling = 0.f;
    hasAnimation = false;
}

Icicle::~Icicle()
{
}

void Icicle::addEffects(std::vector<std::unique_ptr< Effect> >& effects, const Resources& resources)
{
    effects.emplace_back(std::make_unique<SnowDust>(projectile.getPosition(), resources[TextureID::SnowDust]));
}

void Icicle::onCollisionWithEnemy(Enemy& enemy)
{
    enemy.tryTakeDamage(damage);
    enemy.tryChangeState(EnemyState::frost, 2);
}
