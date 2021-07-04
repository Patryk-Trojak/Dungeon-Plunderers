#pragma once
#include <SFML/Graphics.hpp>
#include "Resources.h"
#include "Block.h"
#include "Player.h"
#include "Animation.h"

class Trampoline
	: public sf::Drawable
{
public:
	Trampoline(const sf::Vector2f& position, const Resources& resources);
	void onCollisionWithPlayer(Player& player);
	void tryPlayAnimation(float deltaTime);
	HitboxComponent hitboxComponent;
	HitboxComponent base;
	void setBlockWhichItsStandingOn(std::vector<Block>::const_iterator& block);
	void moveWithBlock(float deltaTime);
	sf::FloatRect getGlobalBoundsOfSprite() const;
	int getNumberOfFrameAnimation() const;
private:
	sf::Sprite trampoline;
	Animation animation;
	bool animate;
	void startPlayingAnimation();
	std::vector<Block>::const_iterator blockItsStandingOn;
	bool isStandingOnBlock;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

