#pragma once
#include<SFML/Graphics.hpp>
#include<map>
#include "Animation.h"

class AnimationComponent
{
public:
	AnimationComponent(sf::Sprite& sprite);
	AnimationComponent(sf::Sprite& sprite, const std::string& NameOfAnimation, const Animation& animation);
	virtual ~AnimationComponent();
	void addAnimation(const std::string& NameOfAnimation, const Animation& animation);
	void playAnimation(const std::string& NameOfAnimation, const float deltaTime);
	bool wasFrameChanged() const;
	int numberOfCurrentFrame() const;
private:
	std::map<std::string, Animation> animations;
	sf::Sprite& sprites;
	bool WasFrameChanged;
	int NumberOfCurrentFrame;
};

