#include "pch.h"
#include "Projectile.h"

Projectile::Projectile(const sf::Vector2f& Position,
	const sf::Vector2f& Velocity, const int Damage,
	const sf::Texture& Texture,
	const Animation& Animation, const Hitbox& Hitbox, 
	bool isReiquireSATCollision)

	:projectile(Texture),
	Movable(Velocity),
	animation(Animation),
	distanceMoved(0),
	damage(Damage),
	hitboxComponent(Hitbox),
	Split(false),
	distanceOfErase(5000.f),
	isReiquireSATCollision(isReiquireSATCollision)
{
	projectile.setPosition(Position);
	currentVelocity = Velocity;
	initialVelocity = currentVelocity;
	if (Velocity.x >= 0)
	{
		projectile.setScale(1, 1);
	}
	else
	{
		projectile.setScale(-1, 1);
	}

	accelerationOfFalling = 200.f;
	globalBoundsOfSprite = projectile.getGlobalBounds();
}

Projectile::~Projectile()
{
}

void Projectile::animate(const float deltaTime)
{
	if(hasAnimation)
		animation.play(projectile, deltaTime);
}

void Projectile::update(const float deltaTime)
{
	distanceMoved += abs(currentVelocity.x * deltaTime) + abs(currentVelocity.y * deltaTime);
	currentVelocity.y += (accelerationOfFalling * deltaTime);
	move(deltaTime);

	globalBoundsOfSprite = projectile.getGlobalBounds();

}

float Projectile::getDistanceMoved() const
{
	return distanceMoved;
}

sf::Vector2f Projectile::getPosition() const
{
	return projectile.getPosition();
}

int Projectile::getDamage() const
{
	return damage;
}

const sf::FloatRect& Projectile::getGlobalBoundsOfSprite() const
{
	return globalBoundsOfSprite;
}

void Projectile::setPositionOfHitboxes()
{
	if (projectile.getScale().x > 0)
	{
		for (auto& i : hitboxComponent.hitboxes)
			i.setPosition(projectile.getPosition() + i.getOffset());
	}
	else
	{
		if (hitboxComponent.hitboxes.size() > 0)
		{
			if (hitboxComponent[0].getScale().x > 0)
			{
				for (auto& i : hitboxComponent.hitboxes)
					i.setPosition(sf::Vector2f(projectile.getPosition().x - i.getGlobalBounds().width - i.getOffset().x, projectile.getPosition().y + i.getOffset().y));
			}
			else
			{
				for (auto& i : hitboxComponent.hitboxes)
					i.setPosition(projectile.getPosition() + i.getOffset());
			}
		}
	;
	}
}

void Projectile::matchHitboxesToAnimation()
{
}

const sf::Vector2f& Projectile::getVelocity() const
{
	return currentVelocity;
}

void Projectile::addVelocity(const sf::Vector2f& velocity)
{
	currentVelocity += velocity;
}

void Projectile::setVelocity(const sf::Vector2f& newVelocity)
{
	currentVelocity = newVelocity;
}

bool Projectile::split() const
{
	return Split;
}

void Projectile::setSplit(bool split)
{
	Split = split;
}

float Projectile::getDistanceOfErase() const
{
	return distanceOfErase;
}

void Projectile::move(const float deltaTime)
{
	projectile.move(currentVelocity * deltaTime);
}

void Projectile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(projectile, states);
}
