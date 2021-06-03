#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "HitboxComponent.h"

class Portal :
	public sf::Drawable
{
public: 
	Portal(const sf::Vector2f& position, const sf::Texture& textureOfPortal);
	virtual ~Portal();
	HitboxComponent hitboxes;
	void setPosition(const sf::Vector2f& position);
private:
	sf::Sprite portal;
	Animation animation;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

