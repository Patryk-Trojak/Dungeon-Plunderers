#pragma once
#include "Enemy.h"

class SpinningSpikes :
	public Enemy
{
public:
	SpinningSpikes(const sf::Vector2f& Position, const sf::Vector2f ChangeDirectionDistance, const Resources& resources, const sf::Vector2f& initialScale = sf::Vector2f(1.f, 1.f));
	virtual ~SpinningSpikes();
	virtual void matchHitboxesToAnimation();
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};