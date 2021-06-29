#include "pch.h"
#include "HitboxComponent.h"

HitboxComponent::HitboxComponent()
{
}

HitboxComponent::HitboxComponent(const Hitbox& hitbox)
{
	hitboxes.emplace_back(hitbox);
}

HitboxComponent::~HitboxComponent()
{
}

void HitboxComponent::addHitbox(const Hitbox&& hitbox)
{
	hitboxes.emplace_back(hitbox);
}

void HitboxComponent::setHitbox(const int numberOfHitbox, const sf::Vector2f& Size, const sf::Vector2f& Offset)
{
	hitboxes[numberOfHitbox].setHitbox(Size, Offset);
}

void HitboxComponent::setPositionOfHitbox(const int numberOfHitbox, const sf::Vector2f& Position)
{
	hitboxes[numberOfHitbox].setPosition(Position);
}

void HitboxComponent::setSizeOfHitbox(const int numberOfHitbox, const sf::Vector2f& Size)
{
	hitboxes[numberOfHitbox].setSize(Size);
}

void HitboxComponent::setOffsetOfHitbox(const int numberOfHitbox, const sf::Vector2f& Offset)
{
	hitboxes[numberOfHitbox].setOffset(Offset);
}

void HitboxComponent::moveHitbox(const int numberOfHitbox, const sf::Vector2f& Offset)
{
	hitboxes[numberOfHitbox].move(Offset);
}

void HitboxComponent::moveAllHitboxes(const sf::Vector2f& Offset)
{
	for (auto& i : hitboxes)
		i.move(Offset);
}

void HitboxComponent::setRotationOfAllHitboxes(const float rotation)
{
	for (auto& i : hitboxes)
		i.setRotation(rotation);
}

void HitboxComponent::setScaleOfAllHitboxes(const sf::Vector2f& scale)
{
	for (auto& i : hitboxes)
		i.setScale(scale);
}

bool HitboxComponent::intersects(const std::vector<Hitbox>& hitboxes) const
{
	for (auto const& i : this->hitboxes)
	{
		for (auto const& j : hitboxes)
		{
			if (i.intersects(j))
			{
				return true;
			}
		}
	}
	return false;
}

bool HitboxComponent::intersects(const sf::FloatRect& floatRect) const
{
	for (auto const& i : this->hitboxes)
	{
		if (i.intersects(floatRect))
		{
			return true;
		}
	}
	return false;
}

bool HitboxComponent::intersects(const std::vector<sf::FloatRect>& floatRects) const
{
	for (auto const& i : this->hitboxes)
	{
		for (auto const& j : floatRects)
		{
			if (i.intersects(j))
			{
				return true;
			}
		}
	}
	return false;
}

bool HitboxComponent::intersects(const HitboxComponent& hitboxComponent) const
{
	for (auto const& i : this->hitboxes)
	{
		for (auto const& j : hitboxComponent.getHitboxes())
		{
			if (i.intersects(j))
			{
				return true;
			}
		}
	}
	return false;
}

bool HitboxComponent::intersects(const Hitbox& hitbox) const
{
	for (auto const& i : this->hitboxes)
	{
		if (i.intersects(hitbox))
		{
			return true;
		}
	}
	return false;
}

bool HitboxComponent::allHitboxesIntersectWith(const HitboxComponent& hitboxComponent) const
{
	for (auto const& i : this->hitboxes)
	{
		for (auto const& j : hitboxComponent.getHitboxes())
		{
			if (!i.intersects(j))
			{
				return false;
			}
		}
	}
	return true;
}


bool HitboxComponent::intersectsSAT(const HitboxComponent& hitboxComponent) const
{
	for (auto const& i : this->hitboxes)
	{
		for (auto const& j : hitboxComponent.getHitboxes())
		{
			if (i.intersectsSAT(j))
			{
				return true;
			}
		}
	}
	return false;
}

bool HitboxComponent::contains(const sf::Vector2f& Point) const
{
	for (auto const & i : this->hitboxes)
	{
		if (i.contains(Point))
		{
			return true;
		}
	}
	return false;
}

size_t HitboxComponent::size() const
{
	return hitboxes.size();
}

void HitboxComponent::clearHitboxes()
{
	hitboxes.clear();
}

const std::vector<Hitbox>& HitboxComponent::getHitboxes() const
{
	return hitboxes;
}

const Hitbox& HitboxComponent::operator[](int i) const 
{
	return hitboxes[i];
}

inline bool HitboxComponent::intersects(const Hitbox& h1, const sf::FloatRect& f2) const
{
	sf::FloatRect f1 = h1.getGlobalBounds();
	if (f1.left + f1.width > f2.left)
	{
		if (f1.left < f2.left + f2.width)
		{
			if (f1.top + f1.height > f2.top)
			{
				if (f1.top < f2.top + f2.height)
				{
					return true;
				}
			}
		}
	}
	return false;
}
