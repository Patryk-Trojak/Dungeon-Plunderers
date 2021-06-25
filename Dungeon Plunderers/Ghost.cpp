#include "pch.h"
#include "Ghost.h"


Ghost::Ghost(const sf::Vector2f& Position, const sf::Vector2f ChangeDirectionDistance, const Resources& resources)
    :Enemy(Position, resources[TextureID::Ghost], resources,
        Animation(1, 1, sf::Vector2i(80, 130), 6, 0.05f), sf::Vector2f(-38.f, -20.f),
        300, 10,
        false)
{
    movingEnemyComponent = std::make_unique<MovingEnemyComponent>(enemy, currentState, initialScale, sf::Vector2f(200.f, 200.f), ChangeDirectionDistance);
    name = EnemyType::ghost;
    enemy.setOrigin(35.f, 0.f);

    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(80.f, 90.f), sf::Vector2f(-35.f, 25.f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(70.f, 105.f), sf::Vector2f(-30.f, 10.f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(50.f, 115.f), sf::Vector2f(-20.f, 0.f)));
    for (auto i = 0; i < 3; i++)
    {
        hitboxComponent.addHitbox(Hitbox());
    }
    base.addHitbox(Hitbox(Position, sf::Vector2f(56, 44), sf::Vector2f(10, 130), sf::Color(0, 255, 0, 100)));

    fire.setOrigin(sf::Vector2f(13.5f, 2.f));
    fire.setScale(sf::Vector2f(3.f, 2.5f));
}

Ghost::~Ghost()
{
}

void Ghost::matchHitboxesToAnimation()
{
    switch (animation.getNumberOfCurrentFrame())
    {
    case 1:
        hitboxComponent.setHitbox(3, sf::Vector2f(15.f, 10.f), sf::Vector2f(-35.f, 120.f));
        hitboxComponent.setHitbox(4, sf::Vector2f(20.f, 10.f), sf::Vector2f(-5.f, 120.f));
        hitboxComponent.setHitbox(5, sf::Vector2f(15.f, 10.f), sf::Vector2f(30.f, 120.f));
        break;
    case 2:
        hitboxComponent.setHitbox(3, sf::Vector2f(20.f, 15.f), sf::Vector2f(-35.f, 115.f));
        hitboxComponent.setHitbox(4, sf::Vector2f(20.f, 10.f), sf::Vector2f(0.f, 120.f));
        hitboxComponent.setHitbox(5, sf::Vector2f(5.f, 5.f), sf::Vector2f(35.f, 120.f));
        break;
    case 3:
        hitboxComponent.setHitbox(3, sf::Vector2f(20.f, 15.f), sf::Vector2f(-30.f, 115.f));
        hitboxComponent.setHitbox(4, sf::Vector2f(20.f, 15.f), sf::Vector2f(5.f, 115.f));
        hitboxComponent.setHitbox(5, sf::Vector2f(0.f, 0.f), sf::Vector2f(-10000.f, -1000.f));
        break;
    case 4:
        hitboxComponent.setHitbox(3, sf::Vector2f(20.f, 15.f), sf::Vector2f(10.f, 115.f));
        hitboxComponent.setHitbox(4, sf::Vector2f(20.f, 10.f), sf::Vector2f(-25.f, 120.f));
        hitboxComponent.setHitbox(5, sf::Vector2f(0.f, 0.f), sf::Vector2f(-10000.f, -1000.f));
        break;
    case 5:
        hitboxComponent.setHitbox(3, sf::Vector2f(20.f, 10.f), sf::Vector2f(-20.f, 120.f));
        hitboxComponent.setHitbox(4, sf::Vector2f(20.f, 10.f), sf::Vector2f(15.f, 120.f));
        hitboxComponent.setHitbox(5, sf::Vector2f(0.f, 0.f), sf::Vector2f(-10000.f, -1000.f));
        break;
    case 6:
        hitboxComponent.setHitbox(3, sf::Vector2f(20.f, 10.f), sf::Vector2f(-15.f, 120.f));
        hitboxComponent.setHitbox(4, sf::Vector2f(20.f, 10.f), sf::Vector2f(20.f, 120.f));
        hitboxComponent.setHitbox(5, sf::Vector2f(0.f, 0.f), sf::Vector2f(-10000.f, -1000.f));
        break;
    }
}