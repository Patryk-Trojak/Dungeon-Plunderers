#include "pch.h"
#include "Portal.h"

Portal::Portal(const sf::Vector2f& position, const sf::Texture& textureOfPortal)
	:portal(textureOfPortal),
	animation(1, 1, sf::Vector2i(108.f, 216.f), 5, 0.5f),
	hitboxes(Hitbox(position, sf::Vector2f(108.f, 216.f)))
{
	portal.setPosition(position);
	animation.setFrame(portal, 1);
}

Portal::~Portal()
{
}

void Portal::setPosition(const sf::Vector2f& position)
{
	portal.setPosition(position);
	for (auto& i : hitboxes.hitboxes)
	{
		i.setPosition(portal.getPosition() + i.getOffset());
	}
}

void Portal::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(portal);
	//target.draw(hitboxes[0]);
}

