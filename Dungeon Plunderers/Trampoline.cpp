#include "pch.h"
#include "Trampoline.h"

Trampoline::Trampoline(const sf::Vector2f& position, const Resources& resources)
	:animation(1, 1, sf::Vector2i(51, 60), 13, 0.001f),
	animate(false),
	isStandingOnBlock(false),
	trampoline(resources[TextureID::Trampoline])
{
	trampoline.setPosition(position);
	hitboxComponent.addHitbox(Hitbox(position, sf::Vector2f(45.f, 6.f), sf::Vector2f(3.f, 54.f)));

	base.addHitbox(Hitbox(position, sf::Vector2f(3.f, 3.f), sf::Vector2f(0.f, 60.f)));
	base.addHitbox(Hitbox(position, sf::Vector2f(45.f, 3.f), sf::Vector2f(3.f, 60.f)));

	base.addHitbox(Hitbox(position, sf::Vector2f(3.f, 3.f), sf::Vector2f(48.f, 60.f)));

	animation.setFrame(trampoline, 1);
}

void Trampoline::onCollisionWithPlayer(Player& player)
{
	player.setCurrentValocity(sf::Vector2f(0.f, -3000.f));
	startPlayingAnimation();
}

void Trampoline::tryPlayAnimation(float deltaTime)
{
	if (animate)
	{
		if (animation.getNumberOfCurrentFrame() == 7)
		{
			animation.setTimeOfFrameChange(0.1f);
		}
		if (animation.getNumberOfCurrentFrame() == 13)
		{
			animate = false;
			animation.setFrame(trampoline, 1);
		}
		animation.play(trampoline, deltaTime);
	}
}

void Trampoline::startPlayingAnimation()
{
	animate = true;
	animation.setTimeOfFrameChange(0.007f);
	animation.setFrame(trampoline, 2);
}

void Trampoline::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(trampoline);
}

void Trampoline::setBlockWhichItsStandingOn(std::vector<Block>::const_iterator& block)
{
	blockItsStandingOn = block;
	isStandingOnBlock = true;
}

void Trampoline::moveWithBlock(float deltaTime)
{
	if (isStandingOnBlock)
	{
		trampoline.move(blockItsStandingOn->getVelocity() * deltaTime);
		for (auto& i : hitboxComponent.hitboxes)
		{
			i.setPosition(trampoline.getPosition() + i.getOffset());
		}
	}
}

sf::FloatRect Trampoline::getGlobalBoundsOfSprite() const
{
	return trampoline.getGlobalBounds();
}

int Trampoline::getNumberOfFrameAnimation() const
{
	return animation.getNumberOfCurrentFrame();
}
