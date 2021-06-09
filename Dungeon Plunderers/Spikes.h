#pragma once
#include "Enemy.h"


enum class SpikeType {
	basic,
	hiding,
	showingAfterDamage
};

class Spikes : 
	public Enemy
{
public:
	Spikes(const sf::Vector2f& Position, const Resources& resources, SpikeType spikeType);
	virtual ~Spikes();
	virtual void playAnimation(const float deltaTime);
	virtual void attack(std::vector<std::unique_ptr<EnemyProjectile>>& Projectiles, const sf::Vector2f& PlayerPosition, const float deltaTime);
	virtual void updateScale(const float PositionXOfPlayer) override;
	virtual void matchHitboxesToAnimation();
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	float timeSinceHidden;
	float timeToStartHiding;
	bool hide;
	bool startAnimation;
	int numberOfStartFrame;
};

