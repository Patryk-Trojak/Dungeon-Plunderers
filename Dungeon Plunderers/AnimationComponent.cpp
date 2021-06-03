#include "pch.h"
#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite& sprite)
	:sprites(sprite),
	WasFrameChanged(false),
	NumberOfCurrentFrame(0)
{
}

AnimationComponent::AnimationComponent(sf::Sprite& sprite, const std::string& NameOfAnimation, const Animation& animation)
	: sprites(sprite)
{
	animations.emplace(std::make_pair(NameOfAnimation, animation));
}

AnimationComponent::~AnimationComponent()
{
}

void AnimationComponent::addAnimation(const std::string& NameOfAnimation, const Animation& animation)
{
	animations.emplace(std::make_pair(NameOfAnimation, animation) );
}

void AnimationComponent::playAnimation(const std::string& NameOfAnimation, const float deltaTime)
{
	Animation& animation = animations.at(NameOfAnimation);
	animation.play(sprites, deltaTime);
	WasFrameChanged = animation.wasFrameChanged();
	NumberOfCurrentFrame = animation.getNumberOfCurrentFrame();
}

bool AnimationComponent::wasFrameChanged() const
{
	return WasFrameChanged;
}

int AnimationComponent::numberOfCurrentFrame() const
{
	return NumberOfCurrentFrame;
}
