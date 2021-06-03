#include "pch.h"
#include "Block.h"

Block::Block(const sf::Vector2f& Position, const sf::Vector2f& Size, const BlocksTypes name)
	:name(name),
	size(Size),
	velocity(0, 0),
	changeDirectionDistance(0.f, 0.f),
	distanceMoved(0.f, 0.f)
{
	position = Position;
	hitboxComponent.addHitbox(Hitbox(Position - (Size / 2.f), Size));

}

Block::Block(const sf::Vector2f& Position, const sf::Vector2f& Size, const BlocksTypes name, const sf::Vector2f& Velocity, const sf::Vector2f& MaxDistanceOfMoving)
	:name(name),
	size(Size),
	velocity(Velocity),
	changeDirectionDistance(MaxDistanceOfMoving),
	distanceMoved(0.f, 0.f)
{
	position = Position;
	hitboxComponent.addHitbox(Hitbox(Position - (Size / 2.f), Size));
	if (MaxDistanceOfMoving.x == 0)
		velocity.x = 0;
	else if(MaxDistanceOfMoving.x > 0)
		velocity.x = 200;
	else
		velocity.x = -200;

	if (MaxDistanceOfMoving.y == 0)
		velocity.y = 0;
	else if (MaxDistanceOfMoving.y > 0)
		velocity.y = 200;
	else
		velocity.y = -200;
}

Block::~Block()
{
}

void Block::move(float deltaTime)
{
	if (changeDirectionDistance != sf::Vector2f(0.f, 0.f))
	{
		distanceMoved += velocity * deltaTime;
		move(velocity * deltaTime);
		if (abs(distanceMoved.x) >= abs(changeDirectionDistance.x))
		{
			if (distanceMoved.x >= 0.f)
				move(sf::Vector2f(abs(changeDirectionDistance.x) - distanceMoved.x, 0.f));
			else
				move(sf::Vector2f(-abs(changeDirectionDistance.x) - distanceMoved.x, 0.f));

			distanceMoved.x = 0.f;
			velocity.x = -velocity.x;
		}

		if (abs(distanceMoved.y) >= abs(changeDirectionDistance.y))
		{
			if (distanceMoved.y >= 0.f)
				move(sf::Vector2f(abs(changeDirectionDistance.y) - distanceMoved.y, 0.f));
			else
				move(sf::Vector2f(-abs(changeDirectionDistance.y) - distanceMoved.y, 0.f));

			distanceMoved.y = 0.f;
			velocity.y = -velocity.y;
		}
	}
}

void Block::setColor(const sf::Color& Color)
{
	color = Color;
}

sf::Color Block::getColor() const
{
	return color;
}

sf::Vector2f Block::getPosition() const
{
	return position;
}

sf::Vector2f Block::getSize() const
{
	return sf::Vector2f(hitboxComponent.getHitboxes()[0].getGlobalBounds().width, hitboxComponent.getHitboxes()[0].getGlobalBounds().height);
}

sf::Vector2f Block::getVelocity() const
{
	return velocity;
}

BlocksTypes Block::getType() const
{
	return name;
}


void Block::move(const sf::Vector2f& offset)
{
	hitboxComponent.moveHitbox(0, offset);
	position += offset;
}



float Block::right() const
{
	return hitboxComponent.getHitboxes()[0].getGlobalBounds().left + hitboxComponent.getHitboxes()[0].getGlobalBounds().width;
}

float Block::left() const
{
	return hitboxComponent.getHitboxes()[0].getGlobalBounds().left;
}

float Block::bottom() const
{
	return hitboxComponent.getHitboxes()[0].getGlobalBounds().top + hitboxComponent.getHitboxes()[0].getGlobalBounds().height;
}


void Block::drawHb(sf::RenderTarget& target)
{
	target.draw(hitboxComponent[0]);
}

float Block::top() const
{
	return hitboxComponent.getHitboxes()[0].getGlobalBounds().top;
}
