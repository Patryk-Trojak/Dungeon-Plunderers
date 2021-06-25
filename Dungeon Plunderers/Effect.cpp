#include "pch.h"
#include "Effect.h"

Effect::Effect(const sf::Vector2f& Position, const sf::Texture& Texture, const int StartFrameX, const int StartFrameY, const sf::Vector2i& SizeOfSingleFrame, const int NumberOfFrames, float TimeOfFrameChange, const float ScaleX)
	:Animation(StartFrameX, StartFrameY, SizeOfSingleFrame, NumberOfFrames, TimeOfFrameChange)
{
	effect.setTexture(Texture);
	//temp
	effect.setPosition(Position + sf::Vector2f(25.f * ScaleX, 0.f));
	//
	currentFrame = startFrame;
	effect.setTextureRect(currentFrame);
	effect.setScale(ScaleX, 1);
}

Effect::~Effect()
{
}

void Effect::update(const float deltaTime)
{
	play(effect, deltaTime);
}

bool Effect::getIsOver() const
{
	return isOver;
}

void Effect::setScale(const sf::Vector2f& scale)
{
	effect.setScale(scale);
}

void Effect::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(effect, states);
}
