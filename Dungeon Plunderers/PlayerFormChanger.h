#pragma once
#include<SFML/Graphics.hpp>
#include"HitboxComponent.h"
#include"Animation.h"
#include"Resources.h"

enum class WaysToChangePlayerForm{
	StormtrooperToHelicopter,
	WizardToWizardOnCloud
};

class PlayerFormChanger :
	public sf::Drawable
{
public:
	PlayerFormChanger(const sf::Vector2f& Position, const sf::Vector2f& initPosition, const Resources& resources, const WaysToChangePlayerForm& howChangeForm);
	virtual ~PlayerFormChanger();
	void backToInitPosition(const float deltaTime);
	HitboxComponent hitboxes;
	WaysToChangePlayerForm getHowChangeForm() const;
	void animate(const float deltaTime);
	sf::FloatRect getGlobalBoundsOfSprite() const;
	sf::Vector2f getPosition() const;
private:
	sf::Sprite changer;
	sf::Vector2f initPosition;
	WaysToChangePlayerForm howChangeForm;
	Animation animation;
	sf::Vector2f velocity;
	bool hasAnimation;
	bool isOnInitPostion;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

