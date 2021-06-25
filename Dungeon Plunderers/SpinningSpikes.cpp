#include "pch.h"
#include "SpinningSpikes.h"

SpinningSpikes::SpinningSpikes(const sf::Vector2f& Position, const sf::Vector2f ChangeDirectionDistance, const Resources& resources, const sf::Vector2f& initialScale)
    :Enemy(Position, resources[TextureID::SpinningSpikes], resources,
        Animation(1, 1, sf::Vector2i(150, 150), 4, 0.03f), sf::Vector2f(-30.f, -30.f),
        300, 10,
        false)
{
    if(ChangeDirectionDistance.x != 0.f or ChangeDirectionDistance.y != 0.f)
        movingEnemyComponent = std::make_unique<MovingEnemyComponent>(enemy, currentState, initialScale, sf::Vector2f(200.f, 0.f), ChangeDirectionDistance);
    name = EnemyType::spinningSpikes;
    enemy.setOrigin(75.0f, 75.0f);
    this->initialScale = initialScale;
    
    for (auto i = 0; i < 13; i++)
    {
        hitboxComponent.addHitbox(Hitbox());
    }

    base.addHitbox(Hitbox(Position, sf::Vector2f(30.1931f, 1.62155f), sf::Vector2f(-11.7739f, 183.949f)));
    isMortal = false;

    isResistantToGivenState[EnemyState::fire] = true;
    isResistantToGivenState[EnemyState::frost] = true;
}

SpinningSpikes::~SpinningSpikes()
{
}

