#pragma once
#include "Animation.h"

class Effect
	: public Animation, 
	public sf::Drawable
{
public:
	Effect(const sf::Vector2f& Position, const sf::Texture& Texture, const int StartFrameX, const int StartFrameY, const sf::Vector2i& SizeOfSingleFrame, const int NumberOfFrames, float TimeOfFrameChange, const float ScaleX);
	virtual ~Effect();
	void update(const float deltaTime);
	bool getIsOver() const;
protected:
	sf::Sprite effect;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

