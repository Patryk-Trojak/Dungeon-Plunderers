#include "pch.h"
#include "Fly.h"

Fly::Fly(const sf::Vector2f& Position, const sf::Vector2f ChangeDirectionDistance, const Resources& resources)
	:Enemy(Position, resources[TextureID::Fly], resources,
        Animation(1, 1, sf::Vector2i(77.f, 57.f), 5, 0.005f), sf::Vector2f(-38.f, -20.f),
		300, 10,	
        false)
{
    movingEnemyComponent = std::make_unique<MovingEnemyComponent>(enemy, currentState, initialScale, sf::Vector2f(200.f, 200.f), ChangeDirectionDistance);
    name = EnemyType::fly;
	enemy.setOrigin(38.f, 0.f);
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(56.325f, 13.2431f), sf::Vector2f(-21.0206f, 40.8756f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(31.4313f, 4.02321f), sf::Vector2f(4.04062f, 36.8524f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(6.00166f, 10.966f), sf::Vector2f(-26.9997f, 41.9997f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(4.02127f, 8.01978f), sf::Vector2f(-31.0197f, 43.9818f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(2.6981f, 11.1137f), sf::Vector2f(35.2704f, 38.8219f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(26.9819f, 6.03516f), sf::Vector2f(-7.96631f, 30.8683f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(29.3883f, 5.27396f), sf::Vector2f(-12.3182f, 25.5943f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(30.5659f, 4.34967f), sf::Vector2f(-17.5406f, 21.2447f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(31.0267f, 4.02342f), sf::Vector2f(-21.0221f, 17.2212f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(29.1323f, 4.4584f), sf::Vector2f(-25.0668f, 12.8172f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(28.8763f, 4.02344f), sf::Vector2f(-27.8828f, 8.79376f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(22.0668f, 3.47972f), sf::Vector2f(-29.0603f, 5.42279f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(12.595f, 2.66417f), sf::Vector2f(-29.1115f, 2.81299f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(10.0242f, 2.82832f), sf::Vector2f(-28.0397f, 0.00466919f))); //13

    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(22.0668f, 3.47972f), sf::Vector2f(-29.0603f, 5.42279f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(12.595f, 2.66417f), sf::Vector2f(-29.1115f, 2.81299f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(10.0242f, 2.82832f), sf::Vector2f(-28.0397f, 0.00466919f))); 
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(22.0668f, 3.47972f), sf::Vector2f(-29.0603f, 5.42279f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(12.595f, 2.66417f), sf::Vector2f(-29.1115f, 2.81299f)));
    hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(10.0242f, 2.82832f), sf::Vector2f(-28.0397f, 0.00466919f))); 


    base.addHitbox(Hitbox(Position, sf::Vector2f(56, 4), sf::Vector2f(7 - 31.206f, 98), sf::Color(0, 255, 0, 100)));

	//animation.play();
}

Fly::~Fly()
{
}

void Fly::matchHitboxesToAnimation()
{
    switch(animation.getNumberOfCurrentFrame())
    {
    case 1:
    case 5:
        hitboxComponent.setHitbox(14, sf::Vector2f(12.2814f, 12.1034f), sf::Vector2f(-32.0424f, 7.93347f));
        hitboxComponent.setHitbox(15, sf::Vector2f(12.0331f, 4.08139f), sf::Vector2f(-29.0831f, 20.f));
        hitboxComponent.setHitbox(16, sf::Vector2f(13.4442f, 3.97583f), sf::Vector2f(-26.0479f, 24.0242f));
        hitboxComponent.setHitbox(17, sf::Vector2f(13.6164f, 3.06104f), sf::Vector2f(-22.9869f, 27.9648f));
        hitboxComponent.setHitbox(18, sf::Vector2f(16.0441f, 4.99619f), sf::Vector2f(-19.9924f, 31.0258f));
        hitboxComponent.setHitbox(19, sf::Vector2f(16.2552f, 4.01103f), sf::Vector2f(-12.0237f, 35.9483f));
        break;
    case 2:
    case 4:
        hitboxComponent.setHitbox(14, sf::Vector2f(27.4333f, 8.06862f), sf::Vector2f(-37.9759f, 21.9288f));
        hitboxComponent.setHitbox(15, sf::Vector2f(25.0732f, 2.00497f), sf::Vector2f(-33.0164f, 29.9765f));
        hitboxComponent.setHitbox(16, sf::Vector2f(20.7768f, 2.99644f), sf::Vector2f(-28.0149f, 32.0035f));
        hitboxComponent.setHitbox(17, sf::Vector2f(21.2395f, 3.01848f), sf::Vector2f(-20.0249f, 35.f));
        hitboxComponent.setHitbox(18, sf::Vector2f(13.5721f, 2.99644f), sf::Vector2f(-8.99435f, 38.f));
        for (int i = 19; i <= 19; i++)
            hitboxComponent.hitboxes[i].setHitbox(sf::Vector2f(0.f, 0.f), sf::Vector2f(-10000.f, -1000.f));
        break;
    case 3:
        hitboxComponent.setHitbox(14, sf::Vector2f(21.4664f, 9.0336f), sf::Vector2f(-16.9847f, 31.9756f));
        hitboxComponent.setHitbox(15, sf::Vector2f(7.07788f, 8.00917f), sf::Vector2f(-24.0161f, 33.f));
        hitboxComponent.setHitbox(17, sf::Vector2f(3.01352f, 6.02707f), sf::Vector2f(-27.0027f, 34.9973f));
        hitboxComponent.setHitbox(18, sf::Vector2f(4.04349f, 4.04347f), sf::Vector2f(-31.0271f, 35.9891f));
        for (int i = 19; i <= 19; i++)
            hitboxComponent.hitboxes[i].setHitbox(sf::Vector2f(0.f, 0.f), sf::Vector2f(-10000.f, -1000.f));
        break;
    }

}