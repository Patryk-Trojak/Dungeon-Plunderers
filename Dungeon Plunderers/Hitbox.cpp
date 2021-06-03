#include "pch.h"
#include "Hitbox.h"

Hitbox::Hitbox(const sf::Vector2f& Position, const sf::Vector2f& Size, const sf::Vector2f& Offset, const sf::Color& color)
	:hitbox(Size),
	offset(Offset)
{
	hitbox.setPosition(Position + Offset);
	if (getShowHitboxes())
	{
		hitbox.setFillColor(color);
	}
	else
	{
		hitbox.setFillColor(sf::Color(255, 0, 0, 0));
	}
	globalBounds = hitbox.getGlobalBounds();
}

Hitbox::Hitbox(const sf::Vector2f& Position, const sf::Vector2f& Size, const sf::Vector2f& Offset, const sf::Vector2f& Origin)
	:Hitbox(Position, Size, Offset, sf::Color::Red)
{
	hitbox.setOrigin(Origin);
}

Hitbox::Hitbox()
	:hitbox(sf::Vector2f(0, 0)),
	offset(0.f, 0.f)
{
	globalBounds = hitbox.getGlobalBounds();
}

Hitbox::~Hitbox()
{
}

void Hitbox::setHitbox(const sf::Vector2f& Size, const sf::Vector2f& Offset)
{
	hitbox.setSize(Size);
	offset = Offset;
	globalBounds = hitbox.getGlobalBounds();
}

void Hitbox::setPosition(const sf::Vector2f& Position)
{
	hitbox.setPosition(Position);
	globalBounds = hitbox.getGlobalBounds();
}

void Hitbox::setOffset(const sf::Vector2f& Offset)
{
	offset = Offset;
}

void Hitbox::setSize(const sf::Vector2f& Size)
{
	hitbox.setSize(Size);
	globalBounds = hitbox.getGlobalBounds();
}

void Hitbox::setRotation(const float rotation)
{
	hitbox.setRotation(rotation);
	globalBounds = hitbox.getGlobalBounds();
}

void Hitbox::move(const sf::Vector2f& Offset)
{
	hitbox.move(Offset);
	globalBounds = hitbox.getGlobalBounds();
}

float Hitbox::getLeft() const
{
	return globalBounds.left;
}

float Hitbox::getRight() const
{
	return globalBounds.left + globalBounds.width;
}

float Hitbox::getTop() const
{
	return globalBounds.top;
}

float Hitbox::getBottom() const
{
	return globalBounds.top + globalBounds.height;
}

sf::Vector2f Hitbox::getCenter() const
{
	return sf::Vector2f(getLeft() + (hitbox.getGlobalBounds().width / 2), getTop() + (hitbox.getGlobalBounds().height / 2));
}

sf::Vector2f Hitbox::getScale() const
{
	return hitbox.getScale();
}

void Hitbox::setScale(const sf::Vector2f& scale)
{
	hitbox.setScale(scale);
	globalBounds = hitbox.getGlobalBounds();
}

const sf::FloatRect& Hitbox::getGlobalBounds() const
{
	return globalBounds;
}


const sf::Transform& Hitbox::getTransform() const
{
	return hitbox.getTransform();
}

const sf::Vector2f& Hitbox::getOffset() const
{
	return offset;
}

sf::Vector2f Hitbox::getPoint(std::size_t index) const
{
	return hitbox.getPoint(index);
}

bool Hitbox::contains(const sf::Vector2f& point) const
{
	if ((point.x >= globalBounds.left) && (point.x < globalBounds.left + globalBounds.width) && (point.y >= globalBounds.top) && (point.y < globalBounds.top + globalBounds.height))
		return true;
	else
		return false;
}

bool Hitbox::intersects(const Hitbox& hitbox2) const
{
	if (globalBounds.left + globalBounds.width > hitbox2.getGlobalBounds().left)
	{
		if (globalBounds.left < hitbox2.getGlobalBounds().left + hitbox2.getGlobalBounds().width)
		{
			if (globalBounds.top + globalBounds.height > hitbox2.getGlobalBounds().top)
			{
				if (globalBounds.top < hitbox2.getGlobalBounds().top + hitbox2.getGlobalBounds().height)
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool Hitbox::intersects(const sf::FloatRect& floatRect) const
{
	if (globalBounds.left + globalBounds.width > floatRect.left)
	{
		if (globalBounds.left < floatRect.left + floatRect.width)
		{
			if (globalBounds.top + globalBounds.height > floatRect.top)
			{
				if (globalBounds.top < floatRect.top + floatRect.height)
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool Hitbox::intersectsSAT(const Hitbox& hitbox2) const
{
	std::array<sf::Vector2f, 4> points1;
	std::array<sf::Vector2f, 4> points2;
	const sf::Transform& transform = hitbox.getTransform();
	for (int i = 0; i < 4; i++)
	{
		points1[i] = transform.transformPoint(hitbox.getPoint(i));
	}
	const sf::Transform& transform2 = hitbox2.getTransform();
	for (int i = 0; i < 4; i++)
	{
		points2[i] = transform2.transformPoint(hitbox2.getPoint(i));
	}


	for (int shape = 0; shape < 2; shape++)
	{
		if(shape == 1)
			std::swap(points1, points2);

		for (int a = 0; a < 4; a++)
		{
			int b = (a + 1) % 4;
			sf::Vector2f axisProj(-(points1[b].y - points1[a].y), points1[b].x - points1[a].x);

			float min1 = INFINITY; float max1 = -INFINITY;
			float min2 = INFINITY; float max2 = -INFINITY;

			for (int p = 0; p < 4; p++)
			{
				float q = points1[p].x * axisProj.x + points1[p].y * axisProj.y;
				min1 = std::min(min1, q);
				max1 = std::max(max1, q);

				q = points2[p].x * axisProj.x + points2[p].y * axisProj.y;
				min2 = std::min(min2, q);
				max2 = std::max(max2, q);
			}

			if(!(max2 >= min1 and max1 >= min2))
				return false;
		}
	}

	return true;
}


void Hitbox::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(hitbox, state);
}
