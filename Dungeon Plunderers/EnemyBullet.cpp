#include "pch.h"
#include "EnemyBullet.h"

EnemyBullet::EnemyBullet(const sf::Vector2f& Position,
	const sf::Vector2f& Velocity, const int Damage,
	const sf::Texture& Texture)
	: EnemyProjectile(Position, Velocity, Damage, Texture,
		Animation(1, 1, sf::Vector2i(224.f, 218.f), 1, 0.5f), Hitbox(Position - sf::Vector2f(-8.f, -8.f), sf::Vector2f(18.f, 18.f), sf::Vector2f(-8.f, -8.f)), false)
{
	projectile.setOrigin(8.5, 8.5);
	whichEffectAdd = RandomEngine::randInt(1, 5);
	accelerationOfFalling = 0;
	hasAnimation = false;
}

EnemyBullet::~EnemyBullet()
{
}

void EnemyBullet::addEffects(std::vector<std::unique_ptr< Effect> >& effects, const Resources& resources)
{
	int scaleX = 1;
	if (currentVelocity.x >= 0)
		scaleX = 1;
	else
		scaleX = -1;
	switch (whichEffectAdd)
	{
	case 1:
		effects.emplace_back(std::make_unique<Blood1>(projectile.getPosition(), resources[TextureID::Blood1], scaleX));
		break;
	case 2:
		effects.emplace_back(std::make_unique<Blood2>(projectile.getPosition(), resources[TextureID::Blood2], scaleX));
		break;
	case 3:
		effects.emplace_back(std::make_unique<Blood3>(projectile.getPosition(), resources[TextureID::Blood3], scaleX));
		break;
	case 4:
		effects.emplace_back(std::make_unique<Blood4>(projectile.getPosition(), resources[TextureID::Blood4], scaleX));
		break;
	case 5:
		effects.emplace_back(std::make_unique<Blood5>(projectile.getPosition(), resources[TextureID::Blood5], scaleX));
		break;
	}
}
