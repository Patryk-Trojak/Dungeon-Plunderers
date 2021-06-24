#include "pch.h"
#include "Bat.h"


Bat::Bat(const sf::Vector2f& Position, const sf::Vector2f ChangeDirectionDistance, const Resources& resources)
    :Enemy(Position, resources[TextureID::Bat], resources,
        Animation(1, 1, sf::Vector2i(72, 128), 10, 0.05f), sf::Vector2f(-52.f, -20.f),
        300, 10,
        false)
{
    movingEnemyComponent = std::make_unique<MovingEnemyComponent>(enemy, currentState, initialScale, sf::Vector2f(200.f, 200.f), ChangeDirectionDistance);
    name = EnemyType::bat;
    enemy.setOrigin(36.f, 0.f);

    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(48.f, 32.f), sf::Vector2f(-20.f, 48.f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(68.f, 12.f), sf::Vector2f(-32.f, 60.f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(60.f, 24.f), sf::Vector2f(-32.f, 48.f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(32.f, 36.f), sf::Vector2f(-8.f, 44.f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(8.f, 40.f), sf::Vector2f(12.f, 40.f)));

    for (auto i = 0; i < 2; i++)
    {
        hitboxComponent.addHitbox(Hitbox());
    }
    base.addHitbox(Hitbox(Position, sf::Vector2f(22, 30), sf::Vector2f(-12, 130), sf::Color(0, 255, 0, 100)));
}

Bat::~Bat()
{
}

void Bat::matchHitboxesToAnimation()
{
    switch (animation.getNumberOfCurrentFrame())
    {
    case 1:
        hitboxComponent.setHitbox(5, sf::Vector2f(40.f, 64.f), sf::Vector2f(-16.f, 64.f));
        hitboxComponent.setHitbox(6, sf::Vector2f(52.f, 8.f), sf::Vector2f(-28.f, 112.f));
        break;
    case 2:
    case 10:
        hitboxComponent.setHitbox(5, sf::Vector2f(36.f, 43.f), sf::Vector2f(-12.f, 65.f));
        hitboxComponent.setHitbox(6, sf::Vector2f(48.f, 8.f), sf::Vector2f(-24.f, 96.f));
        break;
    case 3:
    case 9:
        hitboxComponent.setHitbox(5, sf::Vector2f(40.f, 24.f), sf::Vector2f(-16.f, 64.f));
        hitboxComponent.setHitbox(6, sf::Vector2f(48.f, 12.f), sf::Vector2f(-24.f, 72.f));
        break;
    case 4:
    case 8:
        hitboxComponent.setHitbox(5, sf::Vector2f(40.f, 40.f), sf::Vector2f(-16.f, 40.f));
        hitboxComponent.setHitbox(6, sf::Vector2f(68.f, 4.f), sf::Vector2f(-36.f, 56.f));
        break;
    case 5:
    case 7:
        hitboxComponent.setHitbox(5, sf::Vector2f(40.f, 60.f), sf::Vector2f(-20.f, 20.f));
        hitboxComponent.setHitbox(6, sf::Vector2f(48.f, 8.f), sf::Vector2f(-28.f, 24.f));
        break;
    case 6:
        hitboxComponent.setHitbox(5, sf::Vector2f(40.f, 80.f), sf::Vector2f(-16.f, 0.f));
        hitboxComponent.setHitbox(6, sf::Vector2f(52.f, 8.f), sf::Vector2f(-28.f, 8.f));
        break;
    }
}