void SpinningSpikes::matchHitboxesToAnimation()
{
    switch (animation.getNumberOfCurrentFrame())
    {
    case 1:
        hitboxComponent.setHitbox(0, sf::Vector2f(18.f, 126.f), sf::Vector2f(-9.f, -63.f));
        hitboxComponent.setHitbox(1, sf::Vector2f(126.f, 18.f), sf::Vector2f(-63.f, -9.f));
        hitboxComponent.setHitbox(2, sf::Vector2f(150.f, 6.f), sf::Vector2f(-75.f, -3.f));
        hitboxComponent.setHitbox(3, sf::Vector2f(6.f, 150.f), sf::Vector2f(-3.f, -75.f));
        hitboxComponent.setHitbox(4, sf::Vector2f(78.f, 30.f), sf::Vector2f(-39.f, -15.f));
        hitboxComponent.setHitbox(5, sf::Vector2f(30.f, 78.f), sf::Vector2f(-15.f, -39.f));
        hitboxComponent.setHitbox(6, sf::Vector2f(42.f, 54.f), sf::Vector2f(-21.f, -27.f));
        hitboxComponent.setHitbox(7, sf::Vector2f(54.f, 42.f), sf::Vector2f(-27.f, -21.f));
        
        for (auto i = 8; i <= 12; i++)
            hitboxComponent.hitboxes[i].setHitbox(sf::Vector2f(0.f, 0.f), sf::Vector2f(-10000.f, -1000.f));
        break;

    case 2:
        hitboxComponent.setHitbox(0, sf::Vector2f(54.f, 60.f), sf::Vector2f(-27.f, -33.f));
        hitboxComponent.setHitbox(1, sf::Vector2f(18.f, 24.f), sf::Vector2f(27.f, -27.f));
        hitboxComponent.setHitbox(2, sf::Vector2f(24.f, 6.f), sf::Vector2f(45.f, -33.f));
        hitboxComponent.setHitbox(3, sf::Vector2f(18.f, 12.f), sf::Vector2f(45.f, -27.f));
        hitboxComponent.setHitbox(4, sf::Vector2f(24.f, 12.f), sf::Vector2f(3.f, 27.f));
        hitboxComponent.setHitbox(5, sf::Vector2f(12.f, 24.f), sf::Vector2f(15.f, 39.f));
        hitboxComponent.setHitbox(6, sf::Vector2f(6.f, 24.f), sf::Vector2f(27.f, 45.f));
        hitboxComponent.setHitbox(7, sf::Vector2f(12.f, 48.f), sf::Vector2f(-39.f, -21.f));
        hitboxComponent.setHitbox(8, sf::Vector2f(18.f, 18.f), sf::Vector2f(-57.f, 15.f));
        hitboxComponent.setHitbox(9, sf::Vector2f(12.f, 6.f), sf::Vector2f(-69.f, 27.f));
        hitboxComponent.setHitbox(10, sf::Vector2f(12.f, 30.f), sf::Vector2f(-27.f, -63.f));
        hitboxComponent.setHitbox(11, sf::Vector2f(6.f, 24.f), sf::Vector2f(-33.f, -69.f));
        hitboxComponent.setHitbox(12, sf::Vector2f(12.f, 12.f), sf::Vector2f(-15.f, -45.f));

        break;
    case 3:
        hitboxComponent.setHitbox(0, sf::Vector2f(66.f, 66.f), sf::Vector2f(-33.f, -33.f));
        hitboxComponent.setHitbox(1, sf::Vector2f(18.f, 18.f), sf::Vector2f(-51.f, 27.f));
        hitboxComponent.setHitbox(2, sf::Vector2f(6.f, 12.f), sf::Vector2f(-57.f, 39.f));
        hitboxComponent.setHitbox(3, sf::Vector2f(12.f, 18.f), sf::Vector2f(27.f, 33.f));
        hitboxComponent.setHitbox(4, sf::Vector2f(6.f, 18.f), sf::Vector2f(39.f, 39.f));
        hitboxComponent.setHitbox(5, sf::Vector2f(12.f, 6.f), sf::Vector2f(39.f, 51.f));
        hitboxComponent.setHitbox(6, sf::Vector2f(18.f, 12.f), sf::Vector2f(33.f, -39.f));
        hitboxComponent.setHitbox(7, sf::Vector2f(18.f, 6.f), sf::Vector2f(39.f, -45.f));
        hitboxComponent.setHitbox(8, sf::Vector2f(6.f, 18.f), sf::Vector2f(-45.f, -57.f));
        hitboxComponent.setHitbox(9, sf::Vector2f(12.f, 18.f), sf::Vector2f(-39.f, -51.f));

        for (auto i = 10; i <= 12; i++)
            hitboxComponent.hitboxes[i].setHitbox(sf::Vector2f(0.f, 0.f), sf::Vector2f(-10000.f, -1000.f));
        break;

    case 4:
        hitboxComponent.setHitbox(0, sf::Vector2f(12.f, 96.f), sf::Vector2f(-27.f, -27.f));
        hitboxComponent.setHitbox(1, sf::Vector2f(96.f, 13.f), sf::Vector2f(-69.f, -27.f));
        hitboxComponent.setHitbox(2, sf::Vector2f(42.f, 54.f), sf::Vector2f(-15.f, -27.f));
        hitboxComponent.setHitbox(3, sf::Vector2f(18.f, 24.f), sf::Vector2f(3.f, -51.f));
        hitboxComponent.setHitbox(4, sf::Vector2f(18.f, 24.f), sf::Vector2f(27.f, 3.f));
        hitboxComponent.setHitbox(5, sf::Vector2f(24.f, 12.f), sf::Vector2f(45.f, 15.f));
        hitboxComponent.setHitbox(6, sf::Vector2f(12.f, 30.f), sf::Vector2f(-39.f, -15.f));
        hitboxComponent.setHitbox(7, sf::Vector2f(18.f, 12.f), sf::Vector2f(-57.f, -15.f));
        hitboxComponent.setHitbox(8, sf::Vector2f(30.f, 12.f), sf::Vector2f(-15.f, 27.f));
        hitboxComponent.setHitbox(9, sf::Vector2f(12.f, 24.f), sf::Vector2f(15.f, -69.f));
        hitboxComponent.setHitbox(10, sf::Vector2f(6.f, 24.f), sf::Vector2f(27.f, -21.f));
        hitboxComponent.setHitbox(11, sf::Vector2f(18.f, 6.f), sf::Vector2f(-15.f, -33.f));
        hitboxComponent.setHitbox(12, sf::Vector2f(6.f, 12.f), sf::Vector2f(-15.f, 39.f));
        break;
    }
}

void SpinningSpikes::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(enemy, states);
}
