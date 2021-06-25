#include "pch.h"
#include "Zombie.h"

Zombie::Zombie(const sf::Vector2f& Position, const sf::Vector2f ChangeDirectionDistance, const Resources& resources, const sf::Vector2f& initialScale)
	:Enemy(Position, resources[TextureID::ZombieGirl], resources,
        Animation(1, 1, sf::Vector2i(122, 184), 4, 0.14f), sf::Vector2f(-30.f, -30.f),
		300, 10,
		false)
{
    movingEnemyComponent = std::make_unique<MovingEnemyComponent>(enemy, currentState, initialScale, sf::Vector2f(200.f, 0.f), ChangeDirectionDistance);
    name = EnemyType::zombieGirl;
	enemy.setOrigin(46.f, 0.f);
    this->initialScale = initialScale;
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(54.9454f, 60.6077f), sf::Vector2f(-43.3648f, 41.8187f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(73.61f, 12.5829f), sf::Vector2f(-41.8968f, 29.865f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(68.1575f, 14.0509f), sf::Vector2f(-38.1219f, 16.0238f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(64.1729f, 8.80804f), sf::Vector2f(-36.2345f, 7.21573f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(52.4288f, 6.16232f), sf::Vector2f(-28.0556f, 1.13397f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(46.7665f, 16.9869f), sf::Vector2f(11.3708f, 69.2914f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(18.2452f, 8.80804f), sf::Vector2f(58.3471f, 73.6954f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(4.40402f, 4.19427f), sf::Vector2f(57.5082f, 69.5012f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(15.7287f, 8.80804f), sf::Vector2f(12.2097f, 42.2382f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(7.75948f, 4.19429f), sf::Vector2f(12.f, 51.6754f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(28.1018f, 43.2013f), sf::Vector2f(-16.3116f, 102.238f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(6.50117f, 21.8104f), sf::Vector2f(11.7454f, 123.342f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(6.29146f, 15.3092f), sf::Vector2f(18.0368f, 130.473f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(4.82346f, 10.0663f), sf::Vector2f(24.1186f, 135.925f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(6.92062f, 19.0841f), sf::Vector2f(-23.0674f, 126.278f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(4.82344f, 11.9538f), sf::Vector2f(-27.8908f, 133.828f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(4.82346f, 6.08176f), sf::Vector2f(-32.5045f, 138.232f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(21.7507f, 3.96713f), sf::Vector2f(-38.0538f, 102.241f))); //17


    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(6.29146f, 15.3092f), sf::Vector2f(18.0368f, 130.473f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(4.82346f, 10.0663f), sf::Vector2f(24.1186f, 135.925f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(6.92062f, 19.0841f), sf::Vector2f(-23.0674f, 126.278f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(4.82344f, 11.9538f), sf::Vector2f(-27.8908f, 133.828f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(4.82346f, 6.08176f), sf::Vector2f(-32.5045f, 138.232f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(21.7507f, 3.96713f), sf::Vector2f(-38.0538f, 102.241f))); 
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(4.82344f, 11.9538f), sf::Vector2f(-27.8908f, 133.828f)));//24

   base.addHitbox(Hitbox(Position, sf::Vector2f(30.1931f, 1.62155f), sf::Vector2f(-11.7739f, 183.949f)));

   fire.setOrigin(sf::Vector2f(13.5f, -8.f));
   fire.setScale(sf::Vector2f(3.f, 3.f));
}

Zombie::~Zombie()
{
}

void Zombie::matchHitboxesToAnimation()
{
    switch (animation.getNumberOfCurrentFrame())
    {
    case 1:
        hitboxComponent.setHitbox(18, sf::Vector2f(13.9123f, 6.18323f), sf::Vector2f(4.07053f, 177.831f));
        hitboxComponent.setHitbox(19, sf::Vector2f(2.18991f, 3.99335f), sf::Vector2f(17.854f, 180.021f));
        hitboxComponent.setHitbox(20, sf::Vector2f(14.014f, 38.0663f), sf::Vector2f(1.97292f, 145.957f));
        hitboxComponent.setHitbox(21, sf::Vector2f(14.0114f, 26.0938f), sf::Vector2f(-16.046f, 145.952f));
        hitboxComponent.setHitbox(22, sf::Vector2f(9.97153f, 11.9915f), sf::Vector2f(-13.9655f, 172.042f));
        hitboxComponent.setHitbox(23, sf::Vector2f(6.00227f, 6.03821f), sf::Vector2f(-4.00227f, 177.994f));

        hitboxComponent.hitboxes[24].setHitbox(sf::Vector2f(0.f, 0.f), sf::Vector2f(-10000.f, -1000.f));


        break;

    case 2:
        hitboxComponent.setHitbox(18, sf::Vector2f(13.9123f, 6.18323f), sf::Vector2f(4.07053f, 177.831f));
        hitboxComponent.setHitbox(19, sf::Vector2f(2.18991f, 3.99335f), sf::Vector2f(17.854f, 180.021f));
        hitboxComponent.setHitbox(20, sf::Vector2f(14.014f, 38.0663f), sf::Vector2f(1.97292f, 145.957f));

        hitboxComponent.setHitbox(21, sf::Vector2f(14.0053f, 20.1698f), sf::Vector2f(-16.0289f, 145.943f));
        hitboxComponent.setHitbox(22, sf::Vector2f(21.9543f, 12.0045f), sf::Vector2f(-37.9832f, 154.f));
        hitboxComponent.setHitbox(23, sf::Vector2f(6.00229f, 4.0556f), sf::Vector2f(-38.0358f, 165.951f));
        hitboxComponent.setHitbox(24, sf::Vector2f(5.94821f, 2.05484f), sf::Vector2f(-21.9756f, 151.945f));
        break;
    case 3:
        hitboxComponent.setHitbox(18, sf::Vector2f(13.9123f, 6.18323f), sf::Vector2f(4.07053f, 177.831f));
        hitboxComponent.setHitbox(19, sf::Vector2f(2.18991f, 3.99335f), sf::Vector2f(17.854f, 180.021f));
        hitboxComponent.setHitbox(20, sf::Vector2f(14.014f, 38.0663f), sf::Vector2f(1.97292f, 145.957f));
        hitboxComponent.setHitbox(21, sf::Vector2f(14.0114f, 26.0938f), sf::Vector2f(-16.046f, 145.952f));
        hitboxComponent.setHitbox(22, sf::Vector2f(9.97153f, 11.9915f), sf::Vector2f(-13.9655f, 172.042f));
        hitboxComponent.setHitbox(23, sf::Vector2f(6.00227f, 6.03821f), sf::Vector2f(-4.00227f, 177.994f));

        hitboxComponent.hitboxes[24].setHitbox(sf::Vector2f(0.f, 0.f), sf::Vector2f(-10000.f, -1000.f));
        break;

    case 4:
        hitboxComponent.setHitbox(18, sf::Vector2f(14.0114f, 26.0938f), sf::Vector2f(-16.046f, 145.952f));
        hitboxComponent.setHitbox(19, sf::Vector2f(9.97153f, 11.9915f), sf::Vector2f(-13.9655f, 172.042f));
        hitboxComponent.setHitbox(20, sf::Vector2f(6.00227f, 6.03821f), sf::Vector2f(-4.00227f, 177.994f));

        hitboxComponent.setHitbox(21, sf::Vector2f(13.9931f, 20.0427f), sf::Vector2f(2.00195f, 145.954f));
        hitboxComponent.setHitbox(22, sf::Vector2f(4.05066f, 9.99506f), sf::Vector2f(-2.10126f, 154.003f));
        hitboxComponent.setHitbox(23, sf::Vector2f(1.99915f, 2.00201f), sf::Vector2f(0.000427246f, 163.994f));
        break;
    }



}